/*
    \ \____/ /  \ \
   _/ / __ \ \__/ /     svtraps.c - CPU trap handlers
   __/ /  \ \____/
   _ \ \__/ / __ \.     FENIX Kernel
    \ \____/ /  \ \
   _/ / __ \ \__/ /     Copyright(C) 2019 by Federico Sauter<f.sauter@gmail.com>
   __/ /  \ \____/
   _ \ \__/ / __ \.

    This file is part of the FENIX Kernel.

    The FENIX Kernel is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The FENIX Kernel is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the FENIX Kernel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <svha.h>
#include <sys/ccio.h>

extern volatile unsigned _eax, _ecx, _edx, _ebx;
extern volatile unsigned _ebp, _esi, _edi, _esp;
extern volatile unsigned _eip, _eflags;

/******************************************************************************/
void sv_dump_reg_state()
/******************************************************************************/
{
  cc_printf("================== SAVED REGISTER STATE ======================\n"
            "EAX=%x  ECX=%x  EDX=%x  EBX=%x\n"
            "EBP=%x  ESI=%x  EDI=%x  ESP=%x\n"
            "EIP=%x  EFLAGS=%x\n"
            "==============================================================",
            _eax,
            _ecx,
            _edx,
            _ebx,
            _ebp,
            _esi,
            _edi,
            _esp,
            _eip,
            _eflags);
}

/******************************************************************************/
void sv_panic(const char *msg)
/******************************************************************************/
{
  cc_cpos_set(0, 18);
  cc_printf("==============================================================\n");
  cc_printf(msg);
  sv_dump_reg_state();
  sv_get_ha()->halt();
}

/**************************************************************************************************/
void sv_handle_divide_error()
/**************************************************************************************************/
{
  sv_panic("FAULT: divide error\n");
}

/**************************************************************************************************/
void sv_handle_nmi()
/**************************************************************************************************/
{
  sv_panic("FAULT: nmi\n");
}

/**************************************************************************************************/
void sv_handle_debug()
/**************************************************************************************************/
{
  sv_panic("FAULT: debug\n");
}

/**************************************************************************************************/
void sv_handle_breakpoint()
/**************************************************************************************************/
{
  sv_panic("\nTRAP: breakpoint\n");
}

/**************************************************************************************************/
void sv_handle_overflow()
/**************************************************************************************************/
{
  sv_panic("\nTRAP: overflow\n");
}

/**************************************************************************************************/
void sv_handle_bounds()
/**************************************************************************************************/
{
  sv_panic("FAULT: bounds check\n");
}

/**************************************************************************************************/
void sv_handle_invalid_op()
/**************************************************************************************************/
{
  sv_panic("FAULT: invalid opcode\n");
}

/**************************************************************************************************/
void sv_handle_device_not_avaiable()
/**************************************************************************************************/
{
  sv_panic("FAULT: device not available\n");
}

/**************************************************************************************************/
void sv_handle_double_fault()
/**************************************************************************************************/
{
  sv_panic("\nABORT: double fault\n");
}

/**************************************************************************************************/
void sv_handle_coproc_seg_overrun()
/**************************************************************************************************/
{
  sv_panic("\nABORT: coprocessor segment overrun\n");
}

/**************************************************************************************************/
void sv_handle_inv_tss()
/**************************************************************************************************/
{
  sv_panic("FAULT: invalid TSS\n");
}

/**************************************************************************************************/
void sv_handle_seg_not_present()
/**************************************************************************************************/
{
  sv_panic("FAULT: segment not present\n");
}

/**************************************************************************************************/
void sv_handle_ss()
/**************************************************************************************************/
{
  sv_panic("FAULT: stack segment\n");
}

/**************************************************************************************************/
void sv_handle_gp()
/**************************************************************************************************/
{
  sv_panic("FAULT: general protection fault\n");
}

/**************************************************************************************************/
void sv_handle_pf()
/**************************************************************************************************/
{
  sv_panic("FAULT: page fault\n");
}

/**************************************************************************************************/
void sv_handle_fpe()
/**************************************************************************************************/
{
  sv_panic("FAULT: floating point error\n");
}

/**************************************************************************************************/
void sv_handle_alignment_check()
/**************************************************************************************************/
{
  sv_panic("FAULT: alignment check\n");
}

/**************************************************************************************************/
void sv_idt_handle_irq_glbl()
/**************************************************************************************************/
{
  cc_printf("\n*** Interrupt occurred ***\n");
}
