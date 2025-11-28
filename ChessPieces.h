#include <string>
#include <iostream>

enum class PieceColour {w, b, n};
enum class PieceType {King, Queen, Bishop, Knight, Rook, Pawn};

std::ostream &operator<<(std::ostream &out, PieceColour colour);
std::ostream &operator<<(std::ostream &out, PieceType piece);

// ----- BASE CLASS -----
class ChessPiece {
    protected:
        bool hasMoved = true;
        PieceColour colour;
        ChessPiece(PieceColour colour);
    public:
        virtual ~ChessPiece();
        PieceColour getPieceColour() const;
        virtual PieceType getPieceType() const = 0;
        void setHasMoved(const bool move);
        bool getHasMoved();
        virtual bool canMove(const int startIndex, const int endIndex) const = 0;
        friend std::ostream& operator<<(std::ostream &output, ChessPiece piece);        
};

class King : virtual public ChessPiece {
    private:
        int movement_limit = 1;
    public:
        King(PieceColour _colour);
        PieceType getPieceType() const override;
        PieceColour getPieceColour() const;
        bool canMove(const int startIndex, const int endIndex) const override;
};

class Queen : virtual public ChessPiece {
    private:
        int movement_limit = 8;
    public:
        Queen(PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const int startIndex, const int endIndex) const override;
};

class Bishop : virtual public ChessPiece {
    private:
        int movement_limit = 8;
    public:
        Bishop(PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const int startIndex, const int endIndex) const override ;
};

class Knight : virtual public ChessPiece {
    public:
        Knight(PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const int startIndex, const int endIndex) const override;
};

class Rook : virtual public ChessPiece {
    private:
        int movement_limit = 8;
    public:
        Rook(PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const int startIndex, const int endIndex) const override;
};

class Pawn : virtual public ChessPiece {
    private:
        int movement_limit = 8; 
    public:
        Pawn(PieceColour colour);
        PieceType getPieceType() const override;
        bool canMove(const int startIndex, const int endIndex) const override;
};