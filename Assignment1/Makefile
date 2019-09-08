dict2: dict2.o bstllist.o trips.o
	gcc  -fsanitize=address -Wall -g -o dict2 dict2.o bstllist.o trips.o

dict1: dict1.o bstllist.o trips.o
	gcc -fsanitize=address -Wall -g -o dict1 dict1.o bstllist.o trips.o
    
dict2.o: dict2.c
	gcc  -fsanitize=address -Wall -g -c -o dict2.o dict2.c

dict1.o: dict1.c
	gcc  -fsanitize=address -Wall -g -c -o dict1.o dict1.c

bstllist.o: bstllist.c trips.c
	gcc  -fsanitize=address -Wall -g -c -o bstllist.o bstllist.c

trips.o: trips.c
	gcc  -fsanitize=address -Wall -g -c -o trips.o trips.c