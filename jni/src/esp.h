#ifndef ESP_H
#define ESP_H

#include <stdbool.h>

extern bool espEnabled;
extern bool boxEnabled;
extern bool snapLineEnabled;
extern bool skeletonEnabled;
extern bool healthBarEnabled;
extern bool nicknameEnabled;
extern bool weaponEnabled;
extern bool avatarEnabled;
extern bool chamsEnabled;
extern bool glassChams;
extern float chamsIntensity;
extern bool chamsEnemyOnly;
extern bool wallhackEnabled;
extern bool distanceEnabled;
extern bool headDotEnabled;
extern bool tracersEnabled;
extern bool soundEspEnabled;

void renderESP();
void drawPlayerBox(float x, float y, float w, float h, float color[3]);
void drawSnapLine(float x, float y, float color[3]);
void drawSkeleton(float* bones, float color[3]);
void drawHealthBar(float x, float y, float health, float maxHealth);
void drawNickname(float x, float y, const char* name);
void drawWeapon(float x, float y, const char* weapon);
void drawAvatar(float x, float y, int avatarId);
void drawChams(void* player, float color[3], bool glass);
void drawDistance(float x, float y, float dist);
void drawHeadDot(float x, float y, float color[3]);
void drawTracers(float x1, float y1, float x2, float y2, float color[3]);
void drawSoundIndicator(float x, float y, int type);

#endif
