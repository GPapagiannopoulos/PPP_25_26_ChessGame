#include <string>

class ChessPiece;

class ChessGame {
    private:
        bool validBoard;
        char toGo[2];    
        ChessPiece *boardState[64];
    public:
        ChessGame();
        void loadState(std::string nef);
        void submitMove(const char *start_position,const char *end_position);

        void displayPieces();
        bool piecePresent(const char *coordinates) const;
        bool noPiecesBetween(const char *start_position, const char *end_position) const;
    };