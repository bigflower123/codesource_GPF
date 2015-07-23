CC=gcc
LIBS=-lm
EXEC=sommeC_Snsd
all:$(EXEC)
CCFLAGS=-g -Wall

$(EXEC): main.o readsrc.o chaine.o LR.o RZ.o ILS.o IGA.o f3setupcbarre.o
	gcc $(CCFLAGS) -o  $(EXEC) main.o readsrc.o chaine.o LR.o RZ.o ILS.o IGA.o f3setupcbarre.o $(LIBS)

chaine.o: chaine.c
	$(CC)  $(CCFLAGS) -o chaine.o -c chaine.c

LR.o: LR.c
	$(CC)  $(CCFLAGS) -o LR.o -c LR.c

RZ.o: RZ.c
	$(CC)  $(CCFLAGS) -o RZ.o -c RZ.c
f3setupcbarre.o: f3setupcbarre.c
	$(CC)  $(CCFLAGS) -o f3setupcbarre.o -c f3setupcbarre.c

ILS.o: ILS.c
	$(CC)  $(CCFLAGS) -o ILS.o -c ILS.c

IGA.o: IGA.c
	$(CC)  $(CCFLAGS) -o IGA.o -c IGA.c

readsrc.o: readsrc.c
	$(CC)  $(CCFLAGS) -o readsrc.o -c readsrc.c
 
main.o: main.c
	$(CC)  $(CCFLAGS) -o main.o -c main.c
 
clean:
	rm -vf *.o
