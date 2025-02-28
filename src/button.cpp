#include "button.h"

bool DrawButton(int x, int y, int width, int height, const char* text) {
    // Define button rectangle
    Rectangle rect = { static_cast<float>(x), static_cast<float>(y),
                       static_cast<float>(width), static_cast<float>(height) };
    Vector2 mouse = GetMousePosition();
    bool clicked = false;

    // Handle hover effect & click detection
    if (CheckCollisionPointRec(mouse, rect)) {
        DrawRectangleRec(rect, GRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }
    } else {
        DrawRectangleRec(rect, LIGHTGRAY);
    }

    // Draw button border
    DrawRectangleLines(x, y, width, height, BLACK);

    // Draw centered button text
    int textWidth = MeasureText(text, 20);
    DrawText(text, x + (width - textWidth) / 2, y + (height - 20) / 2, 20, BLACK);

    return clicked;
}
