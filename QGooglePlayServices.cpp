
#include "QGooglePlayServices.h"
#include "s3eGooglePlayServices.h"
#include "QLuaHelpers.h"
#include "lua.h"

using namespace quick;

namespace googlePlayServices {

//------------------------------------------------------------------------------
//C++ callbacks -> Lua events:

int32 SigninCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "status");
    LUA_EVENT_SET_BOOLEAN("signedIn", true);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 SignoutCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "status");
    LUA_EVENT_SET_BOOLEAN("signedIn", false);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementsLoadedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "achievementsLoaded");
    
    s3eGooglePlayAchievements* achs = (s3eGooglePlayAchievements*)systemData;
    
    LUA_EVENT_SET_INTEGER("count", achs->count);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 0; t < achs->count; t++)
    {
        s3eGooglePlayAchievement *ach = achs->achievements + t;
        
        LUA_EVENT_START_TABLE();
        
        LUA_EVENT_SET_STRING("id", ach->id);
        LUA_EVENT_SET_STRING("name", ach->name);
        LUA_EVENT_SET_STRING("description", ach->description);
        
        const char* achType;
        if ((s3eGooglePlayAchievementType)ach->type == s3eGooglePlayAchievementType_Standard)
            achType = "standard";
        else
            achType = "incremental";
    
        LUA_EVENT_SET_STRING("type", achType);
        
        const char* achStatus;
        if ((s3eGooglePlayAchievementStatus)ach->status == s3eGooglePlayAchievementStatus_Unlocked)
            achStatus = "unlocked";
        else if ((s3eGooglePlayAchievementStatus)ach->status == s3eGooglePlayAchievementStatus_Revealed)
            achStatus = "revealed";
        else
            achStatus = "hidden";
        
        LUA_EVENT_SET_STRING("status", achStatus);
        
        LUA_EVENT_SET_INTEGER("currentSteps", ach->currentSteps);
        LUA_EVENT_SET_INTEGER("totalSteps", ach->totalSteps);
        LUA_EVENT_SET_INTEGER("lastUpdate", ach->lastUpdate);
        
        LUA_EVENT_END_AND_INDEX_TABLE(t+1); //Lua arrays start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("achievements");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);
    
    return 0;
}

int32 AchievementUnlockedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "achievementUnlocked");
    LUA_EVENT_SET_STRING("id", (const char*)systemData); //achievement ID
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementRevealedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "achievementRevealed");
    LUA_EVENT_SET_STRING("id", (const char*)systemData); //achievement ID
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// Used by anything that sets a set of score data. Note that as we just push
// values to a stack this function doesn't need any context of where it's
// called from
void PushScoreToLuaEvent(s3eGooglePlayLeaderboardScore* sc)
{
    LUA_EVENT_SET_STRING("rank", sc->rank);
    LUA_EVENT_SET_INTEGER("score", (int)sc->score);
    LUA_EVENT_SET_STRING("displayScore", sc->displayScore);
    LUA_EVENT_SET_STRING("name", sc->name);
    LUA_EVENT_SET_STRING("playerID", sc->playerID);
    LUA_EVENT_SET_INTEGER("timestamp", sc->timestamp);
}

// This returns a single score - top score for the player on leaderboard 
// loadCurrentPlayerLeaderboardScore was called for. It doesn't tell you the
// leaderboard (sadly) so you have to assume it was from the last call to that func...
int32 PlayerScoreLoadedCallback(void* systemData, void* userData)
{
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "playerscoreLoaded");
    
    PushScoreToLuaEvent((s3eGooglePlayLeaderboardScore*)systemData);

    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

void PushLeaderboardScoresToLuaEvent(s3eGooglePlayLeaderboard* lb)
{
    LUA_EVENT_SET_STRING("id", lb->id); //this is *leaderboard*, not player, id and name
    LUA_EVENT_SET_STRING("name", lb->name);
    
    const char* scoreOrder;
    if ((s3eGooglePlayScoreOrder)lb->scoreOrder == s3eGooglePlayScoreOrder_SmallerIsBetter)
        scoreOrder = "smallerIsbetter";
    else
        scoreOrder = "largerIsBetter";
    
    LUA_EVENT_SET_STRING("scoreOrder", scoreOrder);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 0; t < lb->count; t++)
    {
        LUA_EVENT_START_TABLE();
        
        PushScoreToLuaEvent((s3eGooglePlayLeaderboardScore*)lb->scores + t);
    
        LUA_EVENT_END_AND_INDEX_TABLE(t+1); //Lua arrays start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("scores");
}

// This returns all players scores from the leaderboard that was specified when calling
// loadPlayerCenteredScores. It *does* tell you the leaderboard. If you want to get top
// player score in all leaderbaords, call loadPlayerCenteredScores for each and
// then sort the results in this callback. This is generally more useful than
// PlayerScoreLoadedCallback.
int32 PlayerLeaderboardLoadedCallback(void* systemData, void* userData)
{
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "playerLeaderboardLoaded");
    
    PushLeaderboardScoresToLuaEvent((s3eGooglePlayLeaderboard*)systemData);
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 TopScoresLeaderboardLoadedCallback(void* systemData, void* userData)
{
    //Identical logic to PlayerLeaderboardLoadedCallback but with different "type" name
    
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "topScoresLeaderboardLoaded");
    
    PushLeaderboardScoresToLuaEvent((s3eGooglePlayLeaderboard*)systemData);
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 ScoreSubmittedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "scoreSubmitted");
    LUA_EVENT_SET_STRING("id", (const char*)systemData); // leaderboard ID
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// The "error" string is set to a string version of the relevant error code
// from the C extension error enum (s3eGooglePlayServicesError). Example:
// S3E_GOOGLEPLAYSERVICES_ERROR_LOAD_ACHIEVEMENTS ->
// "error" = "S3E_GOOGLEPLAYSERVICES_ERROR_LOAD_ACHIEVEMENTS"
// TODO: This is easy and mean you can check the C++ doc for all info,
// but should we have something nice like just "loadAchievements"
// And generate as part of
// https://github.com/nickchops/MarmaladeQuickExtensionWrapper ?
int32 ErrorCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "error");
    
    s3eGooglePlayServicesErrorInfo* error = (s3eGooglePlayServicesErrorInfo*)systemData;
    LUA_EVENT_SET_STRING("error", error->errorString);
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

//------------------------------------------------------------------------------
//Functions:

bool isAvailable()
{
    return (bool)s3eGooglePlayServicesAvailable();
}

bool init()
{
    if(s3eGooglePlayServicesInit() == S3E_RESULT_ERROR)
        return false;

    //Register all callbacks here:
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_SIGNIN_CALLBACK, SigninCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENTS_LOADED_CALLBACK, AchievementsLoadedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENT_UNLOCKED_CALLBACK, AchievementUnlockedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENT_REVEALED_CALLBACK, AchievementRevealedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_PLAYER_SCORE_LOADED_CALLBACK, PlayerScoreLoadedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_PLAYER_LEADERBOARD_LOADED_CALLBACK, PlayerLeaderboardLoadedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_TOP_SCORES_LEADERBOARD_LOADED_CALLBACK, TopScoresLeaderboardLoadedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_SCORE_SUBMITTED_CALLBACK, ScoreSubmittedCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_ERROR_CALLBACK, ErrorCallback, NULL);
    s3eGooglePlayServicesRegister(S3E_GOOGLEPLAYSERVICES_SIGNOUT_CALLBACK, SignoutCallback, NULL);

    return true;
}

void terminate()
{
    //Un-register all callbacks here:
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_SIGNIN_CALLBACK, SigninCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENTS_LOADED_CALLBACK, AchievementsLoadedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENT_UNLOCKED_CALLBACK, AchievementUnlockedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_ACHIEVEMENT_REVEALED_CALLBACK, AchievementRevealedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_PLAYER_SCORE_LOADED_CALLBACK, PlayerScoreLoadedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_PLAYER_LEADERBOARD_LOADED_CALLBACK, PlayerLeaderboardLoadedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_TOP_SCORES_LEADERBOARD_LOADED_CALLBACK, TopScoresLeaderboardLoadedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_SCORE_SUBMITTED_CALLBACK, ScoreSubmittedCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_ERROR_CALLBACK, ErrorCallback);
    s3eGooglePlayServicesUnRegister(S3E_GOOGLEPLAYSERVICES_SIGNOUT_CALLBACK, SignoutCallback);

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
    return (bool)s3eGooglePlayServicesLoadCurrentPlayerLeaderboardScore(id, span, collection);
}

bool loadPlayerCenteredScores(const char* id, int span, int collection, int max_results, bool force_reload)
{
    return (bool)s3eGooglePlayServicesLoadPlayerCenteredScores(id, span, collection, max_results, force_reload);
}

bool loadTopScores(const char* id, int span, int collection, int max_results, bool force_reload)
{
    return (bool)s3eGooglePlayServicesLoadTopScores(id, span, collection, max_results, force_reload);
}

bool submitScore(const char* id, int score, bool immediate)
{
    return (bool)s3eGooglePlayServicesSubmitScore(id, score, immediate);
}

bool showAllLeaderboards()
{
    return (bool)s3eGooglePlayServicesShowAllLeaderboards();
}

bool showLeaderboard(const char* id)
{
    return (bool)s3eGooglePlayServicesShowLeaderboard(id);
}

bool loadAchievements()
{
    return (bool)s3eGooglePlayServicesLoadAchievements();
}

bool unlockAchievement(const char* id, bool immediate)
{
    return (bool)s3eGooglePlayServicesUnlockAchievement(id, immediate);
}

bool incrementAchievement(const char* id, int num_steps, bool immediate)
{
    return (bool)s3eGooglePlayServicesIncrementAchievement(id, num_steps, immediate);
}

bool revealAchievement(const char* id, bool immediate)
{
    return (bool)s3eGooglePlayServicesRevealAchievement(id, immediate);
}

bool showAchievements()
{
    return (bool)s3eGooglePlayServicesShowAchievements();
}

} //namespace googlePlayServices
