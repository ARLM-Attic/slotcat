LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := main.cpp \
                   AppDelegate.cpp \
                   AndroidInterface.cpp \
                   src/ActionShake.cpp \
                   src/ActionSwing.cpp \
                   src/ActionCoinAnimation.cpp \
                   src/ActionFlicker.cpp \
                   src/AudioManager.cpp \
                   src/BackgroundLayer.cpp \
                   src/GameLayer.cpp \
                   src/GlobalWork.cpp \
                   src/MachineSettings.cpp \
                   src/MenuLayer.cpp \
                   src/ShaderManager.cpp \
                   src/Slot.cpp \
                   src/SettingLayer.cpp \
                   src/HelpLayer.cpp \
                   src/AboutLayer.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/.          

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
