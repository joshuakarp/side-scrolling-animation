#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(Game* game, int width, int height, QWidget* parent)
    : QDialog(parent),
      m_game(game),
      ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->resize(width, height);

    // Establish timer for frame updates.
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(32);

    // Set up playlist so that music track will loop.
    m_playlist = new QMediaPlaylist();
    m_playlist->addMedia(QUrl("qrc:/assets/theValley.wav"));
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    // Set up music track to play (looping with the playlist settings).
    m_music = new QMediaPlayer();
    m_music->setPlaylist(m_playlist);
    m_music->play();
}

Dialog::~Dialog() {
    delete ui;
    delete m_game;
    delete m_timer;
    delete m_playlist;
    delete m_music;
}

void Dialog::nextFrame() {
    update();
}

void Dialog::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    // Render the game object (ie. each of the game's components)
    m_game->renderGame(painter);
}

void Dialog::keyPressEvent(QKeyEvent* event) {
    // On a 'P' press:
    // Either pause or unpause (dependent on whether the timer is currently active)
    // the game components (animation of stickman and background, as well as music)
    if (event->key() == Qt::Key_P) {
        if (m_timer->isActive()) {
            m_timer->stop();
            m_music->pause();
        } else {
            m_timer->start(32);
            m_music->play();
        }
    }

    // On a 'Q' press, safely quit the application.
    if (event->key() == Qt::Key_Q) {
        QApplication::quit();
    }
}
