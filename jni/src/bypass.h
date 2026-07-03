// jni/src/bypass.h
#ifndef BYPASS_H
#define BYPASS_H

#include <vector>
#include <dlfcn.h>
#include <android/log.h>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

#define LOG_TAG "XenonBypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace bypass {

struct hook_info {
    void* target_addr;
    void* hook_func;
    void* original_func;
    bool active;
};

static std::vector<hook_info*> hooks;
static void* (*orig__Unwind_GetRR)(const char*, const char*) = nullptr;

void* hk__Unwind_GetRR(const char* id, const char* report_arg) {
    LOGI("Bypass triggered: %s", report_arg);
    
    // Disable all hooks
    for (auto& info : hooks) {
        if (info->active) {
            // Restore original bytes
            size_t page_size = sysconf(_SC_PAGESIZE);
            void* page_start = (void*)((uintptr_t)info->target_addr & ~(page_size - 1));
            mprotect(page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
            memcpy(info->target_addr, info->original_func, 8);
            mprotect(page_start, page_size, PROT_READ | PROT_EXEC);
            info->active = false;
        }
    }
    
    // Call original
    void* result = orig__Unwind_GetRR(id, report_arg);
    
    // Re-enable hooks
    for (auto& info : hooks) {
        if (!info->active) {
            size_t page_size = sysconf(_SC_PAGESIZE);
            void* page_start = (void*)((uintptr_t)info->target_addr & ~(page_size - 1));
            mprotect(page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
            memcpy(info->target_addr, info->hook_func, 8);
            mprotect(page_start, page_size, PROT_READ | PROT_EXEC);
            info->active = true;
        }
    }
    
    return result;
}

inline void install_hook(void* target, void* hook, void** original) {
    hook_info* info = new hook_info();
    info->target_addr = target;
    info->hook_func = hook;
    info->active = true;
    
    // Save original bytes
    info->original_func = malloc(8);
    memcpy(info->original_func, target, 8);
    
    if (original) *original = info->original_func;
    
    // Write hook
    size_t page_size = sysconf(_SC_PAGESIZE);
    void* page_start = (void*)((uintptr_t)target & ~(page_size - 1));
    mprotect(page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy(target, hook, 8);
    mprotect(page_start, page_size, PROT_READ | PROT_EXEC);
    
    hooks.push_back(info);
}

inline void init() {
    LOGI("Initializing bypass...");
    
    // Find libshared.so
    void* libshared = dlopen("libshared.so", RTLD_LAZY);
    if (!libshared) {
        LOGI("libshared.so not found, trying libil2cpp.so");
        libshared = dlopen("libil2cpp.so", RTLD_LAZY);
    }
    if (!libshared) {
        LOGI("Failed to find library for bypass");
        return;
    }
    
    // Get _Unwind_GetRR address
    void* unwind_addr = dlsym(libshared, "_Unwind_GetRR");
    if (!unwind_addr) {
        LOGI("_Unwind_GetRR not found");
        return;
    }
    
    LOGI("_Unwind_GetRR at %p", unwind_addr);
    
    // Install hook
    install_hook(unwind_addr, (void*)hk__Unwind_GetRR, (void**)&orig__Unwind_GetRR);
    
    LOGI("Bypass initialized");
}

} // namespace bypass

#endif
