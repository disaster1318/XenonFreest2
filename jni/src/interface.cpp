#include "interface.h"
#include "utils.h"
#include <GLES2/gl2.h>
#include <stdio.h>
#include <time.h>

bool fpsCounterEnabled = false;
bool pingDisplayEnabled = false;
bool matchTimeEnabled = false;
bool hideHUDEnabled = false;
bool showSpectatorsEnabled = false;
bool killFeedEnabled = false;

static int frameCount = 0;
static float lastFPSTime = 0.0f;
static float currentFPS = 0.0f;

void renderInterface() {
    if (hideHUDEnabled) return;
    if (fpsCounterEnabled) drawFPS();
    if (pingDisplayEnabled) drawPing();
    if (matchTimeEnabled) drawMatchTime();
    if (showSpectatorsEnabled) drawSpectators();
    if (killFeedEnabled) drawKillFeed();
}

void drawFPS() {
    frameCount++;
    float now = clock() / (float)CLOCKS_PER_SEC;
    if (now - lastFPSTime >= 1.0f) {
        currentFPS = frameCount / (now - lastFPSTime);
        frameCount = 0;
        lastFPSTime = now;
    }
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    char text[16];
    snprintf(text, sizeof(text), "FPS: %.0f", currentFPS);
    // render text at top-left
}

void drawPing() {
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    // render "Ping: XXms" at top-right
}

void drawMatchTime() {
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    // render "Time: XX:XX" at center-top
}

void drawSpectators() {
    glColor4f(0.0f, 0.8f, 1.0f, 1.0f);
    // render spectator list
}

void drawKillFeed() {
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
    // render extended kill feed
}
