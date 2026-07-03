#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>

extern bool fpsCounterEnabled;
extern bool pingDisplayEnabled;
extern bool matchTimeEnabled;
extern bool hideHUDEnabled;
extern bool showSpectatorsEnabled;
extern bool killFeedEnabled;

void renderInterface();
void drawFPS();
void drawPing();
void drawMatchTime();
void drawSpectators();
void drawKillFeed();

#endif
