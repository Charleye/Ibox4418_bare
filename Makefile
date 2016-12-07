pro :=src/led/

src/led/build-in.o:$(patsubst %.c,%.o,$(wildcard src/led/*.c))
	$(call if_changed,ar)

# Convenient variables
comma	:= ,
quote	:= "
squote	:= '
empty	:=
space	:= $(empty) $(empty)

###
# Escape single quote for use in echo statements
escsq = $(subst $(squote),'\$(squote)',$1)

MAKEFLAGS += -rR --include-dir=$(CURDIR) --no-print-directory

ifeq ("$(origin V)", "command line")
	VERBOSE = $(V)
endif
ifndef VERBOSE
	VERBOSE = 0
endif

ifeq ($(VERBOSE), 1)
	quiet =
	Q =
else
	quiet = quiet_
	Q = @
endif

PHONY := _all
_all:

$(CURDIR)/Makefile Makefile: ;

ASFLAGS		:= -O2 -nostdlib -ffunction-sections -fdata-sections -fno-common -Iinclude
LDFLAGS		+= -O2 -static -Tlink.lds -L/usr/lib/gcc/arm-none-eabi/5.4.1/
CFLAGS		:= -O2 -nostdlib -nostdinc
ARFLAGS		:= -rcs
OBJCOPYFLAGS:= -O binary
MCFLAGS		:= -mtune=cortex-a9 -march=armv7-a -mfpu=neon -ftree-vectorize -ffast-math -mfloat-abi=softfp
INCLUDES	:= -Iarm/include/asm -Iinclude -Iinclude/libc/

# cc-cross-prefix
# Usage:
# CROSS_COMPILE := $(call cc-cross-prefix,arm-linux-eabi- arm-none-eabi-)
#
# Return first prefix where a prefix$(CC) is found in PATH.
# If no $(CC) found in PATH with listed prefixes return nothing.
cc-cross-prefix = \
	$(word 1, $(foreach c,$(1),			\
	$(shell set -e;						\
	if (which $(strip $(c))gcc) > /dev/null 2>&1 ; then	\
		echo $(c);						\
	fi)))

CROSS_COMPILE = $(call cc-cross-prefix,arm-none-eabi- arm-linux-eabi-)

echo-cmd = $(if $($(quiet)cmd_$(1)),\
		echo '$(call escsq,$($(quiet)cmd_$(1)))';)

# printing commands
cmd = @$(echo-cmd) $(cmd_$(1))

quiet_cmd_ld = LD	src/$@/$@.efi
cmd_ld = $(LD) -o src/$@/$@.efi $(LDFLAGS)  $(init-y) --start-group $(libs-y) src/led/build-in.o -lgcc --end-group  -cref -Map=src/$@/System.map

quiet_cmd_objcopy = OBJCOPY 	src/$@/$@
cmd_objcopy = $(OBJCOPY) $(OBJCOPYFLAGS) src/$@/$@.efi src/$@/$@

quiet_cmd_cc_o_c = CC	$@
cmd_cc_o_c = $(CC) $(MCFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $<

quiet_cmd_as_o_S = AS	$@
cmd_as_o_S = $(CC) $(MCFLAGS) $(ASFLAGS) -c -o $@ $<

quiet_cmd_ar = AR	$@
cmd_ar = $(AR) $(ARFLAGS) $@ $(filter-out FORCE,$^)


# Find any prerequisites that is newer than target or that does not exist.
# PHONY targets skipped in both cases.
any-prereq = $(filter-out $(PHONY),$?) $(filter-out $(PHONY) $(wildcard $^),$^)

if_changed = $(if $(strip $(any-prereq)),			\
			 @set -e;								\
			 $(echo-cmd) $(cmd_$(1)))

#make variables (CC, etc...)
AS		= $(CROSS_COMPILE)as
ifneq ($(shell $(CROSS_COMPILE)ld.bfd -v 2> /dev/null),)
LD		= $(CROSS_COMPILE)ld.bfd
else
LD		= $(CROSS_COMPILE)ld
endif
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump
RM		= rm
export AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP

libs-y := arm/
libs-y += s5p4418/
libs-y += s5p4418/gpio/
libs-y += s5p4418/clk/
libs-y += s5p4418/interrupt/
libs-y += library/malloc/
libs-y += library/math/
libs-y += library/stdio/
libs-y += library/stdlib/
libs-y += library/string/
libs-y += library/errno/
libs-y += library/exit/
libs-y += library/ctype/

libs-y 	:= $(sort $(libs-y))
dirs 	:= $(patsubst %/,%, $(filter %/, $(libs-y)))
libs-y	:= $(patsubst %/,%/build-in.o,$(libs-y))

heads-y := arm/start.S
init-y	:= $(patsubst %.S, %.o, $(heads-y))

$(init-y):$(heads-y)
	$(call if_changed,as_o_S)

$(foreach v, $(dirs), $(eval $(v)/src := $(wildcard $(v)/*.c)))
$(foreach v, $(dirs), $(eval $(v)/obj := $(patsubst %.c,%.o,$(value $(v)/src))))

arm/obj += $(patsubst %.S,%.o,$(filter-out $(heads-y),$(wildcard arm/*.S)))

$(foreach v, $(dirs), $(eval $(v)/build-in.o : $($(v)/obj)))
%.o : %.c
	$(call if_changed,cc_o_c)
%.o : %.S
	$(call if_changed,as_o_S)

$(libs-y) : FORCE
	$(call if_changed,ar)

led:$(libs-y) $(init-y) src/led/build-in.o
	$(call if_changed,ld)
	$(call if_changed,objcopy)
	tools/mk4418 led.bin tools/nsih.txt tools/2ndboot src/led/led

PHONY += FORCE
FORCE:

PHONY += clean
clean:
	$(Q)$(RM) $(foreach v, $(dirs), $(value $(v)/obj))
	$(Q)$(RM) $(libs-y) $(init-y)

.PHONY:$(PHONY)
