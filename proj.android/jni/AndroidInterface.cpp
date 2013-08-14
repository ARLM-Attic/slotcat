/**
 * @desc	AndroidInterface
 * @author	Hejiabin
 * @date	2012.09.15
 */

#include "AndroidInterface.h"
#include "string.h"
#include "jni.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"


USING_NS_CC;

#define METHOD_PATH	"com/fancyblock/slotcat/AndroidInterface"


const char *getUDID()
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"GetDeviceId",
			"()Ljava/lang/String;" ) )
	{
		CCLog( "[CallJavaMethod]: GetDeviceId" );

		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );

		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();

		return ret->m_sString.c_str();
	}

	return "";
}


/*
unsigned int getAPPVersion()
{
	JniMethodInfo t;

	jint versionCode = 0;
	if( JniHelper::getStaticMethodInfo( t, METHOD_PATH,
			"GetAppVersion",
			"()I" ) )
	{
		CCLog( "[CallJavaMethod]: GetAppVersion" );

		versionCode = (jint)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	return versionCode;
}


std::string getBundleVersion()
{
	return "1.0";
}


std::string Encode( std::string str )
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, METHOD_PATH,
				"Encode",
				"(Ljava/lang/String;)Ljava/lang/String;" ) )
	{
		CCLog( "[CallJavaMethod]: Encode" );

		jstring arg1 = t.env->NewStringUTF( str.c_str() );

		jstring str = (jstring)t.env->CallStaticObjectMethod( t.classID, t.methodID, arg1 );
		t.env->DeleteLocalRef( t.classID );
		t.env->DeleteLocalRef( arg1 );

		std:string result = string( JniHelper::jstring2string(str).c_str() );

		return result;
	}

	return "";
}


std::string Decode( std::string str )
{
	CCLog( "[Decode]: string-> %s", str.c_str() );

	// call Java interface
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
				"Decode",
				"(Ljava/lang/String;)Ljava/lang/String;" ) )
	{
		CCLog( "[CallJavaMethod]: Decode" );

		jstring arg1 = t.env->NewStringUTF( str.c_str() );

		jstring str = (jstring)t.env->CallStaticObjectMethod( t.classID, t.methodID, arg1 );
		t.env->DeleteLocalRef( t.classID );
		t.env->DeleteLocalRef( arg1 );

		std:string result = string( JniHelper::jstring2string(str).c_str() );

		CCLog( "[DecodeResult]: %s", result.c_str() );

		return result;
	}

	return "";
}


const char *getChineseSubStr(const char *str, int max, int start, int end)
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"GetSubString",
			"(Ljava/lang/String;III)Ljava/lang/String;" ) )
	{
		CCLog( "[CallJavaMethod]: getChineseSubStr" );

		jstring arg1 = t.env->NewStringUTF( str );
		jint	arg2 = max;
		jint	arg3 = start;
		jint	arg4 = end;

		jstring str = (jstring)t.env->CallStaticObjectMethod( t.classID, t.methodID, arg1, arg2, arg3, arg4 );
		t.env->DeleteLocalRef( t.classID );
		t.env->DeleteLocalRef( arg1 );

		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();

		return ret->m_sString.c_str();
	}

	return "";
}


const char *getNSUserName()
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"GetDeviceName",
			"()Ljava/lang/String;" ) )
	{
		CCLog( "[CallJavaMethod]: GetDeviceName" );

		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );

		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();

		return ret->m_sString.c_str();
	}

	return "Player";
}

const char *getDeviceLanguage()
{
	JniMethodInfo t;

	jint langCode = 0;
	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"GetDeviceLanguage",
			"()I" ) )
	{
		//CCLog( "[CallJavaMethod]: GetDeviceLanguage" );

		langCode = (jint)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	if( langCode == 1 )
	{
		return "zh-Hans";
	}

	if( langCode == 2 )
	{
		return "zh-Hant";
	}

	return "en";
}

const char *getLangSuffix()
{
	if (strcasecmp(getDeviceLanguage(), "zh-Hans") == 0)
	{
	        return "chs";
	}
	else if (strcasecmp(getDeviceLanguage(), "zh-Hant") == 0)
	{
	        return "cht";
	}
	else
	{
	        return "en";
	}
}


void setScreenLit()
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"SetScreenLit",
			"()V" ) )
	{
		CCLog( "[CallJavaMethod]: SetScreenLit" );

		t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}


void unsetScreenLit()
{
	JniMethodInfo t;

	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"UnsetScreenLit",
			"()V" ) )
	{
		CCLog( "[CallJavaMethod]: UnsetScreenLit" );

		t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}


void beginNetworkTimer()
{
	//TODO
}

const char *getPathExtension(const char *path)
{
	//TODO	never be used

	return "/";
}


int GetMarketId()
{
	JniMethodInfo t;

	jint marketId = 0;
	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"GetMaketId",
			"()I" ) )
	{
		marketId = (jint)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	CCLog( "[MarketId = %d]", marketId );

	return marketId;
}


bool NeedCreditsWall()
{
	JniMethodInfo t;

	jint needCreditsWall = 0;
	if( JniHelper::getStaticMethodInfo( t, "wxyou/shuiguoji/gamestuff",
			"IsCreditsWallExist",
			"()I" ) )
	{
		needCreditsWall = (jint)t.env->CallStaticObjectMethod(t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	if( needCreditsWall == 0 )
	{
		return false;
	}

	return true;
}
*/
