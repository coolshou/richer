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

			case kLanguageChinese:
				{
					strings = Dictionary::createWithContentsOfFile("string_zh.plist");
					strings->retain();
					break;
				}

			}
		}
		String* retStr = static_cast<String*>(strings->objectForKey(strName));
		return retStr;

	}