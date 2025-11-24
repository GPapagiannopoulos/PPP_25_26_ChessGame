#include "ChessGame.h"
#include "ChessPieces.h"

ChessGame::ChessGame() { }

void ChessGame::loadState(std::string fen) {
    char file='A';
    char rank='8';

    for (int idx=0; idx < fen.size(); idx++){
        std::string coordinates;
        coordinates += file;
        coordinates += rank; 
        if (rank < '1') 
            break;
        if (fen[idx] == '/') {
            rank -- ;
            file = 'A';
        } else {
            if (isalpha(fen[idx])) {
                placePiece(coordinates, fen[idx]);
                file++;
            } else {
                file += fen[idx] - '0';
            }
        }
    }
}

// Helper function for loadState
ChessPiece *placePiece(std::string coordinates, char piece) {
    
    PieceColour colour = isupper(piece)? PieceColour::w : PieceColour::b;

    switch (tolower(piece)) { 
        case('k'):
            return new King(coordinates, colour);
        case('q'):
            return new Queen(coordinates, colour);
        case('r'):
            return new Rook(coordinates, colour);
        case('n'):
            return new Knight(coordinates, colour);
        case('b'):
            return new Bishop(coordinates, colour);
        case('p'):
            return new Pawn(coordinates, colour);
        }
};
