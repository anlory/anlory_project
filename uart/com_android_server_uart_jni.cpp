/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "CommModuleService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<android/log.h> 
#include <sys/ioctl.h>
#include <termios.h>

namespace android
{
  static int fd = -1;

  JNIEXPORT jint JNICALL Java_Uart_open
    (JNIEnv *env, jclass cls, jint num){
      char*uart_port[] = {"/dev/ttyHSL1","/dev/ttyHSL0"};
      struct termios cfg;

      __android_log_print(ANDROID_LOG_ERROR,"Uart_Test","openDev ");
      fd = open(uart_port[num],O_RDWR);
      if(fd < 0){
        __android_log_print(ANDROID_LOG_ERROR,"Uart_Test","openDev  Error  fd:%d",fd);
        return -1;
      }

      if (tcgetattr(fd, &cfg)) {
        close(fd);
        return -1;

      }
      //cfg.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
      //cfg.c_oflag  &= ~OPOST;   /*Output*/
	  
		cfg.c_cflag |= CLOCAL | CREAD;
		cfg.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
		cfg.c_oflag &= ~OPOST;
		cfg.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
      if (tcsetattr(fd, TCSANOW, &cfg))
      {

        close(fd);
        /* TODO: throw an exception */
        return NULL;

      }
      return 0;

    }


  /*
   * Class:     Uart
   * Method:    close
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_Uart_close
    (JNIEnv *env, jclass cls)
    {
      __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_close ");
      if(fd >= 0)
        return close(fd);
      return 0;  
    }

  /*
   * Class:     Uart
   * Method:    write
   * Signature: ([BI)I
   */
  JNIEXPORT jint JNICALL Java_Uart_write
    (JNIEnv *env, jclass cls, jbyteArray byteArr, jint byteSize)
    {
      __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_write byteSize : %d",byteSize);
      int ret;
      jbyte* str = env->GetByteArrayElements(byteArr,0);
      if(!str){
        __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_write GetByteArrayElements error ");
        return -1;
      }
      ret = write(fd,str,byteSize);
	  __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_write   RET:%d ",ret);
      if(ret < byteSize){
        __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_write  error   RET:%d ",ret);
      }
      env->ReleaseByteArrayElements(byteArr,str,byteSize);
      return ret;
    }

  /*
   * Class:     Uart
   * Method:    read
   * Signature: ([BI)I
   */
  static jint Java_Uart_read
    (JNIEnv *env, jclass cls, jbyteArray byteArr, jint byteSize)
    {
      __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_read ");
      jint ret;
      jbyte* str = env->GetByteArrayElements(byteArr,0);
      if(!str){
        __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_read GetByteArrayElements error ");
        return -1;
      }
      ret = read(fd,str,byteSize);
	  
      env->ReleaseByteArrayElements(byteArr,str,byteSize);
      __android_log_print(ANDROID_LOG_ERROR,"Uart_Jni","Java_Uart_read readSize : %d ",ret);
      return ret;
    }

  static JNINativeMethod meMethods[] = {
    {"read","([BI)I",(void *)Java_Uart_read},
    {"write","([BI)I",(void *)Java_Uart_write},
    {"close","()I",(void *)Java_Uart_close},
    {"open","(I)I",(void *)Java_Uart_open},
  };



  static JNINativeMethod method_table[] = {
    {"read","([BI)I",(void *)Java_Uart_read},
    {"write","([BI)I",(void *)Java_Uart_write},
    {"close","()I",(void *)Java_Uart_close},
    {"open","(I)I",(void *)Java_Uart_open},
  };

  int register_android_server_CommModuleService(JNIEnv *env)
  {
    return jniRegisterNativeMethods(env, "com/android/server/jw/CommService",
        method_table, NELEM(method_table));
  }

};
