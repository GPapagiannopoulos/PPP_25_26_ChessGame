#include "ChessPieces.h"
#include <string>

ChessPiece::ChessPiece(std::string _position, PieceColour _colour):
                        position(_position),
                        colour(_colour) { };

Pawn::Pawn(std::string _position, PieceColour _colour):
            ChessPiece(_position, _colour) { };

King::King(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

Queen::Queen(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

Bishop::Bishop(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

Knight::Knight(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

Rook::Rook(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };

Pawn::Pawn(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };