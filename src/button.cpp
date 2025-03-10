#include "button.h"

bool DrawButton(int x, int y, int width, int height, const char *text) {
    Rectangle rect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
    Vector2 mouse = GetMousePosition();
    static bool isHeld = false;
    bool clicked = false;

    if (CheckCollisionPointRec(mouse, rect)) {
        DrawRectangleRec(rect, GRAY);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isHeld = true;  // Mark button as held when clicked inside
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isHeld) {
            clicked = true;  // Only trigger when released inside
            isHeld = false;  // Reset state
        }
    } else {
        DrawRectangleRec(rect, LIGHTGRAY);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isHeld = false;  // Reset state if mouse moves away before release
        }
    }

    DrawRectangleLines(x, y, width, height, BLACK);
    int textWidth = MeasureText(text, 20);
    DrawText(text, x + (width - textWidth) / 2, y + (height - 20) / 2, 20, BLACK);

    return clicked;
}

