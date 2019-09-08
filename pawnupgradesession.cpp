#include "pawnupgradesession.h"
#include "ui_pawnupgradesession.h"

PawnUpgradeSession::PawnUpgradeSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PawnUpgradeSession)
{
    ui->setupUi(this);
}

PawnUpgradeSession::~PawnUpgradeSession()
{
    delete ui;
}

void PawnUpgradeSession::on_pushButton_queen_clicked()
{
    upgrade = QUEEN;
    close();
}

void PawnUpgradeSession::on_pushButton_bishop_clicked()
{
    upgrade = BISHOP;
    close();
}

void PawnUpgradeSession::on_pushButton_rook_clicked()
{
    upgrade = ROOK;
    close();
}

void PawnUpgradeSession::on_pushButton_knight_clicked()
{
    upgrade = KNIGHT;
    close();
}
