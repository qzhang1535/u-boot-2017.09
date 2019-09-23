### 说明
- 该uboot在tq210板卡上测试通过
- 同时支持SD启动和nand启动
- 支持fastboot功能
- 支持s3c2440从NOR和NAND启动
- 支持fastboot命令

### 导入编译环境
```
. ../build/envsetup.sh
```

### 编译
```
make tq210_defconfig
make -j8
```

### 制作SD启动卡
```
sudo dd if=u-boot-tq210.bin of=/dev/sdb seek=1
sync
```
make tq2440_defconfig
make -j8
```

### 烧录
- 将u-boot-tq2440.bin从nandflash的0地址处开始写入既可
- 可以使用jlink烧录到norflash,然后在启动uboot,利用fastboot命令烧录到nandflash 
