#include "ChessPieces.h"
#include "ChessGame.h"

#include <cstring>
#include <tuple>
#include <unordered_map>

std::ostream &operator<<(std::ostream &out, PieceColour colour) {
    switch(colour){
        case(PieceColour::w):
            return out<<"White";
        case(PieceColour::b):
            return out<<"Black";
        default:
            return out<<"That is not a valid colour!\n";
        } 
}

std::ostream &operator<<(std::ostream &out, PieceType piece) {
    switch(piece){
        case(PieceType::King):
            return out<<"King";
        case(PieceType::Queen):
            return out<<"Queen";
        case(PieceType::Bishop):
            return out<<"Bishop";
        case(PieceType::Knight):
            return out<<"Knight";
        case(PieceType::Rook):
            return out<<"Rook";
        case(PieceType::Pawn):
            return out<<"Pawn";
        default:
            return out<<"That is not a chess piece!\n";
        } 
}

/**
 * @brief helper function for canMove
 * Validates that the movement of a piece is strictly on a diagonal 
 * @param startIndex the starting sqaure of the piece converted to the index of the 1D array boardState
 * @param endIndex the ending sqaure of the piece converted to the index of the 1D array boardState
 * @return true if the movement is STRICTLY on a diagonal, otherwise false 
 */
bool validDiagonalMovement(const int startIndex, const int endIndex, int limit) {
    // Diagonal movement is equidistant from the x and y axis 
    int fileDiff = (endIndex % 8) - (startIndex % 8);
    int rankDiff = (endIndex / 8) - (startIndex / 8);

    if (abs(rankDiff) != abs(fileDiff))
        return false;
    if (abs(rankDiff) > limit)
        return false;
    return true;
}

/**
 * @brief helper function for canMove
 * Validates that the movement of a piece is strictly along one axis  
 * @param startIndex the starting sqaure of the piece converted to the index of the 1D array boardState
 * @param endIndex the ending sqaure of the piece converted to the index of the 1D array boardState
 * @return true if the movement is STRICTLY on one axis, otherwise false 
 */
bool validOrthogonalMovement(const int startIndex, const int endIndex, int limit) {
    int fileDiff = (endIndex % 8) - (startIndex % 8);
    int rankDiff = (endIndex / 8) - (startIndex / 8);

    if ((rankDiff != 0) && (fileDiff != 0))
        return false;
    return (std::max(std::abs(rankDiff), std::abs(fileDiff)) <= limit);       
}

// Generic Chess Piece  
//----------------------------------------
ChessPiece::ChessPiece(PieceColour _colour) {
    this->colour = _colour;
}
ChessPiece::~ChessPiece() { }
PieceColour ChessPiece::getPieceColour() const {
    return this->colour;
}
bool ChessPiece::getHasMoved() const{
    return this->hasMoved;
}
void ChessPiece::setHasMoved(const bool move) {
    this->hasMoved = move;
    return;
}

// King 
//----------------------------------------
King::King(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType King::getPieceType() const {return PieceType::King;}

bool King::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);

    return (diagMov || horMov);
}

// Queen 
//----------------------------------------
Queen::Queen(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Queen::getPieceType() const {return PieceType::Queen;}

bool Queen::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);
    
    return (diagMov || horMov);
}

// Bishop
//----------------------------------------
Bishop::Bishop(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Bishop::getPieceType() const {return PieceType::Bishop;}

bool Bishop::canMove(const int startIndex, const int endIndex) const {
    return validDiagonalMovement(startIndex, endIndex, this->movement_limit);
}

// Knight
//----------------------------------------
Knight::Knight(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Knight::getPieceType() const {return PieceType::Knight;}

bool Knight::canMove(const int startIndex, const int endIndex) const {
    // Preventing board wrap-around 
    int startFile = startIndex % 8;
    int startRank = startIndex / 8;

    int endFile = endIndex % 8;
    int endRank = endIndex / 8;

    int fileDiff = std::abs(endFile - startFile);
    int rankDiff = std::abs(endRank - startRank);

    return (fileDiff == 1 && rankDiff == 2) ||
           (fileDiff == 2 && rankDiff == 1);
}

// Rook 
//----------------------------------------
Rook::Rook(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Rook::getPieceType() const {return PieceType::Rook;}

bool Rook::canMove(const int startIndex, const int endIndex) const {
    return (validOrthogonalMovement(startIndex, endIndex, this->movement_limit));
}

// Pawn 
//----------------------------------------
Pawn::Pawn(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Pawn::getPieceType() const {return PieceType::Pawn;}

bool Pawn::canMove(const int startIndex, const int endIndex) const {
    int direction = colour == PieceColour::w? 1 : -1;
    int startingRank = colour == PieceColour::w? 1 : 6;
    
    int startRank = startIndex / 8;
    int startFile = startIndex % 8;
    int endRank = endIndex / 8;
    int endFile = endIndex % 8;

    int fileDiff = std::abs(endFile - startFile);
    int rankDiff = endRank - startRank;

    if (fileDiff == 0) {
        if (rankDiff == direction) {
            return true;
        }
        if (startRank == startingRank && rankDiff == (2 * direction)) {
            return true;
        }
        return false;
    }

    if (fileDiff == 1) {
        if (rankDiff == direction) {
            return true;
        }
        return false;
    }

    return false;
}