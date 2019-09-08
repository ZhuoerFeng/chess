#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <QPoint>
#include <QTextStream>


enum PawnMove {NO_MOVE, ONE_MOVE, TWO_MOVE};
enum PieceType {NO_TYPE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
enum WinType {WHITE_WIN, BLACK_WIN, FAIR};

class Board;

class Piece {
public:
    Piece();
    Piece(QString& name, QString& place);
    ~Piece();
    PieceType type;
    PawnMove first_move = NO_MOVE;
    QPoint position;

    bool isWhite = true;
    bool isEaten = false;
    bool isSelected = false;

//    bool hasBlackKing = true;
//    bool hasWhiteKing = true;

    bool is_under_direct_attack();

//    bool isMovable();
//    bool isSafe();
    QVector<QPoint> get_access();

    void do_command(QPoint target);

    Board* current_board = nullptr;
    Board* get_board();

    void move_new(QPoint target);

};

class Board {
public:
    Board();
    Piece* board[9][9];
    bool occupied[9][9];
    bool highlight[9][9];
    void set_highlight(QVector<QPoint>);
    void clear_highlight();
    void clear_all_piece();

    void save_current_board(QTextStream& , bool);
//    void save_current_board_to_net(QTextStream&);


    bool is_under_direct_attack_for_empty(QPoint curp, bool isWhite);

    QVector<QPoint> get_all_black();
    QVector<QPoint> get_all_white();
    QPoint get_black_king();
    QPoint get_white_king();

    bool check_status();

//    WinType checkBlackWin();
    bool blackLongShiftAble = true;
    bool blackShortShiftAble = true;
    bool whiteLongShiftAble = true;
    bool whiteShortShiftAble = true;

    bool load_board_from_string(QString& info);
    bool init();

};


#endif // BOARD_H
