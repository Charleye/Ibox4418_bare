targets := $(sort $(patsubst %/,%,$(shell ls -F src/)))
pdirs 	:= $(addprefix src/,$(targets))
pobjs	:= $(patsubst %,%/build-in.o,$(pdirs))
$(foreach v, $(pdirs), $(eval $(v)/pefi := $(addsuffix .efi,$(v)/$(notdir $(v)))))
$(foreach v, $(pdirs), $(eval $(v)/pbin := $(v)/$(notdir $(v))))

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
	@echo $(targets)

$(CURDIR)/Makefile Makefile: ;

ASFLAGS		:= -O2 -nostdlib -ffunction-sections -fdata-sections -fno-common -Iinclude
LDFLAGS		+= -O2 -static -Tlink.lds -L/usr/lib/gcc/arm-none-eabi/6.2.1/
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

quiet_cmd_ld = LD	$@
cmd_ld = $(LD) -o $@ $(LDFLAGS)  $(init-y) --start-group $(filter-out $(init-y),$^) -lgcc --end-group  -cref -Map=$(dir $@)/System.map

quiet_cmd_objcopy = OBJCOPY	$@
cmd_objcopy = $(OBJCOPY) $(OBJCOPYFLAGS) $(filter-out FORCE,$^) $@

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
RM		= rm -f
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

$(foreach v, $(pdirs), $(eval $(v)/src := $(wildcard $(v)/*.c)))
$(foreach v, $(pdirs), $(eval $(v)/obj := $(patsubst %.c,%.o,$(value $(v)/src))))
$(foreach v, $(pdirs), $(eval $(v)/build-in.o : $(value $(v)/obj)))
$(foreach v, $(pdirs), $(eval $(value $(v)/pbin) : $(addsuffix .efi,$(value $(v)/pbin))))

%.o : %.c
	$(call if_changed,cc_o_c)
%.o : %.S
	$(call if_changed,as_o_S)

$(libs-y) : FORCE
	$(call if_changed,ar)

$(foreach m, $(pdirs), $(value $(m)/pefi)) : $(libs-y) $(init-y)
	$(call if_changed,ld)

$(foreach v, $(pdirs), $(eval $(value $(v)/pefi) : $(v)/build-in.o))

$(foreach m, $(pdirs), $(value $(m)/pbin)) : FORCE
	$(call if_changed,objcopy)

$(pobjs) : FORCE
	$(call if_changed,ar)

$(foreach m, $(pdirs), $(eval $(notdir $(value $(m)/pbin)) : $(value $(m)/pbin)))

MK4418	:= mk4418
NSIH	:= tools/nsih.txt
2NDBOOT	:= tools/2ndboot

$(foreach m, $(targets),$(m)): FORCE $(MK4418)
	@echo "MK4418	$(addsuffix .bin,$@)"
	@./$(MK4418) $(addsuffix .bin,$@) $(NSIH) $(2NDBOOT) $(addprefix src/,$@)/$@

$(MK4418) :
	@echo "GCC	$@"
	$(Q)gcc -o $@ tools/4418.c

PHONY += FORCE
FORCE:

PHONY += clean
clean:
	$(Q)$(RM) $(libs-y) $(init-y)
	$(Q)$(RM) $(foreach m, $(dirs), $(value $(m)/obj))
	$(Q)$(RM) $(pobjs)
	$(Q)$(RM) $(foreach m, $(pdirs), $(value $(m)/obj))
	$(Q)$(RM) $(foreach m, $(pdirs), $(value $(m)/pefi))
	$(Q)$(RM) $(foreach m, $(pdirs), $(value $(m)/pbin))
	$(Q)$(RM) $(foreach m, $(pdirs),  $(m)/System.map $(addsuffix .bin,$(notdir $(m))))
	$(Q)$(RM) $(MK4418)
	@echo "\nClean All Object Files\n"

PHONY += $(foreach m, $(targets), $(addprefix clean-,$(m)))
$(foreach m, $(targets), $(addprefix clean-,$(m))):
	$(Q)$(RM) $(addsuffix /*.o,$(addprefix src/,$(patsubst clean-%,%,$@)))
	$(Q)$(RM) $(addprefix src/,$(patsubst clean-%,%,$@))/$(patsubst clean-%,%,$@)*
	$(Q)$(RM) $(addsuffix .bin,$(patsubst clean-%,%,$@))
	$(Q)$(RM) $(addprefix src/,$(patsubst clean-%,%,$@))/System.map
	@echo "\nClean Object Files for $(patsubst clean-%,%,$@) Project\n"

.PHONY:$(PHONY)
