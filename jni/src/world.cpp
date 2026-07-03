#include "world.h"
#include "utils.h"
#include "offsets.h"

bool fogEnabled = false;
float skyColor[3] = {0.5f, 0.7f, 1.0f};
float fogColor[3] = {0.5f, 0.5f, 0.5f};
float worldColor[3] = {1.0f, 1.0f, 1.0f};
int timeMode = 0;

void applyWorldChanges() {
    uintptr_t worldPtr = getWorldPtr();
    if (!worldPtr) return;
    if (fogEnabled) {
        writeMemory<float>((void*)(worldPtr + FOG_COLOR), fogColor[0]);
        writeMemory<float>((void*)(worldPtr + FOG_COLOR + 4), fogColor[1]);
        writeMemory<float>((void*)(worldPtr + FOG_COLOR + 8), fogColor[2]);
    }
    if (timeMode == 0) {
        writeMemory<float>((void*)(worldPtr + SKYBOX_OVERRIDE), 1.0f);
    } else if (timeMode == 1) {
        writeMemory<float>((void*)(worldPtr + SKYBOX_OVERRIDE), 0.6f);
    } else if (timeMode == 2) {
        writeMemory<float>((void*)(worldPtr + SKYBOX_OVERRIDE), 0.2f);
    }
}

void setSkyColor(float r, float g, float b) {
    skyColor[0] = r;
    skyColor[1] = g;
    skyColor[2] = b;
}

void setFogColor(float r, float g, float b) {
    fogColor[0] = r;
    fogColor[1] = g;
    fogColor[2] = b;
}

void setWorldColor(float r, float g, float b) {
    worldColor[0] = r;
    worldColor[1] = g;
    worldColor[2] = b;
}

void setTimeMode(int mode) {
    timeMode = mode;
}
