#ifndef DIALOG_H
#define DIALOG_H

#include "Game.h"

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>

namespace Ui {
class Dialog;
}

/**
 * Class for instantiating a dialog window to display animation.
 */
class Dialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Basic Dialog constructor
     * @param game - pointer to Game object that encapsulates the game components (factory, stickman, backgrounds)
     * @param width - pixel width of the dialog window
     * @param height - pixel height of the dialog window
     * @param parent - pointer to potential parent QObject (for draw order and memory managemnent)
     */
    Dialog(Game* game, int width, int height, QWidget* parent = nullptr);

    /**
      * @brief Basic Dialog destructor (safely deletes all member variables from heap)
      */
    ~Dialog();

public slots:
    /**
     * @brief Connected with m_timer to be repetitively called (simply calls update(), which in turn calls paintEvent())
     */
    void nextFrame();

protected:
    /**
     * @brief Instantiates QPainter object, and calls m_game's render method (and thus, each game component's
     *        own render method)
     * @param event - potential parameters for paint events (ie. a specific region to re-paint)
     */
    void paintEvent(QPaintEvent* event);

    /**
     * @brief Establishes actions to occur on specific key presses (namely, P to pause/unpause game, and Q to quit game)
     * @param event - the parameters of the key press (eg. the specific key pressed)
     */
    void keyPressEvent(QKeyEvent* event);

private:
    Game* m_game;
    Ui::Dialog *ui;
    QTimer* m_timer;
    // Provides looping background music
    QMediaPlaylist* m_playlist;
    // Facilitates pausing music without returning to beginning of track
    QMediaPlayer* m_music;
};

#endif // DIALOG_H
