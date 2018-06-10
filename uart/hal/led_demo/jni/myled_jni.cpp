

#define LOG_TAG "myled_jnilog"
#include <utils/Log.h>

#include "../hal/myled_hal.h"

#include "jni.h"

static struct led_hw_module_t *pModule;
static struct led_hw_device_t *pDevice;

jint open_led(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	int ret;
	ret = hw_get_module(LED_MODULE_ID, (const struct hw_module_t * * )&pModule);
	if(ret == 0)
	{
		LOGD("hw_get_module  ok\n");
		pModule->common.methods->open(&pModule->common, NULL,
            (struct hw_device_t** )&pDevice);

		if(pDevice != NULL)
			pDevice->open();
		
	}else{
		LOGD("hw_get_module  error\n");
	}
	
	return 0;
}

jint led_on(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	if(pDevice != NULL)
			pDevice->switch_dev(1);
	return 0;
}
jint led_off(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	if(pDevice != NULL)
			pDevice->switch_dev(0);
	return 0;
}

jint close_led(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	if(pDevice != NULL)
			pDevice->common.close((struct hw_device_t*)pDevice);
	return 0;
}

jint addd_num(JNIEnv *env, jobject thiz, jint a, jint b)
{
	LOGD("-----%s----\n", __FUNCTION__);
	return a+b;
}

jstring jni_get_string(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	// ��char*ת����jstring
	return env->NewStringUTF("^_^ hello java");
}
void jni_set_string(JNIEnv *env, jobject thiz, jstring str)
{
	LOGD("-----%s----\n", __FUNCTION__);
	const char *tmp;
	// ��jstringת����char *
	tmp = env->GetStringUTFChars(str, NULL);
	LOGD("tmp = %s\n", tmp);
	//�ͷ�ת�������з���Ŀռ�
	env->ReleaseStringUTFChars(str, tmp);
}

jobject jni_get_student(JNIEnv *env, jobject thiz)
{
	LOGD("-----%s----\n", __FUNCTION__);
	// ʵ����һ��jclass���󣬶�Ӧ�ڲ����Ķ�������
	jclass  stuCls = env->FindClass("com/hq/bean/Student");
	if(stuCls == NULL)
	{
		LOGE("env->FindClass error\n");
		return NULL;
	}
	//��ȡjclass�и������Ժͷ�����id����
	jfieldID  nameID = 	env->GetFieldID(stuCls,"name","Ljava/lang/String;");
	jfieldID  ageID = env->GetFieldID(stuCls, "age", "I");
	jfieldID  heightID = env->GetFieldID(stuCls,"height", "D");
	// ���췽����id����
	jmethodID  constructorID =  env->GetMethodID(stuCls, "<init>", "()V");
	jmethodID  setInfoID = env->GetMethodID(stuCls,"setStudentInfo","(Ljava/lang/String;ID)V");

	
	// ʵ����һ��jobject����
	jobject stuObj = env->NewObject(stuCls,constructorID);

#if 0
	//���ö����еĸ�������
	env->SetObjectField(stuObj,nameID, env->NewStringUTF("peter"));	
	env->SetObjectField(stuObj,ageID,59);
	env->SetObjectField(stuObj,heightID, 1.99);
#else
	//���ö����и�������
	env->CallVoidMethod(stuObj, setInfoID, env->NewStringUTF("james"), 23, 1.89);
#endif
	return stuObj;
	
}

static JNINativeMethod myMethods[] = {
	{"openDev", "()I", (void*)open_led},
	{"devOn", "()I", (void *)led_on},
	{"devOff", "()I", (void *)led_off},
	{"closeDev", "()I", (void *)close_led},
	{"addNum", "(II)I", (void *)addd_num},
	{"getString", "()Ljava/lang/String;", (void *)jni_get_string},
	{"setString", "(Ljava/lang/String;)V", (void *)jni_set_string},
	{"getStudent", "()Lcom/hq/bean/Student;", (void *)jni_get_student},
};

jint JNI_OnLoad(JavaVM * vm,void * reserved)
{
	JNIEnv *env = NULL;
	jint ret ;
	
	LOGD("JNI_OnLoad\n");
	
	ret = vm->GetEnv((void * * )&env, JNI_VERSION_1_4);
	if(ret != 0)
	{
		LOGE("vm->GetEnv error\n");
		return -1;
	}

	// ʵ����class����
	jclass clz = env->FindClass("com/example/ledjnitest/LedActivity");
	if(clz == NULL)
	{
		LOGE("env->FindClass error\n");
		return -1;
	}

	ret = env->RegisterNatives(clz, myMethods, sizeof(myMethods)/sizeof(myMethods[0]));
	if(ret < 0)
	{
		LOGE("env->RegisterNatives error\n");
		return -1;
	}
	return JNI_VERSION_1_4;
}



