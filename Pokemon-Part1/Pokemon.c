/*
 * Pokemon.c
 *
 *  Created on: Nov 26, 2021
 *      Author: ise
 */

#include "Pokemon.h"
#include "Defs.h"
//#pragma GCC diagnostic ignored "-Wunused-variable"

Pokemon* func1_create_pokemon(char *name, char *species, float H, float W, int A, char *kind)
{
	Pokemon *P = (Pokemon*)malloc(sizeof(Pokemon));
	P->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(P->name, name);
	P->species = (char*)malloc((strlen(species) + 1) * sizeof(char));
	strcpy(P->species, species);
	P->type = func2_create_type(kind);
	P->bio = func3_create_Bio(H, W, A);
	return P;
}

type_of_pokemon* func2_create_type(char *kind)
{
	type_of_pokemon *T = (type_of_pokemon*)malloc(sizeof(type_of_pokemon));
	T->kind = (char*)malloc((strlen(kind) + 1) * sizeof(char));
	strcpy(T->kind, kind);
	T->number = 0;
	T->effective_against_me = NULL;
	T->effective_against_others = NULL;
	T->against_me = 0;
	T->against_others = 0;
	return T;
}

Bio_of_pokemon* func3_create_Bio(float H, float W, int A)
{
	Bio_of_pokemon* B = (Bio_of_pokemon*)malloc(sizeof(Bio_of_pokemon));
	B->Height = H;
	B->Weight = W;
	B->Attack = A;
	return B;
}

void func4_add_type_against_me(type_of_pokemon* pokemon_A, type_of_pokemon* pokemon_B)
{
	type_of_pokemon **P = (type_of_pokemon**)malloc((pokemon_A->against_me + 1) * sizeof(type_of_pokemon*));
		int i;
		for (i = 0; i < pokemon_A->against_me; i++)
			P[i] = pokemon_A->effective_against_me[i];
		P[i] = pokemon_B;
		pokemon_A->against_me++;
		free(pokemon_A->effective_against_me);
		pokemon_A->effective_against_me = P;
}


void func5_add_type_against_others(struct Pokemon_type* pokemon_A, struct Pokemon_type* pokemon_B)
{
	type_of_pokemon **P = (type_of_pokemon**)malloc((pokemon_A->against_others + 1) * sizeof(type_of_pokemon*));
		int i;
		for (i = 0; i < pokemon_A->against_others; i++)
			P[i] = pokemon_A->effective_against_others[i];
		P[i] = pokemon_B;
		pokemon_A->against_others++;
		free(pokemon_A->effective_against_others);
		pokemon_A->effective_against_others = P;
}

status func6_remove_type_agains_me(type_of_pokemon* A, char* kind)
{
	int i, j;
		for (i = 0; i < A->against_me; i++)
			if (strcmp(A->effective_against_me[i]->kind, kind) == 0)
				break;
		if (i == A->against_me)
			return failure;
		struct Pokemon_type **P = (struct Pokemon_type**)malloc((A->against_me - 1) * sizeof(struct Pokemon_type*));
		for (i = 0, j = 0; i < A->against_me; i++)
			if (strcmp(A->effective_against_me[i]->kind, kind) != 0)
				P[j++] = A->effective_against_me[i];
		//else
		//	free(A->effective_against_me[i]);
		A->effective_against_me = (struct Pokemon_type**)realloc(A->effective_against_me,sizeof(struct Pokemon_type*)* (A->against_me-1));
		for (i = 0; i < A->against_me - 1; i++)
			A->effective_against_me[i] = P[i];
		free(P);
		A->against_me--;
		return success;
}

status func7_remove_type_agains_others(type_of_pokemon* A, char* kind)
{
	int i, j;
		for (i = 0; i < A->against_others; i++)
			if (strcmp(A->effective_against_others[i]->kind, kind) == 0)
				break;
		if (i == A->against_others)
			return failure;
		struct Pokemon_type **P = (struct Pokemon_type**)malloc((A->against_others - 1) * sizeof(struct Pokemon_type*));
		for (i = 0, j = 0; i < A->against_others; i++)
			if (strcmp(A->effective_against_others[i]->kind, kind) != 0)
				P[j++] = A->effective_against_others[i];


		A->effective_against_others = (struct Pokemon_type**)realloc(A->effective_against_others, sizeof(struct Pokemon_type*)*(A->against_others-1 ));
		for (i = 0; i < A->against_others - 1; i++)
			A->effective_against_others[i] = P[i];
		free(P);
		A->against_others--;
		return success;
}

void func8_print_pokemon(Pokemon *P)
{

		printf("%s%s\n", P->name, " :");
		printf("%s%s%s %s\n", P->species, ", ", P->type->kind, "Type.");
		printf("%s %.2f m    %s %.2f kg    %s %d\n\n", "Height:", P->bio->Height, "Weight:", P->bio->Weight, "Attack:", P->bio->Attack);
}

void func9_print_type(type_of_pokemon *P)
{
	if (P->against_me == 0 && P->against_others == 0)
	{
		printf("Type %s -- %d pokemons\n\n", P->kind, P->number);
	}

	if (P->against_me == 0 && P->against_others > 0)
	{
		printf("Type %s -- %d pokemons\n", P->kind, P->number);
		printf("\t%s moves are super-effective against:", P->kind);
		for (int i = 0; i < P->against_others; i++)
		{
			printf("%s", P->effective_against_others[i]->kind);
			if (i < P->against_others - 1)
				printf(" ,");

		}
		printf("\n\n");

	}

	if (P->against_me > 0 && P->against_others == 0)
	{
		printf("Type %s -- %d pokemons\n", P->kind, P->number);
		printf("\tThese types are super-effective against %s:", P->kind);
		for (int i = 0; i < P->against_me; i++)
		{
			printf("%s", P->effective_against_me[i]->kind);
			if (i < P->against_me - 1)
				printf(" ,");

		}
		printf("\n\n");

	}
	if (P->against_me > 0 && P->against_others > 0)
	{
		printf("Type %s -- %d pokemons\n", P->kind, P->number);
		printf("\tThese types are super-effective against %s:", P->kind);
		for (int i = 0; i < P->against_me; i++)
		{
			printf("%s", P->effective_against_me[i]->kind);
			if (i < P->against_me - 1)
				printf(" ,");
		}
		printf("\n\t%s moves are super-effective against:", P->kind);
		for (int i = 0; i < P->against_others; i++)
		{
			printf("%s", P->effective_against_others[i]->kind);
			if (i < P->against_others - 1)
				printf(" ,");

		}
		printf("\n\n");
	}


}
