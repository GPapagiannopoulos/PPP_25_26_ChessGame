#include "ChessGame.h"
#include "ChessPieces.h"

#include <vector>
#include <iostream>

// ----- HELPER FUNCTIONS -----

// Helper function for determining coordinates 
int flattenCoordinates(const char *coordinates) {
    if (!coordinates)
        return -1;
    int file = coordinates[0] - 'A';
    int rank = coordinates[1] - '1';
    return (file * 8 + rank);
}

char retrieveRank(const int index) {
    return (index / 8) + 'A';
}

char retrieveFile(const int index) {
    return (index % 8) + '1';
}


std::ostream& operator<<(std::ostream& output, ChessPiece& piece){
    std::cout << "At " << piece.position << " there is a " 
    << piece.colour << " " << piece.getPieceType() << "\n";
    return output;
}

// Helper function for loadState
ChessPiece *placePiece(const char *coordinates, char piece) {
    
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
        default:
            std::cout << "This is not a valid code!\n";
            return nullptr;
        }
}

// Helper function for loadState
std::vector<std::string> splitString(std::string string_to_parse, char delimiter) {
    std::vector<std::string> substrings;
    std::string substring;
    unsigned idx = 0;

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

// Debugging function 
void ChessGame::displayPieces() {
    for (int idx=0; idx<64; idx++) {
            if (this->boardState[idx] == nullptr) {
                std::cout << "At " << retrieveFile(idx) << retrieveRank(idx) << " there are no pieces.\n";
            } else {
                std::cout << *this->boardState[idx];
            }
        }
    }

// ----- CHESS GAME -----
ChessGame::ChessGame() { 
    validBoard = false;
    for (int i=0; i<64; i++){
        boardState[i] = nullptr;
    }
}

void ChessGame::loadState(std::string fen) {
    // We use splitString to keep the logic modular 
    // The same effect can be achieved using a single loop but then we would be 
    // dealing with too many if statements
    std::vector<std::string> target_strings = splitString(fen, ' ');
    std::string positions = target_strings[0];

    char file='A';
    char rank='8';
    for (unsigned int idx=0; idx < positions.size(); idx++) {
        if (positions[idx] == '/') {
            rank-- ;
            file = 'A';
        } else if (isdigit(positions[idx])) {
                file += positions[idx] - '0';
        } else if (isalpha(positions[idx])) {
                char coordinates[3] = {file, rank, '\0'};
                int index = flattenCoordinates(coordinates);
                ChessPiece *piece= placePiece(coordinates, positions[idx]);
                this->boardState[index] = piece;
                file++;
            } 
            
        }
    this->validBoard = true;
    this->displayPieces();
}

// Helper function for submitMove 
bool validCoordinates(const char *position) {
    if (!position)
        return false;
    if ((position[0] <'A') || position[0] > 'H') 
        return false;
    if ((position[1] <'1') || (position[1] > '8'))
        return false;
    return true;
}

// Helper function for submitMove 
bool ChessGame::piecePresent(const char *position) const {
    if (!position)
        return false;
    int index = flattenCoordinates(position);
    if (this->boardState[index] == nullptr)
        return false;
    return true;
}

bool ChessGame::noPiecesBetween(const char *start_position, const char *end_position) const {
    int index = flattenCoordinates(start_position);
    ChessPiece *piece = this->boardState[index];

    if (!piece->canMove(start_position, end_position)) 
        return false;
    return true;
} 

void ChessGame::submitMove(const char *start_position, const char *end_position) {
    // Cheeck that board is in a valid state 
    if (!this->validBoard) {
        std::cout << "The board is not in a valid state!\n"
                  << "Reset the board to continue\n";
        return;
    }

    // Check that start and end positions are valid 
    if (!validCoordinates(start_position)) {
        std::cout << start_position[0] << start_position[1]  
                  << " is not a valid square on the board.\n";
        return;
    }
    if (!validCoordinates(end_position)) {
        std::cout << end_position[0] << end_position[1] 
                  << " is not a valid square on the board.\n";
        return;
    }

    // Check that there are pieces in start position 
    if (!piecePresent(start_position)) {
        std::cout << "There are no pieces at " << start_position << "\n";
        return; 
    }

    // Check that the piece can move to the end position 
    // 1) Piece movement 
    // 2) Pieces blocking the way 

    // Check for capture 

    // Check for check 

    // Check for checkmate 
}