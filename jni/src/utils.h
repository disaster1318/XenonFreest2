#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <android/log.h>

#define LOG_TAG "Xenon"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Чтение памяти
template<typename T>
T readMemory(void* address) {
    if (address == nullptr) return T();
    return *reinterpret_cast<T*>(address);
}

// Запись памяти
template<typename T>
void writeMemory(void* address, T value) {
    if (address == nullptr) return;
    *reinterpret_cast<T*>(address) = value;
}

// Чтение по цепочке указателей
uintptr_t followPointerChain(uintptr_t base, int offsets[], int count);

// Получение базового адреса модуля
uintptr_t getBaseAddress();

// Преобразование 3D в экранные координаты (для ESP)
bool worldToScreen(float* worldPos, float* screenPos, float* viewMatrix);

#endif
