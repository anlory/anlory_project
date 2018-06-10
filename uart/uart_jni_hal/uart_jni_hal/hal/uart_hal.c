#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define LOG_TAG "myuart_hallog"
#include <android/log.h> 

//__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","xxxx",...);

#include "uart_hal.h"

static int fd;
int uart_dev_close(struct hw_device_t* device)
{

	__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","%s",__FUNCTION__);
	struct uart_device_t* dev = (struct uart_device_t *) device;
	if(dev)
	{
		close(dev->fd);
		free(dev);
	}

	return 0;
}





static int uart_dev_read(int fd,char *buf, int len)
{
	int ret ;
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","%s",__FUNCTION__);
	ret =   read(fd,buf,len);
	return ret;
}
static int uart_dev_write(int fd,char *buf, int len)
{
	int ret ;
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","%s",__FUNCTION__);
	ret =   write(fd,buf,len);
	return ret;	
}

int uart_module_open(const struct hw_module_t* module, const char* id,
		   struct hw_device_t** device)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","%s",__FUNCTION__);
	// 构建一个device对象
	struct uart_device_t  *uart_dev;
	uart_dev = (struct uart_device_t  *)malloc(sizeof(struct uart_device_t));
	if(uart_dev == NULL)
	{
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_hal","error:uart_module_open");
		return -1;
	}
	uart_dev->common.tag = HARDWARE_DEVICE_TAG,
	uart_dev->common.version = 1;
	uart_dev->common.module = module;
	uart_dev->common.close = uart_dev_close;

	uart_dev->read = uart_dev_read;
	uart_dev->write = uart_dev_write;
	
	uart_dev->fd = -1;
	uart_dev->fd = open("/dev/ttyHSL1",O_RDWR);
	if(uart_dev->fd == -1){
		free(uart_dev);
		return -EFAULT;
	}
	
	// 将uart_dev交给jni层
	*device = (struct hw_device_t*)uart_dev;
	return 0;
}

struct hw_module_methods_t uart_methods = {
	.open = uart_module_open,

};



// 实例化一个module对象,名字一定要是HMI
// p->common.methods->open();
struct uart_module_t  HMI = {  
	common : {
		tag : HARDWARE_MODULE_TAG,
		version_major : 1,
		version_minor : 0,
		id : UART_MODULE_ID,
		name : "this is a simple uart hal",
		author : "big brother",
		methods : &uart_methods,
 	},

};

