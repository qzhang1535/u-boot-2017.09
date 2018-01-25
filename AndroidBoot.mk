
UBOOT_SRC := $(call my-dir)
UBOOT_CFG := tq210_defconfig
UBOOT_BIN := $(UBOOT_SRC)/u-boot-tq210.bin

UBOOT_TARGET := $(PRODUCT_OUT)/uboot.img

PHONY := uboot_menuconfig uboot_img uboot_distclean
.PHONY:$(PHONY)

uboot_menuconfig:$(ACP)
	$(ACP) $(UBOOT_SRC)/configs/$(UBOOT_CFG) $(UBOOT_SRC)/.config
	$(MAKE) -C $(UBOOT_SRC) menuconfig
	$(ACP) $(UBOOT_SRC)/.config $(UBOOT_SRC)/configs/$(UBOOT_CFG)

uboot_img:$(ACP)
	$(MAKE) -C $(UBOOT_SRC) $(UBOOT_CFG)
	$(MAKE) -C $(UBOOT_SRC) CROSS_COMPILE=arm-linux-androideabi-
	$(ACP) $(UBOOT_BIN) $(UBOOT_TARGET)

uboot_distclean:	
	$(MAKE) -C $(UBOOT_SRC) distclean

	
$(INSTALLED_KERNEL_TARGET):uboot_img

	
