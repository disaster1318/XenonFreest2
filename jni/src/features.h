#ifndef FEATURES_H
#define FEATURES_H

#include <stdbool.h>

extern bool noRecoilEnabled;
extern bool headshotSoundEnabled;
extern bool antiAimEnabled;
extern int antiAimMode; // 0 - spin, 1 - back
extern float spinSpeed;
extern bool triggerbotEnabled;
extern float triggerbotDelay;
extern bool antiAFKEnabled;
extern bool screenshotCleanerEnabled;
extern bool autoWallbangEnabled;
extern bool noFlashEnabled;
extern bool radarHackEnabled;

void applyFeatures();
void noRecoil();
void headshotSound();
void antiAim();
void triggerbot();
void antiAFK();
void screenshotCleaner();
void autoWallbang();
void noFlash();
void radarHack();

#endif
