1.每一帧图片数据在badapple.7z压缩包里
2.bmp_read_put.c 实现读取badapple每一帧图片并将所有图片数据输出到bmp_badapple_data.bin
3.output_bmp.c 实现控制台用01代表黑白输出bmp_badapple_data.bin中的数据 可以实现播放效果
但是貌似速度很慢
4.badapple_serial_output.c 实现电脑串口COM4向单片机发送数据，实现oled播放效果
5.文件夹stm32f103c8t6_badapple中存放的是板子的程序 对应二进制烧录文件在OBJ文件夹下
6.因为没有sd卡 板子储存不了太大数据 最终用电脑实现发送数据