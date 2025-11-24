#include "ChessPieces.h"
#include <string>

ChessPiece::ChessPiece(std::string _position, PieceColour _colour):
                        position(_position),
                        colour(_colour) { };

King::King(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string King::getPieceType() {
    return "King";
}

Queen::Queen(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string Queen::getPieceType() {
    return "Queen";
}

Bishop::Bishop(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string Bishop::getPieceType() {
    return "Bishop";
}

Knight::Knight(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string Knight::getPieceType() {
    return "Knight";
}

Rook::Rook(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string Rook::getPieceType() {
    return "Rook";
}

Pawn::Pawn(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string Pawn::getPieceType() {
    return "Pawn";
}