phase1 : main.c threadpool.o socketlayer.o socketqueue.o
	gcc -pthread -o phase1 main.c threadpool.o socketlayer.o socketqueue.o
threadpool.o : threadpool.c threadpool.h
	gcc -c threadpool.c
socketlayer.o : socketlayer.c socketlayer.h
	gcc -c socketlayer.c
socketqueue.o : socketqueue.c socketqueue.h
	gcc -c socketqueue.c
clean : 
	rm *.o phase1
