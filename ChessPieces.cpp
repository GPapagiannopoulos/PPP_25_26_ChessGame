#include "ChessPieces.h"
#include "ChessGame.h"
#include <string>
#include <tuple>
#include <unordered_map>

// Helper function for piece movement 
bool validCoordinates(std::string position) {
    if ((position[0] <'A') || position[0] > 'H') 
        return false;
    if ((position[1] <'1') || (position[1] > '8'))
        return false;
    return true;
}

// Helper function for valid diagonal movement 
bool validDiagonalMovement(std::string start_position, std::string end_position, int limit) {
    // Diagonal movement is equidistant from the x and y axis 
    int x_coordinate_diff = start_position[0] - end_position[0];
    int y_coordinate_diff = start_position[1] - end_position[1];

    if (abs(x_coordinate_diff) != abs(y_coordinate_diff))
        return false;
    if (x_coordinate_diff > limit)
        return false;
    
    
    return true;
}

// Helper function for valid horizontal movement 
bool validHorizontalMovement(std::string start_position, std::string end_position, int limit) {
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
bool noPiecesBetween(std::string start_position, std::string end_position, 
                     std::tuple<int, int> rate_of_change, ChessGame* chessGame) {
    
    std::unordered_map<std::string, ChessPiece*> board_state = chessGame->getBoardState();
    while (start_position[0] != end_position[0] && start_position[1] != end_position[1]) {
        start_position[0] += std::get<0>(rate_of_change);
        start_position[1] += std::get<1>(rate_of_change);
    }
} 
// ----- BASE -----
ChessPiece::ChessPiece(std::string _position, PieceColour _colour):
                        position(_position),
                        colour(_colour) { };

// ----- KING -----
King::King(std::string _position, PieceColour _colour): 
            ChessPiece(_position, _colour) { };
std::string King::getPieceType() {
    return "King";
}
// Helper function for King movement
//bool valid 
//void King::makeMove(std::string target_position){}

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