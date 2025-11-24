#include <string>

class ChessPiece {
    protected:
        std::string position;
        PieceColour colour;
        ChessPiece(std::string position, PieceColour colour);
    public:
        virtual void makeMove(std::string target_position) = 0;
        void capture();
        void beCaptured();
};

enum class PieceColour {w, b};

class King : virtual public ChessPiece {
    public:
        King(std::string _position, PieceColour _colour);
        void makeMove(std::string target_position) override;
        bool isCheck();
};

class Queen : virtual public ChessPiece {
    public:
        Queen(std::string position, PieceColour colour);
        void makeMove(std::string target_position) override;
};

class Bishop : virtual public ChessPiece {
    public:
        Bishop(std::string position, PieceColour colour);
        void makeMove(std::string target_position) override;
};

class Knight : virtual public ChessPiece {
    public:
        Knight(std::string position, PieceColour colour);
        void makeMove(std::string target_position) override;
};

class Rook : virtual public ChessPiece {
    public:
        Rook(std::string position, PieceColour colour);
        void makeMove(std::string target_position) override;
};

class Pawn : virtual public ChessPiece {
    public:
        Pawn(std::string position, PieceColour colour);
        void makeMove(std::string target_position) override;
};