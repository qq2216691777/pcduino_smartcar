PROJECT = test
SRC = main.c key_function.c pthread.c net.c
LIBS = -Wall `pkg-config --cflags --libs --cflags gtk+-3.0 --libs gthread-2.0` -export-dynamic -Wdeprecated-declarations -lpthread

all:
	-rm test
	gcc $(SRC) $(LIBS) -o $(PROJECT)

.PHONY:
clean:
	rm *.o *~
