#include "ChessGame.h"
#include "ChessPieces.h"

#include <vector>
#include <iostream>
#include <string>
// ----- HELPER FUNCTIONS -----

// Helper function for determining coordinates 
int flattenCoordinates(const char *coordinates) {
    if (!coordinates) 
        return -1;
    
    int file = coordinates[0] - 'A'; 
    int rank = coordinates[1] - '1'; 

    if (file < 0 || file > 7 || rank < 0 || rank > 7) 
        return -1;

    return (rank * 8) + file;
}

char recoverRank(const int index) {
    int rankIndex = index / 8;
    return rankIndex + '1'; 
}

char recoverFile(const int index) {
    int fileIndex = index % 8;
    return fileIndex + 'A'; 
}

PieceColour convertColour(const char* colour) {
    if (colour[0] == 'w') {
        return PieceColour::w;
    } else {
        return PieceColour::b;
        }
    }

// Helper function for loadState
ChessPiece *placePiece(char piece) {
    
    PieceColour colour = isupper(piece)? PieceColour::w : PieceColour::b;

    switch (tolower(piece)) { 
        case('k'):
            return new King(colour);
        case('q'):
            return new Queen(colour);
        case('r'):
            return new Rook(colour);
        case('n'):
            return new Knight(colour);
        case('b'):
            return new Bishop(colour);
        case('p'):
            return new Pawn(colour);
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

// ----- CHESS GAME -----
ChessGame::ChessGame() { 
    this->validBoard = false;
    this->blackKingPosition = -1;
    this->whiteKingPosition = -1;
    for (int i=0; i<64; i++) {
        this->boardState[i] = nullptr;
    }
}

ChessGame::~ChessGame() {
    for (int i=0;i<64; i++) {
        delete this->boardState[i];
    }
}

void ChessGame::printBoard() {
    std::cout << "  +-----------------+\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << " | ";
        for (int file = 0; file < 8; file++) {
            int idx = (rank * 8) + file;
            ChessPiece* p = boardState[idx];
            if (p == nullptr) {
                std::cout << ". ";
            } else {
                char c;
                switch(p->getPieceType()) {
                    case PieceType::King: c = 'k'; break;
                    case PieceType::Queen: c = 'q'; break;
                    case PieceType::Rook: c = 'r'; break;
                    case PieceType::Bishop: c = 'b'; break;
                    case PieceType::Knight: c = 'n'; break;
                    case PieceType::Pawn: c = 'p'; break;
                }
                if (p->getPieceColour() == PieceColour::w) c = toupper(c);
                std::cout << c << " ";
            }
        }
        std::cout << "|\n";
    }
    std::cout << "  +-----------------+\n";
    std::cout << "    A B C D E F G H \n\n";
}

void ChessGame::clearBoard() {
    
    this->blackKingPosition = -1;
    this->whiteKingPosition = -1;
    this->validBoard = false;
    this->toGo = PieceColour::w;

    for (int idx=0; idx <64; idx++) {
        this->boardState[idx] = nullptr;
    }

}

void ChessGame::loadState(std::string fen) {
    this->clearBoard();
    std::cout << "A new board state is loaded!\n";
    
    std::vector<std::string> target_strings = splitString(fen, ' ');
    std::string positions = target_strings[0];
    
    const char *turn = target_strings[1].c_str();
    this->toGo = convertColour(turn);

    std::string castlingRights = target_strings[2];

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
                ChessPiece *piece= placePiece(positions[idx]);
                this->boardState[index] = piece;
                if (piece->getPieceType() == PieceType::King) {
                    if (piece->getPieceColour() == PieceColour::b) {
                        this->blackKingPosition = index;
                    } else {
                        this->whiteKingPosition = index;
                    }
                }
                file++;
            } 
            
        }
    this->validBoard = true;

    if (castlingRights == "-")
        return;
    for (char letter : castlingRights) {
        switch(letter) {
            case ('K'):
                if (this->whiteKingPosition != -1) 
                    this->boardState[whiteKingPosition]->setHasMoved(false);
                if (this->boardState[7] != nullptr)    
                    this->boardState[7]->setHasMoved(false);
                break;
            case ('Q'):
                if (this->whiteKingPosition != -1) 
                    this->boardState[whiteKingPosition]->setHasMoved(false);
                if (this->boardState[0] != nullptr)    
                    this->boardState[0]->setHasMoved(false);
                break;
            case ('k'):
                if (this->blackKingPosition != -1) 
                    this->boardState[blackKingPosition]->setHasMoved(false);
                if (this->boardState[63] != nullptr)    
                    this->boardState[63]->setHasMoved(false);
                break;
            case ('q'):
                if (this->blackKingPosition != -1) 
                    this->boardState[blackKingPosition]->setHasMoved(false);
                if (this->boardState[56] != nullptr)    
                    this->boardState[56]->setHasMoved(false);
                break;
            default:
                break;
        }
    }
    return;
}

// Helper function for submitMove 
bool validCoordinates(int index) {
    if (index < 0 || index >= 64)
        return false;
    return true;
}

// Helper function for submitMove
bool ChessGame::validTurn(const int index) const {
    ChessPiece *piece = this->boardState[index];
    if (piece->getPieceColour() == this->toGo) {
        return true;
    }
    std::cout << "It is not " << piece->getPieceColour() << "'s turn to move!\n";
    return false;
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

bool ChessGame::canCapture(const int startIndex, const int endIndex) {
    ChessPiece *movingPiece = this->boardState[startIndex];
    ChessPiece *targetLocation = this->boardState[endIndex];

    if (targetLocation == nullptr) 
        return true;    

    return (movingPiece->getPieceColour() != targetLocation->getPieceColour());
}

bool ChessGame::locationUnderAttack(const int index, const PieceColour colour) const {

    // Knight attackers
    const int knightOffsets[] = {-17, -15, -10, -6, 6, 10, 15, 17};
    int currentFile = index % 8;

    for (int offset : knightOffsets) {
        int target = index + offset;
        if (target >= 0 && target < 64) {
            int targetFile = target % 8;
            if (std::abs(currentFile - targetFile) > 2)
                continue;

            ChessPiece *piece= this->boardState[target];
            if (piece != nullptr) {
                if ((piece->getPieceColour() != colour) &&
                    piece->getPieceType() == PieceType::Knight) 
                    return true;
            }
        }
    }

    // Check Orthogonal Attackers (Rook/Queen)
    const int orthogonalDirections[] = {-8, 8, -1, 1}; // Up, Down, Left, Right
    for (int step : orthogonalDirections) {
        for (int i = index + step; validCoordinates(i); i += step) {
            int prevFile = (i - step) % 8;
            int currFile = i % 8;
            if (std::abs(currFile - prevFile) > 1)
                break; 
            ChessPiece* piece = this->boardState[i];
            if (piece != nullptr) {
                if (piece->getPieceColour() != colour && 
                   (piece->getPieceType() == PieceType::Rook || piece->getPieceType() == PieceType::Queen)) {
                    return true;
                }
                break; 
            }
            
        }
    }

    // Check diagonal attackers (Bishop/Queen)
    const int diagonalDirections[] = {-9, -7, 7, 9};
    for (int step : diagonalDirections) {
        for (int i = index + step; validCoordinates(i); i += step) {
            int prevFile = (i - step) % 8;
            int currFile = i % 8;
            if (std::abs(currFile - prevFile) > 1)
                break;
            ChessPiece* piece = this->boardState[i];
            if (piece != nullptr) {
                if (piece->getPieceColour() != colour && 
                   (piece->getPieceType() == PieceType::Bishop || piece->getPieceType() == PieceType::Queen)) {
                    return true;
                }
                break;
            }
        }
    }

    // Check Pawn attackers
    int attackDirection = (colour == PieceColour::w) ? 1 : -1;
    int diagonalOffsets[2] = {-1, 1};
    for (int offset: diagonalOffsets) {
        int attackerIndex = index + (attackDirection * 8) + offset; 
        
        if (attackerIndex < 0 || attackerIndex >= 64)
            continue;

        int currentFile = index % 8;
        int attackerFile = attackerIndex % 8;
        if (std::abs(currentFile - attackerFile) != 1)
            continue;
        
        ChessPiece *piece = this->boardState[attackerIndex];
        if (piece != nullptr) {
            if (piece->getPieceColour() != colour && 
                piece->getPieceType() == PieceType::Pawn) {
                return true;
            }
        }
    }

    return false;
}

bool ChessGame::kingInCheck(const int kingCoordinates) {
    PieceColour kingColour = this->boardState[kingCoordinates]->getPieceColour();
    
    return this->locationUnderAttack(kingCoordinates, kingColour);
}

// BUG BUG BUG BUG 
bool ChessGame::isMoveSafe(const int startIndex, const int endIndex) {
    ChessPiece* movingPiece = boardState[startIndex];
    ChessPiece* capturedPiece = boardState[endIndex];
    
    int originalKingPos = (movingPiece->getPieceColour() == PieceColour::w) ? whiteKingPosition : blackKingPosition;
    int currentKingPos = originalKingPos;
    
    if (movingPiece->getPieceType() == PieceType::King) {
        currentKingPos = endIndex;
        if (movingPiece->getPieceColour() == PieceColour::w) 
            whiteKingPosition = endIndex;
        else 
            blackKingPosition = endIndex;
    }

    boardState[endIndex] = movingPiece;
    boardState[startIndex] = nullptr;

    bool safe = !kingInCheck(currentKingPos);

    boardState[startIndex] = movingPiece;
    boardState[endIndex] = capturedPiece;
    
    if (movingPiece->getPieceColour() == PieceColour::w) 
        whiteKingPosition = originalKingPos;
    else 
        blackKingPosition = originalKingPos;

    return safe;
}

bool ChessGame::hasLegalMoves(const PieceColour colour) {
    for (int start = 0; start < 64; start++) {
        ChessPiece* piece = this->boardState[start];
        
        if (piece == nullptr || piece->getPieceColour() != colour) 
            continue;

        for (int end = 0; end < 64; end++) {
            if (start == end) 
                continue;
            if (!piece->canMove(start, end)) 
                continue;
            
            if (!noPiecesBetween(start, end, piece)) 
                continue;

            if (this->boardState[end] != nullptr && 
                this->boardState[end]->getPieceColour() == colour) 
                continue;
            if (piece->getPieceType() == PieceType::Pawn) {
                int fileDiff = std::abs((end % 8) - (start % 8));
                bool isDestOccupied = (this->boardState[end] != nullptr);

                if (fileDiff == 0 && isDestOccupied) 
                    continue;
                if (fileDiff > 0 && !isDestOccupied) 
                    continue;
            }
            if (this->isMoveSafe(start, end))
                return true;
        }
    }
    return false;
}

bool ChessGame::isCheckmate(PieceColour colour) {
    int kingPos = (colour == PieceColour::w) ? whiteKingPosition : blackKingPosition;

    if (!this->kingInCheck(kingPos)) 
        return false;
    
    if (hasLegalMoves(colour)) {
        std::cout << colour << " is in check\n";
        return false;
    } else {
        return true;
    };
}

bool ChessGame::isStalemate(PieceColour colour) {
    int kingPos = (colour == PieceColour::w) ? whiteKingPosition : blackKingPosition;

    if (kingInCheck(kingPos)) 
        return false;

    return !hasLegalMoves(colour);
}

bool ChessGame::castlePossible(int startIndex, int endIndex) const {
    ChessPiece* king = boardState[startIndex];
    
    if (king->getPieceType() != PieceType::King) 
        return false;
    if (king->getHasMoved()) 
        return false;

    int rookIdx;
    
    // Determine what sort of castling we are dealing with
    if (startIndex == 4 && endIndex == 6) { 
        rookIdx = 7; // White kingside
    } else if (startIndex == 4 && endIndex == 2) { 
        rookIdx = 0; // White queenside
    } else if (startIndex == 60 && endIndex == 62) { 
        rookIdx = 63; // Black kingside
    } else if (startIndex == 60 && endIndex == 58) { 
        rookIdx = 56; // Black queenside
    } else { 
        return false; 
    } 

    ChessPiece* rook = boardState[rookIdx];
    if (rook == nullptr || 
        rook->getPieceType() != PieceType::Rook || 
        rook->getPieceColour() != king->getPieceColour() || 
        rook->getHasMoved()) {
            return false;
    }

    int direction = (rookIdx > startIndex) ? 1 : -1;
    for (int i = startIndex + direction; i != rookIdx; i += direction) {
        if (boardState[i] != nullptr) 
            return false;
    }

    PieceColour kingCol = king->getPieceColour();
    
    if (locationUnderAttack(startIndex, kingCol)) 
        return false;

    int step = (endIndex > startIndex) ? 1 : -1;
    if (locationUnderAttack(startIndex + step, kingCol)) 
        return false; 
    if (locationUnderAttack(endIndex, kingCol)) 
        return false;          

    return true;
}

bool ChessGame::validMove(const int startIndex, const int endIndex) {
    // Exclude invalid coordinates
    if (!validCoordinates(startIndex) || !validCoordinates(endIndex)) {
        std::cout << "Invalid coordinates entered\n";
        return false;
    }
    
    ChessPiece *piece = this->boardState[startIndex];
    if (piece == nullptr) {
        std::cout << "There is no piece at position " << recoverFile(startIndex) << recoverRank(startIndex) << "!\n";
        return false;
        }
    if (!validTurn(startIndex))
        return false;
    if (!this->noPiecesBetween(startIndex, endIndex, piece)) {
        std::cout << piece->getPieceColour() << "'s "<< piece->getPieceType() << " cannot move to " 
                  << recoverFile(endIndex) << recoverRank(endIndex) << "\n";
        return false;
        }
    
    // Check for special moves
    bool isCastling = (piece->getPieceType() == PieceType::King && std::abs(endIndex - startIndex) == 2);
    if (isCastling) {
        return this->castlePossible(startIndex, endIndex);
    }

    // Pawns are our other special case because movement != capturing 
    if (piece->getPieceType() == PieceType::Pawn) {
        // Since we aren't implementing en passant a piece can move either diagonally to capture or straight 
        // This means that to move diagonally it needs an occupied destination 
        int fileDiff = std::abs((endIndex % 8) - (startIndex % 8));
        
        // If we aren't changing file, we can't capture a piece 
        if (fileDiff == 0) {
            if (this->boardState[endIndex] != nullptr) {
                return false;
            }
        }

        if (fileDiff > 0) {
            if (this->boardState[endIndex] == nullptr || 
                this->boardState[endIndex]->getPieceColour() == piece->getPieceColour()) {
                return false;
                }
            }
        }

    // If we aren't doing any special moves we check if the piece can move like we want it to
    if (!piece->canMove(startIndex, endIndex)) {
        std::cout << piece->getPieceColour() << "'s " << piece->getPieceType() 
                  << " cannot move to " << recoverFile(endIndex) << recoverRank(endIndex) << "!\n";
        return false;
        }
    
    if (!canCapture(startIndex, endIndex)) {
        std::cout << "Cannot capture own piece\n";
        return false;
    }

    return true;
}

void ChessGame::commitMove(const int startIndex, const int endIndex) {
    ChessPiece *movingPiece = boardState[startIndex];
    ChessPiece *targetSquare = boardState[endIndex];

    // Castling logic - cannot castle and capture at the same time
    if (movingPiece->getPieceType() == PieceType::King &&
         std::abs(endIndex - startIndex) == 2) {    
            int rookStartIdx, rookEndIdx;        
            if (endIndex > startIndex) { 
                rookStartIdx = startIndex + 3;
                rookEndIdx = startIndex + 1;  
            } else { 
                rookStartIdx = startIndex - 4; 
                rookEndIdx = startIndex - 1;
                }
            if (boardState[rookStartIdx] != nullptr) {
                boardState[rookEndIdx] = boardState[rookStartIdx];
                boardState[rookStartIdx] = nullptr;
                boardState[rookEndIdx]->setHasMoved(true);
                }
            if (this->toGo == PieceColour::w) {
                this->whiteKingPosition = endIndex;
            } else {
                this->blackKingPosition = endIndex;
            }
            std::cout << this->toGo << "has castled!\n"; 
            return;
            }
    
    // Moving without castling 
    std::cout << this->toGo << "'s " << movingPiece->getPieceType() 
            << " moves from " << recoverFile(startIndex) << recoverRank(startIndex)
            << " to " << recoverFile(endIndex) << recoverRank(endIndex);
    
    if (targetSquare != nullptr) {
        std::cout << " taking " << targetSquare->getPieceColour() << "'s " << targetSquare->getPieceType();
        delete targetSquare;
        } 

    if (movingPiece->getPieceType() == PieceType::King) {
        if (this->toGo == PieceColour::w) {
            this->whiteKingPosition = endIndex;
        } else {
            this->blackKingPosition = endIndex;
            }
        }

    std::cout << "\n";
    boardState[endIndex] = movingPiece;
    boardState[startIndex] = nullptr;
    movingPiece->setHasMoved(true);
}

void ChessGame::submitMove(const char *start_position, const char *end_position) {
    int startIndex = flattenCoordinates(start_position);
    int endIndex = flattenCoordinates(end_position);

    // Validate 
    if (!this->validBoard) {
        std::cout << "Invalid Board arrangement\n";
        return;
    }
    if (!this->validMove(startIndex, endIndex)) {
        return; 
    }
    // Simulate 
    if (!this->isMoveSafe(startIndex, endIndex)){
        return;
    }
    
    // Commit movement 
    this->commitMove(startIndex, endIndex);

    //this->printBoard();
    PieceColour opponent = this->toGo == PieceColour::w ? PieceColour::b : PieceColour::w;    
    if (this->isCheckmate(opponent)){
        std::cout << opponent << " is in checkmate\n";
        return;
        }
    if (this->isStalemate(opponent)){
        std::cout << "Stalemate\n";
        return;
        }
    this->toGo = opponent;    
    return;
};