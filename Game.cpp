#include "Game.h"

Game::Game(const QJsonObject& config)
    : m_config(config),
      m_backgrounds(QList<Background*>())
{}

Game::~Game() {
    for (Background* b : m_backgrounds) {
        delete b;
    }
    delete m_stickman;
    delete m_factory;
}

void Game::initialiseGame() {
    // Get the stage number we want to execute, and thus the corresponding concrete factory.
    QJsonValue stageVal = m_config.value("stage");
    if (stageVal.isUndefined()) {
        throw std::invalid_argument("'stage' value not found in config file.");
    }
    int stageNum = stageVal.toInt();
    switch (stageNum) {
    case 1:
        m_factory = new Stage1Factory;
        break;
    case 2:
        throw std::invalid_argument("Cannot initialise game: no current implementation for Stage 2.");
    case 3:
        throw std::invalid_argument("Cannot initialise game: no current implementation for Stage 3.");
    default:
        throw std::invalid_argument("Cannot initialise game: invalid stage number in config file.");
    }

    // Check that there are stickman and background objects in the config file.
    QJsonValue stickmanVals = m_config.value("stickman");
    QJsonValue backgroundVals = m_config.value("backgrounds");
    if (stickmanVals.isUndefined()) {
        throw std::invalid_argument("'stickman' object not found in config file. Expected to be of form:\n"
                                    "'stickman' : {sourceFolder, sourceFilename, sourceFiletype, "
                                    "numberOfSprites, size, heights:{ground, tiny, normal, large, giant}, "
                                    "position, velocity}");
    }
    if (backgroundVals.isUndefined()) {
        throw std::invalid_argument("'backgrounds' object not found in config file. Expected to be of form:\n"
                                    "'backgrounds' : [array of {source, width, velocityScaling}]");
    }

    QJsonObject stickmanConfig = stickmanVals.toObject();
    QJsonArray backgroundsConfig = backgroundVals.toArray();

    // Initialising m_stickman and m_backgrounds:
    m_stickman = m_factory->createStickman(stickmanConfig);
    for (QJsonValue i : backgroundsConfig) {
        // i_background refers to the ith background object within the "backgrounds" array of the
        // JSON config file.
        QJsonObject i_background = i.toObject();
        m_backgrounds.append(m_factory->createBackground(i_background));
    }

    // Start the stopwatch for animating stickman (used to cycle through sprite images)
    m_stickman->startStopwatch();
}

void Game::renderGame(QPainter& painter) {
    for (Background* b : m_backgrounds) {
        b->render(painter, m_stickman->getVelocity());
    }
    m_stickman->render(painter);
}
