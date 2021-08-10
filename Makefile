FLAGS = -ansi -Wall -pedantic-errors
LIBS = -lm

all: final
	
linuxClean:
	rm -rf *.o
	rm cluster
final:  actionTable.o instructions.o intNode.o parser.o symbolTable.o firstScan.o secondScan.o main.o
	gcc  actionTable.o instructions.o intNode.o parser.o symbolTable.o firstScan.o secondScan.o main.o -o final $(LIBS)

actionTable: actionTable.o
	gcc actionTable.o -o actionTable $(LIBS)
actionTable.o: actionTable.c
	gcc $(FLAGS) -c actionTable.c
firstScan: firstScan.o
	gcc firstScan.o -o firstScan $(LIBS)
firstScan.o: firstScan.c
	gcc $(FLAGS) -c firstScan.c
instructions: instructions.o
	gcc instructions.o -o instructions $(LIBS)
instructions.o: instructions.c
	gcc $(FLAGS) -c instructions.c
intNode: intNode.o
	gcc intNode.o -o intNode $(LIBS)
intNode.o: intNode.c
	gcc $(FLAGS) -c intNode.c
parser: parser.o
	gcc parser.o -o parser $(LIBS)
parser.o: parser.c
	gcc $(FLAGS) -c parser.c
symbolTable: symbolTable.o
	gcc symbolTable.o -o symbolTable $(LIBS)
symbolTable.o: symbolTable.c
	gcc $(FLAGS) -c symbolTable.c
main: main.o
	gcc main.o -o main $(LIBS)
symbolTable.o: main.c
	gcc $(FLAGS) -c main.c
secondScan: secondScan.o
	gcc secondScan.o -o secondScan $(LIBS)
secondScan.o: secondScan.c
