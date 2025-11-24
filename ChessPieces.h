class ChessPiece {
    protected:
        char position[2];
        PieceColour colour;
    public:
        ChessPiece();
        virtual void makeMove(char target_position[2]) = 0;
        void capture();
        void beCaptured();
};

enum class PieceColour {w, b};

class King : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
        bool isCheck();
};

class Queen : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
};

class Bishop : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
};

class Knight : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
};

class Rook : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
};

class Pawn : virtual public ChessPiece {
    public:
        void makeMove(char target_position[2]) override;
};