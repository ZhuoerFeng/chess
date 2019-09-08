#include "board.h"
#include <QPoint>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "pawnupgradesession.h"

Piece::Piece() {
    position = QPoint(-1, -1);
}

bool Piece::is_under_direct_attack() {
    bool flag = false;
    QPoint curp = position;
    auto isValid =[&](QPoint p) {
        if (p.x() >= 1 && p.x() <= 8 && p.y() >= 1 && p.y() <= 8) return true;
        return false;
    };
    auto hasSelf =[&](QPoint p) {
        if ((current_board->occupied[p.x()][p.y()] == true) && (current_board->board[p.x()][p.y()]->isWhite == isWhite) &&
                (current_board->board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };
    auto hasOpposite =[&](QPoint p) {
        if ((current_board->occupied[p.x()][p.y()] == true) && (current_board->board[p.x()][p.y()]->isWhite != isWhite) &&
                (current_board->board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };
    // rook or quuen
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, 0);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != ROOK && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == ROOK ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, 0);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != ROOK && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == ROOK ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(0, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != ROOK && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == ROOK ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(0, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != ROOK && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == ROOK ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    // bishop
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != BISHOP && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == BISHOP ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != BISHOP && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == BISHOP ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under  bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, -i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != BISHOP && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == BISHOP ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, -i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            current_board->board[temp.x()][temp.y()]->type != BISHOP && current_board->board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (current_board->board[temp.x()][temp.y()]->type == BISHOP ||current_board->board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    // knight
    auto test_knight = [&]() {
        bool flag = false;
        QPoint temp1 = curp + QPoint(1, 2);
        QPoint temp2 = curp - QPoint(1, 2);
        QPoint temp3 = curp + QPoint(1, -2);
        QPoint temp4 = curp - QPoint(1, -2);
        QPoint temp5 = curp + QPoint(2, 1);
        QPoint temp6 = curp - QPoint(2, 1);
        QPoint temp7 = curp + QPoint(2, -1);
        QPoint temp8 = curp - QPoint(2, -1);
        if (isValid(temp1) && hasOpposite(temp1) && !hasSelf(temp1) &&
            (current_board->board[temp1.x()][temp1.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp2) && hasOpposite(temp2) && !hasSelf(temp2) &&
            (current_board->board[temp2.x()][temp2.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp3) && hasOpposite(temp3) && !hasSelf(temp3) &&
            (current_board->board[temp3.x()][temp3.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp4) && hasOpposite(temp4) && !hasSelf(temp4) &&
            (current_board->board[temp4.x()][temp4.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp5) && hasOpposite(temp5) && !hasSelf(temp5) &&
            (current_board->board[temp5.x()][temp5.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp6) && hasOpposite(temp6) && !hasSelf(temp6) &&
            (current_board->board[temp6.x()][temp6.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp7) && hasOpposite(temp7) && !hasSelf(temp7) &&
            (current_board->board[temp7.x()][temp7.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp8) && hasOpposite(temp8) && !hasSelf(temp8) &&
            (current_board->board[temp8.x()][temp8.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        return false;
    };

    auto test_king = [&]() {
        bool flag = false;
        QPoint temp1 = curp + QPoint(1, 1);
        QPoint temp2 = curp + QPoint(1, 0);
        QPoint temp3 = curp + QPoint(1, -1);
        QPoint temp4 = curp + QPoint(-1, 1);
        QPoint temp5 = curp + QPoint(-1, 0);
        QPoint temp6 = curp + QPoint(-1, -1);
        QPoint temp7 = curp + QPoint(0, 1);
        QPoint temp8 = curp + QPoint(0, -1);
        if (isValid(temp1) && hasOpposite(temp1) && !hasSelf(temp1) &&
            (current_board->board[temp1.x()][temp1.y()]->type == KING)) {
                qDebug() << "under king";
                flag = true;
                return true;
        }
        if (isValid(temp2) && hasOpposite(temp2) && !hasSelf(temp2) &&
            (current_board->board[temp2.x()][temp2.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp3) && hasOpposite(temp3) && !hasSelf(temp3) &&
            (current_board->board[temp3.x()][temp3.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp4) && hasOpposite(temp4) && !hasSelf(temp4) &&
            (current_board->board[temp4.x()][temp4.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp5) && hasOpposite(temp5) && !hasSelf(temp5) &&
            (current_board->board[temp5.x()][temp5.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp6) && hasOpposite(temp6) && !hasSelf(temp6) &&
            (current_board->board[temp6.x()][temp6.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp7) && hasOpposite(temp7) && !hasSelf(temp7) &&
            (current_board->board[temp7.x()][temp7.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp8) && hasOpposite(temp8) && !hasSelf(temp8) &&
            (current_board->board[temp8.x()][temp8.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        return false;
    };

    if (test_knight()) {
        flag = true;
        return true;
    }

    if (test_king()) {
        flag = true;
        return true;
    }

    // pawn
    if (isWhite) {
        QPoint pawn1 = curp + QPoint(1, 1);
        QPoint pawn2 = curp + QPoint(-1, 1);
        if (isValid(pawn1) && hasOpposite(pawn1) && !hasSelf(pawn1) &&
            (current_board->board[pawn1.x()][pawn1.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
        if (isValid(pawn2) && hasOpposite(pawn2) && !hasSelf(pawn2) &&
            (current_board->board[pawn2.x()][pawn2.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
    } else if (!isWhite) {
        QPoint pawn1 = curp - QPoint(1, 1);
        QPoint pawn2 = curp - QPoint(-1, 1);
        if (isValid(pawn1) && hasOpposite(pawn1) && !hasSelf(pawn1) &&
            (current_board->board[pawn1.x()][pawn1.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
        if (isValid(pawn2) && hasOpposite(pawn2) && !hasSelf(pawn2) &&
            (current_board->board[pawn2.x()][pawn2.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
    }

    return false;
}

bool Board::is_under_direct_attack_for_empty(QPoint curp, bool isWhite) {
    qDebug() << "IN ATTACK FOR EMPTY";
    bool flag = false;
    auto isValid =[&](QPoint p) {
        if (p.x() >= 1 && p.x() <= 8 && p.y() >= 1 && p.y() <= 8) return true;
        return false;
    };
    auto hasSelf =[&](QPoint p) {
        if ((occupied[p.x()][p.y()] == true) && (board[p.x()][p.y()]->isWhite == isWhite) &&
                (board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };
    auto hasOpposite =[&](QPoint p) {
        if ((occupied[p.x()][p.y()] == true) && (board[p.x()][p.y()]->isWhite != isWhite) &&
                (board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };
    // rook or quuen
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, 0);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != ROOK && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (board[temp.x()][temp.y()]->type == ROOK || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, 0);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != ROOK && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (board[temp.x()][temp.y()]->type == ROOK || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(0, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != ROOK && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (board[temp.x()][temp.y()]->type == ROOK || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(0, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != ROOK && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            (board[temp.x()][temp.y()]->type == ROOK || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under rook";
                flag = true;
                return true;
        }
    }
    // bishop
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != BISHOP && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            ( board[temp.x()][temp.y()]->type == BISHOP || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != BISHOP && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            ( board[temp.x()][temp.y()]->type == BISHOP || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under  bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp + QPoint(i, -i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != BISHOP && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            ( board[temp.x()][temp.y()]->type == BISHOP || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    for (int i = 1; i < 8; ++i) {
        QPoint temp = curp - QPoint(i, -i);
        if (isValid(temp) && hasSelf(temp)) break;
        if (isValid(temp) && hasOpposite(temp) &&
            board[temp.x()][temp.y()]->type != BISHOP && board[temp.x()][temp.y()]->type != QUEEN) break;
        if (isValid(temp) && hasOpposite(temp) && !hasSelf(temp) &&
            ( board[temp.x()][temp.y()]->type == BISHOP || board[temp.x()][temp.y()]->type == QUEEN)) {
                qDebug() << "under bishop";
                flag = true;
                return true;
        }
    }
    // knight
    auto test_knight = [&]() {
        bool flag = false;
        QPoint temp1 = curp + QPoint(1, 2);
        QPoint temp2 = curp - QPoint(1, 2);
        QPoint temp3 = curp + QPoint(1, -2);
        QPoint temp4 = curp - QPoint(1, -2);
        QPoint temp5 = curp + QPoint(2, 1);
        QPoint temp6 = curp - QPoint(2, 1);
        QPoint temp7 = curp + QPoint(2, -1);
        QPoint temp8 = curp - QPoint(2, -1);
        if (isValid(temp1) && hasOpposite(temp1) && !hasSelf(temp1) &&
            ( board[temp1.x()][temp1.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp2) && hasOpposite(temp2) && !hasSelf(temp2) &&
            ( board[temp2.x()][temp2.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp3) && hasOpposite(temp3) && !hasSelf(temp3) &&
            ( board[temp3.x()][temp3.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp4) && hasOpposite(temp4) && !hasSelf(temp4) &&
            ( board[temp4.x()][temp4.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp5) && hasOpposite(temp5) && !hasSelf(temp5) &&
            ( board[temp5.x()][temp5.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp6) && hasOpposite(temp6) && !hasSelf(temp6) &&
            ( board[temp6.x()][temp6.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp7) && hasOpposite(temp7) && !hasSelf(temp7) &&
            ( board[temp7.x()][temp7.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp8) && hasOpposite(temp8) && !hasSelf(temp8) &&
            ( board[temp8.x()][temp8.y()]->type == KNIGHT)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        return false;
    };

    auto test_king = [&]() {
        bool flag = false;
        QPoint temp1 = curp + QPoint(1, 1);
        QPoint temp2 = curp + QPoint(1, 0);
        QPoint temp3 = curp + QPoint(1, -1);
        QPoint temp4 = curp + QPoint(-1, 1);
        QPoint temp5 = curp + QPoint(-1, 0);
        QPoint temp6 = curp + QPoint(-1, -1);
        QPoint temp7 = curp + QPoint(0, 1);
        QPoint temp8 = curp + QPoint(0, -1);
        if (isValid(temp1) && hasOpposite(temp1) && !hasSelf(temp1) &&
            ( board[temp1.x()][temp1.y()]->type == KING)) {
                qDebug() << "under king";
                flag = true;
                return true;
        }
        if (isValid(temp2) && hasOpposite(temp2) && !hasSelf(temp2) &&
            ( board[temp2.x()][temp2.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp3) && hasOpposite(temp3) && !hasSelf(temp3) &&
            ( board[temp3.x()][temp3.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp4) && hasOpposite(temp4) && !hasSelf(temp4) &&
            ( board[temp4.x()][temp4.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp5) && hasOpposite(temp5) && !hasSelf(temp5) &&
            ( board[temp5.x()][temp5.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp6) && hasOpposite(temp6) && !hasSelf(temp6) &&
            ( board[temp6.x()][temp6.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp7) && hasOpposite(temp7) && !hasSelf(temp7) &&
            ( board[temp7.x()][temp7.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        if (isValid(temp8) && hasOpposite(temp8) && !hasSelf(temp8) &&
            ( board[temp8.x()][temp8.y()]->type == KING)) {
                qDebug() << "under knight";
                flag = true;
                return true;
        }
        return false;
    };

    if (test_knight()) {
        flag = true;
        return true;
    }

    if (test_king()) {
        flag = true;
        return true;
    }

    // pawn
    if (isWhite) {
        QPoint pawn1 = curp + QPoint(1, 1);
        QPoint pawn2 = curp + QPoint(-1, 1);
        if (isValid(pawn1) && hasOpposite(pawn1) && !hasSelf(pawn1) &&
            (board[pawn1.x()][pawn1.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
        if (isValid(pawn2) && hasOpposite(pawn2) && !hasSelf(pawn2) &&
            ( board[pawn2.x()][pawn2.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
    } else if (!isWhite) {
        QPoint pawn1 = curp - QPoint(1, 1);
        QPoint pawn2 = curp - QPoint(-1, 1);
        if (isValid(pawn1) && hasOpposite(pawn1) && !hasSelf(pawn1) &&
            ( board[pawn1.x()][pawn1.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
        if (isValid(pawn2) && hasOpposite(pawn2) && !hasSelf(pawn2) &&
            ( board[pawn2.x()][pawn2.y()]->type == PAWN)) {
                qDebug() << "under pawn";
                flag = true;
                return true;
        }
    }
    return false;
}

Piece::Piece(QString& name, QString& place) {
    if (name == "pawn") {
        type = PAWN;
    } else if (name == "rook") {
        type = ROOK;
    } else if (name == "knight") {
        type = KNIGHT;
    } else if (name == "bishop") {
        type = BISHOP;
    } else if (name == "queen") {
        type = QUEEN;
    } else if (name == "king") {
        type = KING;
    } else {
        qDebug() << "input piece error";
        type = NO_TYPE;
    }
    std::string temp = place.toStdString();
    if (temp[0] <= 'h' && temp[0] >= 'a' && temp[1] >= '1' && temp[1] <= '8') {
        int x = temp[0] - 'a' + 1;
        int y = temp[1] - '0';
        position = QPoint(x, y);
        qDebug() << position;
    }
    if (temp.size() >= 2) {
        first_move = ONE_MOVE;
    }
}

Piece::~Piece() {
}

QVector<QPoint> Piece::get_access() {
    qDebug() << "in get access";
    auto isValid =[&](QPoint p) {
        if (p.x() >= 1 && p.x() <= 8 && p.y() >= 1 && p.y() <= 8) return true;
        return false;
    };
    auto hasSelf =[&](QPoint p) {
        if ((current_board->occupied[p.x()][p.y()] == true) && (current_board->board[p.x()][p.y()]->isWhite == isWhite) &&
                (current_board->board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };
    auto hasOpposite =[&](QPoint p) {
        if ((current_board->occupied[p.x()][p.y()] == true) && (current_board->board[p.x()][p.y()]->isWhite != isWhite) &&
                (current_board->board[p.x()][p.y()]->isEaten == false))
            return true;
        return false;
    };

    QVector<QPoint> access;
    QPoint current = position;
    if (type == ROOK) {
        qDebug() << current << "rook getting access";
//        if (first_move ==  NO_MOVE)
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, 0);
            if (isValid(temp) && !hasSelf(temp)) {
                qDebug() << " is accessibale";
                access.append(temp);
                if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, 0);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dy=1; dy<= 7; ++dy) {
            QPoint temp = current + QPoint(0, dy);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dy=1; dy<= 7; ++dy) {
            QPoint temp = current - QPoint(0, dy);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
    } else if (type == BISHOP) {
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, -dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, -dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
    } else if (type == QUEEN) {
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, 0);
            if (isValid(temp) && !hasSelf(temp)) {
                qDebug() << " is accessibale";
                access.append(temp);
                if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, 0);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dy=1; dy<= 7; ++dy) {
            QPoint temp = current + QPoint(0, dy);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dy=1; dy<= 7; ++dy) {
            QPoint temp = current - QPoint(0, dy);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        //xiezou
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current + QPoint(dx, -dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
        for (int dx=1; dx<= 7; ++dx) {
            QPoint temp = current - QPoint(dx, -dx);
            if (isValid(temp) && !hasSelf(temp)) {
                    access.append(temp);
                    if (hasOpposite(temp)) break;
            } else break;
        }
    } else if (type == KNIGHT) {
        QPoint temp1 = current + QPoint(1, 2);
        if (isValid(temp1) && !hasSelf(temp1)) access.append(temp1);
        QPoint temp2 = current - QPoint(1, 2);
        if (isValid(temp2) && !hasSelf(temp2)) access.append(temp2);
        QPoint temp3 = current + QPoint(1, -2);
        if (isValid(temp3) && !hasSelf(temp3)) access.append(temp3);
        QPoint temp4 = current - QPoint(1, -2);
        if (isValid(temp4) && !hasSelf(temp4)) access.append(temp4);
        QPoint temp5 = current + QPoint(2, 1);
        if (isValid(temp5) && !hasSelf(temp5)) access.append(temp5);
        QPoint temp6 = current - QPoint(2, 1);
        if (isValid(temp6) && !hasSelf(temp6)) access.append(temp6);
        QPoint temp7 = current + QPoint(2, -1);
        if (isValid(temp7) && !hasSelf(temp7)) access.append(temp7);
        QPoint temp8 = current - QPoint(2, -1);
        if (isValid(temp8) && !hasSelf(temp8)) access.append(temp8);
    } else if (type == KING) {
        QPoint temp1 = current + QPoint(1, 1);
        if (isValid(temp1) && !hasSelf(temp1)) access.append(temp1);
        QPoint temp2 = current - QPoint(1, 1);
        if (isValid(temp2) && !hasSelf(temp2)) access.append(temp2);
        QPoint temp3 = current + QPoint(1, -1);
        if (isValid(temp3) && !hasSelf(temp3)) access.append(temp3);
        QPoint temp4 = current - QPoint(1, -1);
        if (isValid(temp4) && !hasSelf(temp4)) access.append(temp4);
        QPoint temp5 = current + QPoint(1, 0);
        if (isValid(temp5) && !hasSelf(temp5)) access.append(temp5);
        QPoint temp6 = current - QPoint(1, 0);
        if (isValid(temp6) && !hasSelf(temp6)) access.append(temp6);
        QPoint temp7 = current + QPoint(0, 1);
        if (isValid(temp7) && !hasSelf(temp7)) access.append(temp7);
        QPoint temp8 = current - QPoint(0, 1);
        if (isValid(temp8) && !hasSelf(temp8)) access.append(temp8);
        if (first_move == NO_MOVE) {
            if (isWhite) {
                // 经过的所有不能被将 中间不能有棋子
                if (current_board->whiteLongShiftAble && !is_under_direct_attack() &&
                        !current_board->occupied[4][1] && !current_board->occupied[2][1] &&
                        !current_board->occupied[3][1] &&
                        !current_board->is_under_direct_attack_for_empty(QPoint(4, 1), 1) &&
                        !current_board->is_under_direct_attack_for_empty(QPoint(3, 1), 1) ) {
                    access.append(QPoint(3, 1));
                }
                if (current_board->whiteShortShiftAble && !is_under_direct_attack() &&
                           !current_board->occupied[6][1] && !current_board->occupied[7][1] &&
                           !current_board->is_under_direct_attack_for_empty(QPoint(6, 1), 1) &&
                           !current_board->is_under_direct_attack_for_empty(QPoint(7, 1), 1) ) {
                    access.append(QPoint(7, 1));
                }
            } else if (!isWhite) {
                if (current_board->blackLongShiftAble && !is_under_direct_attack() &&
                        !current_board->occupied[4][8] && !current_board->occupied[2][8] &&
                        !current_board->occupied[3][8] &&
                        !current_board->is_under_direct_attack_for_empty(QPoint(4, 8), 0) &&
                        !current_board->is_under_direct_attack_for_empty(QPoint(3, 8), 0) ) {
                    access.append(QPoint(3, 8));
                }
                if (current_board->blackShortShiftAble && !is_under_direct_attack() &&
                           !current_board->occupied[6][8] && !current_board->occupied[7][8] &&
                           !current_board->is_under_direct_attack_for_empty(QPoint(6, 8), 0) &&
                           !current_board->is_under_direct_attack_for_empty(QPoint(7, 8), 0) ) {
                    access.append(QPoint(7, 8));
                }
            }
        }
    } else if (type == PAWN) {
        if (isWhite == true) {
            if (first_move == NO_MOVE) {
                QPoint temp1 = current + QPoint(0, 1);
                QPoint temp2 = current + QPoint(0, 2);
                if (isValid(temp1) && !hasSelf(temp1) && !hasOpposite(temp1)) access.append(temp1);
                if (isValid(temp2) && !hasSelf(temp2) && !hasOpposite(temp2) &&
                        !hasSelf(temp1) && !hasOpposite(temp1)) access.append(temp2); // 面前不能被挡住
                QPoint temp3 = current + QPoint(1, 1);
                QPoint temp4 = current + QPoint(-1, 1);

                if (isValid(temp3) && hasOpposite(temp3)) access.append(temp3); // 不佳特判是因为不会被选中
                if (isValid(temp4) && hasOpposite(temp4)) access.append(temp4);

            } else if (first_move == ONE_MOVE || first_move == TWO_MOVE) {
//                qDebug() << "not first move!!!!!!!1";
                QPoint temp1 = current + QPoint(1, 1);
                QPoint temp2 = current + QPoint(-1, 1);

                QPoint temp3 = current + QPoint(0, 1);
                if (isValid(temp1) && hasOpposite(temp1)) access.append(temp1);
                if (isValid(temp1) && hasOpposite(temp2)) access.append(temp2);

                if (isValid(temp3) && !hasSelf(temp3) && !hasOpposite(temp3)) access.append(temp3);
            }
        } else if (isWhite == false) {
            if (first_move == NO_MOVE) {
                QPoint temp1 = current + QPoint(0, -1);
                QPoint temp2 = current + QPoint(0, -2);
                if (isValid(temp1) && !hasSelf(temp1) && !hasOpposite(temp1)) access.append(temp1);
                if (isValid(temp2) && !hasSelf(temp2) && !hasOpposite(temp2) &&
                        !hasSelf(temp1) && !hasOpposite(temp1)) access.append(temp2); // 面前不能被挡住
                QPoint temp3 = current + QPoint(1, -1);
                QPoint temp4 = current + QPoint(-1, -1);

                if (isValid(temp3) && hasOpposite(temp3)) access.append(temp3);
                if (isValid(temp4) && hasOpposite(temp4)) access.append(temp4);
            } else if (first_move == ONE_MOVE || first_move == TWO_MOVE) {
                QPoint temp1 = current + QPoint(1, -1);
                QPoint temp2 = current + QPoint(-1, -1);

                QPoint temp3 = current + QPoint(0, -1);
                if (isValid(temp1) && hasOpposite(temp1)) access.append(temp1);
                if (isValid(temp2) && hasOpposite(temp2)) access.append(temp2);

                if (isValid(temp3) && !hasSelf(temp3) && !hasOpposite(temp3)) access.append(temp3);
            }
        }

    }
    return access;
}

Board* Piece::get_board() {
    return current_board;
}

void Piece::move_new(QPoint target) {
    // capture 满足：target可达， target非本方棋子
    QPoint curp = position;
    if (current_board->highlight[target.x()][target.y()] == true && current_board->occupied[target.x()][target.y()] == true &&
         current_board->board[target.x()][target.y()]->isWhite != isWhite) {
        qDebug() << "capture " << target;
        if (type == PAWN) {
            if (first_move == NO_MOVE) {
                if (curp.y() - target.y() == 2 || curp.y() - target.y() == -2 ) {
                    qDebug() << "done two move";
                    first_move = TWO_MOVE;
                } else if (curp.y() - target.y() == 1 || curp.y() - target.y() == -1 ) {
                    qDebug() << "done one move";
                    first_move = ONE_MOVE;
                }
            }
            if (isWhite == true && target.y() == 8) {
                // 升变
                PawnUpgradeSession* session = new PawnUpgradeSession;
                session->exec();
                this->type = session->upgrade;
            }
        } else if (type == KING) {
            if (first_move == NO_MOVE) {
                first_move = ONE_MOVE;
                if (isWhite) {
                    current_board->whiteLongShiftAble = false;
                    current_board->whiteShortShiftAble = false;
                } else if (!isWhite) {
                    current_board->blackLongShiftAble = false;
                    current_board->blackShortShiftAble = false;
                }
            }

        } else if (type == ROOK) {
            if (first_move == NO_MOVE) {
                first_move = ONE_MOVE;
                if (isWhite) {
                    if (position == QPoint(1, 1)) {
                        current_board->whiteLongShiftAble = false;
                    } else if (position == QPoint(8, 1)) {
                        current_board->whiteShortShiftAble = false;
                    }
                } else if (!isWhite) {
                    if (position == QPoint(1, 8)) {
                        current_board->whiteLongShiftAble = false;
                    } else if (position == QPoint(8, 8)) {
                        current_board->whiteShortShiftAble = false;
                    }
                }
            }
        }

        current_board->board[target.x()][target.y()]->isEaten = true;  //吃
        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
        current_board->board[curp.x()][curp.y()] = new Piece; // 删除
        //
        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
    // move 满足： target可达 对应位置是空的
    } else if (current_board->highlight[target.x()][target.y()] == true && current_board->occupied[target.x()][target.y()] == false) {
        qDebug() << "move" << target;
        if (type == PAWN) {
            if (first_move == NO_MOVE) {
                if (curp.y() - target.y() == 2 || curp.y() - target.y() == -2 ) {
                    qDebug() << "done two move";
                    first_move = TWO_MOVE;
                } else if (curp.y() - target.y() == 1 || curp.y() - target.y() == -1 ) {
                    qDebug() << "done one move";
                    first_move = ONE_MOVE;
                }
            }
            if (isWhite == true && target.y() == 8) {
                // 升变
                PawnUpgradeSession* session = new PawnUpgradeSession;
                session->exec();
                this->type = session->upgrade;
            }
        } else if (type == KING ) {
            if (first_move == NO_MOVE) {
                first_move = ONE_MOVE;
            }
            //王车易位
            if (target.x() - position.x() == 2 || target.x() - position.x() == -2) {
                if (isWhite) {
                    // long shift
                    if (target.x() - position.x() == -2) {
                        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
                        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
                        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
                        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
                        current_board->board[curp.x()][curp.y()] = new Piece; // 删除

                        current_board->occupied[4][1] = true;  // 占领位置
                        current_board->occupied[1][1] = false;  // 原先位置置空
                        current_board->board[4][1] = current_board->board[1][1];  //更新对应位置内容
                        current_board->board[4][1]->position = QPoint(4, 1);  //更新坐标
                        current_board->board[1][1] = new Piece; // 删除

                        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
                    // short shift
                    } else if (target.x() - position.x() == 2) {
                        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
                        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
                        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
                        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
                        current_board->board[curp.x()][curp.y()] = new Piece; // 删除

                        current_board->occupied[6][1] = true;  // 占领位置
                        current_board->occupied[8][1] = false;  // 原先位置置空
                        current_board->board[6][1] = current_board->board[8][1];  //更新对应位置内容
                        current_board->board[6][1]->position = QPoint(6, 1);  //更新坐标
                        current_board->board[8][1] = new Piece; // 删除

                        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
                    }
                } else if (!isWhite) {
                    // black long shift
                    if (target.x() - position.x() == -2) {
                        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
                        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
                        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
                        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
                        current_board->board[curp.x()][curp.y()] = new Piece; // 删除

                        current_board->occupied[4][8] = true;  // 占领位置
                        current_board->occupied[1][8] = false;  // 原先位置置空
                        current_board->board[4][8] = current_board->board[1][8];  //更新对应位置内容
                        current_board->board[4][8]->position = QPoint(4, 8);  //更新坐标
                        current_board->board[1][8] = new Piece; // 删除

                        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
                    // short shift
                    } else if (target.x() - position.x() == 2) {
                        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
                        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
                        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
                        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
                        current_board->board[curp.x()][curp.y()] = new Piece; // 删除

                        current_board->occupied[6][8] = true;  // 占领位置
                        current_board->occupied[8][8] = false;  // 原先位置置空
                        current_board->board[6][8] = current_board->board[8][8];  //更新对应位置内容
                        current_board->board[6][8]->position = QPoint(6, 8);  //更新坐标
                        current_board->board[8][8] = new Piece; // 删除

                        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
                    }
                }


                return;
            }
        }
        current_board->occupied[target.x()][target.y()] = true;  // 占领位置
        current_board->occupied[curp.x()][curp.y()] = false;  // 原先位置置空
        current_board->board[target.x()][target.y()] = current_board->board[curp.x()][curp.y()];  //更新对应位置内容
        current_board->board[target.x()][target.y()]->position = target;  //更新坐标
        current_board->board[curp.x()][curp.y()] = new Piece; // 删除
        //
        current_board->set_highlight( current_board->board[target.x()][target.y()]->get_access()); // 新位置仍实现高亮
    }
    // 报错
    qDebug() << "movement error!";
}

Board::Board() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Piece* p = new Piece;
            occupied[i][j] = false;
            highlight[i][j] = false;
            p->current_board = this;
            board[i][j] = p;
            if (board[i][j]->current_board == nullptr) {
                qDebug() << "this is a nullptr";
            } else {
//                qDebug() << "this is not a nullptr";
            }
        }
    }
}

void Board::set_highlight(QVector<QPoint> access) {
    clear_highlight();
    for (auto& p: access) {
        highlight[p.x()][p.y()] = true;
    }
}

void Board::clear_highlight() {
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            highlight[i][j] = false;
        }
    }
}

bool Board::load_board_from_string(QString& info) {
    int cnt = 0;
    bool whitemode = true;
    bool whiteturn = true;
    auto set_piece =[&](QStringList para, bool w) {
        int times = para[1].toInt();
        for (int i = 2; i < times + 2; ++i) {
            Piece* p = new Piece(para[0], para[i]);
            p->current_board = this;
            QPoint posi = p->position;
            if (!w)  p->isWhite = false;
            qDebug() << p->isWhite << p->position;
            if (p->type == ROOK) {
                if (p->isWhite) {
                    if (p->position == QPoint(1, 1)) {
                        p->first_move = NO_MOVE;
                    } else if  (p->position == QPoint(8, 1)) {
                       p->first_move = NO_MOVE;
                    } else p->first_move = ONE_MOVE;
                } else if (!p->isWhite) {
                    if (p->position == QPoint(1, 8)) {
                        p->first_move = NO_MOVE;
                    } else if  (p->position == QPoint(8, 8)) {
                       p->first_move = NO_MOVE;
                    } else p->first_move = ONE_MOVE;
                }
            } else if (p->type == KING) {
                if (p->isWhite) {
                    if (p->position == QPoint(5, 1)) {
                        p->first_move = NO_MOVE;
                    } else p->first_move = ONE_MOVE;
                } else if (!p->isWhite) {
                    if (p->position == QPoint(5, 8)) {
                        p->first_move = NO_MOVE;
                    } else p->first_move = ONE_MOVE;
                }
            } else if (p->type == PAWN) {
                if (p->isWhite) {
                    if ((p->position == QPoint(1, 2)) || (p->position == QPoint(2, 2)) ||
                            (p->position == QPoint(3, 2)) || (p->position == QPoint(4, 2)) ||
                            (p->position == QPoint(5, 2)) || (p->position == QPoint(6, 2)) ||
                            (p->position == QPoint(7, 2)) || (p->position == QPoint(8, 2)) ) {
                        p->first_move = NO_MOVE;
                    } else if ((p->position == QPoint(1, 3)) || (p->position == QPoint(2, 3)) ||
                               (p->position == QPoint(3, 3)) || (p->position == QPoint(4, 3)) ||
                               (p->position == QPoint(5, 3)) || (p->position == QPoint(6, 3)) ||
                               (p->position == QPoint(7, 3)) || (p->position == QPoint(8, 3)) ) {
                        p->first_move = ONE_MOVE;
                    } else p->first_move = TWO_MOVE;
                } else if (!p->isWhite) {
                    if ((p->position == QPoint(1, 7)) || (p->position == QPoint(2, 7)) ||
                            (p->position == QPoint(3, 7)) || (p->position == QPoint(4, 7)) ||
                            (p->position == QPoint(5, 7)) || (p->position == QPoint(6, 7)) ||
                            (p->position == QPoint(7, 7)) || (p->position == QPoint(8, 7)) ) {
                        p->first_move = NO_MOVE;
                    } else if ((p->position == QPoint(1, 6)) || (p->position == QPoint(2, 6)) ||
                               (p->position == QPoint(3, 6)) || (p->position == QPoint(4, 6)) ||
                               (p->position == QPoint(5, 6)) || (p->position == QPoint(6, 6)) ||
                               (p->position == QPoint(7, 6)) || (p->position == QPoint(8, 6)) ) {
                        p->first_move = ONE_MOVE;
                    } else p->first_move = TWO_MOVE;
                }
            }
            board[posi.x()][posi.y()] = p;
            occupied[posi.x()][posi.y()] = true;
            cnt++;
        };
    };

    for (auto& line: info.split("\n")) {
        auto temp = line.split(" ");
        qDebug() << temp;
        if(temp[0] == "white") {
            whitemode = true;
        } else if (temp[0] == "black" ) {
            whitemode = false;
        } else if (temp[0] == "king" || temp[0] == "queen" ||  temp[0] == "bishop" ||
                   temp[0] == "knight" ||  temp[0] == "rook" ||  temp[0] == "pawn") {
            set_piece(temp, whitemode);
        }
    }

    if (!whitemode) {
        whiteturn = true;
    } else if (whitemode) {
        whiteturn = false;
    }

    qDebug() << cnt;
    return whiteturn;
}

void Board::clear_all_piece() {
    clear_highlight();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Piece* p = new Piece;
            occupied[i][j] = false;
            highlight[i][j] = false;
            p->current_board = this;
            board[i][j] = p;
            if (board[i][j]->current_board == nullptr) {
                qDebug() << "this is a nullptr";
            } else {
//                qDebug() << "this is not a nullptr";
            }
        }
    }

}

void Board::save_current_board(QTextStream & stream, bool whiteTurn) {
    qDebug() << "into function...... saving board";
    QVector<QPoint> blacks = get_all_black();
    QVector<QPoint> whites = get_all_white();
    auto toQString =[=](int n) {
        if (n == 1) return "a";
        else if (n == 2) return "b";
        else if (n == 3) return "c";
        else if (n == 4) return "d";
        else if (n == 5) return "e";
        else if (n == 6) return "f";
        else if (n == 7) return "g";
        else if (n == 8) return "h";
        return "A";
    };
    auto count_white_piece =[=] (PieceType t) {
        QVector<QString> place;
        place.clear();
        for (auto& temp : whites) {
            if (board[temp.x()][temp.y()]->type == t) {
                QString qs = toQString(temp.x()) + QString::number(temp.y());
                if (board[temp.x()][temp.y()]->first_move == NO_MOVE) {
                    qs += "!";
                }
                place.append(qs);
            }
        }

        return place;
    };
    auto count_black_piece =[=] (PieceType t) {
        QVector<QString> place;
        place.clear();
        for (auto& temp : blacks) {
            if (board[temp.x()][temp.y()]->type == t) {
                QString qs = toQString(temp.x()) + QString::number(temp.y());
                if (board[temp.x()][temp.y()]->first_move != NO_MOVE) {
                    qs += "!";
                }
                place.append(qs);
            }
        }

        return place;
    };

    auto add_item =[&](QVector<QString> pieces) {
        for (int i = 0; i < pieces.size() - 1; ++i) {
            stream << pieces[i] << " ";
        }
        stream << pieces.back() << endl;
    };
    auto save_white =[&]() {
        stream << "white" << endl;
        QString kp = toQString(get_white_king().x()) + QString::number(get_white_king().y());
        stream << "king 1 " << kp << endl;

        QVector<QString> queens = count_white_piece(QUEEN);
        QVector<QString> knights = count_white_piece(KNIGHT);
        QVector<QString> rooks = count_white_piece(ROOK);
        QVector<QString> bishops = count_white_piece(BISHOP);
        QVector<QString> pawns = count_white_piece(PAWN);
        if (!queens.isEmpty()) {
            stream << "queen " << queens.size() << " ";
            add_item(queens);
            queens.clear();
        }
        if (!rooks.isEmpty()) {
            stream << "rook " << rooks.size() << " ";
            add_item(rooks);
            rooks.clear();
        }
        if (!bishops.isEmpty()) {
            stream << "bishop " << bishops.size() << " ";
            add_item(bishops);
            bishops.clear();
        }
        if (!knights.isEmpty()) {
            stream << "knight " << knights.size() << " ";
            add_item(knights);
            knights.clear();
        }
        if (!pawns.isEmpty()) {
            stream << "pawn " << pawns.size() << " ";
            add_item(pawns);
            pawns.clear();
        }
    };

    auto save_black =[&]() {
        stream << "black" << endl;
        QString bkp = toQString(get_black_king().x()) + QString::number(get_black_king().y());
        stream << "king 1 " << bkp << endl;

        QVector<QString> queens = count_black_piece(QUEEN);
        QVector<QString> knights = count_black_piece(KNIGHT);
        QVector<QString> rooks = count_black_piece(ROOK);
        QVector<QString> bishops = count_black_piece(BISHOP);
        QVector<QString> pawns = count_black_piece(PAWN);

        if (!queens.isEmpty()) {
            stream << "queen " << queens.size() << " ";
            add_item(queens);
            queens.clear();
        }
        if (!rooks.isEmpty()) {
            stream << "rook " << rooks.size() << " ";
            add_item(rooks);
            rooks.clear();
        }
        if (!bishops.isEmpty()) {
            stream << "bishop " << bishops.size() << " ";
            add_item(bishops);
            bishops.clear();
        }
        if (!knights.isEmpty()) {
            stream << "knight " << knights.size() << " ";
            add_item(knights);
            knights.clear();
        }
        if (!pawns.isEmpty()) {
            stream << "pawn " << pawns.size() << " ";
            add_item(pawns);
            pawns.clear();
        }
    };

    if (whiteTurn) {
        save_white();
        save_black();
    } else if (!whiteTurn) {
        save_black();
        save_white();
    }
}


bool Board::init() {
    clear_all_piece();
    bool whiteturn = true;
    auto filename = QFileDialog::getOpenFileName(nullptr, "Open", "/Users/chenwei/Desktop/week8/chess/", "*.txt");
    if (!filename.isEmpty()) {
        QFile f(filename);
        if (f.open(QIODevice::ReadOnly | QFile::Text)) {
            QString info = f.readAll();
            qDebug() << info;
            whiteturn = load_board_from_string(info);

        }
    }
    return whiteturn;
}

QVector<QPoint> Board::get_all_black() {
    QVector<QPoint> blacks;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (occupied[i][j] && !board[i][j]->isEaten && !board[i][j]->isWhite) {
                blacks.append(QPoint(i, j));
            }
        }
    }
    return blacks;
}

QVector<QPoint> Board::get_all_white() {
    QVector<QPoint> whites;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (occupied[i][j] && !board[i][j]->isEaten && board[i][j]->isWhite) {
                whites.append(QPoint(i, j));
            }
        }
    }
    return whites;
}


QPoint Board::get_black_king() {
    bool got = false;
    if (!get_all_black().isEmpty()) {
        for (auto& temp: get_all_black()) {
            if (board[temp.x()][temp.y()]->type == KING) {
                got = true;
                return temp;
            }
        }
    }
    if (!got) {
        return QPoint(0, 0);
    }
}

QPoint Board::get_white_king() {
    bool got = false;
    if (!get_all_white().isEmpty()) {
        for (auto& temp: get_all_white()) {
            if (board[temp.x()][temp.y()]->type == KING) {
                got = true;
                return temp;
            }
        }
    }
    if (!got) {
        return QPoint(0, 0);
    }
}

bool Board::check_status() {
    bool blackWon = false;
    bool whiteWon = false;
    bool blackChecked = false;
    bool whiteChecked = false;

    if (get_black_king() == QPoint(0, 0)) {
        whiteWon = true;
        QMessageBox::information(0, "Win!", "White Wins!", QMessageBox::Ok);
        return false;
    }
    // should return and stop
    if (get_white_king() == QPoint(0, 0)) {
        blackWon = true;
        QMessageBox::information(0, "Win!", "Black Wins!", QMessageBox::Ok);
        return false;
    }
    // should return and stop

    //Check!
    QPoint blackKing = get_black_king();
    if (board[blackKing.x()][blackKing.y()]->is_under_direct_attack()) {
        blackChecked = true;
        QMessageBox::information(0, "Check!", "Black Checked!", QMessageBox::Ok);
    } else blackChecked = false;

    QPoint whiteKing = get_white_king();
    if (board[whiteKing.x()][whiteKing.y()]->is_under_direct_attack()) {
        whiteChecked = true;
        QMessageBox::information(0, "Check!", "White Checked!", QMessageBox::Ok);
    } else whiteChecked = false;

    // 逼和
    // for black
    bool black_stalemate = true;
    if (!whiteWon && !blackWon && !blackChecked) {
        qDebug() << "===========================================================duojian";
        for (auto& temp: get_all_black()) {
            QVector<QPoint> accessible = board[temp.x()][temp.y()]->get_access();

            if (board[temp.x()][temp.y()]->type != KING) {
                if (!accessible.isEmpty()) {
                    Piece* savePiece = board[temp.x()][temp.y()];
                    Piece* emptyboard = new Piece;
                    emptyboard->current_board = this;
                    emptyboard->position = temp;
                    emptyboard->isWhite = false;
                    board[temp.x()][temp.y()] = emptyboard;
                    occupied[temp.x()][temp.y()] = false;
                    if (!board[get_black_king().x()][get_black_king().y()]->is_under_direct_attack()) {
                        black_stalemate = false;
                        board[temp.x()][temp.y()] = savePiece;
                        occupied[temp.x()][temp.y()] = true;
                        break;
                    }
                    board[temp.x()][temp.y()] = savePiece;
                    occupied[temp.x()][temp.y()] = true;
                }
            } else if (board[temp.x()][temp.y()]->type == KING) {
                qDebug() << "KING detected)))))))))))";
                if (accessible.isEmpty()) {
                    qDebug() << "accessible Empty QAAQAQAQAQAQAQA";
                    continue;
                } else {
                    // undefined behaviour?
                    QPoint curp = get_black_king();
                    qDebug() << accessible;
                    for (auto& kingtemp: accessible) {
                        QPoint check_posi = kingtemp;
                        if (board[check_posi.x()][check_posi.y()] == nullptr) {
                            qDebug() << check_posi << "is nullptr<<<<<<<<<";
                            board[check_posi.x()][check_posi.y()] = new Piece;
                            board[check_posi.x()][check_posi.y()]->current_board = this;
                            board[check_posi.x()][check_posi.y()]->isWhite = false;
                            board[check_posi.x()][check_posi.y()]->position = check_posi;
                            if (!board[check_posi.x()][check_posi.y()]->is_under_direct_attack()) {
                                black_stalemate = false;
                            }
                            board[check_posi.x()][check_posi.y()] = nullptr;
                        } else if (board[check_posi.x()][check_posi.y()] != nullptr){
                            board[check_posi.x()][check_posi.y()] = new Piece;
                            board[check_posi.x()][check_posi.y()]->current_board = this;
                            board[check_posi.x()][check_posi.y()]->isWhite = false;
                            board[check_posi.x()][check_posi.y()]->position = check_posi;
                            if (!board[check_posi.x()][check_posi.y()]->is_under_direct_attack()) {
                                black_stalemate = false;
                            }
                            board[check_posi.x()][check_posi.y()] = nullptr;
                        }
                    }
                }
            }
        }
    } else if (!whiteWon && !blackWon && blackChecked) {
        qDebug() << "*****************************************************shaojian";
        black_stalemate = false;
    }

    bool white_stalemate = true;
    if (!whiteWon && !blackWon && !whiteChecked) {
        qDebug() << "===========================================================duojian";
        for (auto& temp: get_all_white()) {
            QVector<QPoint> accessible = board[temp.x()][temp.y()]->get_access();

            if (board[temp.x()][temp.y()]->type != KING) {
                if (!accessible.isEmpty()) {
                    Piece* savePiece = board[temp.x()][temp.y()];
                    Piece* emptyboard = new Piece;
                    emptyboard->current_board = this;
                    emptyboard->position = temp;
                    emptyboard->isWhite = true;
                    board[temp.x()][temp.y()] = emptyboard;
                    occupied[temp.x()][temp.y()] = false;
                    if (!board[get_white_king().x()][get_white_king().y()]->is_under_direct_attack()) {
                        white_stalemate = false;
                        board[temp.x()][temp.y()] = savePiece;
                        occupied[temp.x()][temp.y()] = true;
                        break;
                    }
                    board[temp.x()][temp.y()] = savePiece;
                    occupied[temp.x()][temp.y()] = true;
                }
            } else if (board[temp.x()][temp.y()]->type == KING) {
                qDebug() << "KING detected)))))))))))";
                if (accessible.isEmpty()) {
                    qDebug() << "accessible Empty QAAQAQAQAQAQAQA";
                    continue;
                } else {
                    // undefined behaviour?
                    QPoint curp = get_white_king();
                    qDebug() << accessible;
                    for (auto& kingtemp: accessible) {
                        QPoint check_posi = kingtemp;
                        if (board[check_posi.x()][check_posi.y()] == nullptr) {
                            qDebug() << check_posi << "is nullptr<<<<<<<<<";
                            board[check_posi.x()][check_posi.y()] = new Piece;
                            board[check_posi.x()][check_posi.y()]->current_board = this;
                            board[check_posi.x()][check_posi.y()]->isWhite = true;
                            board[check_posi.x()][check_posi.y()]->position = check_posi;
                            if (!board[check_posi.x()][check_posi.y()]->is_under_direct_attack()) {
                                white_stalemate = false;
                            }
                            board[check_posi.x()][check_posi.y()] = nullptr;
                        } else if (board[check_posi.x()][check_posi.y()] != nullptr){
                            board[check_posi.x()][check_posi.y()] = new Piece;
                            board[check_posi.x()][check_posi.y()]->current_board = this;
                            board[check_posi.x()][check_posi.y()]->isWhite = true;
                            board[check_posi.x()][check_posi.y()]->position = check_posi;
                            if (!board[check_posi.x()][check_posi.y()]->is_under_direct_attack()) {
                                white_stalemate = false;
                            }
                            board[check_posi.x()][check_posi.y()] = nullptr;
                        }
                    }
                }
            }
        }
    } else if (!whiteWon && !blackWon && whiteChecked) {
        qDebug() << "*****************************************************shaojian";
        white_stalemate = false;
    }


    if (black_stalemate) {
        QMessageBox::information(0, "StaleMate!", "Black stalemate!", QMessageBox::Ok);
        return false;
    } else if (white_stalemate) {
        QMessageBox::information(0, "StaleMate!", "White stalemate!", QMessageBox::Ok);
        return false;
    }
    return true;
}

