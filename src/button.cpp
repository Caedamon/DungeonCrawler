#include "button.h"

bool DrawButton(int x, int y, int width, int height, const std::string &text) {
    Rectangle rect = { static_cast<float>(x), static_cast<float>(y),
                   static_cast<float>(width), static_cast<float>(height) };
    Vector2 mouse = GetMousePosition();
    bool clicked = false;

    if (CheckCollisionPointRec(mouse, rect)) {
        DrawRectangleRec(rect, GRAY);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }
    } else {
        DrawRectangleRec(rect, LIGHTGRAY);
    }

    DrawRectangleLines(x, y, width, height, BLACK);
    int textWidth = MeasureText(text.c_str(), 20);
    DrawText(text.c_str(), x + (width - textWidth) / 2, y + (height - 20) / 2, 20, BLACK);

    return clicked;
}
