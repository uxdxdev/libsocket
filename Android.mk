LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := socket_shared

LOCAL_MODULE_FILENAME := libsocket

LOCAL_SRC_FILES :=	$(LOCAL_PATH)/external/libsocket/src/socket.c

LOCAL_EXPORT_C_INCLUDES :=	$(LOCAL_PATH)/external											

LOCAL_C_INCLUDES :=	$(LOCAL_PATH)/external/libsocket					 

include $(BUILD_SHARED_LIBRARY)