#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

void saveConfig();
void loadConfig();
void resetConfig();
void loadExternalConfig(const char* path);

#endif
