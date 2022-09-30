


/*
 * MainSecond.c
 *
 *  Created on: Dec 15, 2021
 *      Author: ise*/




#include "Pokemon.h"
#include "Defs.h"
#include "BattleByCategory.h"


int main(int argv, char* argc[])

{



	FILE *file = fopen(argc[3], "r");
	int i, j, k, index1 = 0, size_types = atoi(argc[1]),  *counters, num = 0,counter7=0,counter8=0 ,counter_5=0;
	const char psik[5] = ",", space[2] = " ", comma[2] = ":", slash[5] = "\r\n";
	char  *token, *type, *against, Name[SIZE];
	char Type1[SIZE],Name1[SIZE],Species1[SIZE],Height1[SIZE],Weight1[SIZE],Attack1[SIZE];
	int counter_3=0, counter_4=size_types;
	char ch[SIZE];
	int index2 =0;

	char *name ;
	char *species,*kind;
	char *H , *W;
	char *A;
	type_of_pokemon *types[size_types];

	Pokemon* pok11;



	if (file == NULL)
	{
		printf("File not found, please check it\n");
		return -1;
	}
	fgets(ch, SIZE, file);
	fgets(ch, SIZE, file);
	ch[strlen(ch) - 2] = '\0';
	char* categories=(char*)malloc(sizeof(char)*strlen(ch)+1);
	strcpy(categories,ch);
	token = strtok(ch, psik);
	while (token != NULL)
	{
		types[index1++] = func2_create_type(token);

		token = strtok(NULL, psik);
	}
	 void Freepok(element elem)
	 {
		 struct create_Pokemon * poki=elem;
		 free(poki->species);
		 free(poki->name);
		 free(poki->type->kind);
		 free(poki->type);
		 free(poki->bio);
		 free(poki);
	 }

	 element copypok(element elem1)
	 {

		 return elem1;
	 }

	 void printpok(element elem)
	 {
		func8_print_pokemon((Pokemon*)elem);

	 }

	 int equalfunc(element element1,element element2)
	 {
		struct create_Pokemon * elem1=element1;
		struct create_Pokemon * elem2=element2;
		if(elem1->bio->Attack==elem2->bio->Attack)
			return 0;
		if(elem1->bio->Attack>elem2->bio->Attack)
			return 1;
		else
			return -1;
	 }

	 char* getCategory(element elem)
	 {
		 Pokemon* name_cate =elem;
		 return name_cate->type->kind;
	 }

	 int getAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond)
	 {
		 struct create_Pokemon * elem1=(struct create_Pokemon*)firstElem;
		 struct create_Pokemon * elem2=(struct create_Pokemon*)secondElem;
		 int k,count_1=0,count_2=0,i;
		 struct Pokemon_type* type1;
		 struct Pokemon_type* type2;

		 for(i=0;i<size_types;i++)
		 {
			 if(strcmp(types[i]->kind,elem1->type->kind)==0)
			 {
				 type1=types[i];
			 }
		 }
		 for(j=0;j<size_types;j++)
		 {
			 if(strcmp(types[j]->kind,elem2->type->kind)==0)
			 {
				 type2=types[j];
			 }
		 }

		 for(k=0;k<type1->against_me;k++)
		 {
			 if(strcmp(type2->kind,type1->effective_against_me[k]->kind)==0)
			 {

				 count_1=-10;
			 }

		 }
		 for(k=0;k<type1->against_others;k++)
		 {
			 if(strcmp(type2->kind,type1->effective_against_others[k]->kind)==0)
			 {

				 count_2=-10;
			 }

		 }


		 for(k=0;k<type2->against_me;k++)
		 {
			 if(strcmp(type1->kind,type2->effective_against_me[k]->kind)==0)
			 {

				 count_2=-10;
			 }

		 }
		 for(k=0;k<type2->against_others;k++)
		 {
			 if(strcmp(type1->kind,type2->effective_against_others[k]->kind)==0)
			 {

				 count_1=-10;
			 }

		 }
		 if(count_1<-10)
			 count_1=-10;
		 if(count_2<-10)
			 count_2=-10;

		 * attackFirst=elem1->bio->Attack+count_1;
		 *attackSecond=elem2->bio->Attack+count_2;

		 return * attackFirst-*attackSecond;
	 }

		struct battle_s* pb;
		int capacity=atoi(argc[2]);
		int numberOfCategories=size_types;

		 pb =createBattleByCategory( capacity, numberOfCategories, categories, equalfunc, copypok,Freepok, getCategory, getAttack, printpok);




	while (fgets(ch, SIZE, file) != NULL)
	{
		if (strcmp(ch, "Pokemons\r\n") == 0)
		{
			while (fgets(ch, SIZE, file) != NULL)
			{

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
				pok11 = func1_create_pokemon(name, species, atof(H), atof(W), atoi(A), kind);
				insertObject(pb,pok11);

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

		while (num != 6)
			{
				printf("Please choose one of the following numbers:\n");
				printf("1 : Print all Pokemons by types\n");
				printf("2 : Print all Pokemons types\n");
				printf("3 : Insert Pokemon to battles training camp\n");
				printf("4 : Remove strongest Pokemon by type\n");
				printf("5 : Fight\n");
				printf("6 : Exit\n");
				scanf("%s", &ch);
				num = atoi(ch);
				switch (num)
				{
				case 1:
				{
					displayObjectsByCategories(pb);
				}
				break;

				case 2:
				{
					for(i=0;i<size_types;i++)
					{
						types[i]->number=getNumberOfObjectsInCategory(pb,types[i]->kind);
					}
					for (int k = 0; k < size_types; k++)
						func9_print_type(types[k]);
				break;
				}
				case 3:
				{
					printf("Please enter Pokemon type name:\n");
					scanf("%s", Type1);
					for(i=0;i<size_types;i++)
					{
						counter_3++;
						if(strcmp(Type1,types[i]->kind)==0)
						{
							int size_heap;
							size_heap=getNumberOfObjectsInCategory(pb,types[i]->kind);
							if(size_heap<capacity)
							{
								printf("Please enter Pokemon name:\n");
								scanf("%s",Name1);
								printf("Please enter Pokemon species:\n");
								scanf("%s",Species1);
								printf("Please enter Pokemon height:\n");
								scanf("%s",Height1);
								printf("Please enter Pokemon weight:\n");
								scanf("%s",Weight1);
								printf("Please enter Pokemon attack:\n");
								scanf("%s",Attack1);
								struct create_Pokemon* pok2;
								pok2=func1_create_pokemon(Name1, Species1, atof(Height1),atof(Weight1),atoi(Attack1), Type1);
							//	add_pok(pok2);
								//insertObject(pb,pok2);


								size_heap=getNumberOfObjectsInCategory(pb,types[i]->kind);
								if(size_heap<=capacity)
								{
									insertObject(pb,pok2);
									printf("The Pokemon was successfully added.\n");
									func8_print_pokemon(pok2);
									break;
								}
								else
								{
									Freepok(pok2);


								}

						   }
							else
							{
								printf("Type at full capacity.\n");
							    break;
							}
					}
						if(counter_3==size_types)
						{
							printf("Type name doesn't exist.\n");
							break;
						}
				}

				}
				break;
				case 4 :
				{
					printf("Please enter type name:\n");
					scanf("%s",Type1);
					for(i=0;i<size_types;i++)
					{
						if(strcmp(Type1,types[i]->kind)==0)
						{
							counter_4--;
							int size_heap1;
							size_heap1=getNumberOfObjectsInCategory(pb,types[i]->kind);
							if(size_heap1>0)
							{
								element elem;
								elem=removeMaxByCategory(pb,types[i]->kind);
								printf("The strongest Pokemon was removed:\n");
								func8_print_pokemon(elem);
								Freepok(elem);
								break;
							}
							else
							{
								printf("There is no Pokemon to remove.\n");
								break;
							}
						 }
					 }
					if(counter_4==size_types)
					{
						printf("Type name doesn't exist.\n");
						break;
					}
				}
				break;
			case 5:
				{
					printf("Please enter Pokemon type name:\n");
					scanf("%s",Type1);

					for(i=0;i<size_types;i++)
					{
						counter_5++;
						if(strcmp(Type1,types[i]->kind)==0)
						{

							printf("Please enter Pokemon name:\n");
							scanf("%s",Name1);
							printf("Please enter Pokemon species:\n");
							scanf("%s",Species1);
							printf("Please enter Pokemon height:\n");
							scanf("%s",Height1);
							printf("Please enter Pokemon weight:\n");
							scanf("%s",Weight1);
							printf("Please enter Pokemon attack:\n");
							scanf("%s",Attack1);
							printf("You choose to fight with:\n");
							struct create_Pokemon* pok1=func1_create_pokemon(Name1, Species1, atof(Height1),atof(Weight1),atoi(Attack1), Type1);
							func8_print_pokemon(pok1);
							fight(pb,pok1);
							/*free(pok1->bio);
							free(pok1->name);
							free(pok1->species);
							free(pok1->type->effective_against_me);
							free(pok1->type->effective_against_others);
							free(pok1->type->kind);
							free(pok1->type);
							free(pok1);*/
							Freepok(pok1);
							break;
						}
					}
					if(counter_5==size_types)
					{
						printf("Type name doesn't exist.\n");
						break;
					}

				}

				break;
			case 6 :
			{
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
				destroyBattleByCategory(pb);
				free(categories);
				fclose(file);
				printf("All the memory cleaned and the program is safely closed.\n");
				break;
			}
			default:
					printf("Please choose a valid number.\n");
					break;
				}
		}


	 return 0;
}






