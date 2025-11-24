#include "ChessGame.h"
#include "ChessPieces.h"

ChessGame::ChessGame() { }

void ChessGame::loadState(std::string nef) {

}

// Helper function for loadState
ChessPiece *placePiece(char start_coordinates[2], char piece) {
    
    PieceColour colour;
    if (isupper(piece)){
        colour = PieceColour::w;
    } else {
        colour = PieceColour::b;
    }

    switch (tolower(piece)) { 
        case('k'):
            return new King(start_coordinates, colour);
        case('q'):
            return new Queen(start_coordinates, colour);
        case('r'):
            return new Rook(start_coordinates, colour);
        case('n'):
            return new Knight(start_coordinates, colour);
        case('b'):
            return new Bishop(start_coordinates, colour);
        case('p'):
            return new Pawn(start_coordinates, colour);
        }
};
