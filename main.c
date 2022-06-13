#define  true 1
#define false 0

#include <stdio.h>

typedef int bool;

void NextPlayerMove (bool ok, bool aTurn, int prev, int next, char P[][7])
{
	int a, b, c, d;
	
	a = prev / 10;
	b = prev % 10;
	c = next / 10;
	d = next  % 10;

	if  (aTurn && P[a - 1][b - 1] == ‘A’ && a == c + 1 && ( d == b || d == b + 1 || b == d + 1))
		ok = !ok;
	else if (!aTurn && P[a - 1][b - 1] == ‘B’ && c== a + 1 && ( d == b || d == b + 1 || b == d + 1))
		ok = !ok;
	if (ok && aTurn && P[c - 1][d - 1] == ‘F’)
	{
		P[a - 1][b - 1] = ‘F’;
		P[c - 1][d - 1] = ‘A’;
		aTurn = !aTurn;
		ok = !ok;
	}
	else if (ok && !aTurn && P[c - 1][d - 1] == ‘F’)
	{
		P[a - 1][b - 1] = ‘F’;
		P[c - 1][d - 1] = ‘B’;
		aTurn = !aTurn;
		ok = !ok;
	}
	if (ok && aTurn && P[c - 1][d - 1] == ‘B’ && !(c % 2 == d % 2))
		ok = !ok;
	else if (ok && aTurn && P[c - 1][d - 1] == ‘B’ && (c % 2 == d % 2))
	{
		P[c - 1][d - 1] = ‘F’;
		P[a - 1][b - 1] = ‘F’;
		P[c - 1][d - 1] = ‘A’;
		aTurn = !aTurn;
		ok = !ok;
	}
	if (ok && !aTurn && P[c - 1][d - 1] == ‘A’ && !(c % 2 == d % 2))
		ok = !ok;
	else if (ok && aTurn && P[c - 1][d - 1] == ‘B’ && (c % 2 == d % 2))
	{
		P[c - 1][d - 1] = ‘F’;
		P[a - 1][b - 1] = ‘F’;
		P[c - 1][d - 1] = ‘B’;
		aTurn = !aTurn;
		ok = !ok;
	}
}

bool GameOver (bool over, char P[][7])
{
	int i, j;
	bool zero = false;

	// |Beta| = 0
	for (i = 0; i < 5; i++)
		for (j = 0; j < 7 && !zero; j++)
			if (P[i][j] == ‘B’)
				zero = true;
	if (zero)
	{
		printf(“Alpha Wins”);
		return true;
	}

	// |Alpha| = 0
	zero = false;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 7 && !zero; j++)
			if (P[i][j] == ‘A’)
				zero = true;
	if (zero)
	{
		printf(“Beta Wins”);
		return true;
	}
	
	// Alpha   |Alpha- Y| = 0
	zero = true;
for (i = 0; i < 5; i++)
		for (j = 0; j < 7 && zero; j++)
			if (P[i][j] == ‘A’ && !((i % 2 == j % 2) && i >= 2))
			zero = false;
	if (zero)
	{
		printf(“Alpha Wins”);
		return true;
	}

	// Beta   |Beta- E| = 0
	zero = true;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 7 && zero; j++)
			if (P[i][j] == ‘A’ && !((i % 2 == j % 2) && i <= 6))
			zero = false;
	if (zero)
	{
		printf(“Beta Wins”);
		return true;
	}

	return false;
}

void Display (char P[][7])
{
	int i;
	int line = 196;
	for(i = 0; i < 20; i ++)
		printf(“%c”, line);
	printf(“\n”);
printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][0], P[1][0], P[2][0], P[3][0], P[4][0]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][1], P[1][1], P[2][1], P[3][1], P[4][1]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][2], P[1][2], P[2][2], P[3][2], P[4][2]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][3], P[1][3], P[2][3], P[3][3], P[4][3]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][4], P[1][4], P[2][4], P[3][4], P[4][4]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][5], P[1][5], P[2][5], P[3][5], P[4][5]);
	printf(“|  %c  |  %c  |  %c  |  %c  |  %c  |\n”, P[0][6], P[1][6], P[2][6], P[3][6], P[4][6]);
	for(i = 0; i < 20; i ++)
		printf(“%c”, line);
	printf(“\n”);
}
int main () {

bool over = false;
bool ok = false;
bool aTurn = true;
char P[5][7] = {{‘B’, ‘F’, ‘B’, ‘F’, ‘B’},
  {‘F’, ‘B’, ‘F’, ‘B’, ‘F’},
  {‘F’, ‘F’, ‘F’, ‘F’, ‘F’},
  {‘F’, ‘F’, ‘F’, ‘F’, ‘F’},
  {‘F’, ‘F’, ‘F’, ‘F’, ‘F’},
  {‘F’, ‘A’, ‘F’, ‘A’, ‘F’},
  {‘A’, ‘F’, ‘A’, ‘F’, ‘A’}};
	int prev;
	int next;
	
	printf(“Please enter prev.”);
	scanf(“ %i”, &prev);
	printf(“Please enter next.”);
	scanf(“ %i”, &next);


}
