#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <string>
#include <iostream>

/**
 * @enum PieceColour 
 * @brief indicates the side of a piece 
 *  - w: White
 *  - b: Black 
 *  - n: Error state 
 */
enum class PieceColour {w, b, n};

/**
 * @brief Stream insertion for PieceColour.
 * Outputs full names: "White", "Black".
 */
std::ostream &operator<<(std::ostream &out, PieceColour colour);

/**
 * @enum PieceType
 * @brief Identifies the specific rank of a chess piece.
 */
enum class PieceType {King, Queen, Bishop, Knight, Rook, Pawn};

/**
 * @brief Stream insertion for PieceType.
 * Outputs full names: "King", "Queen", etc.
 */
std::ostream &operator<<(std::ostream &out, PieceType piece);

/**
 * @class ChessPiece 
 * @brief abstract class representing a generic chess piece  
 * *This class defines the characteristics of individual pieces and the geometry of 
 * their movement. It does *NOT* have access to the broader boardState.  
 */
class ChessPiece {
    protected:
        /**
         * @brief tracks whether a specific piece has moved
         * Important for tracking castling rights and pawn double advances 
         */
        bool hasMoved = true;

        PieceColour colour;

        /**
         * @brief protected constructor for chesspieces 
         * Protected to prevent direct initialization of a base class object 
         * @param colour the side to which the piece belongs (White/Black)
         */
        ChessPiece(PieceColour colour);

    public:
        /**
         * @brief virtual destructor
         * Necessary to ensure the proper deletion of derived classes when calling delete on ChessPiece * variables
         */
        virtual ~ChessPiece();

        /**
         * @brief getter for the colour attribute 
         * @return the value of the colour attribute 
         */
        PieceColour getPieceColour() const;

        /**
         * @brief virtual getter for the PieceType 
         * PieceType is not implemented as an attribute since it cannot meaningfully be changed - pawn promotion is the only 
         * application but knowing the piece used to be a pawn adds no value. Therefore this function is overridden in 
         * derived classes to return the correct PieceType rather than getting an attribute. So piece.piecetype or equivalent is NOT implemented.
         * @return the PieceType of the current piece 
         */
        virtual PieceType getPieceType() const = 0;

        /**
         * @brief getter for hasMoved attributed
         * @return boolean hasMoved attribute 
         */
        bool getHasMoved() const;

        /**
         * @brief setter for hasMoved attribute 
         * @param move boolean value to which hasMoved gets changed into
         */
        void setHasMoved(const bool move);

        /**
         * @brief determines whether the movement is geometrically valid for a given piece 
         * Checks only whether moving from startIndex to endIndex is geometrically valid for a given piece. 
         * Does not whether the piece is blocked, the destination occupied by a friend, or the move illegal
         * @param startIndex the index in which the piece is stored in the 1D boardState array 
         * @param endIndex the index to which the piece wants to be placed in the 1D boardState array 
         * @return true if the move matches the piece's rules, false otherwise 
         */
        virtual bool canMove(const int startIndex, const int endIndex) const = 0;
};

/**
 * @class King 
 */
class King : public ChessPiece {
    private:
        int movement_limit = 1;

    public:
        King(PieceColour _colour);

        /**
         * @return PieceType::King 
         */
        PieceType getPieceType() const override;

        /**
         * @brief implements the geometry for standard King moves 
         * Checks whether the start and end positions are within one square in any direction
         * Does NOT accept castling moves because these are handled by the ChessGame object  
         * @return true if move geometrically valid, otherwise false 
         */
        bool canMove(const int startIndex, const int endIndex) const override;
};

/**
 * @class Queen 
 */
class Queen : public ChessPiece {
    private:
        int movement_limit = 8;

    public:
        Queen(PieceColour colour);

        /**
         * @return PieceType::Queen
         */
        PieceType getPieceType() const override;

        /**
         * @brief validates combined Bishop/Rook geometry 
         * Checks strictly for diagonal OR orthogonal movement 
         */
        bool canMove(const int startIndex, const int endIndex) const override;
};

/**
 * @class Bishop
 */
class Bishop : public ChessPiece {
    private:
        int movement_limit = 8;

    public:
        Bishop(PieceColour colour);

        /**
         * @return PieceType::Bishop
         */
        PieceType getPieceType() const override;

        /**
         * @brief validates strictly diagonal movement 
         * Validates movement in any diagonal direction
         */
        bool canMove(const int startIndex, const int endIndex) const override ;
};

/**
 * @class Knight 
 */
class Knight : public ChessPiece {
    public:
        Knight(PieceColour colour);

        /**
         * @return PieceType::Knight
         */
        PieceType getPieceType() const override;

        /**
         * @brief enforces Knight "L"-shape movement
         */
        bool canMove(const int startIndex, const int endIndex) const override;
};

/**
 * @class Rook 
 */
class Rook : public ChessPiece {
    private:
        int movement_limit = 8;

    public:
        Rook(PieceColour colour);

        /**
         * @return PieceType::Rook
         */
        PieceType getPieceType() const override;

        /**
         * @brief enforces strict orthogonal movement along one axis
         */
        bool canMove(const int startIndex, const int endIndex) const override;
};

/**
 * @class Pawn 
 */
class Pawn : public ChessPiece {
    public:
        Pawn(PieceColour colour);

        /**
         * @return PieceType::Pawn 
         */
        PieceType getPieceType() const override;

        /**
         * @brief checks pawn movement during advancement AND capturing 
         * Valid geometry includes one square along the diagonals as during capturing 
         */
        bool canMove(const int startIndex, const int endIndex) const override;
};

#endif