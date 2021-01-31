#ifndef STICKMAN_H
#define STICKMAN_H

#include <QElapsedTimer>
#include <QList>
#include <QPainter>
#include <QPixmap>

/**
 * Abstract class for the Stickman product.
 *
 * To facilitate animation of the stickman, a sequence of images is stored in each stickman object
 * (each image referred to as a sprite) to provide the illusion of animation.
 */
class Stickman {
public:
    /**
     * @brief Basic Stickman constructor
     * @param sprites - list of all loaded image sprites (for animation)
     * @param size - categorical size of stickman (tiny, normal, large, giant)
     * @param xCoord - starting x position of stickman's top-left corner (pixels, from left of Dialog window)
     * @param yCoord - starting y position of stickman's top left-corner (pixels, from top of Dialog window)
     * @param velocity - starting velocity of stickman (pixels per frame update)
     */
    Stickman(QList<QPixmap> sprites, std::string size, int xCoord, int yCoord, int velocity)
        : m_sprites(sprites), m_currentSprite(0), m_size(size), m_xCoord(xCoord), m_yCoord(yCoord),
          m_velocity(velocity), m_stopwatch(QElapsedTimer()) {}

    /**
     * @brief Stickman destructor
     */
    virtual ~Stickman() {}

    /**
     * Basic getters and setters for member variables.
     */
    int getXCoord() const {
        return m_xCoord;
    }
    int getYCoord() const {
        return m_yCoord;
    }
    int getVelocity() const {
        return m_velocity;
    }
    /**
     * @brief Gets the current sprite image in animation sequence
     * @return reference to current sprite image
     */
    const QPixmap& getCurrentSprite() const {
        return m_sprites.at(m_currentSprite);
    }
    /**
     * @brief Provides stickman animation; moves to the next sprite image every (1/m_velocity) seconds.
     * ie. updates the current sprite index to be the next one in list (cyclically; if current index
     * is 5, next index is 0).
     * Restarts the stopwatch (to 0 seconds elapsed) to facilitate check for next sprite update
     */
    void setNextSprite() {
        if (m_stopwatch.elapsed() > (1000 / m_velocity)) {
            m_currentSprite = (m_currentSprite + 1) % m_sprites.size();
            m_stopwatch.restart();
        }
    }

    /**
     * @brief Starts the stopwatch for sprite animation.
     */
    void startStopwatch() {
        m_stopwatch.start();
    }

    /**
     * @brief Move position of stickman
     * @param x - number of pixels to move stickman to right (or left, if negative)
     * @param y - number of pixels to move stickman towards top of window (or bottom, if negative)
     * @note the -= distinction for m_yCoord (as coordinate system has top-left corner as 0,0)
     */
    void moveStickman(int x, int y) {
        m_xCoord += x;
        m_yCoord -= y;
    }

    /**
     * @brief Pure virtual method for rendering the stickman into the Dialog window
     * @param painter - passed QPainter from Dialog.cpp
     * @see Dialog::paintEvent()
     */
    virtual void render(QPainter& painter) = 0;

protected:
    QList<QPixmap> m_sprites;
    int m_currentSprite;
    std::string m_size;
    int m_xCoord;
    int m_yCoord;
    int m_velocity;
    QElapsedTimer m_stopwatch;
};

#endif // STICKMAN_H
