/*
 ============================================================================
 Name        : new_and_last.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Pokemon.h"
#include "Defs.h"

int main(int argv, char* argc[])

{


	FILE *file = fopen(argc[3], "r");
	int i, j, k, index1 = 0, size_types = atoi(argc[1]), size_pokemones = atoi(argc[2]), index2 = 0,  *counters, num = 0,counter7=0,counter8=0;
	const char psik[5] = ",", space[2] = " ", comma[2] = ":", slash[5] = "\r\n";
	char ch[SIZE], *token, *type, *against,   Type[SIZE], Name[SIZE];


	char *name ;
	char *species,*kind;
	char *H , *W;
	char *A;
	type_of_pokemon *types[atoi(argc[1])];
	Pokemon *pokes[atoi(argc[2])];

	if (file == NULL)
	{
		printf("File not found, please check it\n");
		return -1;
	}
	fgets(ch, SIZE, file);
	fgets(ch, SIZE, file);
	ch[strlen(ch) - 2] = '\0';
	token = strtok(ch, psik);
	while (token != NULL)
	{
		types[index1++] = func2_create_type(token);
		token = strtok(NULL, psik);
	}
	while (fgets(ch, SIZE, file) != NULL)
	{
		if (strcmp(ch, "Pokemons\r\n") == 0)
		{
			while (fgets(ch, SIZE, file) != NULL)
			{
				//token = strtok(ch, comma);


				token = strtok(ch, psik);
				int i;
				for (i = 0; i < 6; i++)
				{
					if (i == 0)
					{
						name = token;

					}
					if (i == 1)
					{
						species = token;
					}

					if (i == 2)
					{
						H = (token);

					}
					if (i == 3)
					{
						W = token;
					}
					if (i == 4)
					{
						A = token;

					}
					if (i == 5)
					{

						token = strtok(token, slash);
						kind = token;

						token = strtok(NULL, slash);
					}

					token = strtok(NULL, psik);
				}
				pokes[index2] = func1_create_pokemon(name, species, atof(H), atof(W), atoi(A), kind);
				index2 += 1;
				//token = strtok(NULL, comma);
			}
		}
		else
		{
			type = strtok(ch, space);
			int size = strlen(type);
			for (int i = 1; i <= size; i++)
				type[i - 1] = type[i];
			token = strtok(NULL, space);

			against = strtok(token, comma);

			token = strtok(NULL, comma);
			token = strtok(token, psik);
			while (token != NULL)
			{

				if (token[strlen(token) - 1] == '\n')
				{


					token[strlen(token) - 2] = '\0';

				}

				int i, j;

				for (i = 0; i < size_types; i++)
				{
					if (strcmp(type, types[i]->kind) == 0)

						break;
				}
				for (j = 0; j < size_types; j++)
				{
					if (strcmp(token, types[j]->kind) == 0)
						break;
				}
				if (strcmp(against, "effective-against-me") == 0)
					func4_add_type_against_me(types[i], types[j]);
				else
					func5_add_type_against_others(types[i], types[j]);


				token = strtok(NULL, psik);

		}



		}
	}



	counters = (int*)malloc(index1 * sizeof(int));
		for (i = 0; i < size_types; i++)
			counters[i] = 0;
		for (i = 0; i < size_types; i++)
		{
			for (j = 0; j < size_pokemones; j++)
				if (strcmp(types[i]->kind, pokes[j]->type->kind) == 0)
					counters[i]++;
			types[i]->number = counters[i];
		}


		while (num != 9)
			{
				printf("Please choose one of the following numbers:\n");
				printf("1 : Print all Pokemons\n");
				printf("2 : Print all Pokemons types\n");
				printf("3 : Add type to effective against me list\n");
				printf("4 : Add type to effective against others list\n");
				printf("5 : Remove type from effective against me list\n");
				printf("6 : Remove type from effective against others list\n");
				printf("7 : Print Pokemon by name\n");
				printf("8 : Print Pokemons by type\n");
				printf("9 : Exit\n");
				scanf("%s", &ch);
				num = atoi(ch);
				switch (num)
				{
				case 1:
					for (int i = 0; i < size_pokemones; i++)
						func8_print_pokemon(pokes[i]);
					break;
				case 2:
					for (int k = 0; k < size_types; k++)
						func9_print_type(types[k]);
					break;
				case 3:
					printf("Please enter type name:\n");
					scanf("%s", Type);
					for (j = 0; j < size_types; j++)
						if (strcmp(Type, types[j]->kind) == 0)
							break;
					if (j != size_types)
					{
						printf("Please enter type name to add to %s effective against me list:\n", types[j]->kind);
						scanf("%s", Type);
						for (i = 0; i < size_types; i++)
							if (strcmp(Type, types[i]->kind) == 0)
								break;
						if (i == size_types)
							printf("Type name doesn't exist.\n");
						else
						{
							for (k = 0; k < types[j]->against_me; k++)
								if (strcmp(Type, types[j]->effective_against_me[k]->kind) == 0)
									break;
							if (k == types[j]->against_me)
							{
								func4_add_type_against_me(types[j], types[i]);
								func9_print_type(types[j]);
							}
							else
								printf("This type already exist in the list.\n");
						}
					}
					else
						printf("Type name doesn't exist.\n");
					break;
				case 4:
					printf("Please enter type name:\n");
					scanf("%s", Type);
					for (j = 0; j < size_types; j++)
						if (strcmp(Type, types[j]->kind) == 0)
							break;
					if (j != size_types)
					{
						printf("Please enter type name to add to %s effective against others list:\n", types[j]->kind);
						scanf("%s", Type);
						for (i = 0; i < size_types; i++)
							if (strcmp(Type, types[i]->kind) == 0)
								break;
						if (i == size_types)
							printf("Type name doesn't exist.\n");
						else
						{
							for (k = 0; k < types[j]->against_others; k++)
								if (strcmp(Type, types[j]->effective_against_others[k]->kind) == 0)
									break;
							if (k == types[j]->against_others)
							{
								func5_add_type_against_others(types[j], types[i]);
								func9_print_type(types[j]);
							}
							else
								printf("This type already exist in the list.\n");
						}
					}
					else
						printf("Type name doesn't exist.\n");
					break;
				case 5:
					printf("Please enter type name:\n");
					scanf("%s", Type);
					for (j = 0; j < size_types; j++)
						if (strcmp(Type, types[j]->kind) == 0)
							break;
					if (j != size_types)
					{
						printf("Please enter type name to remove from %s effective against me list:\n", types[j]->kind);
						scanf("%s", Type);
						for (i = 0; i < size_types; i++)
							if (strcmp(Type, types[i]->kind) == 0)
								break;
						if (i == size_types)
							printf("Type name doesn't exist in the list.\n");
						else
						{
							for (k = 0; k < types[j]->against_me; k++)
								if (strcmp(Type, types[j]->effective_against_me[k]->kind) == 0)
									break;
							if (k != types[j]->against_me)
							{
								func6_remove_type_agains_me(types[j], Type);
								func9_print_type(types[j]);
							}
							else
								printf("Type name doesn't exist in the list.\n");
						}
					}
					else
						printf("Type name doesn't exist.\n");
					break;
				case 6:
					printf("Please enter type name:\n");
					scanf("%s", Type);
					for (j = 0; j < size_types; j++)
						if (strcmp(Type, types[j]->kind) == 0)
							break;
					if (j != size_types)
					{
						printf("Please enter type name to remove from %s effective against others list:\n", types[j]->kind);
						scanf("%s", Type);
						for (i = 0; i < size_types; i++)
							if (strcmp(Type, types[i]->kind) == 0)
								break;
						if (i == size_types)
							printf("Type name doesn't exist in the list.\n");
						else
						{
							for (k = 0; k < types[j]->against_others; k++)
								if (strcmp(Type, types[j]->effective_against_others[k]->kind) == 0)
									break;
							if (k != types[j]->against_others)
							{
								func7_remove_type_agains_others(types[j], Type);
								func9_print_type(types[j]);
							}
							else
								printf("This type already exist in the list.\n");
						}
					}
					else
						printf("Type name doesn't exist.\n");
					break;
				case 7:
					printf("Please enter Pokemon name:\n");
					scanf("%s", Name);
					for (i = 0; i < size_pokemones; i++)
						if (strcmp(Name, pokes[i]->name) == 0)
						{
							func8_print_pokemon(pokes[i]);
							break;
						}
					if (i == size_pokemones)
						printf("The Pokemon doesn't exist.\n");
					break;
				case 8:
					counter7 = 0;
					counter8=0;

					printf("Please enter type name:\n");
					scanf("%s", Name);
					for(int i=0;i<size_types;i++)
					{
						if (strcmp(Name, types[i]->kind) == 0)
						{
							counter8 += 1;
						}

					}
					for (int k = 0; k < size_pokemones; k++)
						if (strcmp(Name, pokes[k]->type->kind) == 0)
						{
							counter7 += 1;
						}
					if(counter7 !=0)
					{
						printf("There are %d Pokemons with this type:\n",counter7);
						for (int k = 0; k < size_pokemones; k++)
						if (strcmp(Name, pokes[k]->type->kind) == 0)
						{
							func8_print_pokemon(pokes[k]);
						}

					}
					if (counter8==0 && counter7 == 0)
						printf("Type name doesn't exist.\n");
					if (counter8 != 0 && counter7==0)
						printf("There are no Pokemons with this type.\n");
					break;
		case 9:

					for (k = 0; k < size_types; k++)
					{
						free(types[k]->effective_against_me);
						free(types[k]->effective_against_others);
					}
					for (k = 0; k < size_types; k++)
					{
						free(types[k]->kind);
						free(types[k]);
					}

					for (i = 0; i <size_pokemones; i++)
					{
						free(pokes[i]->species);
						free(pokes[i]->name);
						free(pokes[i]->bio);
						free(pokes[i]->type->kind);
						free(pokes[i]->type);
						free(pokes[i]);
					}

					free(counters);
					fclose(file);
					printf("All the memory cleaned and the program is safely closed.\n");
					break;
				default:
					printf("Please choose a valid number.\n");
					break;
				}
			}
			return 0;
		}
