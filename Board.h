#include <utility>
#include <vector>
#include "Move.cpp"

class Board{
    private:
        enum Turn{
            FIRST,
            SECOND
        };
        enum Pieces{
            EMPTY,
            WHITE,
            BLACK
        };
        const static int boardWidth = 8;
        const static int boardLength = 8;
        enum Turn turn;
        int board[boardWidth][boardLength];
        std::vector<std::pair<int, int>> whitePieces;
        std::vector<std::pair<int, int>> blackPieces;
        std::vector<Move> legalMoves;
        std::vector<std::string> moveHistory;

    public:
        Board();
        void generatePieceLists();
        int getSquare(int r, int c);
        bool isSquarePiece(int r, int c);
        bool isSquareEmpty(int r, int c);
        void displayBoard();
        void makeMove();
        void undoMove();
        bool canCapture();
        bool isGameOver();
        bool isSquareOpponentPiece(int r, int c);
        bool isSquarePartnerPiece(int r, int c);
        void generateLegalMoves();
        void appendToMoveHistory(Move);
        void displayLegalMoves();
        void displayPieceList();
};