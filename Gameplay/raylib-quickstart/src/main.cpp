#include "raylib.h"
#include <cmath>
#include <vector>

#define MAX_RECTS 50

typedef struct Rect {
    Vector2 position;
    float width;
    float height;
    Color color;
} Rect;

int Clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void setBackGround(Rect& Shape, int x, int y)
{
    if (x % 2) {
        if (y % 2)
        {
            Shape.color = LIGHTGRAY;
        }
        else
        {
            Shape.color = DARKGRAY;
        }
    }
    else
    {
        if (y % 2)
        {
            Shape.color = DARKGRAY;
        }
        else
        {
            Shape.color = LIGHTGRAY;
        }
    }
}

Color HSVToRGB(float hue, float saturation, float value) {
    float c = value * saturation;
    float x = c * (1 - fabsf(fmodf(hue / 60.0f, 2) - 1));
    float m = value - c;

    float r = 0, g = 0, b = 0;
    if (hue >= 0 && hue < 60) { r = c; g = x; b = 0; }
    else if (hue >= 60 && hue < 120) { r = x; g = c; b = 0; }
    else if (hue >= 120 && hue < 180) { r = 0; g = c; b = x; }
    else if (hue >= 180 && hue < 240) { r = 0; g = x; b = c; }
    else if (hue >= 240 && hue < 300) { r = x; g = 0; b = c; }
    else if (hue >= 300 && hue < 360) { r = c; g = 0; b = x; }

    return Color{ (unsigned char)((r + m) * 255), (unsigned char)((g + m) * 255), (unsigned char)((b + m) * 255), 255 };
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simple Drawing Package with Color Picker");

    Rect rectangles[MAX_RECTS][MAX_RECTS];
    int RectSize = 10;
    Color currentColor = WHITE;
    bool eyedropperActive = false;

    bool copyMode = false;
    bool copyPasteActive = false; 
    bool selectionActive = false;
    Vector2 selectionStart = { -1, -1 };
    Vector2 selectionEnd = { -1, -1 };
    Color clipboard[MAX_RECTS][MAX_RECTS] = { 0 };

    bool eraseActive = false;

    
    for (int x = 0; x < MAX_RECTS; x++) {
        for (int y = 0; y < MAX_RECTS; y++) {
            rectangles[x][y].position.x = (RectSize * x) + 200;
            rectangles[x][y].position.y = RectSize * y;
            rectangles[x][y].width = 10;
            rectangles[x][y].height = 10;
            setBackGround(rectangles[x][y], x, y);
        }
    }

    Vector2 pickerCenter = { 80, 50 };
    float pickerRadius = 50;
    float innerRadius = 20;
    float hue = 0.0f, saturation = 1.0f;
    float value = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        Vector2 mousePos = GetMousePosition();
        if (!eraseActive) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                float dx = mousePos.x - pickerCenter.x;
                float dy = mousePos.y - pickerCenter.y;
                float distance = sqrtf(dx * dx + dy * dy);

                if (distance <= pickerRadius) {
                    hue = atan2f(dy, dx) * 180.0f / PI;
                    if (hue < 0) hue += 360.0f;
                    currentColor = HSVToRGB(hue, saturation, value);
                }
            }
        }

     
        Rectangle copyPasteButtonBounds = { 40, 200, 80, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, copyPasteButtonBounds)) {
            eraseActive = false;
            copyPasteActive = !copyPasteActive;
            eyedropperActive = false;
            selectionActive = false; 
        }

        Rectangle eraseButtonBounds = { 40, 240, 80, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, eraseButtonBounds)) {
            eraseActive = !eraseActive; 
            if (eraseActive) {
                eyedropperActive = false;
                copyPasteActive = false;
            }
        }

      
        if (copyPasteActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectionStart.x = (mousePos.x - 200) / RectSize;
            selectionStart.y = mousePos.y / RectSize;
            selectionStart.x = Clamp(selectionStart.x, 0, MAX_RECTS - 1);
            selectionStart.y = Clamp(selectionStart.y, 0, MAX_RECTS - 1);
            selectionActive = true;
        }

        
        if (copyPasteActive && selectionActive && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            selectionEnd.x = (mousePos.x - 200) / RectSize;
            selectionEnd.y = mousePos.y / RectSize;
            selectionEnd.x = Clamp(selectionEnd.x, 0, MAX_RECTS - 1);
            selectionEnd.y = Clamp(selectionEnd.y, 0, MAX_RECTS - 1);

          
            int minX = fmin(selectionStart.x, selectionEnd.x);
            int minY = fmin(selectionStart.y, selectionEnd.y);
            int maxX = fmax(selectionStart.x, selectionEnd.x);
            int maxY = fmax(selectionStart.y, selectionEnd.y);

            for (int x = minX; x <= maxX; x++) {
                for (int y = minY; y <= maxY; y++) {
                    clipboard[x - minX][y - minY] = rectangles[x][y].color;
                }
            }

            selectionActive = false;
        }

        
        if (copyPasteActive && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            int pasteX = (mousePos.x - 200) / RectSize;
            int pasteY = mousePos.y / RectSize;
            pasteX = Clamp(pasteX, 0, MAX_RECTS - 1);
            pasteY = Clamp(pasteY, 0, MAX_RECTS - 1);

        
            int copyWidth = fabs(selectionEnd.x - selectionStart.x) + 1;
            int copyHeight = fabs(selectionEnd.y - selectionStart.y) + 1;

           
            for (int x = 0; x < copyWidth; x++) {
                for (int y = 0; y < copyHeight; y++) {
                    int targetX = pasteX + x;
                    int targetY = pasteY + y;

                   
                    if (targetX >= 0 && targetX < MAX_RECTS && targetY >= 0 && targetY < MAX_RECTS) {
                        rectangles[targetX][targetY].color = clipboard[x][y];
                    }
                }
            }
        }

        
        Rectangle eyedropperButtonBounds = { 40, 160, 80, 30 };
        if (!eyedropperActive && !copyPasteActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, eyedropperButtonBounds)) {
            eyedropperActive = true;
        }

        if (eyedropperActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;

            if (GridX >= 0 && GridX < MAX_RECTS && GridY >= 0 && GridY < MAX_RECTS) {
                GridX = Clamp(GridX, 0, MAX_RECTS - 1);
                GridY = Clamp(GridY, 0, MAX_RECTS - 1);

                currentColor = rectangles[GridX][GridY].color;
                eyedropperActive = false;
            }
        }

        
        if (!eraseActive && !eyedropperActive && !copyPasteActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            rectangles[GridX][GridY].color = currentColor;
        }

        if (eraseActive && !eyedropperActive && !copyPasteActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            setBackGround(rectangles[GridX][GridY], GridX, GridY);
        }


       
        if (!eraseActive && !eyedropperActive && !copyPasteActive) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                float dx = mousePos.x - pickerCenter.x;
                float dy = mousePos.y - pickerCenter.y;
                float distance = sqrtf(dx * dx + dy * dy);

                if (distance <= pickerRadius) {
                    hue = atan2f(dy, dx) * 180.0f / PI;
                    hue = (hue < 0) ? (360 + hue) : hue;
                    currentColor = HSVToRGB(hue, saturation, value);
                }
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw color picker
        for (int i = 0; i < 360; i++) {
            Color arcColor = HSVToRGB(i, 1.0f, 1.0f);
            DrawCircleSector(pickerCenter, pickerRadius, i, i + 1, 100, arcColor);
        }

        // Draw color picker center
        DrawCircle(pickerCenter.x, pickerCenter.y, innerRadius, BLACK);
        DrawCircle(pickerCenter.x, pickerCenter.y, innerRadius - 1, WHITE);

        // Draw grid
        for (int x = 0; x < MAX_RECTS; x++) {
            for (int y = 0; y < MAX_RECTS; y++) {
                DrawRectangleRec({ rectangles[x][y].position.x, rectangles[x][y].position.y, rectangles[x][y].width, rectangles[x][y].height }, rectangles[x][y].color);
            }
        }

        // Draw selection area
        if (selectionActive) {
            int minX = fmin(selectionStart.x, (mousePos.x - 200) / RectSize);
            int minY = fmin(selectionStart.y, mousePos.y / RectSize);
            int maxX = fmax(selectionStart.x, (mousePos.x - 200) / RectSize);
            int maxY = fmax(selectionStart.y, mousePos.y / RectSize);

            for (int x = minX; x <= maxX; x++) {
                for (int y = minY; y <= maxY; y++) {
                    DrawRectangleLinesEx({ rectangles[x][y].position.x, rectangles[x][y].position.y, (float)RectSize, (float)RectSize }, 2, RED);
                }
            }
        }


        
        DrawRectangleRec(eyedropperButtonBounds, LIGHTGRAY);
        DrawRectangleLinesEx(eyedropperButtonBounds, 2, BLACK);
        DrawText("Eyedropper", eyedropperButtonBounds.x + 5, eyedropperButtonBounds.y + 7, 10, BLACK);

       
        DrawRectangleRec(copyPasteButtonBounds, LIGHTGRAY);
        DrawRectangleLinesEx(copyPasteButtonBounds, 2, BLACK);
        DrawText("Copy/Paste", copyPasteButtonBounds.x + 5, copyPasteButtonBounds.y + 7, 10, BLACK);

        DrawRectangleRec(eraseButtonBounds, LIGHTGRAY);
        DrawRectangleLinesEx(eraseButtonBounds, 2, BLACK);
        DrawText("Erase", eraseButtonBounds.x + 15, eraseButtonBounds.y + 7, 10, BLACK);


        if (eyedropperActive) {
            DrawText("Eyedropper Active: Click a square to select its color", 200, 580, 20, RED);
        }

        if (copyPasteActive)
        {
            DrawText("selection Active: Select your are to copy and paste", 200, 580, 20, RED);
        }

        if (eraseActive) {
            DrawText("Erase Mode: Right-click to erase squares", 200, 580, 20, RED);
        }

       // if (CheckCollisionPointRec(mousePos, eraseButtonBounds)) {
        //    DrawRectangleRec(eraseButtonBounds, RED);  // Highlight button
        //}

        DrawRectangle(40, 100, 80, 20, currentColor);
        DrawRectangleLines(40, 100, 80, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

