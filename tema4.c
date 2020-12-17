#include "utils.h"

#define LENGHT 1000
#define BOARD_SIZE 50005

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	// Declaring and initialising
	int i, j, n = *((int *) input);
	char *board = malloc(BOARD_SIZE * sizeof(char)), buffer[LENGHT];

	// verifying
	if(board == NULL)
	{
		return NULL;
	}
	strcpy(board,"");
	printf("%d",n);

	for(i = 1; i <= n; ++i)
	{
		for(j = 1; j <= n; ++j)
		{
			sprintf(buffer,"%d%d",(n-j+1), (i));
			strcat(board,buffer);
			if(j != n)
			{
				strcat(board," ");
			}
		}
		if(i!= n)
			strcat(board,"\n");
	}

	return ((void *) board);
}

// Task 2
void *DecodeString(void *input)
{
	char string[LENGHT], *buffer = malloc(LENGHT * sizeof(char));

	if(buffer == NULL)
	{
		return NULL;
	}

	// convert into char*
	strcpy(string, (char *) input);

	// use strtok to split the string into numbers
	char *ptr = strtok(string, "_");
	int sum = 0, num;

	while(ptr != NULL)
	{
		num = atoi((const char *) ptr);
		sum += num;
		ptr = strtok(NULL,"_");
	}
	sprintf(buffer,"%d",sum);

	return ((void *) buffer);
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

//Task 3
void *InvertArray(void *input)
{
	// convert from void* to int*
	int *v = (int *) input, i = 1;
	char *res = malloc(LENGHT * sizeof(char)), buffer[LENGHT];
	if(res == NULL)
	{
		return NULL;
	}
	strcpy(res,"");

	int n = *v;
	// if it is even
	if(n % 2 == 0)
	{
		for(i = 1; i < n; i+=2)
		{
			// swap elements (2k+1,2k+2);
			swap(v+i, v+i+1);
		}
	}
	else
	{
		for(i = 1; i <= n / 2; ++i)
		{
			swap(v+i, v + n - i + 1);
		}
	}
	for(i = 1; i <= n; ++i)
	{
		sprintf(buffer,"%d",*(v+i));
		strcat(res,buffer);
		if(i != n)
			strcat(res, " ");
	}
	
	return ((void *) res);
}

//Task 4
Player *allocPlayer()
{
	// TODO
	return NULL;
}

//Task 4
Game *allocGame()
{
	// TODO
	return NULL;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	// TODO
	return NULL;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	// TODO
	return NULL;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	// TODO
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	// TODO
	return;
}

//Task 7
void *KillPlayer(void *input)
{
	// TODO
	return NULL;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	// TODO
	return;
}

// Task 9
void FreePlayer(Player *player)
{
	// TODO
	return;
}

// Task 9
void FreeGame(Game *game)
{
	// TODO
	return;
}