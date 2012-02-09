phase1 : main.c threadpool.o socketlayer.o socketqueue.o httpparser.o \
                config.o filemanager.o signal_handlers.o
	gcc -pthread -o phase1 main.c threadpool.o socketlayer.o socketqueue.o \
                               config.o filemanager.o signal_handlers.o
threadpool.o : threadpool.c threadpool.h
	gcc -c threadpool.c
socketlayer.o : socketlayer.c socketlayer.h
	gcc -c socketlayer.c
socketqueue.o : socketqueue.c socketqueue.h
	gcc -c socketqueue.c
httpparser.o : httpparser.c httpparser.h
	gcc -c httpparser.c	
config.o : config.c config.h
	gcc -c config.c
filemanager.o : filemanager.c filemanager.h
	gcc -c filemanager.c
signal_handlers.o : signal_handlers.c signal_handlers.h
	gcc -c signal_handlers.c
clean : 
	rm *.o phase1
