#include "Stage1Stickman.h"

Stage1Stickman::Stage1Stickman(QList<QPixmap> sprites, std::string size, int xCoord, int yCoord, int velocity)
    : Stickman(sprites, size, xCoord, yCoord, velocity)
{}

Stage1Stickman::~Stage1Stickman() {}

void Stage1Stickman::render(QPainter& painter) {
    painter.drawPixmap(this->getXCoord(), this->getYCoord(), this->getCurrentSprite());
    // Update the sprite to be the next required one (either stay as current one, or move to next one in sequence,
    // depending on whether enough time has passed according to m_stopwatch)
    this->setNextSprite();
}
