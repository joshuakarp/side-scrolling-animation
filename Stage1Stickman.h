#ifndef STAGE1STICKMAN_H
#define STAGE1STICKMAN_H

#include "Stickman.h"

/**
 * Implementation for the Stage1Stickman concrete product (base class Stickman).
 */
class Stage1Stickman : public Stickman {
public:
    /**
     * @brief Stage1Stickman cosntructor (makes call to Stickman() constructor)
     * @param sprites - list of all loaded image sprites (for animation)
     * @param size - categorical size of stickman (tiny, normal, large, giant)
     * @param xCoord - starting x position of stickman's top-left corner (pixels, from left of Dialog window)
     * @param yCoord - starting y position of stickman's top left-corner (pixels, from top of Dialog window)
     * @param velocity - starting velocity of stickman (pixels per frame update)
     */
    Stage1Stickman(QList<QPixmap> sprites, std::string size, int xCoord, int yCoord, int velocity);

    /**
     * @brief Stage1Stickman destructor.
     */
    virtual ~Stage1Stickman() override;

    /**
     * @brief Renders the stickman into the Dialog window (Stage1Stickman-specific implementation)
     * @param painter - passed QPainter from Dialog.cpp
     * @see Dialog::paintEvent()
     */
    void render(QPainter& painter) override;
};

#endif // STAGE1STICKMAN_H
