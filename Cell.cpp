#include "Cell.hpp"
Cell::Cell(float x, float y, float w, float h) {
    this->collisionbox = {x,y,w,h};
}

void Cell::setPlayer(int player) {
    this->player = player;
}

int Cell::getPlayer() { return this->player; };

int Cell::getX() { return this->positions.x; };
int Cell::getY() { return this->positions.y; };

void Cell::setPositions(int x, int y) {
    this->positions.x = x;
    this->positions.y = y;
}

Rectangle Cell::getCollisionBox() {
    return this->collisionbox;
}

int Cell::getSize() {
    return this->collisionbox.width;
}