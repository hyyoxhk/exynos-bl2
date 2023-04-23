# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2020-2023 hey <hyyoxhk@163.com>
#

ifeq ("$(origin V)", "command line")
  KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

ifeq ($(KBUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(filter 4.%,$(MAKE_VERSION)),)	# make-4
ifneq ($(filter %s ,$(firstword x$(MAKEFLAGS))),)
  quiet=silent_
endif
else					# make-3.8x
ifneq ($(filter s% -s%,$(MAKEFLAGS)),)
  quiet=silent_
endif
endif

export quiet Q KBUILD_VERBOSE

# kbuild supports saving output files in a separate directory.
# To locate output files in a separate directory two syntaxes are supported.
# In both cases the working directory must be the root of the kernel src.
# 1) O=
# Use "make O=dir/to/store/output/files/"
#
# 2) Set KBUILD_OUTPUT
# Set the environment variable KBUILD_OUTPUT to point to the directory
# where the output files shall be placed.
# export KBUILD_OUTPUT=dir/to/store/output/files/
# make
#
# The O= assignment takes precedence over the KBUILD_OUTPUT environment
# variable.

# KBUILD_SRC is set on invocation of make in OBJ directory
# KBUILD_SRC is not intended to be used by the regular user (for now)
ifeq ($(KBUILD_SRC),)

# OK, Make called in directory where kernel src resides
# Do we want to locate output files in a separate directory?
ifeq ("$(origin O)", "command line")
  KBUILD_OUTPUT := $(O)
endif

# That's our default target when none is given on the command line
PHONY := _all
_all:

# Cancel implicit rules on top Makefile
$(CURDIR)/Makefile Makefile: ;

ifneq ($(KBUILD_OUTPUT),)
# Invoke a second make in the output directory, passing relevant variables
# check that the output directory actually exists
saved-output := $(KBUILD_OUTPUT)
KBUILD_OUTPUT := $(shell mkdir -p $(KBUILD_OUTPUT) && cd $(KBUILD_OUTPUT) && /bin/pwd)
$(if $(KBUILD_OUTPUT),, $(error failed to create output directory "$(saved-output)"))

PHONY += sub-make

$(filter-out _all sub-make $(CURDIR)/Makefile, $(MAKECMDGOALS)) _all: sub-make
	@:

sub-make: FORCE
	$(Q)$(MAKE) -C $(KBUILD_OUTPUT) KBUILD_SRC=$(CURDIR) \
	-f $(CURDIR)/Makefile $(filter-out _all sub-make,$(MAKECMDGOALS))

# Leave processing to above invocation of make
skip-makefile := 1
endif # ifneq ($(KBUILD_OUTPUT),)
endif # ifeq ($(KBUILD_SRC),)

# We process the rest of the Makefile if this is the final invocation of make
ifeq ($(skip-makefile),)

# Do not print "Entering directory ...",
# but we want to display it when entering to the output directory
# so that IDEs/editors are able to understand relative filenames.
MAKEFLAGS += --no-print-directory

# Call a source code checker (by default, "sparse") as part of the
# C compilation.
#
# Use 'make C=1' to enable checking of only re-compiled files.
# Use 'make C=2' to enable checking of *all* source files, regardless
# of whether they are re-compiled or not.
#
# See the file "doc/sparse.txt" for more details, including
# where to get the "sparse" utility.

ifeq ("$(origin C)", "command line")
  KBUILD_CHECKSRC = $(C)
endif
ifndef KBUILD_CHECKSRC
  KBUILD_CHECKSRC = 0
endif

PHONY += all
_all: all

ifeq ($(KBUILD_SRC),)
        # building in the source tree
        srctree := .
else
        ifeq ($(KBUILD_SRC)/,$(dir $(CURDIR)))
                # building in a subdirectory of the source tree
                srctree := ..
        else
                srctree := $(KBUILD_SRC)
        endif
endif
objtree		:= .
src		:= $(srctree)
obj		:= $(objtree)

VPATH		:= $(srctree)$(if $(KBUILD_EXTMOD),:$(KBUILD_EXTMOD))

export srctree objtree VPATH

# Make sure CDPATH settings don't interfere
unexport CDPATH

#########################################################################

HOSTARCH := $(shell uname -m | \
	sed -e s/i.86/x86/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/ppc64/powerpc/ \
	    -e s/ppc/powerpc/ \
	    -e s/macppc/powerpc/\
	    -e s/sh.*/sh/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

export	HOSTARCH HOSTOS

#########################################################################

# set default to nothing for native builds
ifeq ($(HOSTARCH),$(ARCH))
CROSS_COMPILE ?=
endif

KCONFIG_CONFIG	?= .config
export KCONFIG_CONFIG

# SHELL used by kbuild
CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	  else if [ -x /bin/bash ]; then echo /bin/bash; \
	  else echo sh; fi ; fi)

HOST_LFS_CFLAGS := $(shell getconf LFS_CFLAGS 2>/dev/null)
HOST_LFS_LDFLAGS := $(shell getconf LFS_LDFLAGS 2>/dev/null)
HOST_LFS_LIBS := $(shell getconf LFS_LIBS 2>/dev/null)

HOSTCC       = cc
HOSTCXX      = c++

KBUILD_HOSTCFLAGS   := -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer \
		$(HOST_LFS_CFLAGS) $(HOSTCFLAGS)
KBUILD_HOSTCXXFLAGS := -O2 $(HOST_LFS_CFLAGS) $(HOSTCXXFLAGS)
KBUILD_HOSTLDFLAGS  := $(HOST_LFS_LDFLAGS) $(HOSTLDFLAGS)
KBUILD_HOSTLDLIBS   := $(HOST_LFS_LIBS) $(HOSTLDLIBS)

# With the move to GCC 6, we have implicitly upgraded our language
# standard to GNU11 (see https://gcc.gnu.org/gcc-5/porting_to.html).
# Some Linux distributions (including RHEL7, SLES13, Debian 8) still
# have older compilers as their default, so we make it explicit for
# these that our host tools are GNU11 (i.e. C11 w/ GNU extensions).
CSTD_FLAG := -std=gnu11
ifeq ($(HOSTOS),linux)
KBUILD_HOSTCFLAGS += $(CSTD_FLAG)
endif

ifeq ($(HOSTOS),cygwin)
KBUILD_HOSTCFLAGS	+= -ansi
endif

# Mac OS X / Darwin's C preprocessor is Apple specific.  It
# generates numerous errors and warnings.  We want to bypass it
# and use GNU C's cpp.	To do this we pass the -traditional-cpp
# option to the compiler.  Note that the -traditional-cpp flag
# DOES NOT have the same semantics as GNU C's flag, all it does
# is invoke the GNU preprocessor in stock ANSI/ISO C fashion.
#
# Apple's linker is similar, thanks to the new 2 stage linking
# multiple symbol definitions are treated as errors, hence the
# -multiply_defined suppress option to turn off this error.
#
ifeq ($(HOSTOS),darwin)
# get major and minor product version (e.g. '10' and '6' for Snow Leopard)
DARWIN_MAJOR_VERSION	= $(shell sw_vers -productVersion | cut -f 1 -d '.')
DARWIN_MINOR_VERSION	= $(shell sw_vers -productVersion | cut -f 2 -d '.')

os_x_before	= $(shell if [ $(DARWIN_MAJOR_VERSION) -le $(1) -a \
	$(DARWIN_MINOR_VERSION) -le $(2) ] ; then echo "$(3)"; else echo "$(4)"; fi ;)

os_x_after = $(shell if [ $(DARWIN_MAJOR_VERSION) -ge $(1) -a \
	$(DARWIN_MINOR_VERSION) -ge $(2) ] ; then echo "$(3)"; else echo "$(4)"; fi ;)	

# Snow Leopards build environment has no longer restrictions as described above
HOSTCC       = $(call os_x_before, 10, 5, "cc", "gcc")
KBUILD_HOSTCFLAGS  += $(call os_x_before, 10, 4, "-traditional-cpp")
KBUILD_HOSTLDFLAGS += $(call os_x_before, 10, 5, "-multiply_defined suppress")

# since Lion (10.7) ASLR is on by default, but we use linker generated lists
# in some host tools which is a problem then ... so disable ASLR for these
# tools
KBUILD_HOSTLDFLAGS += $(call os_x_before, 10, 7, "", "-Xlinker -no_pie")

# macOS Mojave (10.14.X) 
# Undefined symbols for architecture x86_64: "_PyArg_ParseTuple"
KBUILD_HOSTLDFLAGS += $(call os_x_after, 10, 14, "-lpython -dynamclib", "")
endif

# Decide whether to build built-in, modular, or both.
# Normally, just do built-in.

KBUILD_MODULES :=
KBUILD_BUILTIN := 1

# If we have only "make modules", don't compile built-in objects.
# When we're building modules with modversions, we need to consider
# the built-in objects during the descend as well, in order to
# make sure the checksums are up to date before we record them.

ifeq ($(MAKECMDGOALS),modules)
  KBUILD_BUILTIN := $(if $(CONFIG_MODVERSIONS),1)
endif

# If we have "make <whatever> modules", compile modules
# in addition to whatever we do anyway.
# Just "make" or "make all" shall build modules as well

# exynos-bl2 does not need modules
#ifneq ($(filter all _all modules,$(MAKECMDGOALS)),)
#  KBUILD_MODULES := 1
#endif

#ifeq ($(MAKECMDGOALS),)
#  KBUILD_MODULES := 1
#endif

# Check this size of a binary:
# Args:
#   $1: File to check
#   #2: Size limit in bytes (decimal or 0xhex)
define size_check
	actual=$$( wc -c $1 | awk '{print $$1}'); \
	limit=$$( printf "%d" $2 ); \
	if test $$actual -gt $$limit; then \
		echo "$1 exceeds file size limit:" >&2; \
		echo "  limit:  $$(printf %#x $$limit) bytes" >&2; \
		echo "  actual: $$(printf %#x $$actual) bytes" >&2; \
		echo "  excess: $$(printf %#x $$((actual - limit))) bytes" >&2;\
		exit 1; \
	fi
endef
export size_check

export KBUILD_MODULES KBUILD_BUILTIN
export KBUILD_CHECKSRC KBUILD_SRC KBUILD_EXTMOD

# We need some generic definitions (do not try to remake the file).
scripts/Kbuild.include: ;
include scripts/Kbuild.include

# Make variables (CC, etc...)

AS		= $(CROSS_COMPILE)as
# Always use GNU ld
ifneq ($(shell $(CROSS_COMPILE)ld.bfd -v 2> /dev/null),)
LD		= $(CROSS_COMPILE)ld.bfd
else
LD		= $(CROSS_COMPILE)ld
endif
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
LDR		= $(CROSS_COMPILE)ldr
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
LEX		= flex
YACC		= bison
AWK		= awk
PERL		= perl
PYTHON		?= python
PYTHON2		= python2
PYTHON3		= python3
CHECK		= sparse

CHECKFLAGS     := -D__linux__ -Dlinux -D__STDC__ -Dunix -D__unix__ \
		  -Wbitwise -Wno-return-void -D__CHECK_ENDIAN__ $(CF)

KBUILD_CPPFLAGS := -D__KERNEL__

KBUILD_CFLAGS   := -Wall -Wstrict-prototypes \
		   -Wno-format-security \
		   -fno-builtin -ffreestanding $(CSTD_FLAG)
KBUILD_CFLAGS	+= -fshort-wchar -fno-strict-aliasing
KBUILD_AFLAGS   := -D__ASSEMBLY__
KBUILD_LDFLAGS  :=

ifeq ($(cc-name),clang)
ifneq ($(CROSS_COMPILE),)
CLANG_TARGET	:= --target=$(notdir $(CROSS_COMPILE:%-=%))
GCC_TOOLCHAIN_DIR := $(dir $(shell which $(LD)))
CLANG_PREFIX	:= --prefix=$(GCC_TOOLCHAIN_DIR)
GCC_TOOLCHAIN	:= $(realpath $(GCC_TOOLCHAIN_DIR)/..)
endif
ifneq ($(GCC_TOOLCHAIN),)
CLANG_GCC_TC	:= --gcc-toolchain=$(GCC_TOOLCHAIN)
endif
KBUILD_CFLAGS += $(CLANG_TARGET) $(CLANG_GCC_TC) $(CLANG_PREFIX)
KBUILD_AFLAGS += $(CLANG_TARGET) $(CLANG_GCC_TC) $(CLANG_PREFIX)
KBUILD_CFLAGS += $(call cc-option, -no-integrated-as)
KBUILD_AFLAGS += $(call cc-option, -no-integrated-as)
endif

# Don't generate position independent code
KBUILD_CFLAGS	+= $(call cc-option,-fno-PIE)
KBUILD_AFLAGS	+= $(call cc-option,-fno-PIE)

export CONFIG_SHELL HOSTCC KBUILD_HOSTCFLAGS CROSS_COMPILE AS LD CC
export CPP AR NM LDR STRIP OBJCOPY OBJDUMP KBUILD_HOSTLDFLAGS KBUILD_HOSTLDLIBS
export MAKE LEX YACC AWK PERL PYTHON PYTHON2 PYTHON3
export HOSTCXX KBUILD_HOSTCXXFLAGS CHECK CHECKFLAGS DTC DTC_FLAGS

export KBUILD_CPPFLAGS NOSTDINC_FLAGS INCLUDEPATH OBJCOPYFLAGS KBUILD_LDFLAGS
export KBUILD_CFLAGS KBUILD_AFLAGS

export CC_VERSION_TEXT := $(shell $(CC) --version | head -n 1)

# When compiling out-of-tree modules, put MODVERDIR in the module
# tree rather than in the kernel tree. The kernel tree might
# even be read-only.
export MODVERDIR := $(if $(KBUILD_EXTMOD),$(firstword $(KBUILD_EXTMOD))/).tmp_versions

# Files to ignore in find ... statements

export RCS_FIND_IGNORE := \( -name SCCS -o -name BitKeeper -o -name .svn -o    \
			  -name CVS -o -name .pc -o -name .hg -o -name .git \) \
			  -prune -o
export RCS_TAR_IGNORE := --exclude SCCS --exclude BitKeeper --exclude .svn \
			 --exclude CVS --exclude .pc --exclude .hg --exclude .git

# ===========================================================================
# Rules shared between *config targets and build targets

# Basic helpers built in scripts/
PHONY += scripts_basic
scripts_basic:
	$(Q)$(MAKE) $(build)=scripts/basic
	$(Q)rm -f .tmp_quiet_recordmcount

# To avoid any implicit rule to kick in, define an empty command.
scripts/basic/%: scripts_basic ;

PHONY += tools_basic
tools_basic:
	$(Q)$(MAKE) $(build)=tools

PHONY += outputmakefile
# outputmakefile generates a Makefile in the output directory, if using a
# separate output directory. This allows convenient use of make in the
# output directory.
outputmakefile:
ifneq ($(KBUILD_SRC),)
	$(Q)ln -fsn $(srctree) source
	$(Q)$(CONFIG_SHELL) $(srctree)/scripts/mkmakefile \
	    $(srctree) $(objtree)
endif

# FIX: wait for it by hyyoxhk
config-targets := 0
mixed-targets  := 0
dot-config     := 1

ifeq ($(KBUILD_EXTMOD),)
        ifneq ($(filter config %config,$(MAKECMDGOALS)),)
                config-targets := 1
                ifneq ($(words $(MAKECMDGOALS)),1)
                        mixed-targets := 1
                endif
        endif
endif

ifeq ($(mixed-targets),1)
# ===========================================================================
# We're called with mixed targets (*config and build targets).
# Handle them one by one.

PHONY += $(MAKECMDGOALS) __build_one_by_one

$(filter-out __build_one_by_one, $(MAKECMDGOALS)): __build_one_by_one
	@:

__build_one_by_one:
	$(Q)set -e; \
	for i in $(MAKECMDGOALS); do \
		$(MAKE) -f $(srctree)/Makefile $$i; \
	done

else
ifeq ($(config-targets),1)
# ===========================================================================
# *config targets only - make sure prerequisites are updated, and descend
# in scripts/kconfig to make the *config target

KBUILD_DEFCONFIG := sandbox_defconfig
export KBUILD_DEFCONFIG KBUILD_KCONFIG

config: scripts_basic outputmakefile FORCE
	$(Q)$(MAKE) $(build)=scripts/kconfig $@

%config: scripts_basic outputmakefile FORCE
	$(Q)$(MAKE) $(build)=scripts/kconfig $@

else
# ===========================================================================
# Build targets only - this includes vmlinux, arch specific targets, clean
# targets and others. In general all targets except *config targets.

# Additional helpers built in scripts/
# Carefully list dependencies so we do not try to build scripts twice
# in parallel
PHONY += scripts
scripts: scripts_basic tools_basic
	$(Q)$(MAKE) $(build)=$(@)
endif

#
# Xtensa linker script cannot be preprocessed with -ansi because of
# preprocessor operations on strings that don't make C identifiers.
#
ifeq ($(CONFIG_XTENSA),)
LDPPFLAGS	+= -ansi
endif

ifdef CONFIG_CC_OPTIMIZE_FOR_SIZE
KBUILD_CFLAGS	+= -Os
else
KBUILD_CFLAGS	+= -O2

KBUILD_CFLAGS += $(call cc-option,-fno-stack-protector)
KBUILD_CFLAGS += $(call cc-option,-fno-delete-null-pointer-checks)

# disable stringop warnings in gcc 8+
KBUILD_CFLAGS += $(call cc-disable-warning, stringop-truncation)

# Enabled with W=2, disabled by default as noisy
KBUILD_CFLAGS += $(call cc-disable-warning, maybe-uninitialized)

# change __FILE__ to the relative path from the srctree
KBUILD_CFLAGS += $(call cc-option,-fmacro-prefix-map=$(srctree)/=)

KBUILD_CFLAGS += -g
# $(KBUILD_AFLAGS) sets -g, which causes gcc to pass a suitable -g<format>
# option to the assembler.
KBUILD_AFLAGS += -g

# Report stack usage if supported
# ARC tools based on GCC 7.1 has an issue with stack usage
# with naked functions, see commit message for more details
ifndef CONFIG_ARC
ifeq ($(shell $(CONFIG_SHELL) $(srctree)/scripts/gcc-stack-usage.sh $(CC)),y)
	KBUILD_CFLAGS += -fstack-usage
endif
endif

KBUILD_CFLAGS += $(call cc-option,-Wno-format-nonliteral)
KBUILD_CFLAGS += $(call cc-disable-warning, address-of-packed-member)

ifeq ($(cc-name),clang)
KBUILD_CPPFLAGS += $(call cc-option,-Qunused-arguments,)
KBUILD_CFLAGS += $(call cc-disable-warning, format-invalid-specifier)
KBUILD_CFLAGS += $(call cc-disable-warning, gnu)
KBUILD_CFLAGS += $(call cc-disable-warning, address-of-packed-member)
# Quiet clang warning: comparison of unsigned expression < 0 is always false
KBUILD_CFLAGS += $(call cc-disable-warning, tautological-compare)
# CLANG uses a _MergedGlobals as optimization, but this breaks modpost, as the
# source of a reference will be _MergedGlobals and not on of the whitelisted names.
# See modpost pattern 2
KBUILD_CFLAGS += $(call cc-option, -mno-global-merge,)
KBUILD_CFLAGS += $(call cc-option, -fcatch-undefined-behavior)
else

# These warnings generated too much noise in a regular build.
# Use make W=1 to enable them (see scripts/Makefile.extrawarn)
KBUILD_CFLAGS += $(call cc-disable-warning, unused-but-set-variable)
endif

# Prohibit date/time macros, which would make the build non-deterministic
KBUILD_CFLAGS   += $(call cc-option,-Werror=date-time)

include scripts/Makefile.extrawarn

# Add user supplied CPPFLAGS, AFLAGS and CFLAGS as the last assignments
KBUILD_CPPFLAGS += $(KCPPFLAGS)
KBUILD_AFLAGS += $(KAFLAGS)
KBUILD_CFLAGS += $(KCFLAGS)

KBUILD_HOSTCFLAGS += $(if $(CONFIG_TOOLS_DEBUG),-g)

# 开始
BL2INCLUDE    := \
		-Iinclude \
		$(if $(KBUILD_SRC), -I$(srctree)/include) \
		-include $(srctree)/include/linux/kconfig.h

export BL2INCLUDE

NOSTDINC_FLAGS += -nostdinc -isystem $(shell $(CC) -print-file-name=include)

NOSTDINC_FLAGS += $(call cc-option,-mcpu=cortex-a9)

PLATFORM_RELFLAGS += $(call cc-option, -msoft-float) 

PLATFORM_RELFLAGS += -ffunction-sections -fdata-sections \
		     -fno-common -ffixed-r9

PLATFORM_CPPFLAGS = $(call cc-option, -march=armv7-a, $(call cc-option, -march=armv7))


KBUILD_CFLAGS   += $(call cc-option,-mcpu=cortex-a9)

PLATFORM_CPPFLAGS += $(call cc-option,-mcpu=cortex-a9)


cpp_flags := $(KBUILD_CPPFLAGS) $(PLATFORM_CPPFLAGS) $(BL2INCLUDE) $(NOSTDINC_FLAGS)

c_flags := $(KBUILD_CFLAGS) $(cpp_flags)

libs-y += bl2/
libs-y += helper/
libs-y += lib/
libs-y += drivers/

libs-y := $(sort $(libs-y))

exynos-bl2-dirs	:= $(patsubst %/,%,$(filter %/, $(libs-y)))

libs-y		:= $(patsubst %/, %/built-in.o, $(libs-y))

bl2-init := bl2/bl2_entrypoint.o
bl2-main := $(libs-y)

quiet_cmd_bl2__ ?= LD      $@
      cmd_bl2__ ?= $(LD) $(KBUILD_LDFLAGS) -o $@ \
      -T bl2.lds $(bl2-init)                             \
      --start-group $(bl2-main) --end-group                 \
      $(PLATFORM_LIBS) -Map bl2.map

exynos-bl2: $(bl2-init) $(bl2-main) FORCE
	+$(call if_changed,bl2__)

# Normally we fill empty space with 0xff
quiet_cmd_objcopy = OBJCOPY $@
cmd_objcopy = $(OBJCOPY) --gap-fill=0xff $(OBJCOPYFLAGS) \
	-O binary $< $@

exynos-bl2.bin: exynos-bl2 FORCE
	$(call if_changed,objcopy)

exynos-bl2-checksum.bin: exynos-bl2.bin
	$(objtree)/tools/checksum $< $@

exynos-bl2.img: exynos-bl2-checksum.bin
	$(objtree)/tools/codesigner_v21 -v2.1 $< $@ $(objtree)/firmware/Exynos4412_V21.prv -STAGE2

# The actual objects are generated when descending,
# make sure no implicit rule kicks in
$(sort $(bl2-init) $(bl2-main)): $(exynos-bl2-dirs) ;

# Handle descending into subdirectories listed in $(u-boot-dirs)
# Preset locale variables to speed up the build process. Limit locale
# tweaks to this spot to avoid wrong language settings when running
# make menuconfig etc.
# Error messages still appears in the original language

PHONY += $(exynos-bl2-dirs)
$(exynos-bl2-dirs): prepare scripts
	$(Q)$(MAKE) $(build)=$@

# Things we need to do before we recursively start building the kernel
# or the modules are listed in "prepare".
# A multi level approach is used. prepareN is processed before prepareN-1.
# archprepare is used in arch Makefiles and when processed asm symlink,
# version.h and scripts_basic is processed / created.

# Listed in dependency order
PHONY += prepare prepare0 prepare1 prepare2 prepare3

# prepare3 is used to check if we are building in a separate output directory,
# and if so do:
# 1) Check that make has not been executed in the kernel src $(srctree)
prepare3:
ifneq ($(KBUILD_SRC),)
	@$(kecho) '  Using $(srctree) as source for exynos-bl2'
	$(Q)if [ -f $(srctree)/.config -o -d $(srctree)/include/config ]; then \
		echo >&2 "  $(srctree) is not clean, please run 'make mrproper'"; \
		echo >&2 "  in the '$(srctree)' directory.";\
		/bin/false; \
	fi;
endif

# prepare2 creates a makefile if using a separate output directory
prepare2: prepare3 outputmakefile

prepare1: prepare2

prepare0: prepare1 scripts_basic FORCE
	$(Q)$(MAKE) $(build)=.

# All the preparing..
prepare: prepare0

$(version_h): $(srctree)/Makefile FORCE
	$(call filechk,version.h)

all: exynos-bl2.img

export RCS_FIND_IGNORE := \( -name SCCS -o -name BitKeeper -o -name .svn -o    \
			  -name CVS -o -name .pc -o -name .hg -o -name .git \) \
			  -prune -o

#########################################################################

###
# Cleaning is done on three levels.
# make clean     Delete most generated files
#                Leave enough to build external modules
# make mrproper  Delete the current configuration, and all generated files
# make distclean Remove editor backup files, patch leftover files and the like

# Directories & files removed with 'make clean'
CLEAN_DIRS  += $(MODVERDIR) \
	       $(foreach d, spl tpl, $(patsubst %,$d/%, \
			$(filter-out include, $(shell ls -1 $d 2>/dev/null))))

CLEAN_FILES += exynos-bl2* bl2.map

# clean - Delete most, but leave enough to build external modules
#
clean: rm-dirs  := $(CLEAN_DIRS)
clean: rm-files := $(CLEAN_FILES)

PHONY += clean

clean: 
	$(call cmd,rmdirs)
	$(call cmd,rmfiles)
	@find $(if $(KBUILD_EXTMOD), $(KBUILD_EXTMOD), .) $(RCS_FIND_IGNORE) \
		\( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
		-o -name '*.ko.*' -o -name '*.su' -o -name '*.pyc' \
		-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \
		-o -name '*.lex.c' -o -name '*.tab.[ch]' \
		-o -name '*.asn1.[ch]' \
		-o -name '*.symtypes' -o -name 'modules.order' \
		-o -name modules.builtin -o -name '.tmp_*.o.*' \
		-o -name 'dsdt.aml' -o -name 'dsdt.asl.tmp' -o -name 'dsdt.c' \
		-o -name '*.efi' -o -name '*.gcno' -o -name '*.so' \) \
		-type f -print | xargs rm -f

# mrproper - Delete all generated files, including .config
#
mrproper: rm-dirs  := $(wildcard $(MRPROPER_DIRS))
mrproper: rm-files := $(wildcard $(MRPROPER_FILES))
mrproper-dirs      := $(addprefix _mrproper_,scripts)

PHONY += $(mrproper-dirs) mrproper archmrproper
$(mrproper-dirs):
	$(Q)$(MAKE) $(clean)=$(patsubst _mrproper_%,%,$@)

mrproper: clean $(mrproper-dirs)
	$(call cmd,rmdirs)
	$(call cmd,rmfiles)

endif #ifeq ($(config-targets),1)
endif #ifeq ($(mixed-targets),1)
# Single targets
# ---------------------------------------------------------------------------
# Single targets are compatible with:
# - build with mixed source and output
# - build with separate output dir 'make O=...'
# - external modules
#
#  target-dir => where to store outputfile
#  build-dir  => directory in kernel source tree to use

ifeq ($(KBUILD_EXTMOD),)
        build-dir  = $(patsubst %/,%,$(dir $@))
        target-dir = $(dir $@)
else
        zap-slash=$(filter-out .,$(patsubst %/,%,$(dir $@)))
        build-dir  = $(KBUILD_EXTMOD)$(if $(zap-slash),/$(zap-slash))
        target-dir = $(if $(KBUILD_EXTMOD),$(dir $<),$(dir $@))
endif

%.s: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.i: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.o: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.lst: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.s: %.S prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.o: %.S prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)
%.symtypes: %.c prepare scripts FORCE
	$(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)

# FIXME Should go into a make.lib or something
# ===========================================================================

quiet_cmd_rmdirs = $(if $(wildcard $(rm-dirs)),CLEAN   $(wildcard $(rm-dirs)))
      cmd_rmdirs = rm -rf $(rm-dirs)

quiet_cmd_rmfiles = $(if $(wildcard $(rm-files)),CLEAN   $(wildcard $(rm-files)))
      cmd_rmfiles = rm -f $(rm-files)

endif	# skip-makefile

PHONY += FORCE
FORCE:

# Declare the contents of the PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
