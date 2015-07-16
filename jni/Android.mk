LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/GameBaseScene.cpp \
				   ../../Classes/Item.cpp \
				   ../../Classes/Item_ball.cpp \
				   ../../Classes/Item_crab.cpp \
				   ../../Classes/Item_emergency.cpp \
				   ../../Classes/Item_fog.cpp \
				   ../../Classes/Item_strength_up.cpp \
				   ../../Classes/Item_stretcher.cpp \
				   ../../Classes/LanguageString.cpp \
				   ../../Classes/LotteryCard.cpp \
				   ../../Classes/MapChooseScene.cpp \
				   ../../Classes/MenuScene.cpp \
				   ../../Classes/RicherGameController.cpp \
				   ../../Classes/RicherPlayer.cpp \
				   ../../Classes/RouteNavigation.cpp \
				   ../../Classes/SeaScene.cpp \
				   ../../Classes/BeachScene.cpp \
				   ../../Classes/SnowScene.cpp \
				   ../../Classes/SplashScene.cpp \
				   ../../Classes/Util.cpp \
				   ../../Classes/PopupLayer/CocosToast.cpp \
				   ../../Classes/PopupLayer/PopupLayer.cpp \
				   ../../Classes/skill/SkillCard.cpp \
				   ../../Classes/stock/LineChart.cpp \
				   ../../Classes/stock/Stock.cpp \
				   ../../Classes/stock/StockCellCard.cpp \
				   ../../Classes/stock/VisibleRect.cpp \
				   ../../Classes/lottery/EllipseBy.cpp



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					 $(LOCAL_PATH)/../../Classes/PopupLayer \
					 $(LOCAL_PATH)/../../Classes/skill \
					 $(LOCAL_PATH)/../../Classes/stock \
					 $(LOCAL_PATH)/../../Classes/lottery 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
 
# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
 LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
