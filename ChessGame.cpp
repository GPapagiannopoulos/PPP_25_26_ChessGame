#include "ChessGame.h"
#include "ChessPieces.h"

#include <vector>
#include <iostream>


ChessGame::ChessGame(){
    for (char file = 'A'; file < 'I'; file++) {
        for (char rank = '1'; rank < '9'; rank++) {
            std::string coordinates;
            coordinates += file;
            coordinates += rank;
            this->boardState[coordinates] = nullptr;
        }
    }
}


std::ostream& operator<<(std::ostream& out, PieceColour colour) {
    switch(colour){
        case(PieceColour::w):
            return std::cout<<"White";
        case(PieceColour::b):
            return std::cout<<"Black";
    }
}

std::ostream& operator<<(std::ostream& output, ChessPiece& piece){
    std::cout << "At " << piece.position << " there is a " 
    << piece.colour << " " << piece.getPieceType() << "\n";
    return output;
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
}

// Helper function for loadState
std::vector<std::string> splitString(std::string string_to_parse, char delimiter) {
    std::vector<std::string> substrings;
    std::string substring;
    int idx = 0;

    while (idx < string_to_parse.size()) {
        if (string_to_parse[idx] == delimiter) {
            substrings.push_back(substring);
            substring.clear();
        } else {
            substring.push_back(string_to_parse[idx]);
        }
        idx++;
    }
    substrings.push_back(substring);
    return substrings;
}


void ChessGame::displayPieces() {
    for (char file = 'A'; file < 'I'; file++) {
        for (char rank = '1'; rank < '9'; rank++) {
            std::string coordinates;
            coordinates += file;
            coordinates += rank;
            if (this->boardState.at(coordinates) == nullptr) {
                std::cout << "At " << coordinates << " there are no pieces.\n";
            } else {
                std::cout << *this->boardState.at(coordinates);
            }
        }
    }
}

std::unordered_map<std::string, ChessPiece*> ChessGame::getBoardState() {
    return this->boardState;
}

void ChessGame::loadState(std::string fen) {
    // We use splitString to keep the logic modular 
    // The same effect can be achieved using a single loop but then we would be 
    // dealing with too many if statements
    std::vector<std::string> target_strings = splitString(fen, ' ');

    std::string positions = target_strings[0];
    this->turn = target_strings[1];
    this->castling = target_strings[2];

    std::string coordinates = "__";
    char file='A';
    char rank='8';

    for (int idx=0; idx < positions.size(); idx++){
        coordinates[0] = file;
        coordinates[1] = rank; 
        if (positions[idx] == '/') {
            rank -- ;
            file = 'A';
        } else {
            if (isalpha(positions[idx])) {
                ChessPiece *piece= placePiece(coordinates, positions[idx]);
                this->boardState[coordinates] = piece;
                file++;
            } else if (isdigit(positions[idx])){
                file += positions[idx] - '0';
            }
        }
    }
    this->displayPieces();
}