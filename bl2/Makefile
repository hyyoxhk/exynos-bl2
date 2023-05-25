extra-y	:= bl2_entrypoint.o

obj-y += bl2_main.o
obj-$(CONFIG_NORMAL_BOOT)	+= bl2_image_load_v1.o
obj-$(CONFIG_SECURE_BOOT)	+= bl2_image_load_v2.o

#PLATFORM_RELFLAGS += -ffunction-sections -fdata-sections \
#		     -fno-common -ffixed-r9

#PLATFORM_RELFLAGS += $(call cc-option, -msoft-float) \
#      $(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))

# LLVM support
#LLVM_RELFLAGS		:= $(call cc-option,-mllvm,) \
#			$(call cc-option,-mno-movt,)
#PLATFORM_RELFLAGS	+= $(LLVM_RELFLAGS)
