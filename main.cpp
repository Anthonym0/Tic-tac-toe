#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <stdio.h>
#include "Game.hpp"

#define MAIN_MENU 0
#define PLAY 1
#define CIRCLE -2
#define CROSS -3

int GAME_STATE = MAIN_MENU;
bool IA_MODE = false;
int menu_selected = 0;

Game game_info("Tic tac toe", 800, 450);

void MainMenu() {
    const char *name = game_info.getName();
    
    DrawText(name, game_info.getWidth()/2 - MeasureText(name, 35)/2, game_info.getHeight() * 0.3, 35, BLACK);
    
    if (IsKeyPressed(KEY_UP)) {
        menu_selected -= 1;
        if (menu_selected < 0)
            menu_selected = 2;
    } else if (IsKeyPressed(KEY_DOWN)) {
        menu_selected += 1;
        if (menu_selected > 2)
            menu_selected = 0;
    } else if (IsKeyPressed(KEY_ENTER)) {
        if (menu_selected == 0)
            GAME_STATE = PLAY;
        else if (menu_selected == 1) {
            IA_MODE = true;
            GAME_STATE = PLAY;
        } else {
            exit(0);
        }
    }

    switch (menu_selected)
    {
        case 0:
            DrawText("Play", game_info.getWidth()/2 - MeasureText("Play", 30)/2, game_info.getHeight() * 0.45, 30, ORANGE);
            DrawText("Play vs IA", game_info.getWidth()/2 - MeasureText("Play vs IA", 30)/2, game_info.getHeight() * 0.55, 30, BLACK);
            DrawText("Exit", game_info.getWidth()/2 - MeasureText("Exit", 30)/2, game_info.getHeight() * 0.65, 30, BLACK);
            break;
        case 1:
            DrawText("Play", game_info.getWidth()/2 - MeasureText("Play", 30)/2, game_info.getHeight() * 0.45, 30, BLACK);
            DrawText("Play vs IA", game_info.getWidth()/2 - MeasureText("Play vs IA", 30)/2, game_info.getHeight() * 0.55, 30, ORANGE);
            DrawText("Exit", game_info.getWidth()/2 - MeasureText("Exit", 30)/2, game_info.getHeight() * 0.65, 30, BLACK);
            break;
        case 2:
            DrawText("Play", game_info.getWidth()/2 - MeasureText("Play", 30)/2, game_info.getHeight() * 0.45, 30, BLACK);
            DrawText("Play vs IA", game_info.getWidth()/2 - MeasureText("Play vs IA", 30)/2, game_info.getHeight() * 0.55, 30, BLACK);
            DrawText("Exit", game_info.getWidth()/2 - MeasureText("Exit", 30)/2, game_info.getHeight() * 0.65, 30, ORANGE);
            break;
        default:
            break;
    }
}




void RenderGame() {
    std::vector<std::vector<Cell>> Cells = game_info.getCells();

    bool debug_collision = false;

    float cellSize = 100;
    float radius = cellSize * 0.32;
    if (game_info.getVictory())
        DrawText("Congratulations, you won the game!", cellSize, cellSize - 45, 20, BLACK);
    else if (game_info.getEquality())
        DrawText("Equality! No winner for this party.", cellSize, cellSize - 45, 20, BLACK);
    else
        DrawText("It's the player's turn: ", cellSize, cellSize - 45, 20, BLACK);
    
    if (game_info.getVictory() || game_info.getEquality()) {
        DrawText("Press R to restart", cellSize, cellSize - 25, 20, BLACK);
        if (IsKeyPressed(KEY_R)) {
            game_info.Restart();
        }
    }

    if (!game_info.getEquality() && !game_info.getVictory()) {
        if (game_info.getPlayerTurn() == CIRCLE) {
            DrawCircle(360, cellSize - 35, 15, RED);
            DrawCircle(360, cellSize - 35, 15 * 0.85, RAYWHITE);
        }
        else {
            DrawLineEx({350,cellSize - 45}, {370, cellSize - 25}, 2.0f, BLUE);
            DrawLineEx({370,cellSize - 45}, {350, cellSize - 25}, 2.0f, BLUE);
        }
    }

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (debug_collision) {
                DrawRectangleRec(Cells[y][x].getCollisionBox(), GREEN);
            }

            DrawRectangleLines(cellSize + cellSize * y, cellSize + cellSize * x, cellSize, cellSize, BLACK);
            if (Cells[y][x].getPlayer() == CIRCLE) {
                DrawCircle((cellSize * Cells[y][x].getX()) + cellSize/2, (cellSize * Cells[y][x].getY()) + cellSize/2, radius, RED);
                DrawCircle((cellSize * Cells[y][x].getX()) + cellSize/2, (cellSize * Cells[y][x].getY()) + cellSize/2, radius * 0.85, RAYWHITE);
            } else if (Cells[y][x].getPlayer() == CROSS) {
                DrawLineEx({(cellSize * Cells[y][x].getX()), (cellSize * Cells[y][x].getY())}, {cellSize + cellSize * Cells[y][x].getX(), cellSize + cellSize * Cells[y][x].getY()}, 2.0f, BLUE);
                DrawLineEx({(cellSize * Cells[y][x].getX()), (cellSize + cellSize * Cells[y][x].getY())}, {cellSize + cellSize * Cells[y][x].getX(), cellSize * Cells[y][x].getY()}, 2.0f, BLUE);
            }
        }
    }
}


void PlayGame() {
    RenderGame();


    if (IA_MODE && game_info.getPlayerTurn() == CROSS) {
        game_info.PlayBox(GetRandomValue(0, 2), GetRandomValue(0, 2), game_info.getPlayerTurn());

    } else {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !game_info.getVictory() && !game_info.getEquality()) {
            Vector2 mousePos = GetMousePosition();
            Rectangle clickMouseRect = {mousePos.x - 5/2,mousePos.y - 5/2,5,5};
            DrawRectangleRec(clickMouseRect, {0,0,0,0});
    
            std::vector<std::vector<Cell>> Cells = game_info.getCells();
    
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
    
                    bool collide = CheckCollisionRecs(clickMouseRect, Cells[y][x].getCollisionBox());
                    if (collide)
                        game_info.PlayBox(y, x, game_info.getPlayerTurn());
                }
            }
        }
    }
}

int main(void)
{

    InitWindow(game_info.getWidth(), game_info.getHeight(), game_info.getName());
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GAME_STATE == MAIN_MENU)
            MainMenu();
        else 
            PlayGame();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}