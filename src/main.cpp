#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class GameBoard
{
private:
	char game_board[3][3];
	int MAX_TRIES = 9;
	int counter = 0;
	bool game_underway = false;
	string board;
	map<string, vector<int>> Locations;
	vector<string> LocationIDs = {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"};
	vector<string> LocationUsed;

public:

	GameBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				game_board[i][j] = '_';
			}
		}
		InitializeLocationMap();
		DisplayGameBoard();
	}

	void PlayGame(char symbol = 'X')
	{
		game_underway = true;
		cout << "Player " << symbol << endl;
		UpdateLocation(symbol);
		if (CheckResult() == 0)
		{
			if (counter + 1 == MAX_TRIES)
				cout << "No Winner" << endl;
			else
			{
				counter++;
				symbol = (symbol == 'X') ? 'O' : 'X';
				PlayGame(symbol);
			}
		}
		else
		{
			cout << "We have a winner" << endl;
			cout << "Congratulations, Player " << symbol << '!' << endl;
		}
	}

private:

	void InitializeLocationMap() 
	{
		vector<vector<int>> coordinates;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				coordinates.push_back({ i, j });
			}
		}
		for (int i = 0; i < 9; i++)
		{
			Locations.insert({ LocationIDs[i], coordinates[i] });
		}
	}

	string GenerateGameBoard()
	{
		board = "";
		board += "  | 1 | 2 | 3\n--------------\n";
		for (int i = 0; i < 3; i++)
		{
			char row = (i == 0) ? 'A' : (i == 1) ? 'B' : 'C';
			board += row;
			board += " | ";
			for (int j = 0; j < 3; j++)
			{
				board += game_board[i][j];
				if (j < 2)
				{
					board += " | ";
				}
			}
			board += '\n';
			if (i < 2)
			{
				board += "--------------\n";
			}
		}
		return board;
	}

	void DisplayGameBoard()
	{
		cout << GenerateGameBoard() << endl;
		if (game_underway)
			cin.get();
	}

	string AskUserLocation()
	{
		string loc;
		cout << "Please select location: ";
		cin >> loc;
		return loc;
	}

	void UpdateLocation(char val)
	{
		string loc = AskUserLocation();
		loc = VerifyInput(loc);
		if (loc == "0")
		{
			cout << endl;
			cout << "Incorrect input. Player misses a turn." << endl;
			cout << endl;
		}
		else
		{
			LocationUsed.push_back(loc);
			int x = Locations[loc][0];
			int y = Locations[loc][1];
			game_board[x][y] = val;
			DisplayGameBoard();
			cout << endl;
		}
	}

	int CompareRows(int x)
	{
		if ((game_board[x][0] == game_board[x][1]) && (game_board[x][1] == game_board[x][2]))
			if ((game_board[x][0] == 'X') || (game_board[x][0] == 'O'))
				return 1;
			else
				return 0;
		else
			return 0;
	}

	int CompareColumns(int y)
	{
		if ((game_board[0][y] == game_board[1][y]) && (game_board[1][y] == game_board[2][y]))
			if ((game_board[0][y] == 'X') || (game_board[0][y] == 'O'))
				return 1;
			else
				return 0;
		else
			return 0;
	}

	int CompareDiagonals()
	{
		if ((game_board[0][0] == game_board[1][1]) && (game_board[1][1] == game_board[2][2]))
			if ((game_board[0][0] == 'X') || (game_board[0][0] == 'O'))
				return 1;
			else
				return 0;
		else if ((game_board[0][2] == game_board[1][1]) && (game_board[1][1] == game_board[2][0]))
				if ((game_board[0][2] == 'X') || (game_board[0][2] == 'O'))
					return 1;
				else
					return 0;
		else
			return 0;
	}

	int CheckResult()
	{
		for (int i = 0; i < 3; i++)
		{
			if ((CompareRows(i) == 1) || (CompareColumns(i) == 1))
				return 1;
		}
		if (CompareDiagonals() == 1)
			return 1;
		return 0;
	}

	string VerifyInput(string loc)
	{
		transform(loc.begin(), loc.end(), loc.begin(), ::toupper);
		if (find(LocationIDs.begin(), LocationIDs.end(), loc) != LocationIDs.end())
		{
			if (find(LocationUsed.begin(), LocationUsed.end(), loc) == LocationUsed.end())
				return loc;
			else
				return "0";
		}
		else
			return "0";
	}
};

int main()
{
	GameBoard game;
	cout << "Press Enter to begin..." << endl;
	cin.get();
	game.PlayGame();
	cout << "Press Enter to exit...";
	cin.get();
}