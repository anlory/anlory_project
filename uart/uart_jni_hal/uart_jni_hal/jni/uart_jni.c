

#define LOG_TAG "uart_jnilog"
#include <android/log.h>

#include "../hal/uart_hal.h"
//__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","xxxx",...);
#include "jni.h"

static struct uart_module_t *pModule;
static struct uart_device_t *pDevice;

jint open_uart(JNIEnv *env, jclass thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","%s",__FUNCTION__);
	int ret;
	ret = hw_get_module(UART_MODULE_ID, (const struct hw_module_t * * )&pModule);
	if(ret == 0)
	{
		
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","hw_get_module  ok");
		pModule->common.methods->open(&pModule->common, NULL,(struct hw_device_t** )&pDevice);
		
	}else{
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","hw_get_module  error");
	}
	
	return 0;
}



void close_uart(JNIEnv *env, jclass thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","%s",__FUNCTION__);
	if(pDevice != NULL)
			pDevice->common.close((struct hw_device_t*)pDevice);
	return 0;
}







jstring readBuf(JNIEnv *env, jclass thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","%s",__FUNCTION__);
	char str[128] ={0};
	int ret;
	ret = pDevice->read(pDevice->fd,str,127);
	if(ret < 0){
		return NULL;
	}
	return (*env)->NewStringUTF(env,str);
}

jint writeBuf(JNIEnv *env,jclass cls,jstring str,jint len)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","%s",__FUNCTION__);
	int ret;
	const char * buf = (*env)->GetStringUTFChars(env,str,NULL);
	ret = pDevice->write(pDevice->fd,buf,len);
	(*env)->ReleaseStringUTFChars(env,str,buf);
	return ret;
}

static JNINativeMethod myMethods[] = {
	{"writeBuf","(Ljava/lang/String;I)I",(void*)writeBuf},
	{"readBuf","()Ljava/lang/String;",(void*)readBuf},
	{"openDev", "()I", (void*)open_uart},
	{"closeDev", "()V", (void *)close_uart},
};

jint JNI_OnLoad(JavaVM * jvm,void * reserved)
{
	JNIEnv *env = NULL;
	jint ret ;
	
	__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","%s",__FUNCTION__);
	
	ret = (*jvm)->GetEnv(jvm,(void * * )&env, JNI_VERSION_1_4);
	if(ret != 0)
	{
		
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","vm->GetEnv error");
		return -1;
	}

	// 实例化class对象
	jclass clz = (*env)->FindClass(env,"com/jw/uart/Uart");
	if(clz == NULL)
	{
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","vm->GetEnv error");
		return -1;
	}

	ret = (*env)->RegisterNatives(env,clz, myMethods, sizeof(myMethods)/sizeof(myMethods[0]));
	if(ret < 0)
	{
		__android_log_print(ANDROID_LOG_DEBUG,"Uart_jni","vm->GetEnv error");
		return -1;
	}
	return JNI_VERSION_1_4;
}



