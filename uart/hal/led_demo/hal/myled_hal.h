#ifndef __UART_HAL_H__
#define __UART_HAL_H__

#include <hardware/hardware.h>

#define LED_MODULE_ID  "uart_hal"

// �Զ���module ��������
struct led_hw_module_t{
	struct hw_module_t  common;  //���������
	// ���¾Ϳ�����չ

};

struct led_hw_device_t{
	struct hw_device_t common;  //���������
	// ���¾Ϳ�����չ
	int fd;
	int (*open)(void);
	int (*switch_dev)(int on);

};

#endif

