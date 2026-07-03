#include <jni.h>
#include <string.h>
#include <unistd.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <dlfcn.h>

#include "offsets.h"
#include "menu.h"
#include "esp.h"
#include "features.h"
#include "world.h"
#include "config.h"
#include "utils.h"
#include "bypass.h"          // <-- ДОБАВЛЕНО

#define LOG_TAG "Xenon"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static bool initialized = false;
static EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    if (!initialized) {
        LOGI("Xenon init");
        loadConfig();
        initMenu();
        bypass::init();      // <-- ДОБАВЛЕНО
        initialized = true;
    }
    applyFeatures();
    applyWorldChanges();
    renderMenu();
    renderESP();
    return orig_eglSwapBuffers(dpy, surface);
}

void __attribute__((constructor)) xenon_main() {
    LOGI("Xenon start");
    void* egl_handle = dlopen("libEGL.so", RTLD_LAZY);
    if (egl_handle) {
        orig_eglSwapBuffers = (EGLBoolean (*)(EGLDisplay, EGLSurface))dlsym(egl_handle, "eglSwapBuffers");
        if (orig_eglSwapBuffers) {
            LOGI("Hook installed");
        }
    }
}

int getLocalPlayer() {
    uintptr_t base = getBaseAddress();
    if (!base) return 0;
    return readMemory<int>((void*)(base + LOCAL_PLAYER));
}

uintptr_t getPlayerList() {
    uintptr_t base = getBaseAddress();
    if (!base) return 0;
    return readMemory<uintptr_t>((void*)(base + PLAYER_LIST));
}

int getPlayerCount() {
    uintptr_t list = getPlayerList();
    if (!list) return 0;
    return readMemory<int>((void*)list);
}

uintptr_t getPlayerFromList(uintptr_t list, int index) {
    return readMemory<uintptr_t>((void*)(list + 4 + index * 4));
}

void getPlayerPosition(uintptr_t player, float* pos) {
    uintptr_t movement = readMemory<uintptr_t>((void*)(player + MOVEMENT_CONTROLLER));
    if (!movement) return;
    uintptr_t transform = readMemory<uintptr_t>((void*)(movement + TRANSFORM));
    if (!transform) return;
    pos[0] = readMemory<float>((void*)(transform + POSITION));
    pos[1] = readMemory<float>((void*)(transform + POSITION + 4));
    pos[2] = readMemory<float>((void*)(transform + POSITION + 8));
}

float getPlayerHealth(uintptr_t player) {
    uintptr_t hitController = readMemory<uintptr_t>((void*)(player + PLAYER_HIT_CONTROLLER));
    if (!hitController) return 0.0f;
    return readMemory<float>((void*)(hitController + HEALTH));
}

const char* getPlayerName(uintptr_t player) {
    return "Player";
}

const char* getPlayerWeapon(uintptr_t player) {
    return "Weapon";
}

float getDistance(uintptr_t local, uintptr_t player) {
    float pos1[3], pos2[3];
    getPlayerPosition(local, pos1);
    getPlayerPosition(player, pos2);
    float dx = pos1[0] - pos2[0];
    float dy = pos1[1] - pos2[1];
    float dz = pos1[2] - pos2[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}

void getViewMatrix(float* matrix) {
    uintptr_t base = getBaseAddress();
    if (!base) return;
    uintptr_t camera = readMemory<uintptr_t>((void*)(base + CAMERA));
    if (!camera) return;
    uintptr_t view = readMemory<uintptr_t>((void*)(camera + VIEW_MATRIX_A));
    if (!view) return;
    view = readMemory<uintptr_t>((void*)(view + VIEW_MATRIX_B));
    if (!view) return;
    view = readMemory<uintptr_t>((void*)(view + VIEW_MATRIX_C));
    if (!view) return;
    memcpy(matrix, (void*)view, 16 * sizeof(float));
}

uintptr_t getWorldPtr() {
    uintptr_t base = getBaseAddress();
    if (!base) return 0;
    return readMemory<uintptr_t>((void*)(base + 0x100000));
}
