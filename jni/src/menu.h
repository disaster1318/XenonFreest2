#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

void initMenu();
void renderMenu();
void toggleMenu();
bool isMenuVisible();
void setMenuVisible(bool visible);
int getCurrentTab();
void setCurrentTab(int tab);
float getMenuScale();
void setMenuScale(float scale);
int getTabPosition();
void setTabPosition(int pos);

void drawBackground();
void drawHeader();
void drawTabBar();
void drawTabContent(int tab);
void drawToggle(float x, float y, const char* label, bool* value);
void drawSlider(float x, float y, const char* label, float* value, float min, float max);
void drawMinimizedIcon();

#endif
