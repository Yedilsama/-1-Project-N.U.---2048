#include<iostream>
#include<windows.h>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<stdio.h>
using namespace std;
int score = 0;
int board[4][4];
int dirRow[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};
pair<int, int>generateUnocupiedPosition() {
	int occupied = 1;
	int row;
	int column;
	while (occupied) {
		row = rand() % 4;
		column = rand() % 4;
		if (board[row][column] == 0) {
			occupied = 0;
		}
	}
	return make_pair(row, column);
}
void addPiece() {
	pair<int, int>pos = generateUnocupiedPosition();
	board[pos.first][pos.second] = 2;
}
void newGame() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}
	addPiece();
}

void printUI() {
	system("cls");
	cout << endl << "           Score:" << score << endl << "┌──────┬──────┬──────┬──────┐" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "│";
			if (board[i][j] == 0) {
				cout << setw(6) << " ";
			}
			else {
				cout << setw(6) << board[i][j];
			}
		}
		cout << "│" << endl << ((i==3)?"└──────┴──────┴──────┴──────┘":"├──────┼──────┼──────┼──────┤") << endl;
	}
	cout << "\n Control Keys:\n  [N] - New Game \n  [W] - Up  \n  [D] - Right \n  [A] - Left \n  [Q] - Quit \n";
}
bool moveActive(int row, int column, int nextRow, int nextColumn) {
	if (nextRow < 0 || nextColumn < 0 || nextRow >= 4 || nextColumn >= 4 || (board[row][column] != board[nextRow][nextColumn] && board[nextRow][nextColumn] != 0)) {
		return false;
	}
	return true;
}

void applyMove(int direction) {
	int startRow = 0;
	int startColumn = 0;
	int rowStep = 1;
	int columnStep = 1;
	if (direction == 0) {
		startRow = 3;
		rowStep = -1;
	}
	if (direction == 1) {
		startColumn = 3;
		columnStep = -1;
	}
	int movePossible;
	int addPieceActive = 0;
	int crash = 0;
	do {
		crash++;
		movePossible = 0;
		for (int i = startRow; i >= 0 && i < 4; i += rowStep) {
			for (int j = startColumn; j >= 0 && j < 4; j += columnStep) {
				int nextI = i + dirRow[direction];
				int nextJ = j + dirColumn[direction];
				if (board[i][j] && moveActive(i, j, nextI, nextJ)) {
					score += board[nextI][nextJ]+board[nextI][nextJ];
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					movePossible = addPieceActive = 1;
					break;
				}
			}
		}
	} while (movePossible);
	if (addPieceActive) {
		addPiece();
	}
}
bool checkContinue() {
	int count = 0;
	bool isFull = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				isFull = false;
			}
			if (board[i][j] == 2048) {
				printUI();
				system("cls");
				cout << endl << endl << endl << endl << endl
					<< "      __            _______ _   __" << endl
					<< "      \\ \\          / /_   _| \\ |  |" << endl
					<< "       \\ \\   / \\  / /  | | |  \\|  |" << endl
					<< "        \\ \\ /   \\/ /   | | |  .`  |" << endl
					<< "         \\   / \\  /   _| |_|  |\\  |" << endl
					<< "          \\ /   \\/   |_____| _| \\_|" << endl;
				cout << "                          [press any button to exit]";
				char c = _getch();
				return false;
			}

		}
	}
	bool lose = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (((j == 3 && (board[i][j] == board[i][j - 1])) || (j == 0 && (board[i][j] == board[i][j + 1])) || (j > 0 && j < 3 && (board[i][j] == board[i][j + 1] || board[i][j] == board[i][j - 1])))
				|| ((i == 3 && (board[i][j] == board[i - 1][j])) || (i == 0 && (board[i][j] == board[i + 1][j])) || (i > 0 && i < 3 && (board[i][j] == board[i + 1][j] || board[i][j] == board[i - 1][j])))) {
				lose = false;
				break;
			}
		}
	}
	if (isFull&&lose) {
		printUI();
		system("cls");
		cout << endl << endl << endl << endl << endl
			<< "       _      ____" << endl
			<< "      | |    / __ \\" << endl
			<< "      | |   | |  | |___  ___" << endl
			<< "      | |   | |  | / __|/ _ \\" << endl
			<< "      | |___| |__ |\\__ \\  __/" << endl
			<< "      |______\\____/|___/\\___|" << endl;
		cout << "                          [press any button to exit]";
		char c = _getch();
		return false;
	}
	return true;
}
void introLogo() {
	cout << "     .        *         .                       .       " << endl
		<< " .                            .            .                       " << endl
		<< "            .                                            .           .    *  " << endl
		<< "                  ,               .                                  " << endl
		<< "                                   .          *               .      " << endl
		<< "          .                .   _   _   _   _   _   _       .         " << endl
		<< "  .                   *       / \\ / \\ / \\ / \\ / \\ / \\             ." << endl
		<< "         .              .    ( E | N | I | G | M | A )            *         ,   " << endl
		<< " .            *               \\_/ \\_/ \\_/ \\_/ \\_/ \\_/          .          . " << endl << endl
		<< "       ,                  .        *                .          ." << endl
		<< "                                          .                       .        .  " << endl
		<< "          .             *                               .                 *" << endl
		<< "                                             .                   . " << endl
		<< "  .                .                 .                     .               .      .   " << endl;
}
void introState() {
	introLogo();
	for (long long i = 0; i < 9960000000; i += 10) {
		if (i % 10000000 == 0) {
			cout << "█";
		}
	}
	system("cls");
	introLogo();
	cout 
<<"            _____  _                      ___     __   _ _    ___ "<<endl
<<"           |_   _|| |_     ___     o O O |_  )   /  \\ | | |  ( _ )  "<<endl
<<"             | |  | ' \\   / -_)   o       / /   | () ||_ _|  / _ \\  "<<endl 
<<"            _|_|_ |_||_|  \\___|  TS__[O] /___|  _\\__/  _|_|_ \\___/  "<<endl
<<"          _|^^^^^_|^^^^^_|^^^^^|{======_|^^^^^_|^^^^^_|^^^^^_|^^^^^|"<<endl 
<<"          `-0-0-^`-0-0-^`-0-0-./o--000^`-0-0-^`-0-0-^`-0-0-^`-0-0-./"<<endl<<endl<<endl;
	cout << "                               The game is ready"<<endl<<"                             Press any button to START"<<endl;
}
int main() {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 700, 500, TRUE);
	system("color 1f");
	//                                      osi zherge gruppalastatindi i ozndi  https://patorjk.com/software/taag/#p=display&f=Bubble&t=%0A
	introState();
	char c = _getch();
	srand((int)time(0));
	system("color 8f");	
	MoveWindow(console, r.left, r.top, 500, 400, TRUE);
	char commandToDir[128];
	commandToDir['s'] = 0; 
	commandToDir['d'] = 1; 
	commandToDir['w'] = 2; 
	commandToDir['a'] = 3; 
	while (checkContinue()) {
		printUI();
		char command = _getch();
		if (command == 'n' || command == 'N') {
			score=0;
			newGame();
		}
		else if (command == 'q' || command == 'Q' || command == 27) {
			break;
		}
		else {
			int currentDirection = commandToDir[command];
			//cout << currentDirection << endl;
			applyMove(currentDirection);
		}
	}
	return 0;
}
