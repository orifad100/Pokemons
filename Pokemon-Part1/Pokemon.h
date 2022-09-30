/*
 * Pokemon.h
 *
 *  Created on: Nov 26, 2021
 *      Author: ise
 */

#ifndef _POKEMON_H
#define _POKEMON_H


#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 300

typedef struct Pokemon_type
{
    char *kind;
    int number;

	int against_me;
    struct Pokemon_type **effective_against_me;
	int against_others;
    struct Pokemon_type **effective_against_others;
}type_of_pokemon;

typedef struct Pokemon_bio
{
    float Height;
    float Weight;
    int Attack;
}Bio_of_pokemon;

typedef struct create_Pokemon
{
    char *name;
    char *species;
    Bio_of_pokemon *bio;
    type_of_pokemon *type;
}Pokemon;

Pokemon* func1_create_pokemon(char *name, char *species, float H, float W, int A,char *kind);
type_of_pokemon* func2_create_type(char *);
Bio_of_pokemon* func3_create_Bio(float, float, int);
void func4_add_type_against_me(type_of_pokemon*, type_of_pokemon*);
void func5_add_type_against_others(struct Pokemon_type*, struct Pokemon_type*);
status func6_remove_type_agains_me(type_of_pokemon*, char*);
status func7_remove_type_agains_others(type_of_pokemon*, char*);
void func8_print_pokemon(Pokemon *P);
void func9_print_type(type_of_pokemon *S);
#endif /* POKEMON_H_ */
