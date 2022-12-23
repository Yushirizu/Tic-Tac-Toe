#include <iostream>
#include <cstring>  // for strcmp()
#include <cstdlib>


const int ROWS = 3;
const int COLS = 3;

char board[ROWS][COLS] = {};  // Initialize all cells to be empty
int moves = 0;  // Keep track of the number of moves

void clearScreen() {
    // Clear the screen
    std::cout << "\033[2J\033[1;1H";
}

bool isValidMove(char rowLabel, char colLabel) {
    // Check if the row label is a valid number (1, 2, or 3)
    if (rowLabel < '1' || rowLabel > '3') {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }

    // Check if the column label is a valid letter ('A', 'B', or 'C')
    if (colLabel != 'A' && colLabel != 'B' && colLabel != 'C' && colLabel != 'a' && colLabel != 'b' && colLabel != 'c') {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }

    // Convert the row and column labels to indices (0, 1, or 2)
    int rowIndex = rowLabel - '1';
    int colIndex = -1;
    if (colLabel == 'A' || colLabel == 'a') {
        colIndex = 0;
    }
    else if (colLabel == 'B' || colLabel == 'b') {
        colIndex = 1;
    }
    else if (colLabel == 'C' || colLabel == 'c') {
        colIndex = 2;
    }

    // Check if the cell is empty
    if (board[rowIndex][colIndex] != '\0') {
        std::cout << "That cell is already occupied. Please try again." << std::endl;
        return false;
    }

    // If the row and column labels are within the valid range and the cell is empty, return true
    return true;
}

void updateBoard(int row, int col, char player) {
    board[row][col] = player;  // Update the game board with the player's move
    moves++;  // Increment the number of moves
}

bool checkForWin(char player) {
    // Check for three in a row horizontally
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    // Check for three in a row vertically
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // Check for three in a row diagonally
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    // If none of the above conditions are met, return false
    return false;
}

bool checkForDraw() {
    // Check if all cells are filled
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == '\0') {  // '\0' represents an empty cell
                return false;
            }
        }
    }

    // If all cells are filled and no winner, return true
    std::cout << "The game has ended in a draw." << std::endl;
    return true;
    system("pause");
}

int main() {
    clearScreen();  // Clear the screen before the game starts
    system("pause");
    bool gameOver = false;
    char player = 'X';  // Start with X
    const int MAX_INVALID_MOVES = 8;  // Maximum number of invalid moves allowed
    int invalidMoveCounter = 0;  // Keep track of the number of invalid moves
    while (!gameOver) {
        // Print the game board
        std::cout << "  A B C" << std::endl;
        for (int i = 0; i < ROWS; i++) {
            std::cout << i + 1 << " ";
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == '\0') {  // '\0' represents an empty cell
                    std::cout << "  ";
                }
                else {
                    std::cout << board[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        // Prompt the player for a move
        std::cout << "Player " << player << ", enter your move (row column): ";
        char rowLabel;
        char colLabel;
        std::cin >> rowLabel >> colLabel;

        // Validate the player's move
        if (isValidMove(rowLabel, colLabel)) {
            // Convert the row and column labels to indices (0, 1, or 2)
            int rowIndex = rowLabel - '1';
            int colIndex = -1;
            if (colLabel == 'A' || colLabel == 'a') {
                colIndex = 0;
            }
            else if (colLabel == 'B' || colLabel == 'b') {
                colIndex = 1;
            }
            else if (colLabel == 'C' || colLabel == 'c') {
                colIndex = 2;
            }

            // Update the game board with the player's move
            updateBoard(rowIndex, colIndex, player);

            // Check if the player has won
            if (checkForWin(player)) {
                std::cout << "Player " << player << " has won!" << std::endl;
                gameOver = true;
                break;
                system("pause");
            }

            // Check if the game has ended in a draw
            if (checkForDraw()) {
                gameOver = true;
                break;
            }

            // Switch to the other player
            if (player == 'X') {
                player = 'O';
            }
            else {
                player = 'X';
            }

            // Reset the invalid move counter
            invalidMoveCounter = 0;
        }
        else {
            // Increment the invalid move counter
            invalidMoveCounter++;
            if (invalidMoveCounter == MAX_INVALID_MOVES) {
                // If the maximum number of invalid moves has been reached, end the game
                std::cout << "Too many invalid moves. The game has ended." << std::endl;
                gameOver = true;
                break;
                system("pause");
            }
        }
    }

    return 0;
}
