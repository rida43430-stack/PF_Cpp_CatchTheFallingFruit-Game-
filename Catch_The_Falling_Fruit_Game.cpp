#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

const int ROWS = 15;
const int COLUMNS = 50;
const int FRUITS = 15;
const int BOMBS = 8;

struct positionType {
    int row;
    int col;
};

struct scoreType {
    int player1;
    int player2;
};

void gotoXY(int x, int y);
void hideCursor();
void instructions();
void clearGrid(char grid[][COLUMNS]);
void displayGrid(char grid[][COLUMNS], scoreType score);
void movePlayers(char key, int &player1, int &player2);
void moveFruits(positionType fruits[], scoreType &score, int player1, int player2);
void moveBombs(positionType bombs[], scoreType &score, int player1, int player2);
void placeObjects(char grid[][COLUMNS], positionType fruits[], positionType bombs[], int player1, int player2);
void showWinner(scoreType score);

int main() {
    srand(time(0));

    char grid[ROWS][COLUMNS];
    positionType fruits[FRUITS];
    positionType bombs[BOMBS];
    scoreType score = {0, 0};

    int player1 = 10;
    int player2 = 38;
    char key;
    int turns = 0;

    instructions();

    for (int i = 0; i < FRUITS; i++) {
        fruits[i].row = rand() % (ROWS - 3);
        fruits[i].col = rand() % COLUMNS;
    }

    for (int i = 0; i < BOMBS; i++) {
        bombs[i].row = rand() % (ROWS - 3);
        bombs[i].col = rand() % COLUMNS;
    }

    hideCursor();
    system("cls");

    while (turns < 250) {
        if (_kbhit()) {
            key = _getch();

            if (key == 'q' || key == 'Q') {
                break;
            }

            movePlayers(key, player1, player2);
        }

        moveFruits(fruits, score, player1, player2);
        moveBombs(bombs, score, player1, player2);

        clearGrid(grid);
        placeObjects(grid, fruits, bombs, player1, player2);

        gotoXY(0, 0);
        displayGrid(grid, score);

        Sleep(350);
        turns++;
    }

    system("cls");
    cout << "==============================================\n";
    cout << "                 GAME OVER\n";
    cout << "==============================================\n\n";
    cout << "Player 1 Score: " << score.player1 << endl;
    cout << "Player 2 Score: " << score.player2 << endl << endl;
    showWinner(score);

    return 0;
}

void gotoXY(int x, int y) {
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void instructions() {
    cout << "==============================================\n";
    cout << "          CATCH THE FALLING FRUITS\n";
    cout << "==============================================\n\n";
    cout << "Player 1 Basket: <=>\n";
    cout << "Controls: A = Left, D = Right\n\n";
    cout << "Player 2 Basket: [=]\n";
    cout << "Controls: J = Left, L = Right\n\n";
    cout << "Fruit = O  gives +1 score\n";
    cout << "Bomb  = X  gives -1 score\n\n";
    cout << "Press Q to quit the game.\n";
    cout << "Press any key to start...";
    _getch();
}

void clearGrid(char grid[][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            grid[i][j] = ' ';
        }
    }
}

void displayGrid(char grid[][COLUMNS], scoreType score) {
    cout << "=============== CATCH THE FRUITS ===============\n";
    cout << "Player 1: " << score.player1 << "        Player 2: " << score.player2;
    cout << "        Q: Quit\n";
    cout << "+";

    for (int i = 0; i < COLUMNS; i++) {
        cout << "-";
    }

    cout << "+\n";

    for (int i = 0; i < ROWS; i++) {
        cout << "|";

        for (int j = 0; j < COLUMNS; j++) {
            cout << grid[i][j];
        }

        cout << "|\n";
    }

    cout << "+";

    for (int i = 0; i < COLUMNS; i++) {
        cout << "-";
    }

    cout << "+\n";
    cout << "P1: A/D                 P2: J/L\n";
}

void movePlayers(char key, int &player1, int &player2) {
    if (key == 'a' || key == 'A') {
        player1--;
    }

    if (key == 'd' || key == 'D') {
        player1++;
    }

    if (key == 'j' || key == 'J') {
        player2--;
    }

    if (key == 'l' || key == 'L') {
        player2++;
    }

    if (player1 < 0) {
        player1 = 0;
    }

    if (player1 > COLUMNS - 3) {
        player1 = COLUMNS - 3;
    }

    if (player2 < 0) {
        player2 = 0;
    }

    if (player2 > COLUMNS - 3) {
        player2 = COLUMNS - 3;
    }
}

void moveFruits(positionType fruits[], scoreType &score, int player1, int player2) {
    for (int i = 0; i < FRUITS; i++) {
        fruits[i].row++;

        if (fruits[i].row == ROWS - 1) {
            if (fruits[i].col >= player1 && fruits[i].col <= player1 + 2) {
                score.player1++;
            }

            if (fruits[i].col >= player2 && fruits[i].col <= player2 + 2) {
                score.player2++;
            }

            fruits[i].row = 0;
            fruits[i].col = rand() % COLUMNS;
        }
    }
}

void moveBombs(positionType bombs[], scoreType &score, int player1, int player2) {
    for (int i = 0; i < BOMBS; i++) {
        bombs[i].row++;

        if (bombs[i].row == ROWS - 1) {
            if (bombs[i].col >= player1 && bombs[i].col <= player1 + 2) {
                score.player1--;
            }

            if (bombs[i].col >= player2 && bombs[i].col <= player2 + 2) {
                score.player2--;
            }

            bombs[i].row = 0;
            bombs[i].col = rand() % COLUMNS;
        }
    }
}

void placeObjects(char grid[][COLUMNS], positionType fruits[], positionType bombs[], int player1, int player2) {
    for (int i = 0; i < FRUITS; i++) {
        grid[fruits[i].row][fruits[i].col] = 'O';
    }

    for (int i = 0; i < BOMBS; i++) {
        grid[bombs[i].row][bombs[i].col] = 'X';
    }

    grid[ROWS - 1][player1] = '<';
    grid[ROWS - 1][player1 + 1] = '=';
    grid[ROWS - 1][player1 + 2] = '>';

    grid[ROWS - 1][player2] = '[';
    grid[ROWS - 1][player2 + 1] = '=';
    grid[ROWS - 1][player2 + 2] = ']';
}

void showWinner(scoreType score) {
    if (score.player1 > score.player2) {
        cout << "Player 1 Won!\n";
    } else if (score.player2 > score.player1) {
        cout << "Player 2 Won!\n";
    } else {
        cout << "It is a Draw!\n";
    }

    cout << "==============================================\n";
}

