phase2 : main.c socketlayer.o
	gcc -o phase2 main.c socketlayer.o 
socketlayer.o : socketlayer.c socketlayer.h
	gcc -c socketlayer.c
clean : 
	rm *.o phase2
