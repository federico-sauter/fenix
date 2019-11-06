![FENIX logo](/doc/fenix_logo.png)

FENIX is a small operating system kernel for the IA-32 architecture,
written by Federico Sauter.

The current state (version 0.2) may be really interesting for
people that want to learn about implementing an operating system,
but don't want to spend as much time learning about the CPU and
getting the system initialization right. One could jump right
into writing C code to implement new functionality, since the
system is already running albeit in a minimal form.

An interactive shell is provided. The kernel supports multitasking
and implements a simple scheduler.

# Building and running FENIX

## Prerequisites

The build system has been tested to work on Ubuntu 18.04 (bionic).
To build and test FENIX on a VM, install the following packages:
```
sudo apt-get install grub-pc-bin nasm qemu-kvm qemu virt-manager virt-viewer libvirt-bin
```

## Build

To build and run FENIX, go to the `src` directory and execute:
```
make run
```

This will start a VM with FENIX. To stop the VM, kill the VM process manually,
or execute the program `util/stopvms.sh`, which kills all qemu VMs currently
running.

## Other make targets

* `make all`: Build the kernel and create a bootable disk image
* `make kernel`: Build the kernel binary
* `make run`: Build the kernel, create a bootable disk image and start a VM with it
* `make clean`: Delete intermediate files
* `make distclean`: Delete intermediate files and directories

# Implementation notes

One of the interesting aspects of implementing an operating system kernel
is how it seems like all aspects of it depend on one another, making a
gradual implementation difficult to achieve.

For the development of the FENIX kernel, the primary goal has been set at
implementing a multi-tasking pre-emptive kernel with interactive capabilities.
This means that all work that did not strictly contribute to reach this goal
was deferred, in particular memory management, file systems, etc.

## Project organization

The `bin` directory contains the kernel binary.

The `img` directory contains the bootable operating system image.

The `util` directory contains utility programs aimed at making testing
the operating system faster.

### Kernel sources

The `include` directory contains the header files that would define the
API to the kernel from a user-space program.

The `sv` directory contains the (mostly) platform-independent code for
the supervisor, which is the kernel main program.

The `sys` directory contains some system headers that should be relevant
for the kernel only.

The `util` directory contains the standard library and utility functions
required to make the supervisor work.

### Architecture-specific portions

The FENIX kernel was designed for the IA-32 and is not envisioned to be
portable. However, the architecture-specific code has been abstracted
and can be found in the `src/arch/ia32/` directory. The rest of the code
should be architecture-independent. There is one exception to this separation,
which is the task state, which is part of the `task_t` type and has been
simply defined as the contents of the IA-32 registers.

The entry point to the kernel, as loaded by grub2, is the `sv_startup` function,
which is an assembly language function.

There is as little assembly code as possible, so as to make the kernel
easier to understand.

### Naming conventions

One of the primary goals of the FENIX kernel design was to aid
discoverability in its programming interfaces. The following naming convention
applies to function names:

`<component>_<object>_<verb>_<thing>`

**Component**: identifies the component of the function. Currently the following
component acronyms are used:
* `sv` for the supervisor
* `cc` for the console controller
* `ia32` for an Intel 32-bit architecture specific implementation
**Object**: identifies the object within the context of the component in which the function operates.
**Verb**: denotes the action that the function performs.
**Thing**: optionally specifies the target object of the function operation.

## The supervisor program

The supervisor task is responsible for starting up the system and setting up
the bare hardware configuration to run. This includes remapping the programmable
IRQs as well as the taskor faults to be handled by the kernel. The supervisor
spawns new taskes and handles all task-related tasks, such as task termination.

In the current implementation, the supervisor term can be used exchangebly with
kernel to refer to the operating system core.

## The shell task

The user-facing task that controls the interaction with the user is the shell
task. Currently, it also has a portion of code that interacts directly with
the keyboard interrupt. This is to be fixed in a subsequent release.

### Available shell commands

There is only a very limited set of commands currently avilable over the
FENIX interactive shell:

* `ver`: Shows the operating system version.
* `clear`: Clears the screen.
* `ps`: Prints the list of currently running tasks.
* `help`: Shows information about the usage of the shell.
* `exit-test [wait]`: Program to demonstrate how tasks can exit and optionally the
wait syscall.
* `demo`: Multitasking demonstration program. Note that you must restart the
computer to exit this program.

## Task switching

In order to save and retrieve the task state, an intermediate storage for the
CPU registers in the `_eax`, `_ebx`, etc. global variables is used. When a
system call is performed, the IRQ handler (written in assembly) stores the
CPU state in those variable first, and then the actual supervisor handler,
e.g. the scheduler, saves that state into the actual task data structure.

When the system call (or IRQ handler) completes, the state is copied into
the buffer `_eax`, `_ebx`, etc., global variables, where the interrupt handler
obtains the state that is then set in the CPU registers.

This is obviously not efficient but it was the only way in which everything
worked. This is an aspect that should change in a future update, to ensure
that the CPU state is copied only once instead of twice.

### Task context

The context of a task is defined as the CPU register state that the next
instruction for that task shall have when executing.

The task context does not comprise any segment registers (`cs, ds, es, fs, gs, ss`)
because the current FENIX implementation does not make use of Intel's segmented
architecture. Those registers are set only once during operating system startup;
and should not be changed after it.

## Task scheduler

The scheduler has a task table with a maximum of 32 tasks. Given that there
is no heap implementation available, this is a hard limit. Of those task slots,
only 30 are available for "user" tasks, since one is alloted to the system
idle task and the other one is used by the shell.

Currently, the scheduler has a list (called the "runnable" list) with the
tasks that can be selected for getting CPU time. Within that list, a round
robin scheme is followed to schedule tasks, with the exception of the
keyboard interrupt, which is placed at the head of the list to be handled
with the greatest priority.

Note that the list implementation is akward due to the fact that there is
no heap or memory management implemented and thus all data structures must
have a fixed size from the beginning on. This also has clear consequences
in the way the algorithms are implemented, often iterating over the whole
tasks table, given the way in which tasks are removed. When memory management
is available, these data structures will be reimplemented in a more
straightforward manner.

## IA-32 system initialization and data structures

The data structures that are used for initializing the IA-32 CPU are
defined in `arch/ia32/ds.h`. The names given to the fields of the structures
should be self-documenting; else refer to the Intel programming manual for
more information.

There are three main data structures:

* `gdt_elem_t`, which defines an entry in the Global Descriptor Table (GDT)

![GDT Entry](/doc/gdt.png)

* `idt_elem_t`, which represents an entry in the Interrupt Descriptor Table (IDT)

![IDT Entry](/doc/idt.png)

* `load_ptr_t`, which is a pointer to either the GDT or the IDT

![load_ptr_t](/doc/load_ptr_t.png)

The FENIX supervisor is loaded by GRUB2 (or another multiboot-compliant bootloader.)
This means that the supervisor binary must adhere to the multiboot header specification.

During the startup sequence, the first initialization subroutines occurr within the
`ia32init.asm` source file. Its first section defines the required fields for a simple
multiboot-compliant binary configuration.

The supervisor loading subroutine is very straightforward: it just sets up the
supervisor stack into `ESP` (which is reserved at the end of the file, see the
`.BSS` section of the file) and then jumps into the supervisor main routine.

CPU faults and traps are mapped to be handled by interrupt handling subroutines
found in `ia32traps.asm`. All of those subroutines are very similar: their only
function is to save the context, call a handler function and then return using
an `IRET` instruction. In other words, they are just wrappers with the proper
initialization and cleanup for the handling functions found in the `svirqs.c` file.

The `SAVE_CTX` and `RETR_CTX` macros define (in `ia32macros.asm`) what context will
be saved for tasks when an interrupt request occurs. This is worth mentioning, as it
has important implications in the supervisor general design and its data structures.
FENIX does not save the segment registers because it uses a flat memory model
so that their values should never change (until the system implements multiple
privilege levels.)

## Limitations

A BIOS is required to boot FENIX. It does not yet support UEFI.

There is no heap implementation and no memory management; all memory operations
are done on the stack.

There is no real distinction between user-space and kernel space, so all
tasks are actually kernel tasks.

The console does not implement any function keys; in particular there is no
support for backspace yet.

# Next steps

The following is a list of possible next steps for the project:

* Add system calls for console I/O; don't use direct video writing from
"user-space" processes.
* Add support for multiple (virtual) consoles.
* Add decimal integer formatting to `cc_printf`.
* Add a `getch` function that blocks, which requires support for a return value
from system calls.
* Implement semaphores/mutexes.
* Implement a heap and basic memory management.
* Implement a memory file system.
* Create a privilege distinction between user mode and kernel mode.
* Port a text editor, e.g. a version of `vi`.
* Port a language interpreter, such as:
  * [micropython](https://micropython.org/)
  * [v7](https://github.com/cesanta/v7)
  * [duktape](https://duktape.org/)
  * [myBasic](https://github.com/paladin-t/my_basic)
  * [ubasic](http://dunkels.com/adam/ubasic/)

# Copyright notice

FENIX kernel Copyright&#9400; 2019 by Federico Sauter

Includes `tinysh` Copyright&#9400; 2001 by Michel Gutierrez

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
