
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
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    /*
    s3eGooglePlayAchievements* achs = (s3eGooglePlayAchievements*)systemData;
    s3eDebugTracePrintf(">>>>>>>>>>> AchievementsLoadedCallback, count = %d", achs->count);
    AppendMessage("Achievements Loaded:");
    for (int t = 0; t < achs->count; t++)
    {
        s3eGooglePlayAchievement *ach = achs->achievements + t;
        s3eDebugTracePrintf("-----------------------------------");
        s3eDebugTracePrintf("\tid = %s", ach->id);
        s3eDebugTracePrintf("\tname = %s", ach->name);
        s3eDebugTracePrintf("\tdescription = %s", ach->description);
        s3eDebugTracePrintf("\ttype = %d", ach->type);
        s3eDebugTracePrintf("\tstatus = %d", ach->status);
        s3eDebugTracePrintf("\tcurrentSteps = %d", ach->currentSteps);
        s3eDebugTracePrintf("\ttotalSteps = %d", ach->totalSteps);
        s3eDebugTracePrintf("\tlastUpdate = %d", ach->lastUpdate);
    }
    */
    
    return 0;
}

int32 AchievementUnlockedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "achievementUnlocked");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementRevealedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "achievementRevealed");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 PlayerScoreLoadedCallback(void* systemData, void* userData)
{
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "playerscoreLoaded");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    /*
    s3eGooglePlayLeaderboardScore* sc = (s3eGooglePlayLeaderboardScore*)systemData;
    s3eDebugTracePrintf(">>>>>>>>>>> PlayerScoreLoadedCallback");
    AppendMessage("Player Score Loaded");
    s3eDebugTracePrintf("\trank = %s", sc->rank);
    s3eDebugTracePrintf("\tscore = %d", (int)sc->score);
    s3eDebugTracePrintf("\tdisplayScore = %s", sc->displayScore);
    s3eDebugTracePrintf("\tname = %s", sc->name);
    s3eDebugTracePrintf("\tplayerID = %s", sc->playerID);
    s3eDebugTracePrintf("\ttimestamp = %d", sc->timestamp);
    */

    return 0;
}

int32 PlayerLeaderboardLoadedCallback(void* systemData, void* userData)
{
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "playerLeaderboardLoaded");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    /*
    s3eGooglePlayLeaderboard* lb = (s3eGooglePlayLeaderboard*)systemData;
    s3eDebugTracePrintf(">>>>>>>>>>> PlayerleaderboardLoadedCallback, count = %d", lb->count);
    AppendMessage("Player Leaderboard Loaded");
    s3eDebugTracePrintf("\tid = %s", lb->id);
    s3eDebugTracePrintf("\tname = %s", lb->name);
    s3eDebugTracePrintf("\tscoreOrder = %d", lb->scoreOrder);
    for (int t = 0; t < lb->count; t++)
    {
        s3eGooglePlayLeaderboardScore* sc = lb->scores + t;
        s3eDebugTracePrintf("-----------------------------------");
        s3eDebugTracePrintf("\trank = %s", sc->rank);
        s3eDebugTracePrintf("\tscore = %d", (int)sc->score);
        s3eDebugTracePrintf("\tdisplayScore = %s", sc->displayScore);
        s3eDebugTracePrintf("\tname = %s", sc->name);
        s3eDebugTracePrintf("\tplayerID = %s", sc->playerID);
        s3eDebugTracePrintf("\ttimestamp = %d", sc->timestamp);
    }
    */

    return 0;
}

int32 TopScoresLeaderboardLoadedCallback(void* systemData, void* userData)
{
	LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "topScoresLeaderboardLoaded");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    /*
    s3eGooglePlayLeaderboard* lb = (s3eGooglePlayLeaderboard*)systemData;
    s3eDebugTracePrintf(">>>>>>>>>>> TopScoresLeaderboardLoadedCallback, count = %d", lb->count);
    AppendMessage("Top Scores Leaderboard Loaded");
    s3eDebugTracePrintf("\tid = %s", lb->id);
    s3eDebugTracePrintf("\tname = %s", lb->name);
    s3eDebugTracePrintf("\tscoreOrder = %d", lb->scoreOrder);
    for (int t = 0; t < lb->count; t++)
    {
        s3eGooglePlayLeaderboardScore* sc = lb->scores + t;
        s3eDebugTracePrintf("-----------------------------------");
        s3eDebugTracePrintf("\trank = %s", sc->rank);
        s3eDebugTracePrintf("\tscore = %d", (int)sc->score);
        s3eDebugTracePrintf("\tdisplayScore = %s", sc->displayScore);
        s3eDebugTracePrintf("\tname = %s", sc->name);
        s3eDebugTracePrintf("\tplayerID = %s", sc->playerID);
        s3eDebugTracePrintf("\ttimestamp = %d", sc->timestamp);
    }
    */

    return 0;
}

int32 ScoreSubmittedCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "scoreSubmitted");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 ErrorCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("googlePlayServices");
    LUA_EVENT_SET_STRING("type", "error");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
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
