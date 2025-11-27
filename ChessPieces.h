#include <string>
#include <iostream>

enum class PieceColour {w, b, n};
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
        virtual bool canMove(const char* start_position, const char* target_position) const = 0;
        virtual PieceType getPieceType() const = 0;
        PieceColour getPieceColour() const;
        //void capture();
        //void beCaptured();
};

class King : virtual public ChessPiece {
    private:
        int movement_limit = 1;
        bool hasMoved = false;
    public:
        King(const char *position, PieceColour _colour);
        PieceType getPieceType() const override;
        PieceColour getPieceColour() const;
        bool canMove(const char *start_position, const char *target_position) const override;
        bool makeFirstMove();
        //bool isCheck();
        
};

class Queen : virtual public ChessPiece {
    private:
        int movement_limit = 8;
    public:
        Queen(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const char *start_position, const char *target_position) const override;
};

class Bishop : virtual public ChessPiece {
    private:
        int movement_limit = 8;
    public:
        Bishop(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const char *start_position, const char *target_position) const override;
};

class Knight : virtual public ChessPiece {
    public:
        Knight(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const char *start_position, const char *target_position) const override;
};

class Rook : virtual public ChessPiece {
    private:
        int movement_limit = 8;
        bool hasMoved = false;  
    public:
        Rook(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const char *start_position, const char *target_position) const override;
        bool makeFirstMove();
};

class Pawn : virtual public ChessPiece {
    private:
        int movement_limit = 8; 
        bool hasMoved = false;   
    public:
        Pawn(const char* position, PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const char *start_position, const char *target_position) const override;
        bool makeFirstMove();
};