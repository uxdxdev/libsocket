LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libsocket_shared

LOCAL_MODULE_FILENAME := libsocket

LOCAL_SRC_FILES :=	$(LOCAL_PATH)/src/socket.cc

LOCAL_EXPORT_C_INCLUDES :=	$(LOCAL_PATH)/include

LOCAL_C_INCLUDES :=	$(LOCAL_PATH)/include					 

include $(BUILD_SHARED_LIBRARY)