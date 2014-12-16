LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE :=native
LOCAL_SRC_FILES := \
android_native_app_glue.c\
ApplicationAndroid.cpp\
ResourceManagerAndroid.cpp

LOCAL_CFLAGS := -std=gnu++11
LOCAL_CPPFLAGS := -std=gnu++0x -std=c++11 -DANDROID_GAME=1
LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2

include $(BUILD_SHARED_LIBRARY)