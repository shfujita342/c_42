#include <stdbool.h>

bool	search_board(char **board, int row, int col, char *word, int i, int j,
		int index)
{
	char	temp;
	bool	ok;

	if (word[index] == '\0')
		return (true);
	if (i < 0 || i >= row || j < 0 || j >= col || board[i][j] != word[index])
		return (false);
	ok = false;
	temp = board[i][j];
	board[i][j] = '\0';
	if (search_board(board, row, col, word, i + 1, j, index + 1)
		|| search_board(board, row, col, word, i - 1, j, index + 1)
		|| search_board(board, row, col, word, i, j + 1, index + 1)
		|| search_board(board, row, col, word, i, j - 1, index + 1))
		ok = true;
	board[i][j] = temp;
	return (ok);
}

bool	exist(char **board, int boardSize, int *boardColSize, char *word)
{
	int	row;
	int	col;

	row = boardSize;
	col = *boardColSize;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (search_board(board, row, col, word, i, j, 0))
			{
				return (true);
			}
		}
	}
	return (false);
}
