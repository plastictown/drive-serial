CC=gcc
CCFLAGS=-Wall -O2 -pipe -I.
APPNAME=app
LINK=gcc
LINKFLAGS=-lrt
RM=rm

all: drive-serial.o main.o
	$(CC) -o $(APPNAME) $(CCFLAGS) drive-serial.o main.o $(LINKFLAGS)
drive-serial.o:
	$(CC) -c $(CCFLAGS) drive-serial.c $(LINKFALGS)
main.o:
	$(CC) -c $(CCFLAGS) main.c $(LINKFLAGS)
clean:
	$(RM) -f *.o
	$(RM) -f $(APPNAME)
