#include "esp.h"
#include "utils.h"
#include "offsets.h"
#include <GLES2/gl2.h>
#include <stdio.h>

bool espEnabled = true;
bool boxEnabled = true;
bool snapLineEnabled = false;
bool skeletonEnabled = false;
bool healthBarEnabled = true;
bool nicknameEnabled = true;
bool weaponEnabled = true;
bool avatarEnabled = false;
bool chamsEnabled = true;
bool glassChams = false;
float chamsIntensity = 2.6f;
bool chamsEnemyOnly = true;
bool wallhackEnabled = true;
bool distanceEnabled = false;
bool headDotEnabled = false;
bool tracersEnabled = false;
bool soundEspEnabled = false;

void renderESP() {
    if (!espEnabled) return;
    uintptr_t localPlayer = getLocalPlayer();
    if (!localPlayer) return;
    uintptr_t playerList = getPlayerList();
    if (!playerList) return;
    float viewMatrix[16];
    getViewMatrix(viewMatrix);
    int playerCount = getPlayerCount();
    for (int i = 0; i < playerCount; i++) {
        uintptr_t player = getPlayerFromList(playerList, i);
        if (!player || player == localPlayer) continue;
        float pos[3];
        getPlayerPosition(player, pos);
        float screen[2];
        if (!worldToScreen(pos, screen, viewMatrix)) continue;
        float health = getPlayerHealth(player);
        float maxHealth = 100.0f;
        float boxHeight = 1.0f / screen[1] * 200.0f;
        float boxWidth = boxHeight * 0.4f;
        float x = screen[0] - boxWidth / 2;
        float y = screen[1] - boxHeight;
        if (boxEnabled) {
            float color[3] = {1.0f, 0.0f, 0.0f};
            drawPlayerBox(x, y, boxWidth, boxHeight, color);
        }
        if (snapLineEnabled) {
            float color[3] = {1.0f, 1.0f, 1.0f};
            drawSnapLine(screen[0], screen[1], color);
        }
        if (healthBarEnabled) {
            drawHealthBar(x, y - 10.0f, health, maxHealth);
        }
        if (nicknameEnabled) {
            const char* name = getPlayerName(player);
            drawNickname(x + boxWidth / 2, y - 20.0f, name);
        }
        if (weaponEnabled) {
            const char* weapon = getPlayerWeapon(player);
            drawWeapon(x + boxWidth / 2, y + boxHeight + 10.0f, weapon);
        }
        if (distanceEnabled) {
            float dist = getDistance(localPlayer, player);
            drawDistance(x + boxWidth / 2, y + boxHeight + 20.0f, dist);
        }
        if (headDotEnabled) {
            float color[3] = {1.0f, 0.0f, 0.0f};
            drawHeadDot(screen[0], screen[1] - boxHeight * 0.8f, color);
        }
        if (chamsEnabled) {
            float color[3] = {0.0f, 1.0f, 0.0f};
            drawChams((void*)player, color, glassChams);
        }
    }
}

void drawPlayerBox(float x, float y, float w, float h, float color[3]) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color[0], color[1], color[2], 0.8f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    glDisable(GL_BLEND);
}

void drawSnapLine(float x, float y, float color[3]) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color[0], color[1], color[2], 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glEnd();
    glDisable(GL_BLEND);
}

void drawHealthBar(float x, float y, float health, float maxHealth) {
    float ratio = health / maxHealth;
    float width = 30.0f;
    float height = 3.0f;
    float r = 1.0f - ratio;
    float g = ratio;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    glColor4f(r, g, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width * ratio, y);
    glVertex2f(x + width * ratio, y + height);
    glVertex2f(x, y + height);
    glEnd();
    glDisable(GL_BLEND);
}

void drawNickname(float x, float y, const char* name) {
    // заглушка, для текста нужен рендер шрифтов
}

void drawWeapon(float x, float y, const char* weapon) {
    // заглушка
}

void drawAvatar(float x, float y, int avatarId) {
    // заглушка
}

void drawChams(void* player, float color[3], bool glass) {
    // заглушка, требует доступа к модели игрока
}

void drawDistance(float x, float y, float dist) {
    // заглушка
}

void drawHeadDot(float x, float y, float color[3]) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color[0], color[1], color[2], 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glDisable(GL_BLEND);
}

void drawTracers(float x1, float y1, float x2, float y2, float color[3]) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color[0], color[1], color[2], 0.6f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glDisable(GL_BLEND);
}

void drawSoundIndicator(float x, float y, int type) {
    // заглушка
}
