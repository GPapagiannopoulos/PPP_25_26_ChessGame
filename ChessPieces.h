#include <string>
#include <iostream>

enum class PieceColour {w, b};
// PieceType used in testing and debugging  
enum class PieceType {King, Queen, Bishop, Knight, Rook, Pawn};

std::ostream& operator<<(std::ostream& out, PieceColour colour);

class ChessPiece {
    protected:
        std::string position;
        PieceColour colour;
        ChessPiece(std::string position, PieceColour colour);
    public:
        friend std::ostream& operator<<(std::ostream& output, ChessPiece& piece);        
        //virtual void makeMove(std::string target_position) = 0;
        virtual std::string getPieceType() = 0;
        //void capture();
        //void beCaptured();
};

class King : virtual public ChessPiece {
    public:
        King(std::string _position, PieceColour _colour);
        std::string getPieceType() override;
        /*
        void makeMove(std::string target_position) override;
        bool isCheck();
        */
};

class Queen : virtual public ChessPiece {
    public:
        Queen(std::string position, PieceColour colour);
        std::string getPieceType() override;

        //void makeMove(std::string target_position) override;
};

class Bishop : virtual public ChessPiece {
    public:
        Bishop(std::string position, PieceColour colour);
        std::string getPieceType() override;

        //void makeMove(std::string target_position) override;
};

class Knight : virtual public ChessPiece {
    public:
        std::string getPieceType() override;
        Knight(std::string position, PieceColour colour);
        //void makeMove(std::string target_position) override;
};

class Rook : virtual public ChessPiece {
    public:
        std::string getPieceType() override;
        Rook(std::string position, PieceColour colour);
        //void makeMove(std::string target_position) override;
};

class Pawn : virtual public ChessPiece {
    public:
        std::string getPieceType() override;
        Pawn(std::string position, PieceColour colour);
        //void makeMove(std::string target_position) override;
};