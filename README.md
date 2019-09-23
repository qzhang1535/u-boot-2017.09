### 说明
- 支持s3c2440从NOR和NAND启动
- 支持fastboot命令

### 导入编译环境
```
. ../build/envsetup.sh
```

### 编译
```
make tq2440_defconfig
make -j8
```

### 烧录
- 将u-boot-tq2440.bin从nandflash的0地址处开始写入既可
- 可以使用jlink烧录到norflash,然后在启动uboot,利用fastboot命令烧录到nandflash 
