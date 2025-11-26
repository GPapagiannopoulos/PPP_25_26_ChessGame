#include <string>
#include <iostream>

enum class PieceColour {w, b};
// PieceType used in testing and debugging  
enum class PieceType {King, Queen, Bishop, Knight, Rook, Pawn};

std::ostream& operator<<(std::ostream& out, PieceColour colour);

std::ostream& operator<<(std::ostream& out, PieceType piece);

class ChessPiece {
    protected:
        char position[3];
        PieceColour colour;
        ChessPiece(const char *position, PieceColour colour);
    public:
        friend std::ostream& operator<<(std::ostream& output, ChessPiece& piece);        
        //virtual void makeMove(const char* start_position, const char* target_position, int limit) = 0;
        virtual PieceType getPieceType() const = 0;
        //void capture();
        //void beCaptured();
};

class King : virtual public ChessPiece {
    public:
        King(const char *position, PieceColour _colour);
        PieceType getPieceType() const override;
        //void makeMove(std::string target_position) override;
        //bool isCheck();
        
};

class Queen : virtual public ChessPiece {
    public:
        Queen(const char* position, PieceColour colour);
        PieceType getPieceType() const override;

        //void makeMove(std::string target_position) override;
};

class Bishop : virtual public ChessPiece {
    public:
        Bishop(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        //void makeMove(std::string start_position, std::string target_position, int limit) override;
};

class Knight : virtual public ChessPiece {
    public:
        Knight(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        //void makeMove(std::string target_position) override;
};

class Rook : virtual public ChessPiece {
    public:
        Rook(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        //void makeMove(std::string target_position) override;
};

class Pawn : virtual public ChessPiece {
    public:
        Pawn(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        //void makeMove(std::string target_position) override;
};