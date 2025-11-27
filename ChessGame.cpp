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
    return (rank * 8 + file);
}

char recoverRank(const int index) {
    return (index / 8) + 'A';
}

char recoverFile(const int index) {
    return (index % 8) + '1';
}

std::ostream& operator<<(std::ostream& output, ChessPiece& piece){
    std::cout << "At " << piece.position << " there is a " 
    << piece.colour << " " << piece.getPieceType() << "\n";
    return output;
}

PieceColour convertColour(const char* colour) {
    switch(colour[0]) {
        case('w'):
            return PieceColour::w;
        case('b'):
            return PieceColour::b;
        default:
            std::cout << "Invalid colour. Malformed FEN string likely.\n";
            return PieceColour::n;
    }
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
            if (this->boardState[idx] != nullptr)
                std::cout << *this->boardState[idx];
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
    const char *turn = target_strings[1].c_str();
    this->toGo = convertColour(turn);

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
//    this->displayPieces();
}

void ChessGame::clearBoard() {
    for (int idx=0; idx <64; idx++) {
        this->boardState[idx] = nullptr;
    }
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
bool ChessGame::validTurn(const char *start_coordinates) const {
    int idx = flattenCoordinates(start_coordinates);
    ChessPiece *piece = this->boardState[idx];
    if (piece->getPieceColour() == this->toGo) {
        return true;
    }
    return false;
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

bool ChessGame::noPiecesBetween(const int startIndex, const int endIndex, const ChessPiece *piece) const {
    if (piece->getPieceType() == PieceType::Knight)
        return true;
    
    int fileDiff = (endIndex%8) - (startIndex%8);
    int rankDiff = (endIndex/8) - (startIndex/8);

    int fileUnit = (fileDiff == 0) ? 0 : (fileDiff > 0 ? 1 : -1);
    int rankUnit = (rankDiff == 0) ? 0 : (rankDiff > 0 ? 1 : -1);

    int stride = (rankUnit * 8) + fileUnit;
    for (int currIndex = startIndex + stride; currIndex != endIndex; currIndex += stride) {
        if (this->boardState[currIndex] != nullptr)
            return false;
    }
    
    return true;
} 

// BUG
bool ChessGame::validMove(const int startIndex, const int endIndex) const {
    ChessPiece *piece = this->boardState[startIndex];
    
    if (!piece->canMove(startIndex, endIndex)) {
        std::cout << piece->getPieceType() << " cannot move from " 
                  << recoverFile(startIndex) << recoverRank(startIndex) << " to " 
                  << recoverFile(endIndex) << recoverRank(endIndex) << ".\n";
        return false;
        }
    if (!this->noPiecesBetween(startIndex, endIndex, piece)) {
        std::cout << "There are pieces between "  
                  << recoverFile(startIndex) << recoverRank(startIndex) << " and " 
                  << recoverFile(endIndex) << recoverRank(endIndex) << ".\n";
        return false;
        }
    return true;
}

bool ChessGame::validCapture(const int startIndex, const int endIndex) {
    ChessPiece *movingPiece = this->boardState[startIndex];

    if (this->boardState[endIndex] == nullptr) {
        return true;    
    }

    if (this->boardState[startIndex]->getPieceColour() == this->boardState[endIndex]->getPieceColour())
        return false;
    
    if (this->boardState[endIndex] != nullptr) {
        //delete this->boardState[endIndex];
    }
    this->boardState[endIndex] = movingPiece;
    this->boardState[startIndex] = nullptr;
    return true;
}

//    if (!piece->canMove(start_position, end_position)) return false;
void ChessGame::submitMove(const char *start_position, const char *end_position) {
    int startIndex = flattenCoordinates(start_position);
    int endIndex = flattenCoordinates(end_position);

    // Cheeck that board is in a valid state 
    if (!this->validBoard) {
        std::cout << "The board is not in a valid state!\n"
                  << "Reset the board to continue\n";
        return;
    }

    // Check that start and end positions are valid 
    // Separating start and end positions in the check to give more granularity 
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

    // Check whether this colour to move 
    if (!validTurn(start_position)) {
        std::cout << "It is " << this->toGo << " to move!\n";
        return; 
    }

    // Check whether we have a special move 
    // 1) Castling 
    // 2) En passant 
    // 3) Pawn promotion 
    // 4) Illegal move 
    
    // Check that the piece can move to the end position 
    if (!this->validMove(startIndex, endIndex)) {
        std::cout << start_position << " to " << end_position
                  << " is not a valid move.\n";
        return; 
    }

    // Check for capture 
    if (!this->validCapture(startIndex, endIndex)) {
        std::cout << "You cannot capture your own piece.\n";
        return;
    }

    // Check for check 

    
    // Check for checkmate 

    std::cout << "Valid move.\n";
};