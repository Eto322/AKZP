import java.util.*;

public class Main {
	public static void sort(int m, int n, int [][]array)
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

    public static void out(int m, int n, int [][]array)
    { 
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                {System.out.print(array[i][j]+ " ");}
            System.out.print("\n");
        }
    }

    public static void main(String[] args)
    {
        int array[][] = {
		{5, 2, 3, 4, 5},
		{5, 2, 3, 4, 5},
		{5, 2, 3, 4, 5}};

	sort(3, 5, array);
	out(3, 5, array);
    
    }
}