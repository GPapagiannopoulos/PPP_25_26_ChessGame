#include <string>

class ChessGame {
    public:
        ChessGame();
        void loadState(std::string nef);
        void submitMove(char start_position[2], char end_position[2]);
};