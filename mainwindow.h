#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QPoint>
#include <QMouseEvent>
#include "board.h"
#include "createclient.h"
#include "createserver.h"
#include <QTimer>

//enum GameTurn {WHITE_TURN, BLACK_TURN};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void drawBoard();
    void drawPiece(Piece* p);
    void drawHighlight();
    void mousePressEvent(QMouseEvent* ev);



    CreateServer* server = nullptr;
    CreateClient* client = nullptr;
    bool isClient = false;

    bool isWhiteTurn = true;
    bool myTurn = false;

    bool isBegin = false;
//    void isEnd();

    QPoint getToggled();
    void setToggled(QPoint);
    void clearToggled();
    QTimer* timer;

    Board* board;

    ~MainWindow();

    void save_file();
    void save_to_net(QTextStream&);
    void syncBoard(QTextStream & stream);

    void read_from_net(QTextStream&);
    void initTime();
    void processTime();
    int TimeLeft = 60;

    void endGame();

public slots:
    void process();


private slots:
    void on_actionNew_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_actionSave_triggered();

    void on_actionResign_triggered();

    void on_actionStart_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
