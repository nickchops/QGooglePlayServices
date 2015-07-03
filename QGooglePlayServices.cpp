#include "QGooglePlayServices.h"
#include "s3eGooglePlayServices.h"
#include "QLuaHelpers.h"
#include "lua.h"

int32 SignedInCallback(void* systemData, void* userData)
{
	quick::LUA_EVENT_PREPARE("googlePlayServices");
	quick::LUA_EVENT_SET_STRING("type", "status");
	quick::LUA_EVENT_SET_BOOLEAN("signedIn", true);
	quick::LUA_EVENT_SEND();
	lua_pop(quick::g_L, 1);

	return 0;
}

int32 ErrorSignedInCallback(void* systemData, void* userData)
{
	quick::LUA_EVENT_PREPARE("googlePlayServices");
	quick::LUA_EVENT_SET_STRING("type", "status");
	quick::LUA_EVENT_SET_BOOLEAN("signedIn", false);
	quick::LUA_EVENT_SEND();
	lua_pop(quick::g_L, 1);

	return 0;
}

//TODO: achievement callbacks!

namespace googlePlayServices {

	bool isAvailable()
	{
		return s3eGooglePlayServicesAvailable();
	}

	bool init()
	{
        bool ret = false;
		
        if (s3eGooglePlayServicesAvailable())
		{
			if (s3eGooglePlayServicesInit() == S3E_RESULT_SUCCESS)
                ret = true;
            
			s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_SIGNIN_CALLBACK, SignedInCallback, NULL);
            //TODO: register for achievement callbacks
		}
        
        return ret;
	}

	void terminate()
	{
		s3eGooglePlayServicesTerminate();
	}

	void signIn()
	{
		s3eGooglePlayServicesSignIn();
	}

	void signOut()
	{
		s3eGooglePlayServicesSignOut();
	}

	bool loadCurrentPlayerLeaderboardScore(const char* id, int span, int collection)
	{
        return s3eGooglePlayServicesLoadCurrentPlayerLeaderboardScore(id, span, collection);
	}

	bool loadPlayerCenteredScores(const char* id, int span, int collection, int max_results, bool force_reload)
	{
        return s3eGooglePlayServicesLoadPlayerCenteredScores(id, span, collection, max_results, force_reload);
	}

	bool loadPlayServicesLoadTopScores(const char* id, int span, int collection, int max_results, bool force_reload)
	{
        return s3eGooglePlayServicesLoadTopScores(id, span, collection, max_results, force_reload);
	}

	bool submitScore(const char* id, int score, bool immediate)
	{
        return s3eGooglePlayServicesSubmitScore(id, score, immediate);
	}
    
	bool showAllLeaderboards()
	{
        return s3eGooglePlayServicesShowAllLeaderboards();
	}
    
	bool showLeaderboard(const char* id)
	{
        return s3eGooglePlayServicesShowLeaderboard(id);
	}
    
	bool loadAchievements()
	{
        return s3eGooglePlayServicesLoadAchievements();
	}
    
	bool unlockAchievement(const char* id, bool immediate)
	{
        return s3eGooglePlayServicesUnlockAchievement(id, immediate);
	}
    
	bool incrementAchievement(const char* id, int num_steps, bool immediate)
	{
        return s3eGooglePlayServicesIncrementAchievement(id, num_steps, immediate);
	}
    
	bool revealAchievement(const char* id, bool immediate)
	{
        return s3eGooglePlayServicesRevealAchievement(id, immediate);
	}
    
	bool showAchievements()
	{
        return s3eGooglePlayServicesShowAchievements();
	}

} //namespace googlePlayServices

	