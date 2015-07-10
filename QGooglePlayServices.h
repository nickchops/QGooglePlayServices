
#ifndef __QGOOGLEPLAYSERVICES_H
#define __QGOOGLEPLAYSERVICES_H


// tolua_begin
namespace googlePlayServices {
    bool isAvailable();
    bool init();
    void terminate();
    void signIn();
    void signOut();
    bool loadCurrentPlayerLeaderboardScore(const char* id, int span, int collection);
    bool loadPlayerCenteredScores(const char* id, int span, int collection, int max_results, bool force_reload);
    bool loadPlayServicesLoadTopScores(const char* id, int span, int collection, int max_results, bool force_reload);
    bool submitScore(const char* id, int score, bool immediate);
    bool showAllLeaderboards();
    bool showLeaderboard(const char* id);
    bool loadAchievements();
    bool unlockAchievement(const char* id, bool immediate);
    bool incrementAchievement(const char* id, int num_steps, bool immediate);
    bool revealAchievement(const char* id, bool immediate);
    bool showAchievements();
}

// tolua_end

#endif // QGOOGLEPLAYSERVICES_H
