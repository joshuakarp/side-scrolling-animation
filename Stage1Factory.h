#ifndef STAGE1FACTORY_H
#define STAGE1FACTORY_H

#include "AbstractStageFactory.h"
#include "Stage1Stickman.h"
#include "Stage1Background.h"

#include <QApplication>
#include <QJsonArray>
#include <QJsonObject>

/**
 * Concrete factory for stage 1 of the assignment.
 * Used to instantiate concrete products (specifically, Stage1Stickmen and Stage1Backgrounds)
 */
class Stage1Factory : public AbstractStageFactory {
public:
    /**
     * @brief Instantiates new Stage1Stickman object from config file
     * @param stickmanConfig - JSON object containing stickman parameters (retrieved from config file)
     * @return pointer to new Stage1Stickman
     * @throws std::invalid_argument if any part of the stickman config is invalid or missing
     */
    Stickman* createStickman(const QJsonObject& stickmanConfig) override;

    /**
     * @brief Instantiates new Stage1Background object from config file
     * @param backgroundConfig - JSON object containing background parameters (retrieved from config file)
     * @return pointer to new Stage1Background
     * @throws std::invalid_argument if any part of the background config is invalid or missing
     */
    Background* createBackground(const QJsonObject& backgroundConfig) override;
};

#endif // STAGE1FACTORY_H
