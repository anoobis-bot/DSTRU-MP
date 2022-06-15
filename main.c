#define  true 1
#define false 0

#include <stdio.h>

#define WIDTH 5
#define HEIGHT 7

#define CLEAR "\e[1;1H\e[2J"

typedef int bool;

void NextPlayerMove(bool *ok, bool *aTurn, int prev, int next, char P[HEIGHT][WIDTH], int *numA, int *numB)
{
	
	int a, b, c, d;
	
	a = prev % 10;
	b = prev / 10;
	c = next % 10;
	d = next / 10;

	if  ((*aTurn) && P[a - 1][b - 1] == 'A' && a == c + 1 && ( d == b || d == b + 1 || b == d + 1))
		(*ok) = !(*ok);
	else if (!(*aTurn) && P[a - 1][b - 1] == 'B' && c== a + 1 && ( d == b || d == b + 1 || b == d + 1))
		(*ok) = !(*ok);
	
	if ((*ok) && (*aTurn) && P[c - 1][d - 1] == 'F')
	{
		P[a - 1][b - 1] = 'F';
		P[c - 1][d - 1] = 'A';
		(*aTurn) = !(*aTurn);
		(*ok) = !(*ok);
	}
	else if ((*ok) && !(*aTurn) && P[c - 1][d - 1] == 'F')
	{
		P[a - 1][b - 1] = 'F';
		P[c - 1][d - 1] = 'B';
		(*aTurn) = !(*aTurn);
		(*ok) = !(*ok);
	}
	
	if ((*ok) && (*aTurn) && P[c - 1][d - 1] == 'B' && !(c % 2 == d % 2))
		(*ok) = !(*ok);
	else if ((*ok) && (*aTurn) && P[c - 1][d - 1] == 'B' && (c % 2 == d % 2))
	{
		P[c - 1][d - 1] = 'F';
		P[a - 1][b - 1] = 'F';
		P[c - 1][d - 1] = 'A';
		(*aTurn) = !(*aTurn);
		(*ok) = !(*ok);

		(*numB)--;
	}

	if ((*ok) && !(*aTurn) && P[c - 1][d - 1] == 'A' && !(c % 2 == d % 2))
		(*ok) = !(*ok);
	else if ((*ok) && !(*aTurn) && P[c - 1][d - 1] == 'A' && (c % 2 == d % 2))
	{
		P[c - 1][d - 1] = 'F';
		P[a - 1][b - 1] = 'F';
		P[c - 1][d - 1] = 'B';
		(*aTurn) = !(*aTurn);
		(*ok) = !(*ok);

		(*numA)--;
	}
}

// bool GameOver (char P[HEIGHT][WIDTH], int numA, int numB)
// {
// 	int i, j;
// 	bool zero = false;

// 	// |Beta| = 0
// 	for (i = 0; i < 5; i++)
// 		for (j = 0; j < 7 && !zero; j++)
// 			if (P[i][j] == 'B')
// 				zero = true;
// 	if (zero)
// 	{
// 		printf("Alpha Wins");
// 		return true;
// 	}

// 	// |Alpha| = 0
// 	zero = false;
// 	for (i = 0; i < 5; i++)
// 		for (j = 0; j < 7 && !zero; j++)
// 			if (P[i][j] == 'A')
// 				zero = true;
// 	if (zero)
// 	{
// 		printf("Beta Wins");
// 		return true;
// 	}
	
// 	// Alpha   |Alpha- Y| = 0
// 	zero = true;
// 	for (i = 0; i < 5; i++)
// 		for (j = 0; j < 7 && zero; j++)
// 			if (P[i][j] == 'A' && !((i % 2 == j % 2) && i >= 2))
// 			zero = false;
// 	if (zero)
// 	{
// 		printf("Alpha Wins");
// 		return true;
// 	}

// 	// Beta   |Beta- E| = 0
// 	zero = true;
// 	for (i = 0; i < 5; i++)
// 		for (j = 0; j < 7 && zero; j++)
// 			if (P[i][j] == 'A' && !((i % 2 == j % 2) && i <= 6))
// 			zero = false;
// 	if (zero)
// 	{
// 		printf("Beta Wins");
// 		return true;
// 	}

// 	return false;
// }

bool GameOver(char P[HEIGHT][WIDTH], int numA, int numB)
{
	int nCurrHeight;
	int nCurrWidth;

	bool winA = false;
	bool winB = false;

	if (numA == 0)
	{
		printf(CLEAR);
		printf("Beta Wins!");
		return true;
	}
	else if (numB == 0)
	{
		printf(CLEAR);
		printf("Alpha wins!");
		return true;
	}
	else
	{
		for (nCurrHeight = 0; nCurrHeight < 2; nCurrHeight++)
		{
			for (nCurrWidth = nCurrHeight % 2; nCurrWidth < WIDTH; nCurrWidth += 2)
			{
				if (P[nCurrHeight][nCurrWidth] == 'A')
					numA--;
			}
		}

		if (numA > 0)
		{
			for (nCurrHeight = 5; nCurrHeight < 7; nCurrHeight++)
			{
				for (nCurrWidth = nCurrHeight % 2; nCurrWidth < WIDTH; nCurrWidth += 2)
				{
					if (P[nCurrHeight][nCurrWidth] == 'B')
						numB--;
				}
			}
			if (numB <= 0)
			{
				printf(CLEAR);
				printf("Beta wins!");
				winB = true;
			}
		}
		else
		{
			printf(CLEAR);
			printf("Alpha wins!");
			winA = true;
		}
	}

	return (winA || winB);
}

void Display (char P[HEIGHT][WIDTH])
{
	int nCurrWidth;
	int nCurrHeight;

	// numbers at top
	for (nCurrWidth = 0 ; nCurrWidth < (WIDTH * 2) + 1; nCurrWidth++)
	{
		if (nCurrWidth % 2 != 0)
		{
			printf("%d", ((nCurrWidth - 1) / 2) + 1);
		}
		else
			printf(" ");
	}

	printf("\n");

	for (nCurrHeight = 0 ; nCurrHeight < (HEIGHT * 2) + 1; nCurrHeight++)
	{

		for (nCurrWidth = 0; nCurrWidth < (WIDTH * 2) + 1; nCurrWidth++)
		{
			if (nCurrWidth % 2 == 0)
			{
				if (nCurrHeight % 2 == 0)
				{
					printf(" ");
				}
				else
				{
					printf("|");

					if (nCurrWidth == (WIDTH * 2))
						printf(" %d", ((nCurrHeight - 1) / 2) + 1);
				}
			}

			else
			{
				if (nCurrHeight % 2 == 0)
				{
					printf("%c", 196);  
				}
				else
				{
					if (P[(nCurrHeight - 1) / 2][(nCurrWidth - 1) / 2] == 'F')
						printf(" ");

					else
					{
						printf("%c", P[(nCurrHeight - 1) / 2][(nCurrWidth - 1) / 2]);
					}
				}
			}
		}
		
		printf("\n");
	}
	
}

int main () 
{
	bool over = false;
	bool aTurn = true;
	bool ok = false;
	
	int numA = 5;
	int numB = 5;


	char P[HEIGHT][WIDTH] = 
	{
		{'B', 'F', 'B', 'F', 'B'},
		{'F', 'B', 'F', 'B', 'F'},
		{'F', 'F', 'F', 'F', 'F'},
		{'F', 'F', 'F', 'F', 'F'},
		{'F', 'F', 'F', 'F', 'F'},
		{'F', 'A', 'F', 'A', 'F'},
		{'A', 'F', 'A', 'F', 'A'}
	};
	int prev;
	int next;
	
	while (!over)
	{
		printf(CLEAR);

		Display(P);

		printf("\n");

		if (aTurn)
			printf("Alpha's Turn\n");
		else
			printf ("Beta's Turn\n");

		printf("\n\n");
	
		printf("Please enter prev: ");
		scanf(" %i", &prev);
		printf("Please enter next: ");
		scanf(" %i", &next);
		
		NextPlayerMove(&ok, &aTurn, prev, next, P, &numA, &numB);

		over = GameOver(P, numA, numB);

		if (over)
		{
			printf("\n\n");
			Display(P);
		}
	}
	
	

	return 0;
}
