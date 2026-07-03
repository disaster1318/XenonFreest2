#include "menu.h"
#include "utils.h"
#include <GLES2/gl2.h>
#include <string.h>

static bool menuVisible = true;
static int currentTab = 0;
static float menuScale = 0.7f;
static int tabPosition = 0;
static bool isExpanded = true;
static float animTime = 0.0f;

void initMenu() {
    menuVisible = true;
    currentTab = 0;
    isExpanded = true;
    animTime = 0.0f;
}

void toggleMenu() {
    isExpanded = !isExpanded;
}

void renderMenu() {
    if (!menuVisible) return;
    if (!isExpanded) {
        drawMinimizedIcon();
        return;
    }
    glPushMatrix();
    float centerX = 0.0f;
    float centerY = 0.0f;
    glTranslatef(centerX, centerY, 0.0f);
    glScalef(menuScale, menuScale, 1.0f);
    drawBackground();
    drawHeader();
    drawTabBar();
    drawTabContent(currentTab);
    glPopMatrix();
}

void drawBackground() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.05f, 0.05f, 0.1f, 0.85f);
    float w = 0.8f;
    float h = 0.6f;
    glBegin(GL_QUADS);
    glVertex2f(-w/2, -h/2);
    glVertex2f(w/2, -h/2);
    glVertex2f(w/2, h/2);
    glVertex2f(-w/2, h/2);
    glEnd();
    glDisable(GL_BLEND);
}

void drawHeader() {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    // Xenon title
    // minimize button
    // close button
}

void drawTabBar() {
    const char* icons[] = {"ESP", "WORLD", "DOP", "VISUAL", "UI", "SET"};
    int count = 6;
    float startX = -0.35f;
    float y = 0.25f;
    float step = 0.12f;
    for (int i = 0; i < count; i++) {
        float x = startX + i * step;
        if (i == currentTab) {
            glColor4f(0.0f, 0.8f, 1.0f, 1.0f);
        } else {
            glColor4f(0.6f, 0.6f, 0.6f, 0.8f);
        }
        glBegin(GL_QUADS);
        glVertex2f(x - 0.03f, y - 0.03f);
        glVertex2f(x + 0.03f, y - 0.03f);
        glVertex2f(x + 0.03f, y + 0.03f);
        glVertex2f(x - 0.03f, y + 0.03f);
        glEnd();
    }
}

void drawTabContent(int tab) {
    float yStart = 0.15f;
    float step = -0.05f;
    float x = -0.3f;
    if (tab == 0) {
        drawToggle(x, yStart, "ESP Enable", &espEnabled);
        drawToggle(x, yStart + step, "Box", &boxEnabled);
        drawToggle(x, yStart + step*2, "Snap Line", &snapLineEnabled);
        drawToggle(x, yStart + step*3, "Skeleton", &skeletonEnabled);
        drawToggle(x, yStart + step*4, "Health Bar", &healthBarEnabled);
        drawToggle(x, yStart + step*5, "Nickname", &nicknameEnabled);
        drawToggle(x, yStart + step*6, "Weapon", &weaponEnabled);
        drawToggle(x, yStart + step*7, "Avatar", &avatarEnabled);
        drawToggle(x, yStart + step*8, "Chams", &chamsEnabled);
        drawToggle(x, yStart + step*9, "Glass", &glassChams);
        drawSlider(x + 0.3f, yStart + step*9, "Intensity", &chamsIntensity, 0.0f, 5.0f);
        drawToggle(x, yStart + step*10, "Wallhack", &wallhackEnabled);
        drawToggle(x, yStart + step*11, "Distance", &distanceEnabled);
        drawToggle(x, yStart + step*12, "Head Dot", &headDotEnabled);
        drawToggle(x, yStart + step*13, "Tracers", &tracersEnabled);
        drawToggle(x, yStart + step*14, "Sound ESP", &soundEspEnabled);
    }
}

void drawToggle(float x, float y, const char* label, bool* value) {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    // label text
    float size = 0.02f;
    if (*value) {
        glColor4f(0.0f, 0.8f, 1.0f, 1.0f);
    } else {
        glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    }
    glBegin(GL_QUADS);
    glVertex2f(x + 0.25f, y - size);
    glVertex2f(x + 0.25f + 0.05f, y - size);
    glVertex2f(x + 0.25f + 0.05f, y + size);
    glVertex2f(x + 0.25f, y + size);
    glEnd();
}

void drawSlider(float x, float y, const char* label, float* value, float min, float max) {
    // stub
}

void drawMinimizedIcon() {
    glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.02f);
    glVertex2f(0.05f, -0.02f);
    glVertex2f(0.05f, 0.02f);
    glVertex2f(-0.05f, 0.02f);
    glEnd();
}

bool isMenuVisible() {
    return menuVisible;
}

void setMenuVisible(bool visible) {
    menuVisible = visible;
}

int getCurrentTab() {
    return currentTab;
}

void setCurrentTab(int tab) {
    currentTab = tab;
}

float getMenuScale() {
    return menuScale;
}

void setMenuScale(float scale) {
    menuScale = scale;
}

int getTabPosition() {
    return tabPosition;
}

void setTabPosition(int pos) {
    tabPosition = pos;
}
