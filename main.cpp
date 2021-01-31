#include "Dialog.h"
#include "Game.h"

#include <iostream>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <stdexcept>

/**
 * Custom config file location in the "build-AssignmentStage1" folder.
 * Must be manually copied over after initial build of project.
 */
const QString CONFIG_FILENAME = "debug\\config.json";

/**
 * @brief Opens and reads the config .json file (filename specified in CONFIG_FILENAME global variable).
 * @return a QJsonObject containing all other objects (stickman, background, etc) from the .json file.
 * @note if config file cannot be read or found, default config is used.
 */
QJsonObject readConfig() {
    QFile configFile;
    configFile.setFileName(CONFIG_FILENAME);
    bool openResult = configFile.open(QIODevice::ReadOnly | QIODevice::Text);
    // Check if file was found, and successfully opened; otherwise, use the default config compiled
    // with the .exe file.
    if (openResult == false) {
        std::cout << "Unable to read config file (\'" + CONFIG_FILENAME.toStdString()
                     + "\') from directory \'"
                     + (QCoreApplication::applicationDirPath()).toStdString() + "\'." << std::endl;
        std::cout << "Running animation using 'defaultConfig.json'. To set custom config values, "
                     "copy 'config.json' from the source code folder into the above directory and "
                     "edit it from there." << std::endl;
        configFile.setFileName("://defaultConfig.json");
        configFile.open(QIODevice::ReadOnly | QIODevice::Text);
    }
    QString jsonString = configFile.readAll();
    configFile.close();
    QJsonObject config = QJsonDocument::fromJson(jsonString.toUtf8()).object();
    return config;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialise and read the config file.
    QJsonObject config;
    config = readConfig();

    // Get the dimensions of the Dialog window from the config file.
    QJsonValue worldVals = config.value("world");
    if (worldVals.isUndefined()) {
        std::cerr << "'worlds' object not found in config file.\n"
                     "'worlds' (JSON object): specifies dimensions of Dialog window "
                     "(ie. in form {width:<pixels>, height:<pixels>})";
    }
    QJsonObject worldObj = config.value("world").toObject();
    int width = worldObj.value("width").toInt();
    int height = worldObj.value("height").toInt();

    // Instantiate and initialise the Game object (with the given config file)
    Game* newGame = new Game(config);
    try {
        newGame->initialiseGame();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Display and render the Game object.
    Dialog w(newGame, width, height);
    w.show();

    return a.exec();
}
