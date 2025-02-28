#ifndef UI_H
#define UI_H

#include "raylib.h"

// Button drawing function
bool DrawButton(int x, int y, int width, int height, const char *text);

// Screen rendering functions
void DrawStartScreen(int &currentScreen);
void DrawHeroSelectionScreen(int &currentScreen);
