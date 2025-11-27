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
        void loadState(std::string nef);
        void clearBoard();
        void submitMove(const char *startPosition,const char *endPosition);

        bool validTurn(const int index) const;
        void displayPieces();
        bool piecePresent(const int index) const;
        bool noPiecesBetween(const int startIndex, const int endIndex, const ChessPiece *piece) const;
        bool validCapture(const int startIndex, const int endIndex);
        bool validMove(const int startIndex, const int endIndex) const;
        bool locationUnderAttack(const int index, const PieceColour colour) const;
        bool kingInCheck(const int kingCoordinates);
    };