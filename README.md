### 说明
- 该uboot在tq210板卡上测试通过
- 同时支持SD启动和nand启动
- 支持fastboot功能

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
