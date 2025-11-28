#include <string>

class ChessPiece;
enum class PieceColour;

class ChessGame {
    private:
        bool validBoard;
        PieceColour toGo;    
        ChessPiece *boardState[64];
        int blackKingPosition;
        int whiteKingPosition;

    public:
        ChessGame();
        ~ChessGame();
        ChessGame(const ChessGame&) = delete;
        ChessGame &operator=(const ChessGame&) = delete;
        void loadState(std::string nef);
        void clearBoard();
        void submitMove(const char *startPosition,const char *endPosition);

        void printBoard();
        bool validTurn(const int index) const;
        void displayPieces();
        bool piecePresent(const int index) const;
        bool noPiecesBetween(const int startIndex, const int endIndex, const ChessPiece *piece) const;
        bool canCapture(const int startIndex, const int endIndex);
        bool isMoveSafe(const int startIndex, const int endIndex);
        bool castlePossible(int startIdx, int endIdx) const;
        bool validMove(const int startIndex, const int endIndex);
        void commitMove(const int startIndex, const int endIndex);
        bool locationUnderAttack(const int index, const PieceColour colour) const;
        bool kingInCheck(const int index);
        bool hasLegalMoves(PieceColour colour);
        bool isCheckmate(PieceColour colour);
        bool isStalemate(PieceColour colour);

        void endTurn(const int startIndex);
    };