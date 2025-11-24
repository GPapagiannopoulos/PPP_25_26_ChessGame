#include <string>
#include <vector>

class ChessPiece;

class ChessGame {
    private:
        std::string turn;
        std::string castling;

        std::vector<ChessPiece *> pieces_in_play;
    public:
        ChessGame();
        void loadState(std::string nef);
        void submitMove(char start_position[2], char end_position[2]);

        void displayPieces();
};