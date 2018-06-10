LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES = test_uart.c
LOCAL_MODULE := test_uart_exe


include $(BUILD_EXECUTABLE)
