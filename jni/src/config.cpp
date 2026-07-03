#include "config.h"
#include "utils.h"
#include "esp.h"
#include "features.h"
#include "world.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#define CONFIG_FILE "/sdcard/Xenon/config.cfg"

void saveConfig() {
    FILE* file = fopen(CONFIG_FILE, "w");
    if (!file) return;
    fprintf(file, "espEnabled=%d\n", espEnabled);
    fprintf(file, "boxEnabled=%d\n", boxEnabled);
    fprintf(file, "snapLineEnabled=%d\n", snapLineEnabled);
    fprintf(file, "skeletonEnabled=%d\n", skeletonEnabled);
    fprintf(file, "healthBarEnabled=%d\n", healthBarEnabled);
    fprintf(file, "nicknameEnabled=%d\n", nicknameEnabled);
    fprintf(file, "weaponEnabled=%d\n", weaponEnabled);
    fprintf(file, "avatarEnabled=%d\n", avatarEnabled);
    fprintf(file, "chamsEnabled=%d\n", chamsEnabled);
    fprintf(file, "glassChams=%d\n", glassChams);
    fprintf(file, "chamsIntensity=%f\n", chamsIntensity);
    fprintf(file, "wallhackEnabled=%d\n", wallhackEnabled);
    fprintf(file, "distanceEnabled=%d\n", distanceEnabled);
    fprintf(file, "headDotEnabled=%d\n", headDotEnabled);
    fprintf(file, "tracersEnabled=%d\n", tracersEnabled);
    fprintf(file, "soundEspEnabled=%d\n", soundEspEnabled);
    fprintf(file, "fogEnabled=%d\n", fogEnabled);
    fprintf(file, "skyColor=%f,%f,%f\n", skyColor[0], skyColor[1], skyColor[2]);
    fprintf(file, "fogColor=%f,%f,%f\n", fogColor[0], fogColor[1], fogColor[2]);
    fprintf(file, "worldColor=%f,%f,%f\n", worldColor[0], worldColor[1], worldColor[2]);
    fprintf(file, "timeMode=%d\n", timeMode);
    fprintf(file, "noRecoilEnabled=%d\n", noRecoilEnabled);
    fprintf(file, "headshotSoundEnabled=%d\n", headshotSoundEnabled);
    fprintf(file, "antiAimEnabled=%d\n", antiAimEnabled);
    fprintf(file, "antiAimMode=%d\n", antiAimMode);
    fprintf(file, "spinSpeed=%f\n", spinSpeed);
    fprintf(file, "triggerbotEnabled=%d\n", triggerbotEnabled);
    fprintf(file, "triggerbotDelay=%f\n", triggerbotDelay);
    fprintf(file, "antiAFKEnabled=%d\n", antiAFKEnabled);
    fprintf(file, "screenshotCleanerEnabled=%d\n", screenshotCleanerEnabled);
    fprintf(file, "autoWallbangEnabled=%d\n", autoWallbangEnabled);
    fprintf(file, "noFlashEnabled=%d\n", noFlashEnabled);
    fprintf(file, "radarHackEnabled=%d\n", radarHackEnabled);
    fprintf(file, "menuScale=%f\n", getMenuScale());
    fprintf(file, "tabPosition=%d\n", getTabPosition());
    fclose(file);
}

void loadConfig() {
    FILE* file = fopen(CONFIG_FILE, "r");
    if (!file) return;
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        char key[64];
        char value[64];
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            if (strcmp(key, "espEnabled") == 0) espEnabled = atoi(value);
            else if (strcmp(key, "boxEnabled") == 0) boxEnabled = atoi(value);
            else if (strcmp(key, "snapLineEnabled") == 0) snapLineEnabled = atoi(value);
            else if (strcmp(key, "skeletonEnabled") == 0) skeletonEnabled = atoi(value);
            else if (strcmp(key, "healthBarEnabled") == 0) healthBarEnabled = atoi(value);
            else if (strcmp(key, "nicknameEnabled") == 0) nicknameEnabled = atoi(value);
            else if (strcmp(key, "weaponEnabled") == 0) weaponEnabled = atoi(value);
            else if (strcmp(key, "avatarEnabled") == 0) avatarEnabled = atoi(value);
            else if (strcmp(key, "chamsEnabled") == 0) chamsEnabled = atoi(value);
            else if (strcmp(key, "glassChams") == 0) glassChams = atoi(value);
            else if (strcmp(key, "chamsIntensity") == 0) chamsIntensity = atof(value);
            else if (strcmp(key, "wallhackEnabled") == 0) wallhackEnabled = atoi(value);
            else if (strcmp(key, "distanceEnabled") == 0) distanceEnabled = atoi(value);
            else if (strcmp(key, "headDotEnabled") == 0) headDotEnabled = atoi(value);
            else if (strcmp(key, "tracersEnabled") == 0) tracersEnabled = atoi(value);
            else if (strcmp(key, "soundEspEnabled") == 0) soundEspEnabled = atoi(value);
            else if (strcmp(key, "fogEnabled") == 0) fogEnabled = atoi(value);
            else if (strcmp(key, "skyColor") == 0) sscanf(value, "%f,%f,%f", &skyColor[0], &skyColor[1], &skyColor[2]);
            else if (strcmp(key, "fogColor") == 0) sscanf(value, "%f,%f,%f", &fogColor[0], &fogColor[1], &fogColor[2]);
            else if (strcmp(key, "worldColor") == 0) sscanf(value, "%f,%f,%f", &worldColor[0], &worldColor[1], &worldColor[2]);
            else if (strcmp(key, "timeMode") == 0) timeMode = atoi(value);
            else if (strcmp(key, "noRecoilEnabled") == 0) noRecoilEnabled = atoi(value);
            else if (strcmp(key, "headshotSoundEnabled") == 0) headshotSoundEnabled = atoi(value);
            else if (strcmp(key, "antiAimEnabled") == 0) antiAimEnabled = atoi(value);
            else if (strcmp(key, "antiAimMode") == 0) antiAimMode = atoi(value);
            else if (strcmp(key, "spinSpeed") == 0) spinSpeed = atof(value);
            else if (strcmp(key, "triggerbotEnabled") == 0) triggerbotEnabled = atoi(value);
            else if (strcmp(key, "triggerbotDelay") == 0) triggerbotDelay = atof(value);
            else if (strcmp(key, "antiAFKEnabled") == 0) antiAFKEnabled = atoi(value);
            else if (strcmp(key, "screenshotCleanerEnabled") == 0) screenshotCleanerEnabled = atoi(value);
            else if (strcmp(key, "autoWallbangEnabled") == 0) autoWallbangEnabled = atoi(value);
            else if (strcmp(key, "noFlashEnabled") == 0) noFlashEnabled = atoi(value);
            else if (strcmp(key, "radarHackEnabled") == 0) radarHackEnabled = atoi(value);
            else if (strcmp(key, "menuScale") == 0) setMenuScale(atof(value));
            else if (strcmp(key, "tabPosition") == 0) setTabPosition(atoi(value));
        }
    }
    fclose(file);
}

void resetConfig() {
    espEnabled = true;
    boxEnabled = true;
    snapLineEnabled = false;
    skeletonEnabled = false;
    healthBarEnabled = true;
    nicknameEnabled = true;
    weaponEnabled = true;
    avatarEnabled = false;
    chamsEnabled = true;
    glassChams = false;
    chamsIntensity = 2.6f;
    wallhackEnabled = true;
    distanceEnabled = false;
    headDotEnabled = false;
    tracersEnabled = false;
    soundEspEnabled = false;
    fogEnabled = false;
    skyColor[0] = 0.5f; skyColor[1] = 0.7f; skyColor[2] = 1.0f;
    fogColor[0] = 0.5f; fogColor[1] = 0.5f; fogColor[2] = 0.5f;
    worldColor[0] = 1.0f; worldColor[1] = 1.0f; worldColor[2] = 1.0f;
    timeMode = 0;
    noRecoilEnabled = false;
    headshotSoundEnabled = false;
    antiAimEnabled = false;
    antiAimMode = 0;
    spinSpeed = 2.0f;
    triggerbotEnabled = false;
    triggerbotDelay = 0.1f;
    antiAFKEnabled = false;
    screenshotCleanerEnabled = false;
    autoWallbangEnabled = false;
    noFlashEnabled = false;
    radarHackEnabled = false;
    setMenuScale(0.7f);
    setTabPosition(0);
}

void loadExternalConfig(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) return;
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        char key[64];
        char value[64];
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            if (strcmp(key, "espEnabled") == 0) espEnabled = atoi(value);
            else if (strcmp(key, "boxEnabled") == 0) boxEnabled = atoi(value);
            else if (strcmp(key, "snapLineEnabled") == 0) snapLineEnabled = atoi(value);
            else if (strcmp(key, "skeletonEnabled") == 0) skeletonEnabled = atoi(value);
            else if (strcmp(key, "healthBarEnabled") == 0) healthBarEnabled = atoi(value);
            else if (strcmp(key, "nicknameEnabled") == 0) nicknameEnabled = atoi(value);
            else if (strcmp(key, "weaponEnabled") == 0) weaponEnabled = atoi(value);
            else if (strcmp(key, "avatarEnabled") == 0) avatarEnabled = atoi(value);
            else if (strcmp(key, "chamsEnabled") == 0) chamsEnabled = atoi(value);
            else if (strcmp(key, "glassChams") == 0) glassChams = atoi(value);
            else if (strcmp(key, "chamsIntensity") == 0) chamsIntensity = atof(value);
            else if (strcmp(key, "wallhackEnabled") == 0) wallhackEnabled = atoi(value);
            else if (strcmp(key, "distanceEnabled") == 0) distanceEnabled = atoi(value);
            else if (strcmp(key, "headDotEnabled") == 0) headDotEnabled = atoi(value);
            else if (strcmp(key, "tracersEnabled") == 0) tracersEnabled = atoi(value);
            else if (strcmp(key, "soundEspEnabled") == 0) soundEspEnabled = atoi(value);
            else if (strcmp(key, "fogEnabled") == 0) fogEnabled = atoi(value);
            else if (strcmp(key, "skyColor") == 0) sscanf(value, "%f,%f,%f", &skyColor[0], &skyColor[1], &skyColor[2]);
            else if (strcmp(key, "fogColor") == 0) sscanf(value, "%f,%f,%f", &fogColor[0], &fogColor[1], &fogColor[2]);
            else if (strcmp(key, "worldColor") == 0) sscanf(value, "%f,%f,%f", &worldColor[0], &worldColor[1], &worldColor[2]);
            else if (strcmp(key, "timeMode") == 0) timeMode = atoi(value);
            else if (strcmp(key, "noRecoilEnabled") == 0) noRecoilEnabled = atoi(value);
            else if (strcmp(key, "headshotSoundEnabled") == 0) headshotSoundEnabled = atoi(value);
            else if (strcmp(key, "antiAimEnabled") == 0) antiAimEnabled = atoi(value);
            else if (strcmp(key, "antiAimMode") == 0) antiAimMode = atoi(value);
            else if (strcmp(key, "spinSpeed") == 0) spinSpeed = atof(value);
            else if (strcmp(key, "triggerbotEnabled") == 0) triggerbotEnabled = atoi(value);
            else if (strcmp(key, "triggerbotDelay") == 0) triggerbotDelay = atof(value);
            else if (strcmp(key, "antiAFKEnabled") == 0) antiAFKEnabled = atoi(value);
            else if (strcmp(key, "screenshotCleanerEnabled") == 0) screenshotCleanerEnabled = atoi(value);
            else if (strcmp(key, "autoWallbangEnabled") == 0) autoWallbangEnabled = atoi(value);
            else if (strcmp(key, "noFlashEnabled") == 0) noFlashEnabled = atoi(value);
            else if (strcmp(key, "radarHackEnabled") == 0) radarHackEnabled = atoi(value);
            else if (strcmp(key, "menuScale") == 0) setMenuScale(atof(value));
            else if (strcmp(key, "tabPosition") == 0) setTabPosition(atoi(value));
        }
    }
    fclose(file);
}
