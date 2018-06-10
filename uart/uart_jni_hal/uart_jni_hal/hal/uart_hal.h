#ifndef __MYLED_HAL_H__
#define __MYLED_HAL_H__

#include <hardware/hardware.h>

#define UART_MODULE_ID  "uart_hal"

// �Զ���module ��������
struct uart_module_t{
	struct hw_module_t  common;  //���������
	// ���¾Ϳ�����չ

};

struct uart_device_t{
	struct hw_device_t common;  //���������
	// ���¾Ϳ�����չ
	int fd;
	int (*read)(int fd,char *buf,int len);
	int (*write)(int fd,char *buf,int len);

};

#endif

