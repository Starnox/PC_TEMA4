#include "utils.h"

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = (char *)calloc(MAX_LEN_STR_ATR, sizeof(char));
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
	char *board = calloc(MAX_LEN_STR_OUT, sizeof(char)), buffer[MAX_LEN_STR_LOC];

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
	char string[MAX_LEN_STR_LOC], *buffer = calloc(MAX_LEN_STR_LOC, sizeof(char));

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

void Swap(int *a, int *b)
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
	char *res = (char *) malloc(MAX_LEN_STR_LOC * sizeof(char)), 
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
			Swap(v+i, v+i+1);
		}
	}
	else
	{
		for(i = 1; i <= n / 2; ++i)
		{
			Swap(v+i, v + n - i + 1);
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


void SelectRole(Player *player,char *playerRole)
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
	Player *myPlayer = (Player *) calloc(1, sizeof(Player));
	if(myPlayer == NULL)
		return NULL;
	myPlayer->name = (char *)malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->color = (char *)malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->hat = (char *)malloc(MAX_LEN_STR_ATR * sizeof(char));
	myPlayer->alive = 1;
	return myPlayer;
}

//Task 4
Game *allocGame()
{
	Game *myGame = (Game *) calloc(1, sizeof(Game));
	if(myGame == NULL)
		return NULL;
	myGame->name = (char *) malloc(MAX_LEN_STR_ATR * sizeof(char));
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

	fscanf(inputFile,"%s\n",playerName);
	fscanf(inputFile,"%s\n",color);
	fscanf(inputFile,"%s\n",hat);
	fscanf(inputFile,"%d\n",&numOfLocations);

	strcpy(myPlayer->name,playerName);
	strcpy(myPlayer->color,color);
	strcpy(myPlayer->hat,hat);
	myPlayer->numberOfLocations = numOfLocations;
	myPlayer->locations = (Location *) calloc (myPlayer->numberOfLocations, sizeof(Location *));

	for(i = 0; i < numOfLocations; ++i)
	{
		if(i != numOfLocations - 1)
			fscanf(inputFile,"(%d,%d) ",&myPlayer->locations[i].x,&myPlayer->locations[i].y);
		else
			fscanf(inputFile,"(%d,%d)",&myPlayer->locations[i].x,&myPlayer->locations[i].y);
	}
	fscanf(inputFile,"%s",playerRole);
	SelectRole(myPlayer, playerRole);

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

	myGame->crewmates = (Player **) calloc(numCrewmates, sizeof(Player *));

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
	char *playerRoleString = fromEnumtoString(player->playerRole);
	fprintf(outputFile,"Player %s with color %s, hat %s and role %s has entered the game.\n",player->name,
		player->color,player->hat,playerRoleString);

	free(playerRoleString);
	fprintf(outputFile,"Player's locations: ");
	for(int i = 0; i < player->numberOfLocations; ++i)
	{
		fprintf(outputFile,"(%d,%d) ",player->locations[i].x, player->locations[i].y);
	}
	fprintf(outputFile,"\n");
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	fprintf(outputFile,"Game %s has just started!\n",game->name);
	fprintf(outputFile,"\tGame options:\n");
	fprintf(outputFile,"Kill Range: %d\n",game->killRange);
	fprintf(outputFile,"Number of crewmates: %d\n\n",game->numberOfCrewmates);
	fprintf(outputFile,"\tCrewmates:\n");

	for(int i = 0; i< game->numberOfCrewmates; ++i)
	{
		WritePlayer(game->crewmates[i],outputFile);
	}
	fprintf(outputFile,"\n");
	fprintf(outputFile,"\tImpostor:\n");
	WritePlayer(game->impostor,outputFile);
	return;
}

int CalculateDistance(Player *player, Player *impostor)
{
	int playerX = player->locations[player->indexOfLocation].x,
		playerY = player->locations[player->indexOfLocation].y,
		impostorX = impostor->locations[impostor->indexOfLocation].x,
		impostorY = impostor->locations[impostor->indexOfLocation].y;

	return (abs(playerX - impostorX) + abs(playerY - impostorY));
}


//Task 7
void *KillPlayer(void *input)
{
	Game *myGame = (Game *) input;
	int i, minDistance = -1, newDistance, killedSomeone = 0;
	Player *selectedPlayer = NULL;

	// Go through each of the crewmates
	for(i = 0; i < myGame->numberOfCrewmates; ++i)
	{
		newDistance = CalculateDistance(myGame->crewmates[i], myGame->impostor);
		if(myGame->crewmates[i]->alive == 1 && minDistance == -1 && newDistance <= myGame->killRange){
			minDistance = newDistance;
			selectedPlayer = myGame->crewmates[i];
			killedSomeone = 1;
		}
		else
		{
			if(myGame->crewmates[i]->alive == 1 && newDistance <= minDistance 
					&& newDistance <= myGame->killRange)
			{
				minDistance = newDistance;
				selectedPlayer = myGame->crewmates[i];
			}
		}
	}

	char *result = (char *) malloc(MAX_LEN_STR_OUT * sizeof(char));
	if(result == NULL)
		return NULL;
	// If no player is in range
	if(minDistance == -1 || killedSomeone == 0)
		sprintf(result,"Impostor %s couldn't kill anybody.", myGame->impostor->name);
	else
	{
		selectedPlayer->alive = 0;
		sprintf(result,"Impostor %s has just killed crewmate %s from distance %d.",
			myGame->impostor->name, selectedPlayer->name, minDistance);
	}

	return ((void *) result);
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	int i, n = game->numberOfCrewmates;
	Player *currentPlayer;
	for(i = 0; i < n; ++i)
	{
		currentPlayer = game->crewmates[i];
		// If the player is alive
		if(currentPlayer->alive == 1)
		{
			// Update the location
			currentPlayer->indexOfLocation = (currentPlayer->indexOfLocation + 1)
				% currentPlayer->numberOfLocations;
			
			fprintf(outputFile,"Crewmate %s went to location (%d,%d).\n",currentPlayer->name,
					currentPlayer->locations[currentPlayer->indexOfLocation].x,
					currentPlayer->locations[currentPlayer->indexOfLocation].y);

			fprintf(outputFile,"Crewmate %s's output:\n",currentPlayer->name);
			char *abilityString = (char *) currentPlayer->ability(inputMatrix[i]);
			fprintf(outputFile, "%s\n", abilityString);
			free(abilityString);
		}
		else
		{
			//Player [nume_jucator] is dead.[\n]
			fprintf(outputFile,"Crewmate %s is dead.\n",currentPlayer->name);
		}
		
	}
	// For the impostor
	Player *impostor = game->impostor;
	impostor->indexOfLocation = (impostor->indexOfLocation + 1)
				% impostor->numberOfLocations;
	fprintf(outputFile,"Impostor %s went to location (%d,%d).\n",impostor->name,
					impostor->locations[impostor->indexOfLocation].x,
					impostor->locations[impostor->indexOfLocation].y);
	fprintf(outputFile,"Impostor %s's output:\n",impostor->name);
	char *killPlayerString = (char *) KillPlayer((void *) game);
	fprintf(outputFile,"%s\n", killPlayerString);
	free(killPlayerString);
	return;
}

// Task 9
void FreePlayer(Player *player)
{
	free(player->locations);

	free(player->hat);
	free(player->color);
	free(player->name);
	
	free(player);
	return;
}

// Task 9
void FreeGame(Game *game)
{
	int i;
	
	FreePlayer(game->impostor);
	
	for(i = 0; i < game->numberOfCrewmates; ++i)
	{
		FreePlayer(game->crewmates[i]);
	}
	free(game->crewmates);
	free(game->name);
	free(game);
	return;
}