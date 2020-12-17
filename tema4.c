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
	// Declaring and initialising
	int i, j, n = *((int *) input);
	char *board = malloc(MAX_LEN_STR_OUT * sizeof(char)), buffer[MAX_LEN_STR_LOC];

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
	char string[MAX_LEN_STR_LOC], *buffer = malloc(MAX_LEN_STR_LOC * sizeof(char));

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
	char *res = malloc(MAX_LEN_STR_LOC * sizeof(char)), 
			buffer[MAX_LEN_STR_LOC];
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


void selectRole(Player *player,char *playerRole)
{	
	if(strcmp(playerRole,"Rotator") == 0){
		player->playerRole = Rotator;
		player->ability = RotateMatrix;
	}
	else if(strcmp(playerRole,"Decoder") == 0)
	{
		player->playerRole = Decoder;
		player->ability = DecodeString;
	}
	else if(strcmp(playerRole,"Invertor") == 0)
	{
		player->playerRole = Invertor;
		player->ability = InvertArray;
	}
	else
	{
		player->playerRole = Impostor;
		player->ability = KillPlayer;
	}
	
}

//Task 4
Player *allocPlayer()
{
	Player *myPlayer = malloc(sizeof(Player));
	if(myPlayer == NULL)
		return NULL;
	myPlayer->name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->color = malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->hat = malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->alive = 1;
	return myPlayer;
}

//Task 4
Game *allocGame()
{
	Game *myGame = malloc(sizeof(myGame));
	if(myGame == NULL)
		return NULL;
	myGame->name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	return myGame;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	Player *myPlayer = allocPlayer();
	if(myPlayer == NULL)
	{
		return NULL;
	}

	char playerName[MAX_LEN_STR_ATR], color[MAX_LEN_STR_ATR],
		hat[MAX_LEN_STR_ATR], playerRole[MAX_LEN_STR_ATR];

	int numOfLocations, i;
	Location myLocation;
	
	fscanf(inputFile,"%s\n",playerName);
	fscanf(inputFile,"%s\n",color);
	fscanf(inputFile,"%s\n",hat);
	fscanf(inputFile,"%d\n",&numOfLocations);

	strcpy(myPlayer->name,playerName);
	strcpy(myPlayer->color,color);
	strcpy(myPlayer->hat,hat);
	myPlayer->numberOfLocations = numOfLocations;
	myPlayer->locations = malloc(numOfLocations * sizeof(Location));

	for(i = 0; i < numOfLocations; ++i)
	{
		if(i != numOfLocations - 1)
			fscanf(inputFile,"(%d,%d) ",&myLocation.x,&myLocation.y);
		else
			fscanf(inputFile,"(%d,%d)",&myLocation.x,&myLocation.y);
		myPlayer->locations[i] = myLocation;
	}
	fscanf(inputFile,"%s",playerRole);
	selectRole(myPlayer, playerRole);

	return myPlayer;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	char gameName[MAX_LEN_STR_ATR];
	int killRange, numCrewmates, i; 

	fscanf(inputFile,"%s\n",gameName);
	fscanf(inputFile,"%d\n",&killRange);
	fscanf(inputFile,"%d\n",&numCrewmates);

	Game *myGame = allocGame();
	strcpy(myGame->name,gameName);
	myGame->killRange = killRange;
	myGame->numberOfCrewmates = numCrewmates;

	myGame->crewmates = malloc(numCrewmates * sizeof(Player));

	for(i = 0; i < numCrewmates; ++i)
	{
		Player *newPlayer = ReadPlayer(inputFile);
		myGame->crewmates[i] = newPlayer;
	}

	Player *newImpostor = ReadPlayer(inputFile);
	myGame->impostor = newImpostor;
	
	return myGame;
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