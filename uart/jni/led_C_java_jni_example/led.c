#include "led.h"
#include <string.h>

/*
 * Class:     led
 * Method:    intMethod
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_led_intMethod
  (JNIEnv *env, jobject obj, jint  num)
{
	return num*num;
}

/*
 * Class:     led
 * Method:    booleanMethod
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_led_booleanMethod
  (JNIEnv *env, jobject obj, jboolean boolean)
{
	return !boolean;
}

/*
 * Class:     led
 * Method:    stringMethod
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_led_stringMethod
  (JNIEnv * env, jobject obj, jstring string)
{
	const char* str = (*env)->GetStringUTFChars(env,string,0);
	char cap[128];
	strcpy(cap,str);
	(*env)->ReleaseStringUTFChars(env,string,0);
	return (*env)->NewStringUTF(env,cap);
}


/*
 * Class:     led
 * Method:    intArrayMethod
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_led_intArrayMethod
  (JNIEnv *env, jobject obj, jintArray array)
{
	int i,sum = 0;
	jsize len = (*env)->GetArrayLength(env,array);
	jint *body = (*env)->GetIntArrayElements(env,array,0);
	for( i = 0; i < len; i++)
	{
		sum +=body[i];
		
	}
	(*env)->ReleaseIntArrayElements(env,array,body,0);
	return sum;
}
