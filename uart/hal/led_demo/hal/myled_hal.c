


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define LOG_TAG "myled_hallog"
#include <utils/Log.h>


#include "myled_hal.h"

static int fd;
int led_dev_close(struct hw_device_t* device)
{
	LOGD("-----%s----\n", __FUNCTION__);
	if(device != NULL)
	{
		free(device);
	}
	close(fd);

	return 0;
}

int led_dev_open(void)
{
	LOGD("-----%s----\n", __FUNCTION__);
	fd = open("/dev/led1", O_RDWR);
	if(fd<0)
	{
		LOGE("open : %s\n", strerror(errno));
		return -1;
	}
	return 0;
	
}

int led_switch_dev(int on)
{
	LOGD("-----%s----\n", __FUNCTION__);
	int ret;
	int val;
	if(on)
	{
		val = 1;
		ret = write(fd, &val, 4);
		if(ret < 0)
		{
			LOGE("write : %s\n", strerror(errno));
			return -1;
		}
	}else
	{
		val = 0;
		ret = write(fd, &val, 4);
		if(ret < 0)
		{
			LOGE("write : %s\n", strerror(errno));
			return -1;
		}
	}

	return 0;
}

int led_module_open(const struct hw_module_t* module, const char* id,
		   struct hw_device_t** device)
{
	LOGD("-----%s----\n", __FUNCTION__);
	// 构建一个device对象
	struct led_hw_device_t  *led_dev;
	led_dev = (struct led_hw_device_t  *)malloc(sizeof(struct led_hw_device_t));
	if(led_dev == NULL)
	{
		LOGE("malloc error");
		return -1;
	}
	led_dev->common.tag = HARDWARE_DEVICE_TAG,
	led_dev->common.version = 1;
	led_dev->common.module = module;
	led_dev->common.close = led_dev_close;

	led_dev->open = led_dev_open;
	led_dev->switch_dev = led_switch_dev;
	// 将led_dev交给jni层
	*device = (struct hw_device_t*)led_dev;
	return 0;	
}

struct hw_module_methods_t led_methods = {
	open : led_module_open,

};



// 实例化一个module对象,名字一定要是HMI
// p->common.methods->open();
struct led_hw_module_t  HMI = {  
	common : {
		tag : HARDWARE_MODULE_TAG,
		version_major : 1,
		version_minor : 0,
		id : LED_MODULE_ID,
		name : "this is a simple led hal",
		author : "big brother",
		methods : &led_methods,
 	},

};

