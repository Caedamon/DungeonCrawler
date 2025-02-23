#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "game_state.h"

bool DrawButton(int x, int y, int width, int height, const char *text);

void DrawStartScreen(int &currentScreen);
void DrawHeroSelectionScreen(int &currentScreen);

#endif
