####################################################################################################
##  ia32 - Intel Architecture 32 (x86) specific functionality
####################################################################################################

OBJ_DIR=../../../obj/arch/ia32
C_SRCS=ia32idt.c ia32sysinit.c ia32video.c ia32svha.c
ASM_SRCS=ia32init.asm ia32irqs.asm ia32macros.asm ia32syscall.asm ia32tasks.asm ia32traps.asm
OBJS=$(C_SRCS:%.c=$(OBJ_DIR)/%.o) $(ASM_SRCS:%.asm=$(OBJ_DIR)/%.o)
INCLUDES=-I../../ -I../../util -I../../include

####################################################################################################
##	tools configuration
####################################################################################################
AS=nasm
ASFLAGS=-f elf

####################################################################################################
##	make rules -- do not modify form here
####################################################################################################
.SUFFIXES: .asm .c .o

all: dir $(OBJS)

clean:
	@rm -f $(OBJS) $(TARGET)

dir:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: %.c
	${CC} -o $@ -c ${CCFLAGS} ${INCLUDES} $<
