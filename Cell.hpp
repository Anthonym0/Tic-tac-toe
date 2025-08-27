#include "raylib/src/raylib.h"

class Cell
{
    private:
        int player;
        Vector2 positions;
        Rectangle collisionbox;
    public:
        Cell(float x, float y, float w, float h);
        void setPlayer(int player);
        int getPlayer();
        int getX();
        int getY();
        Rectangle getCollisionBox();
        int getSize();
        void setPositions(int x, int y);
};

