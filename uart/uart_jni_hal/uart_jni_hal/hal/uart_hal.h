#ifndef __MYLED_HAL_H__
#define __MYLED_HAL_H__

#include <hardware/hardware.h>

#define UART_MODULE_ID  "uart_hal"

// 自定义module 对象类型
struct uart_module_t{
	struct hw_module_t  common;  //必须是这个
	// 以下就可以扩展

};

struct uart_device_t{
	struct hw_device_t common;  //必须是这个
	// 以下就可以扩展
	int fd;
	int (*read)(int fd,char *buf,int len);
	int (*write)(int fd,char *buf,int len);

};

#endif

