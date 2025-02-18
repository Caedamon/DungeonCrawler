#include "button.h"

bool DrawButton(int x, int y, int width, int height, const std::string &text) {
    Rectangle rect = { (float)x, (float)y, (float)width, (float)height };
    Vector2 mouse = GetMousePosition();
    bool clicked = false;

    if (CheckCollisionPointRec(mouse, rect)) {
        DrawRectangleRec(rect, GRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }
    } else {
        DrawRectangleRec(rect, LIGHTGRAY);
    }

    DrawRectangleLines(x, y, width, height, BLACK);
    DrawText(text.c_str(), x + 20, y + 15, 20, BLACK);

    return clicked;
}
