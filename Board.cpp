#include <iostream>
#include "Board.h"

Board::Board(){
    // initialize the board
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < boardWidth; j++){
            board[i][j] = Pieces::WHITE;
        }
    }
    for(int i = 2; i < boardLength - 2; i++){
        for(int j = 0; j < boardWidth; j++){
            board[i][j] = Pieces::EMPTY;
        }
    }
    for(int i = boardLength - 2; i < boardLength; i++){
        for(int j = 0; j < boardWidth; j++){
            board[i][j] = Pieces::BLACK;
        }
    }
    generatePieceLists();
    turn = Turn::FIRST;
}

// gets the piece lists
void Board::generatePieceLists(){
    whitePieces.clear();
    blackPieces.clear();
    for(int i = 0; i < boardLength; i++){
        for(int j = 0; j < boardWidth; j++){
            if(board[i][j] == Pieces::WHITE){
                whitePieces.push_back({i, j});
            }
            if(board[i][j] == Pieces::BLACK){
                blackPieces.push_back({i, j});
            }
        }
    }
}

// gets a square
int Board::getSquare(int r, int c){
    if(r > boardLength or r < 0) return -1;
    if(c >= boardWidth or c < 0) return -1;
    return board[r][c];
}

// if square contains an opponent piece
bool Board::isSquareOpponentPiece(int r, int c){
    if(getSquare(r, c) == Pieces::EMPTY) return false;
    if(getSquare(r, c) == Pieces::BLACK && turn == Turn::FIRST) return true;
    if(getSquare(r, c) == Pieces::WHITE && turn == Turn::SECOND) return true;
    else return true;
}

// if square contains a partner piece
bool Board::isSquarePartnerPiece(int r, int c){
    bool dec;
    if(getSquare(r, c) == Pieces::EMPTY) return false;
    (turn == Turn::FIRST) ? (dec = getSquare(r, c) == Pieces::WHITE) : (dec = getSquare(r, c) == Pieces::BLACK);
    return dec;
}

// if square is empty
bool Board::isSquareEmpty(int r, int c){
    if(getSquare(r, c) == Pieces::EMPTY) return true;
    return false;
}

// if the square has a piece
bool Board::isSquarePiece(int r, int c){
    int square = getSquare(r, c);
    if(square == Pieces::WHITE || square == Pieces::BLACK) return true;
    return false;
}

// generate legal moves
void Board::generateLegalMoves(){
    // clear every time
    legalMoves.clear();
    // white to move
    if(turn == Turn::FIRST){
        for(int i = 0; i < whitePieces.size(); i++){
            int squareR = whitePieces[i].first + 1;
            int pieceC = whitePieces[i].second;
            if(getSquare(squareR, pieceC) == Pieces::EMPTY){
                Move mov(whitePieces[i].first, pieceC, squareR, pieceC);
                legalMoves.push_back(mov);
            }
            if(getSquare(squareR, pieceC + 1) == Pieces::EMPTY || getSquare(squareR, pieceC) == Pieces::BLACK){
                Move mov(whitePieces[i].first, pieceC, squareR, pieceC + 1);
                legalMoves.push_back(mov);
            }
            if(getSquare(squareR, pieceC - 1) == Pieces::EMPTY || getSquare(squareR, pieceC) == Pieces::BLACK){
                Move mov(whitePieces[i].first, pieceC, squareR, pieceC - 1);
                legalMoves.push_back(mov);
            }
        }
    }
    // black to move
    if(turn == Turn::SECOND){
        for(int i = 0; i < blackPieces.size(); i++){
            int squareR = blackPieces[i].first - 1;
            int pieceC = blackPieces[i].second;
            if(getSquare(squareR, pieceC) == Pieces::EMPTY){
                Move mov(blackPieces[i].first, pieceC, squareR, pieceC);
                legalMoves.push_back(mov);
            }
            if(getSquare(squareR, pieceC + 1) == Pieces::EMPTY || getSquare(squareR, pieceC) == Pieces::WHITE){
                Move mov(blackPieces[i].first, pieceC, squareR, pieceC + 1);
                legalMoves.push_back(mov);
            }
            if(getSquare(squareR, pieceC - 1) == Pieces::EMPTY || getSquare(squareR, pieceC) == Pieces::WHITE){
                Move mov(blackPieces[i].first, pieceC, squareR, pieceC - 1);
                legalMoves.push_back(mov);
            }
        }
    }
}

bool Board::isGameOver(){
    for(int i = 0; i < boardWidth; i++){
        if(getSquare(0, i) == Pieces::BLACK) return true;
    }
    for(int i = 0; i < boardWidth; i++){
        if(getSquare(boardLength - 1, i) == Pieces::WHITE) return true;
    }
    return false;
}

Board::Winner Board::whoWon(){
    for(int i = 0; i < boardWidth; i++){
        if(getSquare(0, i) == Pieces::BLACK) return Winner::B;
    }
    for(int i = 0; i < boardWidth; i++){
        if(getSquare(boardLength - 1, i) == Pieces::WHITE) return Winner::W;
    }
    return Winner::N;
}

void Board::appendToMoveHistory(Move m){
    moveHistory.push_back(m.toString());
}

void Board::displayMoveHistory(){
    for(int i = 0; i < moveHistory.size(); i++){
        if(i == moveHistory.size() - 1) std::cout << moveHistory[i];
        std::cout << moveHistory[i] << ", ";
    }
}

// display the board
void Board::displayBoard(){
    for(int i = boardLength - 1; i >= 0; i--){
        for(int j = 0; j < boardWidth; j++){
            if(board[i][j] == Pieces::WHITE) std::cout << "w";
            if(board[i][j] == Pieces::BLACK) std::cout << "b";
            if(board[i][j] == Pieces::EMPTY) std::cout << "-";
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Board::displayLegalMoves(){
    for(int i = 0; i < legalMoves.size(); i++){
        std::cout << legalMoves[i].toString() << ", ";
    }
}

void Board::displayPieceList(){
    for(int i = 0; i < whitePieces.size(); i++){
        std::cout << whitePieces[i].first << "," << whitePieces[i].second << std::endl;
    }
}

int main(){
    Board board;
    board.displayBoard();
    board.generateLegalMoves();
    board.displayLegalMoves();
    // board.displayPieceList();
}