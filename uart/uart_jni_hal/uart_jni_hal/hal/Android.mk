LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := uart_hal.c

LOCAL_MODULE_TAGS := optional
#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_SHARED_LIBRARIES := libcutils \
	libhardware

LOCAL_MODULE := uart_hal.default 

include $(BUILD_SHARED_LIBRARY)
