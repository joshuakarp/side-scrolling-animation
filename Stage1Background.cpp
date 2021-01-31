#include "Stage1Background.h"

Stage1Background::Stage1Background(QPixmap img, int width, double velocityScaler)
    : Background(img, width),
      m_velocityScaler(velocityScaler)
{}

Stage1Background::~Stage1Background() {}

void Stage1Background::render(QPainter &painter, int stickmanVelocity) {
    // 1. Shift both background objects (by velocity of stickman * velocity scaling factor)
    int displacement = int(stickmanVelocity * m_velocityScaler);
    // If displacement as float is between 0 and 1, integer cast will make it 0. So make it 1 instead.
    if (displacement == 0) {
        displacement = 1;
    }
    this->shiftBackground1(displacement);
    this->shiftBackground2(displacement);

    // 2. Check if either background objects are past 0-width
    // If they are, move it to: other background's position + width.
    if (m_bg1XCoord < 0 - m_width) {
        m_bg1XCoord = m_bg2XCoord + m_width;
    } else if (m_bg2XCoord < 0 - m_width) {
        m_bg2XCoord = m_bg1XCoord + m_width;
    }

    // 3. Render the background images.
    painter.drawPixmap(m_bg1XCoord, 0, m_img);
    painter.drawPixmap(m_bg2XCoord, 0, m_img);
}
