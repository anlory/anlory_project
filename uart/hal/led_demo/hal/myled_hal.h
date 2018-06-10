#ifndef __UART_HAL_H__
#define __UART_HAL_H__

#include <hardware/hardware.h>

#define LED_MODULE_ID  "uart_hal"

// 自定义module 对象类型
struct led_hw_module_t{
	struct hw_module_t  common;  //必须是这个
	// 以下就可以扩展

};

struct led_hw_device_t{
	struct hw_device_t common;  //必须是这个
	// 以下就可以扩展
	int fd;
	int (*open)(void);
	int (*switch_dev)(int on);

};

#endif

