#include <stdio.h>

void sort(int m, int n, int array[m][n])
{
	int j;
	for (int row = 0; row < m; row++)
	{
		for (int column = 2; column < n; column++)
		{
			array[row][0] = array[row][column];
			j = column;
			while (array[row][0] > array[row][j - 1])
			{
				array[row][j] = array[row][j - 1];
				j = j - 1;
			}
			array[row][j] = array[row][0];
		}
	}
}

void out(int m, int n, int array[m][n])
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", array[i][j]);
		puts("");
	}
}

int main()
{
	int array[4][5] = {
		{5, 2, 3, 4, 5},
		{5, 2, 3, 4, 5},
		{5, 2, 3, 4, 5},
		{5, 2, 3, 4, 5}};

	sort(4, 5, array);
	out(4, 5, array);

	return 0;
}
