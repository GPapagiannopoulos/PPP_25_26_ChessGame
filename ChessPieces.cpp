#include "ChessPieces.h"
#include "ChessGame.h"
#include <cstring>
#include <tuple>
#include <unordered_map>

std::ostream& operator<<(std::ostream& out, PieceColour colour) {
    switch(colour){
        case(PieceColour::w):
            return std::cout<<"White";
        case(PieceColour::b):
            return std::cout<<"Black";
        default:
            return std::cout<<"That is not a valid colour!\n";
        } 
}

std::ostream& operator<<(std::ostream& out, PieceType piece) {
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

    // XOR operation
    if ((rankDiff != 0) != (fileDiff != 0))
        return true;
    if ((rankDiff < limit) && (fileDiff < limit))
        return false;
    return false;        
}

// ----- BASE -----
ChessPiece::ChessPiece(const char *_position, PieceColour _colour) {
    this->colour = _colour;
    if (_position) {
        std::strncpy(this->position, _position, 2);
    }
    this->position[2] = '\0';
}

PieceColour ChessPiece::getPieceColour() const {
    return this->colour;
}

// ----- KING -----
King::King(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType King::getPieceType() const {return PieceType::King;}

bool King::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);

    return (diagMov || horMov);
}

// ----- QUEEN -----
Queen::Queen(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Queen::getPieceType() const {return PieceType::Queen;}

bool Queen::canMove(const int startIndex, const int endIndex) const {
    bool diagMov = validDiagonalMovement(startIndex, endIndex, this->movement_limit);
    bool horMov = validOrthogonalMovement(startIndex, endIndex, this->movement_limit);
    
    return (diagMov || horMov);
}

// ----- BISHOP -----
Bishop::Bishop(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Bishop::getPieceType() const {return PieceType::Bishop;}

bool Bishop::canMove(const int startIndex, const int endIndex) const {
    return validDiagonalMovement(startIndex, endIndex, this->movement_limit);
}

// ----- KNIGHT -----
Knight::Knight(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Knight::getPieceType() const {return PieceType::Knight;}

bool Knight::canMove(const int startIndex, const int endIndex) const {
    int fileDiff = std::abs((endIndex % 8) - (startIndex % 8));
    int rankDiff = std::abs((endIndex / 8) - (endIndex / 8));

    return (rankDiff * fileDiff == 2);
}

// ----- ROOK -----
Rook::Rook(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Rook::getPieceType() const {return PieceType::Rook;}

bool Rook::canMove(const int startIndex, const int endIndex) const {
    return (validOrthogonalMovement(startIndex, endIndex, this->movement_limit));
}

// ----- PAWN -----
Pawn::Pawn(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Pawn::getPieceType() const {return PieceType::Pawn;}

bool Pawn::canMove(const int startIndex, const int endIndex) const {
    int fileDiff = std::abs((endIndex % 8) - (startIndex % 8));
    int rankDiff = (endIndex / 8) - (startIndex /8); 

    if (colour == PieceColour::w) {
        if (rankDiff < 1 || rankDiff > 2) return false; 
    } else {
        if (rankDiff > -1 || rankDiff < -2) return false; 
    }

    int forwardSteps = std::abs(rankDiff);

    if (forwardSteps == 2) {
        return (!hasMoved) && (fileDiff == 0); 
    }

    return (forwardSteps == 1) && (fileDiff <= 1);
}