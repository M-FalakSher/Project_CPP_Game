#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <iomanip>
#include <limits>

using namespace std;

int gridSize = 2;
const int maxGridSize = 10;
int grid[10][10];
string correctPassword = "0000";
string playerName;
int padding = (80 - playerName.length() - 6) / 2;
int moveCount = 0;
clock_t startTime, endTime;

void initializeGrid();
void displayGrid();
void findEmptySpace(int &x, int &y);
bool isSolved();
void moveBlock(char direction);
bool validatePassword();
void changePassword();
void getPlayerName();
void selectLevel();
void startTimer();
void endTimer();
void showElapsedTime();

int main() {
    cout << string(padding, ' ') <<"Welcome to The World of Asendix Enigma!" << endl;
    getPlayerName();

    if (!validatePassword()) {
        return 0;
    }

    char choice;
    cout<<"Please choose an Option \n 1)Play Game\n2)Change Password"<<endl;
    cin>>choice;
    if(choice == '2'){
        changePassword();
        cout << "Please enter the new password to continue: "<<endl;
        if (!validatePassword()) {
            return 0;
        }
    }

    selectLevel();

    while (gridSize <= maxGridSize) {
        initializeGrid();
        moveCount = 0;
        startTimer();

        while (true) {
            displayGrid();
            cout << playerName << ",Use Arrow Keys for movement of numbers \n Use # to exit: ";
            char move = _getch();
            if (move == '#') {
                cout << "Exiting the game..." << endl;
                return 0;
            }
            moveBlock(move);
            moveCount++;

            if (isSolved()) {
                endTimer();
                displayGrid();
                showElapsedTime();
                cout << "Congratulations, " << playerName << "! You solved the " << gridSize << "x" << gridSize << " puzzle in " << moveCount << " moves!" << endl;
                gridSize++;
                break;
            }
        }

        if (gridSize > maxGridSize) {
            cout << "You've completed all levels, " << playerName << "! Well Done!" << endl;
            break;
        }
    }
    return 0;
}

void initializeGrid() {
    int numbers[maxGridSize * maxGridSize];
    for (int i = 0; i < gridSize * gridSize; i++) {
        numbers[i] = i;
    }

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < gridSize * gridSize; i++) {
        int j = rand() % (gridSize * gridSize);
        swap(numbers[i], numbers[j]);
    }

    int index = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = numbers[index++];
        }
    }
}

void displayGrid() {
    system("cls");
    cout << "Player: " << playerName << " | Level: " << gridSize << "x" << gridSize << " | Moves: " << moveCount << endl;
    cout << "------------------------------------" << endl;
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            cout << "| ";
            if (grid[i][j] == 0)
                cout << "   ";
            else
                 cout << setw(2) << grid[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "------------------------------------" << endl;
}

void findEmptySpace(int &x, int &y) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
               x = i;
               y = j;
               return;
            }
        }
    }
}

bool isSolved() {
    int correctNumber = 1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] != correctNumber % (gridSize * gridSize)) {
                return false;
            }
            correctNumber++;
        }
    }
    return true;
}

void moveBlock(char direction) {
    int x, y;
    findEmptySpace(x, y);

    switch (direction) {
        case 80:
            if (x > 0) {
                swap(grid[x][y], grid[x - 1][y]);
            } else {
                Beep(500, 200);
            }
            break;
        case 72:
            if (x < gridSize - 1) {
                swap(grid[x][y], grid[x + 1][y]);
            } else {
                Beep(500, 200);
            }
            break;
        case 77:
            if (y > 0) {
                swap(grid[x][y], grid[x][y - 1]);
            } else {
                Beep(500, 200);
            }
            break;
        case 75:
            if (y < gridSize - 1) {
                swap(grid[x][y], grid[x][y + 1]);
            } else {
                Beep(500, 200);
            }
            break;
        default:
            break;
    }
}

bool validatePassword() {
    string inputPassword;
    while (true) {
      cout <<"Hey, "<<playerName << "! \n Please enter the password to access the game: "<<endl;
        cin >> inputPassword;
        if (inputPassword == correctPassword) {
            return true;
        } else {
            cout << "Incorrect password. Please try again." << endl;
        }
    }
}

void changePassword() {
    string newPassword;
    cout << "Enter a New Password: ";
    cin >> newPassword;
    correctPassword = newPassword;
    cout << "Password Changed Successfully!" << endl;
}

void getPlayerName() {
    cout << "Enter your name: ";
    getline(cin, playerName);
}

void selectLevel() {
    int level;
    while (true) {
        cout << "Select level (2 to " << maxGridSize << "): ";
        cin >> level;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 2 and " << maxGridSize << "." << endl;
        } else if (level >= 2 && level <= maxGridSize) {
            gridSize = level;
            break;
        } else {
            cout << "Invalid level. Please select a level between 2 and " << maxGridSize << "." << endl;
        }
    }
}

void startTimer() {
    startTime = clock();
}

void endTimer() {
    endTime = clock();
}

void showElapsedTime() {
    double elapsed = double(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Time taken: " << elapsed << " Seconds" <<setprecision(8)<< endl;
}