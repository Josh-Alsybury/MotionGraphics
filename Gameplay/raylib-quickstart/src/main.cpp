#include "raylib.h"
#include <cmath>

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

int main() {
   
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simple Drawing Package with Color Picker");

    Rect rectangles[MAX_RECTS][MAX_RECTS];
    int RectSize = 10;
    Color currentColor = WHITE;
    bool eyedropperActive = false;

    // Initialize the grid
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

    while (!WindowShouldClose()) {
        // Update
        Vector2 mousePos = GetMousePosition();

        Rectangle eyedropperButtonBounds = { 40, 160, 80, 30 };
        if (!eyedropperActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, eyedropperButtonBounds)) {
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
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            float dx = mousePos.x - pickerCenter.x;
            float dy = mousePos.y - pickerCenter.y;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance <= pickerRadius && distance >= innerRadius) {
                
                float angle = atan2f(dy, dx) * (180.0f / PI);
                if (angle < 0) angle += 360.0f;

                hue = angle;  
                saturation = (distance - innerRadius) / (pickerRadius - innerRadius);  
                currentColor = HSVToRGB(hue, saturation, value);
            }
        }
        
       // if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        //    Vector2 mousePos = GetMousePosition();
       //     int GridX = (mousePos.x - 200) / RectSize;
       //     int GridY = mousePos.y / RectSize;
       //     GridX = Clamp(GridX, 0, MAX_RECTS - 1);
       //     GridY = Clamp(GridY, 0, MAX_RECTS - 1);
       //     rectangles[GridX][GridY].color = currentColor;
       // }
        
        // Drawing grid logic
        if (!eyedropperActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            rectangles[GridX][GridY].color = currentColor;
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            setBackGround(rectangles[GridX][GridY], GridX, GridY);
        }

      
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        for (int i = 0; i < 360; i += 1) {
            Color arcColor = HSVToRGB(i, 1.0f, 1.0f);
            DrawCircleSector(pickerCenter, pickerRadius, i, i + 1, 100, arcColor);
        }

      
        DrawCircle(pickerCenter.x, pickerCenter.y, innerRadius, BLACK);
        DrawCircle(pickerCenter.x, pickerCenter.y, innerRadius - 1, WHITE);

       
        for (int x = 0; x < MAX_RECTS; x++) {
            for (int y = 0; y < MAX_RECTS; y++) {
                DrawRectangleRec({ rectangles[x][y].position.x, rectangles[x][y].position.y, rectangles[x][y].width, rectangles[x][y].height }, rectangles[x][y].color);
            }
        }

        DrawRectangleRec(eyedropperButtonBounds, LIGHTGRAY);
        DrawRectangleLinesEx(eyedropperButtonBounds, 2, BLACK);
        DrawText("Eyedropper", eyedropperButtonBounds.x + 5, eyedropperButtonBounds.y + 7, 10, BLACK);

       
        if (eyedropperActive) {
            DrawText("Eyedropper Active: Click a square to select its color", 200, 580, 20, RED);
        }
        
        DrawRectangle(40, 100, 80, 20, currentColor);
        DrawRectangleLines(40, 100, 80, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
