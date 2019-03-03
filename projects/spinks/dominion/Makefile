CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#Rand Card tests for 4 Cards
randtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randtest1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randtest2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randtest3: randomtestcard3.c dominion.o rngs.o
	gcc -o randtest3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)

runRandtest1: randcardtest1
	./randtest1 >> randomtestadventurer.out
	gcov -b -c randomtestcard1.c >> randomtestadventurer.out

runRandtest2: randcardtest2
	./randtest2 >> randomcardtest2.out
	gcov -b -c randomtestcard2.c >> randomcardtest2.out

runRandtest3: randcardtest3
	./randtest3 >> randomcardtest3.out
	gcov -b -c randomtestcard3.c >> randomcardtest3.out
#End random Card tests for 4 Cards

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestresults: runRandtest1 runRandtest2 runRandtest3

all: playdom player randomtestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
