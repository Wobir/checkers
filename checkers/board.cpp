#include "board.h"

#include <QDebug>

Board::Board()
{
    m_board.resize(CELL_COUNT);
    for (int i = 0; i< CELL_COUNT; ++i){
        m_board[i].resize(CELL_COUNT);
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

bool Board::isDarkCell(int row, int col) const
{
    return (row + col) % 2 == 1;
}

Piece* Board::pieceAt(int row, int col) const
{
    if(!isValidPosition(row, col)) return nullptr;
    return m_board[row][col];
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

QVector<Move> Board::getPossibleMoves(int row, int col) const{
    QVector<Move> moves;
    Piece* piece = pieceAt(row,col);

    QVector<QPair<int,int>> directions;
    if (piece->color() == PieceColor::White || piece->isKing()){
        directions << QPair<int, int>(-1, -1) << QPair<int,int>(-1, 1);
    }
    if (piece->color() == PieceColor::Black || piece->isKing()){
        directions << QPair<int, int>(1, -1) << QPair<int,int>(1, 1);
    }

    for(const auto& dir : directions){
        int newRow = row + dir.first;
        int newCol = col + dir.second;

        if(isValidPosition(newRow, newCol) && !pieceAt(newRow, newCol)){
            Move move{row, col, newRow, newCol, false, -1, -1};
            moves.append(move);
        }
    }

    return moves;
}

QVector<Move> Board::getCaptureMoves(int row, int col) const{
    QVector<Move> moves;

    Piece* piece = pieceAt(row, col);

    if(!piece) return moves;

    QVector<QPair<int,int>> directions;
    if (piece->color() == PieceColor::White || piece->isKing()){
        directions << QPair<int, int>(-1,-1) << QPair<int, int>(-1, 1);
    }
    if (piece->color() == PieceColor::Black || piece->isKing()){
        directions << QPair<int, int>(1,-1) << QPair<int, int>(1,1);
    }

    for (const auto& dir : directions){
        int midRow = row + dir.first;
        int midCol = col + dir.second;
        int newRow = row + 2 * dir.first;
        int newCol = col + 2 * dir.second;

        if (isValidPosition(newRow, newCol) && !pieceAt(newRow, newCol)){
            Piece* midPiece = pieceAt(midRow, midCol);
            if (midPiece && midPiece->color() != piece->color()){
                Move move{row, col, newRow, newCol, true, midRow, midCol};
                moves.append(move);
            }
        }
    }
    return moves;
}

















