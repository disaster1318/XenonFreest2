#include "visual.h"
#include "utils.h"
#include <GLES2/gl2.h>
#include <math.h>
#include <android/log.h>

bool crosshairEnabled = false;
int crosshairType = 0;
float crosshairColor[3] = {0.0f, 1.0f, 0.0f};
float crosshairSize = 0.02f;
bool hitMarkerEnabled = false;
bool damageIndicatorEnabled = false;
bool zoomEnabled = false;
float zoomLevel = 2.0f;
bool brightnessEnabled = false;
float brightnessLevel = 1.2f;
bool antiFlashEnabled = false;
bool chamsWeaponEnabled = false;
float chamsWeaponColor[3] = {0.0f, 0.5f, 1.0f};
bool glowEnabled = false;
float glowColor[3] = {1.0f, 1.0f, 0.0f};
bool thirdPersonEnabled = false;

static float hitMarkerTimer = 0.0f;
static float damageIndicators[4] = {0.0f, 0.0f, 0.0f, 0.0f};

void renderVisuals() {
    if (crosshairEnabled) drawCrosshair();
    if (hitMarkerEnabled && hitMarkerTimer > 0.0f) {
        hitMarkerTimer -= 0.01f;
        drawHitMarker();
    }
    if (damageIndicatorEnabled) {
        for (int i = 0; i < 4; i++) {
            if (damageIndicators[i] > 0.0f) {
                drawDamageIndicator(i * 90.0f);
                damageIndicators[i] -= 0.01f;
            }
        }
    }
    if (zoomEnabled) applyZoom();
    if (brightnessEnabled) applyBrightness();
    if (antiFlashEnabled) applyAntiFlash();
    if (chamsWeaponEnabled) drawChamsWeapon();
    if (glowEnabled) drawGlow();
    if (thirdPersonEnabled) applyThirdPerson();
}

void drawCrosshair() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(crosshairColor[0], crosshairColor[1], crosshairColor[2], 1.0f);
    glLineWidth(2.0f);
    float s = crosshairSize;
    if (crosshairType == 0) {
        glBegin(GL_LINES);
        glVertex2f(-s, 0.0f);
        glVertex2f(-s * 0.3f, 0.0f);
        glVertex2f(s * 0.3f, 0.0f);
        glVertex2f(s, 0.0f);
        glVertex2f(0.0f, -s);
        glVertex2f(0.0f, -s * 0.3f);
        glVertex2f(0.0f, s * 0.3f);
        glVertex2f(0.0f, s);
        glEnd();
    } else if (crosshairType == 1) {
        glPointSize(s * 20.0f);
        glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f);
        glEnd();
    } else if (crosshairType == 2) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 20; i++) {
            float angle = i * 3.14159f * 2.0f / 20.0f;
            glVertex2f(cos(angle) * s, sin(angle) * s);
        }
        glEnd();
    }
    glDisable(GL_BLEND);
}

void drawHitMarker() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    glLineWidth(2.0f);
    float s = 0.03f;
    glBegin(GL_LINES);
    glVertex2f(-s, -s);
    glVertex2f(-s * 0.4f, -s * 0.4f);
    glVertex2f(s, -s);
    glVertex2f(s * 0.4f, -s * 0.4f);
    glVertex2f(-s, s);
    glVertex2f(-s * 0.4f, s * 0.4f);
    glVertex2f(s, s);
    glVertex2f(s * 0.4f, s * 0.4f);
    glEnd();
    glDisable(GL_BLEND);
}

void drawDamageIndicator(float angle) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    float rad = angle * 3.14159f / 180.0f;
    float x = cos(rad) * 0.3f;
    float y = sin(rad) * 0.3f;
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + 0.05f, y + 0.02f);
    glVertex2f(x + 0.05f, y - 0.02f);
    glEnd();
    glDisable(GL_BLEND);
}

void applyZoom() {
    // OpenGL zoom via matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    float ratio = 1.0f / zoomLevel;
    glScalef(ratio, ratio, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void applyBrightness() {
    // Simulate brightness via color multiplier
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(brightnessLevel, brightnessLevel, brightnessLevel, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    glDisable(GL_BLEND);
}

void applyAntiFlash() {
    // Override flash shader - stub
}

void drawChamsWeapon() {
    // Requires weapon model access - stub
}

void drawGlow() {
    // Requires object list - stub
}

void applyThirdPerson() {
    // Requires camera offset - stub
}
