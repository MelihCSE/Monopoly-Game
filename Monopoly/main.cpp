#include "Game.h"
#include "raylib.h"
#include <string>
#include <sstream>

int main() {
    // Initialize raylib window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Monopoly - Raylib GUI");
    SetTargetFPS(60);

    Game game;
    // Quick default players for GUI demo
    game.addPlayer("Player 1");
    game.addPlayer("Player 2");

    std::string lastCardText = "";

    auto tilePosition = [&](int idx) {
        // Map 40 tiles around a rectangle. We'll place the rectangle centered with margins.
        const int left = 120;
        const int top = 80;
        const int right = screenWidth - 120;
        const int bottom = screenHeight - 140;

        const int cols = 10; // tiles per side
        const int tileW = (right - left) / (cols - 1);
        const int tileH = (bottom - top) / (cols - 1);

        Vector2 p{0,0};
        if (idx >= 0 && idx <= 9) {
            // bottom row: 0..9 left-to-right but place 0 at rightmost
            int pos = idx;
            p.x = right - pos * tileW;
            p.y = bottom;
        } else if (idx >= 10 && idx <= 19) {
            // left column: 10..19 bottom-to-top
            int pos = idx - 10;
            p.x = left;
            p.y = bottom - pos * tileH;
        } else if (idx >= 20 && idx <= 29) {
            // top row: 20..29 left-to-right
            int pos = idx - 20;
            p.x = left + pos * tileW;
            p.y = top;
        } else if (idx >= 30 && idx <= 39) {
            // right column: 30..39 top-to-bottom
            int pos = idx - 30;
            p.x = right;
            p.y = top + pos * tileH;
        }
        return p;
    };

    while (!WindowShouldClose()) {
        // Input handling
        Vector2 mousePos = GetMousePosition();
        bool leftReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

        // Define button rectangles
        Rectangle playBtn = {20, 480, 140, 40};
        Rectangle drawBtn = {180, 480, 140, 40};
        Rectangle addBtn  = {340, 480, 140, 40};

        if (leftReleased) {
            if (CheckCollisionPointRec(mousePos, playBtn)) {
                game.playTurn();
            } else if (CheckCollisionPointRec(mousePos, drawBtn)) {
                ChanceCard* c = game.getChanceDeck().drawCard();
                if (c) {
                    lastCardText = c->getText();
                    c->apply(game.getCurrentPlayer(), game);
                } else {
                    lastCardText = "No card";
                }
            } else if (CheckCollisionPointRec(mousePos, addBtn)) {
                int next = (int)game.getPlayers().size() + 1;
                if (next <= 4) {
                    std::ostringstream os;
                    os << "Player " << next;
                    game.addPlayer(os.str());
                }
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Monopoly - Board View", 20, 20, 24, DARKGRAY);

        // Draw board rectangle and tiles
        const int left = 120;
        const int top = 80;
        const int right = screenWidth - 120;
        const int bottom = screenHeight - 140;

        // Draw outline
        DrawRectangleLines(left - 10, top - 10, right - left + 20, bottom - top + 20, DARKGRAY);

        // Draw tiles around
        for (int i = 0; i < 40; ++i) {
            Vector2 pos = tilePosition(i);
            // tile size for drawing small squares
            const int tw = 60;
            const int th = 40;
            DrawRectangle((int)pos.x - tw/2, (int)pos.y - th/2, tw, th, LIGHTGRAY);
            // draw index
            DrawText(TextFormat("%d", i), (int)pos.x - 6, (int)pos.y - 8, 10, BLACK);
        }

        // Players list on right
        DrawText("Players:", right + 20 - 40, 60, 20, BLACK);
        const auto& players = game.getPlayers();
        for (size_t i = 0; i < players.size(); ++i) {
            std::ostringstream os;
            os << (i + 1) << ". " << players[i].getName() << " - $" << players[i].getMoney();
            DrawText(os.str().c_str(), right + 20 - 40, 90 + (int)i * 30, 18, BLACK);
        }

        // Buttons
        DrawRectangleRec(playBtn, LIGHTGRAY);
        DrawText("Play Turn", (int)playBtn.x + 10, (int)playBtn.y + 10, 18, BLACK);

        DrawRectangleRec(drawBtn, LIGHTGRAY);
        DrawText("Draw Chance", (int)drawBtn.x + 10, (int)drawBtn.y + 10, 18, BLACK);

        DrawRectangleRec(addBtn, LIGHTGRAY);
        DrawText("Add Player", (int)addBtn.x + 10, (int)addBtn.y + 10, 18, BLACK);

        // Last card info
        DrawText("Last Chance Card:", 20, bottom + 10, 20, BLACK);
        DrawText(lastCardText.c_str(), 20, bottom + 40, 18, MAROON);

        // Draw player tokens
        Color tokenColors[4] = { RED, BLUE, GREEN, ORANGE };
        for (size_t i = 0; i < players.size(); ++i) {
            Vector2 tp = tilePosition(players[i].getPosition());
            // offset if multiple players on same tile
            float offsetX = (float)( (int)i % 2 ) * 14 - 7;
            float offsetY = (float)( (int)i / 2 ) * 14 - 7;
            DrawCircleV({tp.x + offsetX, tp.y + offsetY}, 10, tokenColors[i % 4]);
            DrawText(players[i].getName().c_str(), (int)tp.x + 14 + (int)offsetX, (int)tp.y + (int)offsetY - 6, 10, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}