#ifndef GAME_H
#define GAME_H

#include "AbstractStageFactory.h"
#include "Stage1Factory.h"
#include "Background.h"
#include "Stickman.h"

#include <QJsonArray>
#include <QJsonObject>

/**
 * "Worker" class for rendering and updating the state of the 'game'.
 * ie. it encapsulates the factory, stickman and background objects of the game.
 * As a result of the abstract factory, this class is also impartial to the concrete types of the
 * graphical objects it contains, as the objects themselves are simply stored as pointers to their
 * superclass, abstract type.
 */
class Game {
public:
    /**
     * Constructor for game object. Assumes JSON config file is of the form:
     *             "stage" : <game stage number to run>
     *          "stickman" : { size, position, velocity }
     *       "backgrounds" : [ array of { filename, width, velocityScaling } ]
     * @param config - the config file in its entirety (ie. containing all objects) as a QJsonObject
     * @see return value of readConfig() in main.cpp
     * @note initialises ONLY m_config and m_backgrounds list - other member variables are dependent
     *       on m_config, and are thus initialised in initialiseGame()
     */
    Game(const QJsonObject& config);
    ~Game();

    /**
     * Instantiates remainder of member variables, reading from m_config.
     * @throws std::invalid_argument if any part of the config file is invalid or missing
     */
    void initialiseGame();

    QList<Background*> getBackgrounds() const {
        return m_backgrounds;
    }

    /**
     * @brief Renders each game object (stickman and background layers), ordering their renders appropriately.
     * @brief Does so by making calls to each game object's own render() method
     * @param painter - passed QPainter from Dialog.cpp
     * @see Dialog::paintEvent()
     */
    void renderGame(QPainter& painter);

private:
    QJsonObject m_config;
    AbstractStageFactory* m_factory = nullptr;
    Stickman* m_stickman = nullptr;
    // Visual background is composed of layers of Background objects to provide parallax scrolling).
    QList<Background*> m_backgrounds;
};

#endif // GAME_H
