#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QPixmap>

/**
 * Abstract class for the Background product.
 *
 * In order to achieve seamless, cyclic parallax background scrolling, each background object
 * requies 2 identical images to be rendered together (initially, one is placed at x-coord 0,
 * and the other at x-coord 'width' (this is the width of the background; see below).
 * When bg1's pos becomes < 0-width, then it needs to move to bg2's pos+width (and vice-versa
 * for bg2 and bg1).
 */
//      DIALOG WINDOW
// +---------------------+
// |+--------------------|----------------------------------+
// ||                    |      |                           |
// ||           bg1      |      |           bg2             |
// ||                    |      |                           |
// |+--------------------|----------------------------------+
// +---------------------+

class Background {
public:
    /**
     * @brief Basic Background constructor
     * @param img - source image of background (retrieved from resources.qrc)
     * @param width - width of background image (pixels)
     * @note bg1's x-coord is set to 0, and bg2's set to width.
     */
    Background(QPixmap img, int width)
        : m_img(img), m_width(width), m_bg1XCoord(0), m_bg2XCoord(width) {}

    /**
     * @brief Background destructor (no member variables on heap, so no need for deletes)
     */
    virtual ~Background() {}

    /**
     * Basic getters and setters for member variables.
     */
    const QPixmap& getImg() const {
        return m_img;
    }
    int getWidth() const {
        return m_width;
    }
    int getBG1XCoord() const {
        return m_bg1XCoord;
    }
    int getBG2XCoord() const {
        return m_bg2XCoord;
    }
    void setBG1XCoord(int x) {
        m_bg1XCoord = x;
    }
    void setBG2XCoord(int x) {
        m_bg2XCoord = x;
    }

    /**
     * @brief Moves the position of background 1 (to the left) by passed value
     * @param x - amount to move the background (to the left of the screen)
     */
    void shiftBackground1(int x) {
        m_bg1XCoord -= x;
    }

    /**
     * @brief Moves the position of background 2 (to the left) by passed value
     * @param x - amount to move the background (to the left of the screen)
     */
    void shiftBackground2(int x) {
        m_bg2XCoord -= x;
    }

    /**
     * @brief Pure virtual method for rendering the background into the Dialog window
     * @param painter - passed QPainter from Dialog.cpp
     * @see Dialog::paintEvent()
     * @param stickmanVelocity - current velocity of the stickman (dictates magnitude of background movement)
     */
    virtual void render(QPainter& painter, int stickmanVelocity) = 0;

protected:
    QPixmap const m_img;
    int const m_width;
    int m_xCoord;

    int m_bg1XCoord;
    int m_bg2XCoord;
};

#endif // BACKGROUND_H
