#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <string.h>
#include <QStringList>
#include <QFileDialog>
#include <QFileDialog>
//#include "board.h"
#include "createserver.h"
#include "createclient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    board(new Board),
    timer(new QTimer)
{
    ui->setupUi(this);
    setFixedSize(600, 600);
    ui->lcdNumber->setEnabled(false);
    ui->actionStart->setEnabled(false);
    ui->actionResign->setEnabled(false);

}

void MainWindow::initTime() {
    TimeLeft = 60;
    timer->disconnect();
    ui->lcdNumber->setEnabled(true);
    ui->lcdNumber->display(TimeLeft);
}

void MainWindow::processTime() {
    if (!myTurn) return;
    initTime();
    timer->start(1000);
    connect(timer, &QTimer::timeout, [=](){
        ui->lcdNumber->display(--TimeLeft);
        if (TimeLeft <= 0) {
            if (isClient) {
                if (client != nullptr) {
                    auto& out = client->transmit();
                    out << "timeout" << endl;
                    QMessageBox::information(this, "Timeout", "You have running out of time! You lost!",
                                             QMessageBox::Ok);
                }
            } else {
                if (server !=nullptr) {
                    auto& out = server->transmit();
                    out << "timeout" << endl;
                    QMessageBox::information(this, "Timeout", "You have running out of time! You lost!",
                                             QMessageBox::Ok);
                }
            }
            timer->stop();
        }
    });
}


void MainWindow::paintEvent(QPaintEvent* event) {
    drawBoard();
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (board->occupied[i][j] && board->board[i][j]->isEaten == false) {
                drawPiece(board->board[i][j]);
            }
        }
    }
}

void MainWindow::drawBoard() {
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(210, 180, 140));
    p.drawRect(QRect(QPoint(60, 60), QPoint(540, 540)));
    // (100, 100) ->  (500, 500)
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if ((i + j) % 2 == 0) {
                p.setBrush(QColor(255, 245, 238, 180));
                p.drawRect(QRect(QPoint(50 + j * 50, 50 + i * 50), QPoint(100 + j * 50, 100 + i * 50)));
            } else if ((i + j) % 2 == 1) {
                p.setBrush(QColor(135, 51, 36, 180));
                p.drawRect(QRect(QPoint(50 + j * 50, 50 + i * 50), QPoint(100 + j * 50, 100 + i * 50)));
            }

            if (board->highlight[j][i]) {
                p.setBrush(QColor(135, 206, 235, 1));
                 p.drawRect(QRect(QPoint(50 + j * 50, 50 + (9 - i) * 50), QPoint(100 + j * 50, 100 + (9 - i) * 50)));
                 qDebug() << QPoint(i, j);
            }
        }
    }
    //覆盖问题？？？？
    for (int i = 1; i <= 8; ++i ){
        for (int j = 1; j <= 8 ;++j) {
            if (board->highlight[j][i]) {
                p.setBrush(QColor(135, 206, 235, 100));
                 p.drawRect(QRect(QPoint(50 + j * 50, 50 + (9 - i) * 50), QPoint(100 + j * 50, 100 + (9 - i) * 50)));
                 qDebug() << QPoint(i, j);
            }
        }
    }

    QFont f;
    f.setPointSize(18);
    p.setFont(f);

    p.setPen(QPen(QColor(255, 250, 250), 4));
    p.setBrush(QColor(255, 255, 255));

    for (int i = 1; i <= 8; ++i) {
        p.drawText(QRect(QPoint(60, 550 - i * 50), QPoint(100, 500 - i * 50)), Qt::AlignCenter, QString::number(i));
    }
    for (int i = 1; i<=8; ++i) {
        char c = i + 96;
        p.drawText(QRect(QPoint(50 + i * 50, 500), QPoint(100 + i * 50, 530)), Qt::AlignCenter, QString(c));
    }
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void MainWindow::drawPiece(Piece* p) {
//    QPixmap pm("/Users/chenwei/Desktop/week8/chess/src/black_bishop.png");
    QPainter gongjuren(this);
    auto paint = [&](QPixmap pm) {
        QPainter gongjuren(this);
        gongjuren.setRenderHint(QPainter::SmoothPixmapTransform);
        pm = pm.scaled(QSize(40, 40), Qt::KeepAspectRatio);
        int x = p->position.x() * 50 + 55;
        int y = (9 - p->position.y()) * 50 + 55;
        gongjuren.drawPixmap(QRect(QPoint(x, y), QPoint(x, y)+QPoint(40 ,40)), pm);
    };

    if (!p->isEaten) {
        if (getToggled() == p->position)
        {
            int x = p->position.x() * 50 + 65;
            int y = (9 - p->position.y()) * 50 + 65;
            gongjuren.setBrush(QColor(255, 255, 255, 120));
            gongjuren.drawEllipse(QRect(QPoint(x, y), QPoint(x, y)+QPoint(20 ,20)));
        }
        if (p->isWhite) {
            if (p->type == PAWN) {
                QPixmap pm(":/pics/src/white_pawn.png");
                paint(pm);
            } else if (p->type == ROOK) {
                QPixmap pm(":/pics/src/white_rook.png");
                paint(pm);
            } else if (p->type == KNIGHT) {
                QPixmap pm(":/pics/src/white_knight.png");
                paint(pm);
            } else if (p->type == BISHOP) {
                QPixmap pm(":/pics/src/white_bishop.png");
                paint(pm);
            } else if (p->type == QUEEN) {
                QPixmap pm(":/pics/src/white_queen.png");
                paint(pm);
            } else if (p->type == KING) {
                QPixmap pm(":/pics/src/white_king.png");
                paint(pm);
            }
        } else if (!p->isWhite) {
            if (p->type == PAWN) {
                QPixmap pm(":/pics/src/black_pawn.png");
                paint(pm);
            } else if (p->type == ROOK) {
                QPixmap pm(":/pics/src/black_rook.png");
                paint(pm);
            } else if (p->type == KNIGHT) {
                QPixmap pm(":/pics/src/black_knight.png");
                paint(pm);
            } else if (p->type == BISHOP) {
                QPixmap pm(":/pics/src/black_bishop.png");
                paint(pm);
            } else if (p->type == QUEEN) {
                QPixmap pm(":/pics/src/black_queen.png");
                paint(pm);
            } else if (p->type == KING) {
                QPixmap pm(":/pics/src/black_king.png");
                paint(pm);
            }
        }
    }
}

QPoint MainWindow::getToggled() {
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (board->occupied[i][j] == true) {
                if (board->board[i][j]->isSelected)
                    return QPoint(i, j);
            }
        }
    }
    return  QPoint(0, 0);
}

void MainWindow::clearToggled() {
    board->board[getToggled().x()][getToggled().y()]->isSelected = false;
}

void MainWindow::setToggled(QPoint p) {
    if (isWhiteTurn && board->board[p.x()][p.y()]->isWhite == false) return;
    if (!isWhiteTurn && board->board[p.x()][p.y()]->isWhite == true) return;
    clearToggled();
    board->board[p.x()][p.y()]->isSelected = true;
    board->set_highlight(board->board[p.x()][p.y()]->get_access()); // 加高亮
    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    int x = ev->x() / 50 - 1;
    int y = 10 - ev->y() / 50 ;
    qDebug() << ev->x() << ev->y() <<x << y;
    // 1 判断轮次
    // 2 判断有没有选中棋子 （选中棋子
    // 3 选中的棋子 移动=抓子 （如果键入无效坐标 => 5/6
    // 4 回合结束
    // 5 选中新的 己方棋子
    // 6 取消 已选棋子
    if (!myTurn) return;
    if (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
        //1 没有已选中的棋子 现在是错的
        if (getToggled() == QPoint(0, 0)) {
            qDebug() << "1";
            // 2 若满足条件则选中一个棋子 否则什么也不做
            if (board->occupied[x][y] == true) {
                qDebug() << "2";
                if (isWhiteTurn == board->board[x][y]->isWhite)
                    setToggled(QPoint(x, y));
            }
        //3 已经有选中的棋子了
        } else if (getToggled() != QPoint(0, 0)) {
            qDebug() << "3";
            // 4 点击是己方的一个切换命令
            if (board->occupied[x][y] == true && getToggled()!= QPoint(x,y) && board->board[x][y]->isEaten == false &&
                    board->board[x][y]->isWhite == board->board[getToggled().x()][getToggled().y()]->isWhite) {
                qDebug() << "4";
                setToggled(QPoint(x, y));
            // 5 点击点到了对方的棋子
            } else if (board->occupied[x][y] == true && getToggled()!= QPoint(x,y) && board->board[x][y]->isEaten == false &&
                       board->board[x][y]->isWhite != board->board[getToggled().x()][getToggled().y()]->isWhite) {
                   qDebug() << "5";
                   // 9 capture
                   if (board->highlight[x][y] == true) {
                       qDebug() << "9";
                       board->board[getToggled().x()][getToggled().y()]->move_new(QPoint(x, y));
                       clearToggled();
                       isWhiteTurn = !isWhiteTurn; // 【下一步】
                       myTurn = false;
                       initTime();
                       if (isClient) {
                           qDebug() << "CLIENT MOVE";
                           qDebug() << "i am a client i am a client i am a client i am a client i am a client ";
                           if (client!= nullptr) {
                               auto& out = client->transmit();
                               out << "turn" << endl;
                               save_to_net(out);
                           }
                       } else {
                           qDebug() << "SERVER MOVE";
                           if (server!= nullptr) {
                               auto& out = server->transmit();
                               out << "turn" << endl;
                               save_to_net(out);
                           }
                       }

                       if (!board->check_status()) endGame();

                   // 10 切换成对方的棋子 【仅供调试】 就不用了
                   }

            // 6 只考虑移动操作
            } else {
                qDebug() << "6";
                // 7 是可达区域
                if (board->highlight[x][y]) {
                    qDebug() << "7";
                    board->board[getToggled().x()][getToggled().y()]->move_new(QPoint(x, y));
                    clearToggled();
                    isWhiteTurn = !isWhiteTurn; // 【下一步】
                    myTurn = false;
                    initTime();
                    if (isClient) {
                        qDebug() << "CLIENT MOVE";
                        qDebug() << "i am a client i am a client i am a client i am a client i am a client ";
                        if (client!= nullptr) {
                            auto& out = client->transmit();
                            out << "turn" << endl;
                            save_to_net(out);
                        }
                    } else if (!isClient){
                        qDebug() << "SERVER MOVE";
                        if (server!= nullptr) {
                            auto& out = server->transmit();
                            out << "turn" << endl;
                            save_to_net(out);
                        }
                    }
                    if (!board->check_status()) endGame();
                // 8 不可达
                } else {
                    qDebug() << "8 not accessible";
                }
            }
        }
    }
    this->update();
}

void MainWindow::save_file() {
    auto filename = QFileDialog::getSaveFileName(0, "Save a file", QDir::homePath());
    if (!filename.isEmpty()) {
        QFile f(filename);
        if (f.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&f);
            board->save_current_board(out, isWhiteTurn);
            f.flush();
            f.close();
        }
    }
}

void MainWindow::process() {
    qDebug() << "fuck process";
    if (isClient) {
        //
        auto& in = client->transmit();
        read_from_net(in);
    } else if (!isClient) {
        auto& in = server->transmit();
        read_from_net(in);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_to_net(QTextStream & stream) {
    qDebug() << "fuck fuck fuck fuck fuck";
//    stream << "turn" << endl;
    stream << "sync" << endl;
    board->save_current_board(stream, isWhiteTurn);
    stream << "sync_done" << endl;
}

void MainWindow::syncBoard(QTextStream & stream) {
    stream << "sync" << endl;
    qDebug() << "sync" << endl;
    board->save_current_board(stream, isWhiteTurn);
    stream << "sync_done" << endl;
}

void MainWindow::read_from_net(QTextStream & stream) {
    qDebug() << "fuck read net";

    QString info;
    while (!stream.atEnd()) {
        auto line = stream.readLine();
        qDebug() << "read from net LINE **********************************";
        if (line == "sync") {
            qDebug() << "read from net SYNC **********************************";
            auto tempLine = stream.readLine();
            while(tempLine!= "sync_done") {
                info += tempLine + "\n";
                tempLine = stream.readLine();
    //                qDebug() << tempLine;
            }
        } else if (line == "turn") {
            if (isWhiteTurn) {
                qDebug() << "white turn";
            } else qDebug() << "black turn";

            isWhiteTurn = !isWhiteTurn;
            myTurn = true;

            if (isWhiteTurn) {
                qDebug() << "white turn";
            } else qDebug() << "black turn";
            initTime();
            processTime();
            qDebug() << "changed TUUUUUUUUUUUUUUUUUUUUUUN";
        } else if (line == "resign") {
            QMessageBox::information(this, "Resign", "The opposite send to resign! You won!",
                                     QMessageBox::Ok);
            endGame();
        } else if (line == "timeout") {
            QMessageBox::information(this, "Timeout", "The opposite has running out of time! You won!",
                                     QMessageBox::Ok);
            endGame();
        } else if (line == "endsignal") {
            QMessageBox::information(this, "End!", "The game Ends!",
                                     QMessageBox::Ok);
            myTurn = false;
            ui->actionResign->setEnabled(false);
            timer->stop();
        }
    }

    qDebug() << "fuck loading";
    if (!info.isEmpty()) {
        board->clear_all_piece();
        board->clear_highlight();
        isWhiteTurn = board->load_board_from_string(info);
        ui->actionResign->setEnabled(true);
        board->check_status();
        this->update();
    } else {
        qDebug() << "empty empty empty empty empty empty empty empty";
    }

}

void MainWindow::on_actionNew_triggered()
{
    ui->actionStart->setEnabled(true);
    isWhiteTurn = board->init();
    this->update();
    if (isClient) {
        if (client != nullptr) {
            auto& out = client->transmit();
            save_to_net(out);
        }
    } else {
        if (server !=nullptr) {
            auto& out = server->transmit();
            save_to_net(out);
        }
    }
}

void MainWindow::on_action_triggered()
{
    server = new CreateServer;
    connect(this->server, SIGNAL(data_ready()), this, SLOT(process()));
    isClient = false;
    isWhiteTurn = true;
    myTurn = false;
    server->show();
}

void MainWindow::on_action_2_triggered()
{
    client = new CreateClient;
    connect(this->client, SIGNAL(data_ready()), this, SLOT(process()));
    isClient = true;
    isWhiteTurn = true;
    myTurn = false;
    client->show();
}

void MainWindow::on_actionSave_triggered()
{
    save_file();
}

void MainWindow::on_actionResign_triggered()
{
    if (isClient) {
        if (client != nullptr) {
            auto& out = client->transmit();
            out << "resign" << endl;
            QMessageBox::information(this, "Resign", "You have send a resign message. You loooooost!",
                                     QMessageBox::Ok);
        }
    } else {
        if (server !=nullptr) {
            auto& out = server->transmit();
            out << "resign" << endl;
            QMessageBox::information(this, "Resign", "You have send a resign message. You loooooost!",
                                     QMessageBox::Ok);
        }
    }
}

void MainWindow::endGame() {
    myTurn = false;
    ui->actionResign->setEnabled(false);
    timer->stop();
    if (isClient) {
        if (client != nullptr) {
            auto& out = client->transmit();
            out << "endsignal" << endl;
//            QMessageBox::information(this, "End!", "The game Ends!",
//                                     QMessageBox::Ok);
        }
    } else {
        if (server !=nullptr) {
            auto& out = server->transmit();
            out << "endsignal" << endl;
//            QMessageBox::information(this, "End!", "The game Ends!",
//                                     QMessageBox::Ok);
        }
    }
}

void MainWindow::on_actionStart_triggered()
{
    initTime();
    myTurn = true;
    ui->actionStart->setEnabled(false);
    ui->actionResign->setEnabled(true);
}
