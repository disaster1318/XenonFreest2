#ifndef VISUAL_H
#define VISUAL_H

#include <stdbool.h>

extern bool crosshairEnabled;
extern int crosshairType;   // 0-cross, 1-dot, 2-circle
extern float crosshairColor[3];
extern float crosshairSize;
extern bool hitMarkerEnabled;
extern bool damageIndicatorEnabled;
extern bool zoomEnabled;
extern float zoomLevel;
extern bool brightnessEnabled;
extern float brightnessLevel;
extern bool antiFlashEnabled;
extern bool chamsWeaponEnabled;
extern float chamsWeaponColor[3];
extern bool glowEnabled;
extern float glowColor[3];
extern bool thirdPersonEnabled;

void renderVisuals();
void drawCrosshair();
void drawHitMarker();
void drawDamageIndicator(float angle);
void applyZoom();
void applyBrightness();
void applyAntiFlash();
void drawChamsWeapon();
void drawGlow();
void applyThirdPerson();

#endif
