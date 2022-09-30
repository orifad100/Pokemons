PokemonsBattles: BattleByCategory.o LinkedList.o MainSecond.o MaxHeap.o Pokemon.o
	gcc -g BattleByCategory.o LinkedList.o MainSecond.o MaxHeap.o Pokemon.o -o PokemonsBattles
BattleByCategory.o: BattleByCategory.c Defs.h BattleByCategory.h LinkedList.h MaxHeap.h
	gcc -c BattleByCategory.c -g
LinkedList.o: LinkedList.c LinkedList.h Defs.h 
	gcc -c LinkedList.c -g
MainSecond.o: MainSecond.c Pokemon.h Defs.h BattleByCategory.h
	gcc -c MainSecond.c -g
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c -g
Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c -g
clean:
	rm -f *.o
