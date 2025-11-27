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
bool validDiagonalMovement(const char *start_position, const char *end_position, int limit) {
    // Diagonal movement is equidistant from the x and y axis 
    int file = start_position[0] - end_position[0];
    int rank = start_position[1] - end_position[1];

    if (abs(rank) != abs(file))
        return false;
    if (rank < limit)
        return false;
    return true;
}

// Helper function for valid horizontal movement 
bool validHorizontalMovement(const char *start_position, const char *end_position, int limit) {
    int fileDiff = abs(start_position[0] - end_position[0]);
    int rankDiff = abs(start_position[1] - end_position[1]);

    // XOR operation
    if ((rankDiff != 0) != (fileDiff != 0))
        return true;
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

bool King::canMove(const char *start_position, const char *target_position) const {
    bool diagMov = validDiagonalMovement(start_position, target_position, this->movement_limit);
    bool horMov = validHorizontalMovement(start_position, target_position, this->movement_limit);

    return (diagMov && horMov);
}

// ----- QUEEN -----
Queen::Queen(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Queen::getPieceType() const {return PieceType::Queen;}

bool Queen::canMove(const char *start_position, const char *target_position) const {
    bool diagMov = validDiagonalMovement(start_position, target_position, this->movement_limit);
    bool horMov = validHorizontalMovement(start_position, target_position, this->movement_limit);
    
    return (diagMov && horMov);
}

// ----- BISHOP -----
Bishop::Bishop(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Bishop::getPieceType() const {return PieceType::Bishop;}

bool Bishop::canMove(const char *start_position, const char *target_position) const {
    return validDiagonalMovement(start_position, target_position, this->movement_limit);
}

// ----- KNIGHT -----
Knight::Knight(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Knight::getPieceType() const {return PieceType::Knight;}

bool Knight::canMove(const char *start_position, const char *target_position) const {
    int fileDiff = abs(start_position[0] - target_position[0]);
    int rankDiff = abs(start_position[1] - target_position[1]);

    return (rankDiff * fileDiff == 2);
}

// ----- ROOK -----
Rook::Rook(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Rook::getPieceType() const {return PieceType::Rook;}

bool Rook::canMove(const char *start_position, const char *target_position) const {
    return (validHorizontalMovement(start_position, target_position, this->movement_limit));
}

// ----- PAWN -----
Pawn::Pawn(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

PieceType Pawn::getPieceType() const {return PieceType::Pawn;}

bool Pawn::canMove(const char* start, const char* end) const {
    int fileDiff = std::abs(start[0] - end[0]);
    int rankDiff = end[1] - start[1]; 

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