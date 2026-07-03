#include "features.h"
#include "utils.h"
#include "offsets.h"
#include <math.h>
#include <android/log.h>

bool noRecoilEnabled = false;
bool headshotSoundEnabled = false;
bool antiAimEnabled = false;
int antiAimMode = 0;
float spinSpeed = 2.0f;
bool triggerbotEnabled = false;
float triggerbotDelay = 0.1f;
bool antiAFKEnabled = false;
bool screenshotCleanerEnabled = false;
bool autoWallbangEnabled = false;
bool noFlashEnabled = false;
bool radarHackEnabled = false;

void applyFeatures() {
    if (noRecoilEnabled) noRecoil();
    if (headshotSoundEnabled) headshotSound();
    if (antiAimEnabled) antiAim();
    if (triggerbotEnabled) triggerbot();
    if (antiAFKEnabled) antiAFK();
    if (screenshotCleanerEnabled) screenshotCleaner();
    if (autoWallbangEnabled) autoWallbang();
    if (noFlashEnabled) noFlash();
    if (radarHackEnabled) radarHack();
}

void noRecoil() {
    uintptr_t localPlayer = getLocalPlayer();
    if (!localPlayer) return;
    uintptr_t weapon = readMemory<uintptr_t>((void*)(localPlayer + WEAPON));
    if (!weapon) return;
    float recoilValues[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < 6; i++) {
        uintptr_t recoilAddr = weapon + RECOIL_1 + i * 4;
        writeMemory<float>((void*)recoilAddr, 0.0f);
    }
}

void headshotSound() {
    // звук проигрывается при хуке на попадание
    // реализация в хуке урона
}

void antiAim() {
    uintptr_t localPlayer = getLocalPlayer();
    if (!localPlayer) return;
    uintptr_t aimController = readMemory<uintptr_t>((void*)(localPlayer + AIM_CONTROLLER));
    if (!aimController) return;
    if (antiAimMode == 0) {
        static float angle = 0.0f;
        angle += spinSpeed * 0.01f;
        writeMemory<float>((void*)(aimController + VIEW_DIRECTION), angle);
    } else if (antiAimMode == 1) {
        float viewDir = readMemory<float>((void*)(aimController + VIEW_DIRECTION));
        writeMemory<float>((void*)(aimController + VIEW_DIRECTION), viewDir + 3.14159f);
    }
}

void triggerbot() {
    uintptr_t localPlayer = getLocalPlayer();
    if (!localPlayer) return;
    uintptr_t aimController = readMemory<uintptr_t>((void*)(localPlayer + AIM_CONTROLLER));
    if (!aimController) return;
    float viewDir = readMemory<float>((void*)(aimController + VIEW_DIRECTION));
    // проверка пересечения с игроками
    // если враг в прицеле -> симулировать выстрел
}

void antiAFK() {
    // эмуляция небольшого движения каждые 10 секунд
    static int counter = 0;
    counter++;
    if (counter > 600) {
        counter = 0;
        // симулировать нажатие клавиши движения
    }
}

void screenshotCleaner() {
    // при обнаружении скриншота отключаем ESP
}

void autoWallbang() {
    // проверка стен и автоматический выстрел
}

void noFlash() {
    uintptr_t localPlayer = getLocalPlayer();
    if (!localPlayer) return;
    // отключение эффекта ослепления
    // нужен оффсет на flashEffect
}

void radarHack() {
    // включение всех игроков на миникарте
    // нужен оффсет на radar
}
