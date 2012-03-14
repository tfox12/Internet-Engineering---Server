phase1 : main.c threadpool.o socketlayer.o socketqueue.o httpparser.o \
                config.o filemanager.o signal_handlers.o httpget.o    \
                protoheaders.o scripting.o logger.o
	gcc -g -pthread -o phase1 main.c threadpool.o socketlayer.o socketqueue.o \
        config.o filemanager.o signal_handlers.o httpparser.o httpget.o    \
		protoheaders.o scripting.o logger.o

threadpool.o : threadpool.c threadpool.h
	gcc -g -c threadpool.c
socketlayer.o : socketlayer.c socketlayer.h
	gcc -g -c socketlayer.c
socketqueue.o : socketqueue.c socketqueue.h
	gcc -g -c socketqueue.c
httpparser.o : httpparser.c httpparser.h
	gcc -g -c httpparser.c	
httpget.o : httpget.c httpget.h
	gcc -g -c httpget.c
protoheaders.o : protoheaders.c protoheaders.h
	gcc -g -c protoheaders.c
config.o : config.c config.h
	gcc -g -c config.c
filemanager.o : filemanager.c filemanager.h
	gcc -g -c filemanager.c
signal_handlers.o : signal_handlers.c signal_handlers.h
	gcc -g -c signal_handlers.c
scripting.o : scripting.c scripting.h
	gcc -g -c scripting.c
logger.o : logger.c logger.h
	gcc -g -c logger.c
clean : 
	rm *.o phase1
