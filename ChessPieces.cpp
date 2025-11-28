#include "ChessPieces.h"
#include "ChessGame.h"
#include <cstring>
#include <tuple>
#include <unordered_map>

std::ostream &operator<<(std::ostream &out, PieceColour colour) {
    switch(colour){
        case(PieceColour::w):
            return std::cout<<"White";
        case(PieceColour::b):
            return std::cout<<"Black";
        default:
            return std::cout<<"That is not a valid colour!\n";
        } 
}

std::ostream &operator<<(std::ostream &out, PieceType piece) {
    switch(piece){
        case(PieceType::King):
            return std::cout<<"King";
        case(PieceType::Queen):
            return std::cout<<"Queen";
        case(PieceType::Bishop):
            return std::cout<<"Bishop";
        case(PieceType::Knight):
            return std::cout<<"Knight";
        case(PieceType::Rook):
            return std::cout<<"Rook";
        case(PieceType::Pawn):
            return std::cout<<"Pawn";
        default:
            return std::cout<<"That is not a chess piece!\n";
        } 
}

// Helper function for valid diagonal movement 
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

// Helper function for valid horizontal movement 
bool validOrthogonalMovement(const int startIndex, const int endIndex, int limit) {
    int fileDiff = (endIndex % 8) - (startIndex % 8);
    int rankDiff = (endIndex / 8) - (startIndex / 8);

    if ((rankDiff != 0) && (fileDiff != 0))
        return false;
    return (std::max(std::abs(rankDiff), std::abs(fileDiff)) <= limit);       
}

// ----- BASE -----
ChessPiece::ChessPiece(PieceColour _colour) {
    this->colour = _colour;
}
ChessPiece::~ChessPiece() { }
PieceColour ChessPiece::getPieceColour() const {
    return this->colour;
}
bool ChessPiece::getHasMoved() {
    return this->hasMoved;
}
void ChessPiece::setHasMoved(const bool move) {
    this->hasMoved = move;
    return;
}

// ----- KING -----
King::King(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType King::getPieceType() const {return PieceType::King;}

bool King::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);

    return (diagMov || horMov);
}

// ----- QUEEN -----
Queen::Queen(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Queen::getPieceType() const {return PieceType::Queen;}

bool Queen::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);
    
    return (diagMov || horMov);
}

// ----- BISHOP -----
Bishop::Bishop(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Bishop::getPieceType() const {return PieceType::Bishop;}

bool Bishop::canMove(const int startIndex, const int endIndex) const {
    return validDiagonalMovement(startIndex, endIndex, this->movement_limit);
}

// ----- KNIGHT -----
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

// ----- ROOK -----
Rook::Rook(PieceColour _colour): 
            ChessPiece(_colour) { };

PieceType Rook::getPieceType() const {return PieceType::Rook;}

bool Rook::canMove(const int startIndex, const int endIndex) const {
    return (validOrthogonalMovement(startIndex, endIndex, this->movement_limit));
}

// ----- PAWN -----
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