#include "board.h"

#include <QDebug>

Board::Board()
{
    m_board.resize(CELL_COUNT);
    for (int i = 0; i< CELL_COUNT; ++i){
        m_board[i].resize(CELL_COUNT, nullptr);
    }
}

void Board::setupInitialPosition()
{
    for (int r = 0; r < CELL_COUNT; ++r){
        for (int c = 0; c < CELL_COUNT; ++c){
            if(!isDarkCell(r, c)) continue;

            if (r< 3) {
                auto* piece = new Piece(PieceColor::Black, PieceType::Regular,r, c);
                setPiece(r, c, piece);
            } else if (r >= CELL_COUNT - 3){
                auto* piece = new Piece(PieceColor::White, PieceType::Regular,r, c);
                setPiece(r, c, piece);
            }
        }
    }
}

bool Board::isValidPosition(int row, int col) const
{
    return row >= 0 && row < CELL_COUNT && col >= 0 && col < CELL_COUNT;
}

bool Board::isDarkCell(int row, int col) const;
{
    return (row + col) % 2 == 1;
}

Piece* Board::pieceAt(int row, int col) const
{
    if(!isValidPosition(row, col)) return nullptr;
    return m_board[row][col]
}

void Board::setPiece(int row, int col, Piece *piece)
{
    if (!isValidPosition(row, col)) return;
    m_board[row][col] = piece;
    if (piece) piece->setPosition(row, col);
}

void Board::removePiece(int row, int col)
{
    if (!isValidPosition(row, col)) return;
    delete m_board[row][col];
    m_board[row][col] = nullptr;
}
