#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "game.h"

// Button drawing function
bool DrawButton(int x, int y, int width, int height, const char *text);

// Screen rendering functions
void DrawStartScreen(Game &game);
void DrawHeroSelectionScreen(Game &game);

#endif