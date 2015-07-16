#include "LanguageString.h"

LanguageString* LanguageString::instance;
Dictionary * LanguageString::strings;

LanguageString::LanguageString()
{
}


LanguageString::~LanguageString()
{
}

LanguageString * LanguageString::getInstance()
{
	if(instance == NULL)
	{
		instance = new LanguageString();
	}
	
	return instance;
}

String* LanguageString::getLanguageString(const char* strName)
	{
		LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();

		if(strings == NULL)
		{
			switch (currentLanguageType)
			{
			case kLanguageEnglish:
				{
					strings = Dictionary::createWithContentsOfFile("string_en.plist");
					strings->retain();
					break;
				}
//http://stackoverflow.com/questions/10697436/cocos2d-x-localization-simplified-traditional-chinese
//For Android , modify cocos2d/cocos/platform/android/CCApplication-android.cpp
//For iOS     , modify cocos2d/cocos/platform/ios/CCApplication-ios.mm
//For Linux   , modify cocos2d/cocos/platform/linux/CCApplication-linux.cpp
			case kLanguageChinese:
				{
					strings = Dictionary::createWithContentsOfFile("string_zh_TW.plist");
					strings->retain();
					break;
				}

			}
		}
		String* retStr = static_cast<String*>(strings->objectForKey(strName));
		return retStr;

	}
