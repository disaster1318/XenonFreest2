#include "utils.h"
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <android/log.h>

uintptr_t followPointerChain(uintptr_t base, int offsets[], int count) {
    uintptr_t addr = base;
    for (int i = 0; i < count; i++) {
        if (addr == 0) return 0;
        addr = readMemory<uintptr_t>((void*)addr);
        if (addr == 0) return 0;
        addr += offsets[i];
    }
    return addr;
}

uintptr_t getBaseAddress() {
    Dl_info info;
    if (dladdr((void*)getBaseAddress, &info)) {
        return (uintptr_t)info.dli_fbase;
    }
    return 0;
}

bool worldToScreen(float* worldPos, float* screenPos, float* viewMatrix) {
    float w = viewMatrix[3] * worldPos[0] + viewMatrix[7] * worldPos[1] + viewMatrix[11] * worldPos[2] + viewMatrix[15];
    if (w < 0.01f) return false;
    float x = viewMatrix[0] * worldPos[0] + viewMatrix[4] * worldPos[1] + viewMatrix[8] * worldPos[2] + viewMatrix[12];
    float y = viewMatrix[1] * worldPos[0] + viewMatrix[5] * worldPos[1] + viewMatrix[9] * worldPos[2] + viewMatrix[13];
    screenPos[0] = (x / w + 1.0f) * 0.5f;
    screenPos[1] = (1.0f - y / w) * 0.5f;
    return true;
}
