#include "Stage1Factory.h"

Stickman* Stage1Factory::createStickman(const QJsonObject& stickmanConfig) {
    // Firstly, get all the values from their respective objects in config.
    // Source values:
    QJsonValue folderVal = stickmanConfig.value("sourceFolder");
    QJsonValue filenameVal = stickmanConfig.value("sourceFilename");
    QJsonValue filetypeVal = stickmanConfig.value("sourceFiletype");
    QJsonValue numSpritesVal = stickmanConfig.value("numberOfSprites");
    // Stickman property values:
    QJsonValue sizeVal = stickmanConfig.value("size");
    QJsonValue heightVals = stickmanConfig.value("heights");
    QJsonValue positionVal = stickmanConfig.value("position");
    QJsonValue velocityVal = stickmanConfig.value("velocity");
    QJsonValue groundVal = stickmanConfig.value("groundCoordinate");

    // Throw an exception if any of these values are not found in the config file:
    if (folderVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'sourceFolder' value not found in config file.\n"
                                    "'sourceFolder' (string): local directory location of stickman size assets, "
                                    "in .qrc format (eg. \'//graphics/stickman/\')");
    }
    if (filenameVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'sourceFilename' value not found in config file.\n"
                                    "'sourceFilename' (string): filename of all stickman sprites "
                                    "(excluding appended file number; usually just 'sprite')");
    }
    if (filetypeVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'sourceFieltype' value not found in config file.\n"
                                    "'sourceFiletype' (string): filetype of all stickman sprites (usually '.png')");
    }
    if (numSpritesVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'numberOfSprites' value not found in config file.\n"
                                    "'numberOfSprites' (int): number of sprite images for each stickman "
                                    "size (used for animation)");
    }
    if (sizeVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'size' value not found in config file.\n"
                                    "'size' (string): categorical size of stickman (tiny, normal, large, giant)");
    }
    if (heightVals.isUndefined()) {
        throw std::invalid_argument("Stickman 'heights' object not found in config file.\n"
                                    "'heights' (JSON object): object containing the pixel heights of all "
                                    "stickman sizes (ie. in form {tiny:<height>, normal:<height>, etc})");
    }
    if (positionVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'position' value not found in config file.\n"
                                    "'position' (int): initial x-coordinate of stickman (taken from "
                                    "left-most side of stickman sprite)");
    }
    if (velocityVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'velocity' value not found in config file.\n"
                                    "'velocity' (int): initial speed (in pixels per frame update) of stickman "
                                    "(and thus, the speed of the background layers)");
    }
    if (groundVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'groundCoordinate' value not found in config file.\n"
                                    "'groundCoordinate' (int): y-coordinate of the top of ground background layer "
                                    "(used to position stickman's y-coordinate appropriately)");
    }

    // At this stage, all stickman parameters exist. So systematically get each of the values for the
    // Stage1Stickman constructor.
    // 1. Load all sprite images.
    QList<QPixmap> sprites;
    for (int i = 1; i <= numSpritesVal.toInt(); i++) {
        // File path is in form '//graphics/stickman/<size>/sprite<spriteNum><filetype>
        QString spritePath = folderVal.toString() + sizeVal.toString() + "/" + filenameVal.toString() +
                             QString::number(i) + filetypeVal.toString();
        QPixmap i_sprite(spritePath);
        // Check that current sprite image can be found.
        if (i_sprite.isNull()) {
            throw std::invalid_argument("Stickman sprite image file not found: '" + spritePath.toStdString() + "'");
        }
        sprites.append(i_sprite);
    }

    // 2. Get stickman size. Make sure it's a valid size.
    std::string stickmanSize = sizeVal.toString().toStdString();
    if (stickmanSize != "tiny" && stickmanSize != "normal" && stickmanSize != "large" && stickmanSize != "giant") {
        throw std::invalid_argument("Invalid stickman 'size' value ('" + stickmanSize + "') in config file.\n"
                                    "'size' must be specified as any of the following: {tiny, normal, large, giant}");
    }

    // 3. Get stickman's initial x position.
    int xCoord = positionVal.toInt();

    // 4. Get stickman's initial y position. This is dependent on the height value (for stickman size) and ground coordinate.
    /**
      * @todo Stage2/3Stickman will instead need to store the ground and height values as parameters in Stickman object
      * @todo (in order to facilitate jumping, changing size of stickman mid-game, etc)
      */
    QJsonObject heightObj = heightVals.toObject();
    QJsonValue heightVal;
    if (stickmanSize == "tiny") {
        heightVal = heightObj.value("tiny");
    } else if (stickmanSize == "normal") {
        heightVal = heightObj.value("normal");
    } else if (stickmanSize == "large") {
        heightVal = heightObj.value("large");
    } else if (stickmanSize == "giant") {
        heightVal = heightObj.value("giant");
    }
    // Make sure the height value exists in the height object in JSON.
    if (heightVal.isUndefined()) {
        throw std::invalid_argument("Stickman 'heights':'" + stickmanSize + "' value not found in config file.\n"
                                    "'heights':'" + stickmanSize + "' (int): pixel height of stickman size '"
                                    + stickmanSize + "'");
    }
    // The y-coordinate of the stickman is the coordinate of the top-left corner of the sprite image.
    // This is equal to: (the y-coordinate of the top of the ground later - the sprite's height)
    int yCoord = groundVal.toInt() - heightVal.toInt();

    // 5. Get stickman's initial velocity.
    int velocity = velocityVal.toInt();

    return new Stage1Stickman(sprites, stickmanSize, xCoord, yCoord, velocity);
}

Background* Stage1Factory::createBackground(const QJsonObject& backgroundConfig) {
    // Firstly, get the value from the "source" object in config (throw exception if doesn't exist).
    QJsonValue sourceVal = backgroundConfig.value("source");
    if (sourceVal.isUndefined()) {
        throw std::invalid_argument("Background 'source' value not found in config file for one of the background images.");
    }

    // Store this source value as an identifier for potential exceptions.
    std::string imgLocation = sourceVal.toString().toStdString();

    // Get all parameters from the passed background JSON object.
    QJsonValue widthJsonVal = backgroundConfig.value("width");
    QJsonValue scalerVal = backgroundConfig.value("velocityScaling");
    // Make sure all these parameters exist in the background object in JSON file.
    if (widthJsonVal.isUndefined()) {
        throw std::invalid_argument("Background 'width' value not found in config file for image '" + imgLocation + "'.\n"
                                    "'width' (int): pixel width of background image");
    }
    if (scalerVal.isUndefined()) {
        throw std::invalid_argument("Background 'velocityScaling' value not found in config file for image '"
                                    + imgLocation + "'.\n"
                                    "'velocityScaling' (double): velocity scaling factor for background image "
                                    "(see parralax scrolling)");
    }

    // At this point, all parameters exist.
    // Now check that the image source, width, and velocityScaling values are all valid.
    QPixmap img(sourceVal.toString());
    if (img.isNull()) {
        throw std::invalid_argument("Background image file not found: '" + imgLocation + "'");
    }

    int width = backgroundConfig.value("width").toInt();
    if (width <= 0) {
        throw std::invalid_argument("Invalid 'width' value (" + std::to_string(width) +
                                    ") in config file for background image '" + imgLocation + "'.");
    }
    double velocityScaling = backgroundConfig.value("velocityScaling").toDouble();
    if (velocityScaling <= 0) {
        throw std::invalid_argument("Invalid 'velocityScaling' value (" + std::to_string(velocityScaling) +
                                    ") in config file for background image '" + imgLocation + "'.");
    }

    return new Stage1Background(img, width, velocityScaling);
}
