LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_MODULE_TAGS := optional


LOCAL_SHARED_LIBRARIES := \
        libcutils \
	libhardware

LOCAL_MODULE:= libmyled_jni

LOCAL_C_INCLUDES += \
        $(JNI_H_INCLUDE)


LOCAL_SRC_FILES:= myled_jni.cpp

include $(BUILD_SHARED_LIBRARY)
