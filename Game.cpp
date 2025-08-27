#include "Game.hpp"

Game::Game(std::string name, int w, int h) 
: name(name), width(w), height(h) {
    this->victory = false;
    this->equality = false;
    this->player_turn = -2;
    this->cells.resize(3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Cell cell(100 * (j + 1) + 5, 100 * (i + 1) + 5, 90, 90);
            cell.setPlayer(-1);
            cell.setPositions(j + 1, i + 1);
            this->cells[i].push_back(cell);
        }
    }
}



int Game::getWidth() { return this->width; };
int Game::getHeight() { return this->height; };

const char *Game::getName() { return this->name.c_str(); };

bool Game::CheckVictory(int player) {
    int possibilities[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int count = 0;
    int col = 0;

    for (int i = 0; i < 8; i++) {
        count = 0;
        for (int j = 0; j < 3; j++) {
            int row = possibilities[i][j] / 3;
            int col = possibilities[i][j] % 3;
            if (this->cells[row][col].getPlayer() == player)
                count++;
            if (count >= 3)
                return true;
        }
    }
    return false;
};

bool Game::CheckEquality() {
    int cellsfilled = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->cells[i][j].getPlayer() != -1) // check if cell is not empty
                cellsfilled += 1;
        }
    }
    if (cellsfilled == 9)
        return true;
    return false;
}

void Game::PlayBox(int y, int x, int player) {
    if (this->cells[y][x].getPlayer() != -1) return;
    this->cells[y][x].setPlayer(player);


    if (CheckVictory(player)) {
        this->victory = true;
        this->winner = player;
    }
    if (CheckEquality()) {
        this->equality = true;
    }
    
    if (player == -2)
        this->player_turn = -3;
    else if (player == -3)
        this->player_turn = -2;
}

std::vector<std::vector<Cell>> Game::getCells() {
    return this->cells;
}

int Game::getPlayerTurn() { return this->player_turn; };

bool Game::getVictory() {
    return this->victory;
}

int Game::getWinner() {
    return this->winner;   
}

bool Game::getEquality() { return this->equality; };