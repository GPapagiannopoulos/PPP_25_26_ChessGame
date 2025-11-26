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
    int x_coordinate_diff = start_position[0] - end_position[0];
    int y_coordinate_diff = start_position[1] - end_position[1];

    if (abs(x_coordinate_diff) != abs(y_coordinate_diff))
        return false;
    // x = y so doesn't matter which one we choose 
    if (x_coordinate_diff > limit)
        return false;
    return true;
}

// Helper function for valid horizontal movement 
bool validHorizontalMovement(const char *start_position, const char *end_position, int limit) {
    int x_coordinate_diff = abs(start_position[0] - end_position[0]);
    int y_coordinate_diff = abs(start_position[1] - end_position[1]);

    // Not moving your piece is not a valid move
    if ((x_coordinate_diff == 0) && (y_coordinate_diff == 0))
        return false;
    if ((x_coordinate_diff == 0) && (y_coordinate_diff < limit)) 
        return true;
    if ((x_coordinate_diff < limit) && (y_coordinate_diff == 0)) 
        return true;           
}

// Helper function for pieces in between
bool noPiecesBetween(const char *start_position, const char *end_position) {
} 

// ----- BASE -----
ChessPiece::ChessPiece(const char *_position, PieceColour _colour) {
    this->colour = _colour;
    if (_position) {
        std::strncpy(this->position, _position, 2);
    }
    this->position[2] = '\0';
 };


// ----- KING -----
King::King(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType King::getPieceType() const {
    return PieceType::King;
    }
// Helper function for King movement
//bool valid 
//void King::makeMove(std::string target_position){}

Queen::Queen(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType Queen::getPieceType() const {
    return PieceType::Queen;
    }

Bishop::Bishop(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType Bishop::getPieceType() const {
    return PieceType::Bishop;
    }

Knight::Knight(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType Knight::getPieceType() const {
    return PieceType::Knight;
    }

Rook::Rook(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType Rook::getPieceType() const {
    return PieceType::Rook;
    }

Pawn::Pawn(const char* _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
PieceType Pawn::getPieceType() const {
    return PieceType::Pawn;
    }