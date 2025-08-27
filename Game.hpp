#include <string>
#include <vector>
#include "Cell.hpp"

class Game
{
    private:
        std::string name;
        std::vector<std::vector<Cell>> cells;
        int width;
        int height;
        int player_turn;
        bool victory;
        bool equality;

        bool CheckVictory(int player);
        bool CheckEquality();
    public:
        Game(std::string name, int width, int height);

        int getWidth();
        int getHeight();
        int getPlayerTurn();
        std::vector<std::vector<Cell>> getCells();
        const char *getName();
        void PlayBox(int y, int x, int player);
        bool getVictory();
        bool getEquality();
        void Restart();
};

