#include <string>
#include <unordered_map>

class ChessPiece;

class ChessGame {
    private:
        std::string turn;
        std::string castling;

        std::unordered_map<std::string, ChessPiece*> boardState;
    public:
        ChessGame();
        void loadState(std::string nef);
        void submitMove(char start_position[2], char end_position[2]);

        void displayPieces();
        std::unordered_map<std::string, ChessPiece*> getBoardState();

    };