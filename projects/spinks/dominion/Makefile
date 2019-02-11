CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#Unit tests for 4 functions
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

#End tests for 4 functions

#Card tests for 4 Cards
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

#End Card tests for 4 Cards

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

runUnittest1: unittest1
	./unittest1 >> unittestresults.out
	gcov -b -c unittest1.c >> unittestresults.out

runUnittest2: unittest2
	./unittest2 >> unittestresults.out
	gcov -b -c unittest2.c >> unittestresults.out

runUnittest3: unittest3
	./unittest3 >> unittestresults.out
	gcov -b -c unittest3.c >> unittestresults.out

runUnittest4: unittest4
	./unittest4 >> unittestresults.out
	gcov -b -c unittest4.c >> unittestresults.out

runCardtest1: cardtest1
	./cardtest1 >> unittestresults.out
	gcov -b -c cardtest1.c >> unittestresults.out

runCardtest2: cardtest2
	./cardtest2 >> unittestresults.out
	gcov -b -c cardtest2.c >> unittestresults.out

runCardtest3: cardtest3
	./cardtest3 >> unittestresults.out
	gcov -b -c cardtest3.c >> unittestresults.out

runCardtest4: cardtest4
	./cardtest4 >> unittestresults.out
	gcov -b -c cardtest4.c >> unittestresults.out

unittestresults: runUnittest1 runUnittest2 runUnittest3 runUnittest4 runCardtest1 runCardtest2 runCardtest3 runCardtest4
	

all: playdom player unittestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittestresults.out
