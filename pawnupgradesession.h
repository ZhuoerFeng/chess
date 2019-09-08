#ifndef PAWNUPGRADESESSION_H
#define PAWNUPGRADESESSION_H

#include <QDialog>
#include <QString>
#include <board.h>

namespace Ui {
class PawnUpgradeSession;
}

class PawnUpgradeSession : public QDialog
{
    Q_OBJECT

public:
    explicit PawnUpgradeSession(QWidget *parent = nullptr);
    ~PawnUpgradeSession();
    PieceType upgrade = QUEEN;

private slots:
    void on_pushButton_queen_clicked();

    void on_pushButton_bishop_clicked();

    void on_pushButton_rook_clicked();

    void on_pushButton_knight_clicked();

private:
    Ui::PawnUpgradeSession *ui;
};

#endif // PAWNUPGRADESESSION_H
