LOCAL_PATH	:=$(call	my-dir)
include $(CLEAR_VARS)
LOCAL_CERTIFICATE := platform
LOCAL_MODULE	:=	AvtronsysAPanel
LOCAL_SRC_FILES :=	\
	Avtronsys/Avtronsys_Log.cpp	\
	Avtronsys/Avtronsys_EGLDisplay.cpp	\
	Avtronsys/Avtronsys_EventLoop.cpp	\
	Avtronsys/Avtronsys_ResourceHandler.cpp	\
	Avtronsys/Avtronsys_TexTureHandler.cpp	\
	Avtronsys/Avtronsys_DrawTexture.cpp	\
	Avtronsys/Avtronsys_SoundHandler.cpp	\
	Avtronsys/Avtronsys_PlaySound.cpp	\
	\
	APanel_Exit.cpp	\
	APanel_CEventLink.cpp	\
	APanel_CDrawControl.cpp	\
	APanel_CSynchronousCtrls.cpp	\
	APanel_CCtrlGroup.cpp	\
	APanel_CCtrlGroups.cpp	\
	APanel_CDrawButton.cpp	\
	APanel_CDrawDireButton.cpp	\
	APanel_CDrawCheckButton.cpp	\
	APanel_CDrawPage.cpp	\
	APanel_CPanelManage.cpp \
	\
	APanel_ActivityHandler.cpp	\
	APanel_InputHandler.cpp	\
	APanel_Drawing.cpp	\
	\
	APanel_XMLHelper.cpp	\
	APanel_md5.cpp	\
	APanel_GetMac.cpp	\
	APanel_linuxping.cpp	\
	APanel_AndroidPing.cpp	\
	test.cpp	\
	\
	APanel_Main.cpp	
	

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)	\
$(LOCAL_PATH)/libpng	\
$(LOCAL_PATH)/libxml2/include \
$(LOCAL_PATH)/libxml2/include/libxml \
$(LOCAL_PATH)/libiconv/include \
$(LOCAL_PATH)/libiconv \
$(LOCAL_PATH)/libiconv/libcharset \
$(LOCAL_PATH)/libiconv/lib \
$(LOCAL_PATH)/libiconv/libcharset/include	

LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv1_CM -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue png iconv xml2
include $(BUILD_SHARED_LIBRARY)
include $(call all-makefiles-under,$(LOCAL_PATH))
$(call import-module,android/native_app_glue)
