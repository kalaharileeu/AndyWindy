LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#LOCAL_MODULE    := libFreeImage
#LOCAL_SRC_FILES := ../../../../Libs.Android/libFreeImage.$(TARGET_ARCH_ABI).a
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := NativeLib

SDL_PATH := ../SDL
#added SDL2_image and SDL2_ttf as some of SDL external libraries
#MiniSDL is the source code generated in VS2015, this get included in here for android
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/../SDL2_image \
	$(LOCAL_PATH)/../SDL2_ttf \
	$(LOCAL_PATH)../../SDL/src \
	$(LOCAL_PATH)/../../MiniSDL \
	$(LOCAL_PATH)/../../ \
	$(LOCAL_PATH)/../ \
#	$(LOCAL_PATH)/../../Engine/Core \
#	$(LOCAL_PATH)../../../../../Chapter3/2_AsyncTaskQueues \
#	$(LOCAL_PATH)../../../../../Chapter4/1_ArchiveFileAccess/src \

# Engine
LOCAL_SRC_FILES := ../SDL_android_main.c \
#	../../../../Chapter3/2_AsyncTaskQueues/IntrusivePtr.cpp \
#	../../../../Chapter4/1_ArchiveFileAccess/src/Archive.cpp \
#	../../../../Chapter4/1_ArchiveFileAccess/src/FileSystem.cpp \
#	../../../../Chapter4/1_ArchiveFileAccess/src/libcompress.c \
#	../../Engine/Core/Library.cpp \
#	../../Engine/Core/VecMath.cpp \
#	../../Engine/Graphics/Bitmap.cpp \
#	../../Engine/Graphics/FI_Utils.cpp \
#	../../Engine/Graphics/Geometry.cpp \
#	../../Engine/LGL/GLClasses.cpp \
#	../../Engine/LGL/LGL.cpp \
#	../../Engine/SDLWindow.cpp \

# All the files below were created in VS2015 for window app, no used here for android
# Application: add += some more .cpp files
LOCAL_SRC_FILES += \
	../../MiniSDL/main.cpp \
	../../MiniSDL/Game.cpp \
	../../MiniSDL/StateMachine.cpp \
	../../MiniSDL/InputHandler.cpp \
	../../MiniSDL/TextureManager.cpp \
	../../MiniSDL/GeneralParameters.cpp \
	../../MiniSDL/MovingObject.cpp \
	../../MiniSDL/PlayState.cpp \
	../../MiniSDL/MainMenuState.cpp \
	../../MiniSDL/MenuButton.cpp \
	../../MiniSDL/StateParser.cpp \
	../../MiniSDL/StaticObject.cpp \
	../../MiniSDL/DoneState.cpp \
	../../MiniSDL/YelloBlue.cpp \
	../../MiniSDL/NumberDraw.cpp \
	../../MiniSDL/Texter.cpp \
	../../MiniSDL/SumState.cpp
#Cornel add SDL2 libraries and external libraries
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf
#LOCAL_STATIC_LIBRARIES += FreeImage
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
LOCAL_CPPFLAGS = -std=c++11
include $(BUILD_SHARED_LIBRARY)
