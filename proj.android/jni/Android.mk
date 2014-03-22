LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
			../../Classes/ActionSprite.cpp \
			../../Classes/AppDelegate.cpp \
			../../Classes/Bomb.cpp \
			../../Classes/GameFaildLayer.cpp \
			../../Classes/GameSceneLayer.cpp \
			../../Classes/GameVictoryLayer.cpp \
			../../Classes/GLES-Render.cpp \
			../../Classes/HelloWorldScene.cpp \
			../../Classes/Hero.cpp \
			../../Classes/logo.cpp \
			../../Classes/MainScene.cpp \
			../../Classes/MyObject.cpp \
			../../Classes/MySprite.cpp \
			../../Classes/SceneManager.cpp \
			../../Classes/SelectLevelScene.cpp \
			../../Classes/global/Global.cpp \
			../../Classes/global/Setting.cpp \
			../../Classes/tools/HCSVFile.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/global \
					$(LOCAL_PATH)/../../Classes/tools

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

