#!/bin/sh

#cat E4412_N.bl1.bin exynos-bl2.img u-boot.bin > test.img

sudo dd iflag=dsync oflag=dsync if=/dev/zero of=/dev/sdb bs=512 seek=1 count=8192 

sudo dd iflag=dsync oflag=dsync if=./firmware/E4412_N.bl1.SCP2G.bin of=/dev/sdb bs=512 seek=1 conv=notrunc

sudo dd iflag=dsync oflag=dsync if=./exynos-bl2.img  of=/dev/sdb bs=512 seek=31 conv=notrunc

sudo dd iflag=dsync oflag=dsync if=./u-boot.bin  of=/dev/sdb bs=512 seek=63 conv=notrunc

sudo dd iflag=dsync oflag=dsync if=./firmware/tzsw_SMDK4412_SCP_2GB.bin  of=/dev/sdb bs=512 seek=1087 conv=notrunc


