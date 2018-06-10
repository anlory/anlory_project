LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_MODULE_TAGS := optional


LOCAL_SHARED_LIBRARIES := \
        libcutils \
	libhardware

LOCAL_MODULE:= libuart_jni

LOCAL_C_INCLUDES += \
        $(JNI_H_INCLUDE)


LOCAL_SRC_FILES:= uart_jni.c

include $(BUILD_SHARED_LIBRARY)
