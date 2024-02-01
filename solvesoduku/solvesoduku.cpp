// solvesoduku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

const char BASEBOARD[9][9] = {
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
};

void show(vector<vector<char>> board)
{
	cout << "************start************" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}

	cout << "************end*************" << endl;
}


const char Patton[9] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9'
};


class Solve
{
public:
	Solve()
	{
	}

	~Solve()
	{

	}

	void solveSudoku(vector<vector<char>>& board) {
		int i, j, m;

		if (isPass(board))
		{
			//show(board);
			return;
		}

		//vector<vector<int>> flag(81, vector<int>(9));
		vector<int>flag(9);
		//while (1)
		//{
			//show(board);

			fill(board, i, j);

			int t = 0;
			for (m = 0; m < 9; m++)
			{
				if (Check(board, i, j, Patton[m]))
				{
					flag[t++] = m;
				}
			}

			if (t == 0)
			{
				//cout << "t = 0 ---> i = " << i << " j=" << j<<endl;
				//show(board);
				return;
			}

			for (int x = 0; x < t; x++)
			{

				if (isPass(board))
				{
				//	show(board);
					return;
				}

				vector<vector<char>> current_board(board);

				board[i][j] = Patton[flag[x]];
				
				solveSudoku(board);

				if (isPass(board))
				{
					//cout << "Pass...>>>>>>>>>.........." << endl;
					//show(board);
					return;
				}

				board.swap(current_board);
			}
		//}


	}

	bool Check(vector<vector<char>>& board, int i, int j, char s)
	{
		int n;
		for (n = 0; n < 9; n++)
		{
			if (n == j) continue;
			if (board[i][n] == s)
			{
				return false;
			}
		}

		for (n = 0; n < 9; n++)
		{
			if (n == i) continue;
			if (board[n][j] == s)
			{
				return false;
			}
		}


		int nCellx = (int)(i / 3);
		int nCelly = (int)(j / 3);
		int m;
		for (n = nCellx * 3; n < nCellx * 3 + 3; n++)
		{
			for (m = nCelly * 3; m < nCelly * 3 + 3; m++)
			{
				if ((n != i) && (m != j) && (board[n][m] == s))
				{
					return false;
				}
			}
		}

		return true;
	}

	bool isPass(vector<vector<char>>& board)
	{
		//show(board);
		int i, j;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (board[i][j] == '.') return false;
			}
		}

		return true;
	}
	//寻找在同一行，同一列中可填数字量最少的一个位置，提高回溯效率
	void fill(vector<vector<char>>& board, int& row, int& col)
	{
		int count, nMax = -1;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == '.')
				{
					int n;
					count = 0;
					for (n = 0; n < 9; n++)
					{
						//同一行中的已知个数
						if (board[i][n] != '.')
						{
							count++;
						}
						//同一列中的已知个数
						if ((board[n][j] != '.') && (n != i))
						{
							count++;
						}
					}
					//同一个3*3网格中的已知个数
					int nCellx = (int)(i / 3);
					int nCelly = (int)(j / 3);
					int m;
					for (n = nCellx * 3; n < nCellx * 3 + 3; n++)
					{
						for (m = nCelly * 3; m < nCelly * 3 + 3; m++)
						{
							if ((n != i) && (m != j) && (board[n][m] != '.'))
							{
								count++;
							}
						}
					}
					if (nMax < count)
					{
						//count最大意味着这个位置可填的数字最少
						nMax = count;
						row = i;
						col = j;
					}
				}
			}

		}
	}

};

int main()
{
	vector<vector<char>> TestBoard(9, vector<char>(9));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			TestBoard[i][j] = BASEBOARD[i][j];
		}
	}


	show(TestBoard);
	Solve solve;

	//int row, col;
	//solve.fill(TestBoard, row, col);

	solve.solveSudoku(TestBoard);
	show(TestBoard);
	
	int b;
	cin >> b;
	return 0;
}

