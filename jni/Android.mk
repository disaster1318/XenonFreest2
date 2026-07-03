LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := xenon
LOCAL_SRC_FILES := src/main.cpp \
                   src/menu.cpp \
                   src/esp.cpp \
                   src/features.cpp \
                   src/world.cpp \
                   src/config.cpp \
                   src/utils.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src
LOCAL_CPP_FEATURES := exceptions rtti
LOCAL_CFLAGS := -O2 -fvisibility=hidden -fPIC
LOCAL_LDFLAGS := -llog -landroid -lEGL -lGLESv2 -lz

include $(BUILD_SHARED_LIBRARY)
