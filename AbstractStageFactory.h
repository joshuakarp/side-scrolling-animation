#ifndef ABSTRACTSTAGEFACTORY_H
#define ABSTRACTSTAGEFACTORY_H

#include "Stickman.h"
#include "Background.h"

/**
 * Abstract factory class used as an interface for concrete "stage" factories (ie. a concrete factory
 * to be created for each stage of assignment). Each stage requires a 'Stickman' and' Background'
 * product, with their concrete implementations differing between assignment stages (eg. stage 1 only
 * requires limited functionality for the stickman, whereas later stages require dynamic movement and
 * collision detection). As such, we can represent each stage's stickman and background as a separate
 * concrete product, instantiated by their respective concrete factory.
 */
class AbstractStageFactory {
public:
    virtual ~AbstractStageFactory() {}

    /**
     * @brief Instantiates new Stickman object from config file
     * @param stickmanConfig - JSON object containing stickman parameters (retrieved from config file)
     * @return pointer to new Stickman (subclass type dependent on concrete factory)
     */
    virtual Stickman* createStickman(const QJsonObject& stickmanConfig) = 0;

    /**
     * @brief Instantiates new Background object from config file
     * @param backgroundConfig - JSON object containing background parameters (retrieved from config file)
     * @return pointer to new Background (subclass type dependent on concrete factory)
     */
    virtual Background* createBackground(const QJsonObject& backgroundConfig) = 0;
};

#endif // ABSTRACTSTAGEFACTORY_H
