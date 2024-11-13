#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

void setBackGround(Rect& Shape, int x,int y)
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

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simple Drawing Package - Rectangle Mode");

    // Variables
    Rect rectangles[MAX_RECTS][MAX_RECTS];
    int RectSize = 10;
    Color currentColor = WHITE;  // Default color for drawing rectangles
    bool drawing = false;

    // Define a simple color palette
    Color palette[] = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, MAROON, PINK, };
    int paletteSize = sizeof(palette) / sizeof(palette[0]);
    int selectedColor = 0;

    SetTargetFPS(60);
    
    for(int x = 0;x < MAX_RECTS;x++) 
    {
        for (int y = 0; y < MAX_RECTS; y++)
        {
            Vector2 rectEnd = GetMousePosition();
            rectangles[x][y].position.x = (RectSize*x) +200 ;
            rectangles[x][y].position.y = RectSize*y;
            rectangles[x][y].width = 10;
            rectangles[x][y].height = 10;
            setBackGround(rectangles[x][y], x, y);

        }
    }

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
        {
            Vector2 mousePos = GetMousePosition();
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            rectangles[GridX][GridY].color = currentColor;
        
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            int GridX = (mousePos.x - 200) / RectSize;
            int GridY = mousePos.y / RectSize;
            GridX = Clamp(GridX, 0, MAX_RECTS - 1);
            GridY = Clamp(GridY, 0, MAX_RECTS - 1);
            setBackGround(rectangles[GridX][GridY], GridX, GridY);
        }
        

        // Change color based on palette selection
        for (int i = 0; i < paletteSize; i++) {
            Rectangle colorButton = { 10 + 40 * i, screenHeight - 40, 30, 30 };
            if (GuiButton(colorButton, "")) {
                currentColor = palette[i];
                selectedColor = i;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the palette buttons
        for (int i = 0; i < paletteSize; i++) {
            Rectangle colorButton = { 10 + 40 * i, screenHeight - 40, 30, 30 };
            DrawRectangleRec(colorButton, palette[i]);
            if (i == selectedColor) {
                DrawRectangleLinesEx(colorButton, 2, BLACK);  // Highlight selected color
            }
        }

        // Draw all stored rectangles
        for (int x = 0; x < MAX_RECTS; x++) 
        {
            for (int y = 0; y < MAX_RECTS; y++)
            {
                DrawRectangleRec({ rectangles[x][y].position.x, rectangles[x][y].position.y, rectangles[x][y].width, rectangles[x][y].height }, rectangles[x][y].color);
            }
        }

       


        // Draw the current rectangle if drawing


        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}