### 说明
- 支持s5pv210,且支持SD启动和nand启动
- 支持s3c2440,且支持NOR和NAND启动
- 支持fastboot命令

### 导入编译环境
```
. ../build/envsetup.sh
```

### s5pv210编译
```
make tq210_defconfig
make -j8
```

### s5pv210烧录
```
// 制作SD启动卡并从SD卡启动UBOOT，然后在通过UBOOT烧写NANDFLASH
sudo dd if=u-boot-tq210.bin of=/dev/sdb seek=1
sync
```



### tq2440编译
```
make tq2440_defconfig
make -j8
```

### tq2440烧录
- 使用jlink烧录到norflash并从NORFLASH启动UBOOT。然后在通过UBOOT烧写NANDFLASH。
- 将u-boot-tq2440.bin从nandflash的0地址处开始写入既可
