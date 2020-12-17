#include "utils.h"

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
	// TODO
	return NULL;
}

// Task 2
void *DecodeString(void *input)
{
	// TODO
	return NULL;
}

//Task 3
void *InvertArray(void *input)
{
	// TODO
	return NULL;
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