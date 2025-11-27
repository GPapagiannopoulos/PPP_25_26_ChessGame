#include <string>

class ChessPiece;
enum class PieceColour;

class ChessGame {
    private:
        bool validBoard;
        PieceColour toGo;    
        ChessPiece *boardState[64];
    public:
        ChessGame();
        void loadState(std::string nef);
        void clearBoard();
        void submitMove(const char *start_position,const char *end_position);

        bool validTurn(const char *coordinates) const;
        void displayPieces();
        bool piecePresent(const char *coordinates) const;
        bool noPiecesBetween(const int startIndex, const int endIndex, const ChessPiece *piece) const;
        bool validMove(const char *start_position, const char *end_position) const;
    };