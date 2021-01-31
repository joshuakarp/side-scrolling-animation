#ifndef STAGE1BACKGROUND_H
#define STAGE1BACKGROUND_H

#include "Background.h"

/**
 * Implementation for the Stage1Background concrete product (base class Background).
 */
class Stage1Background : public Background {
public:
    /**
     * @brief Stage1Background constructor (makes call to Background() constructor)
     * @param img - source image of background (retrieved from resources.qrc)
     * @param width - width of background image (pixels)
     * @param velocityScaler - background velocity scaling factor (foreground layers move
     *        faster than back layers)
     */
    Stage1Background(QPixmap img, int width, double velocityScaler);

    /**
     * @brief Stage1Background destructor.
     */
    virtual ~Stage1Background() override;

    /**
     * @brief Getter for the velocity scaling factor.
     */
    double getVelocityScaler() const {
        return m_velocityScaler;
    }

    /**
     * @brief Renders the background into the Dialog window (Stage1Background-specific implementation)
     * @param painter - passed QPainter from Dialog.cpp
     * @see Dialog::paintEvent()
     * @param stickmanVelocity - current velocity of the stickman (dictates magnitude of background movement)
     */
    void render(QPainter& painter, int stickmanVelocity) override;

protected:
    double m_velocityScaler;
};

#endif // STAGE1BACKGROUND_H
