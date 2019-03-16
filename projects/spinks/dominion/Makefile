CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

#Unit tests for 4 functions
testDiscard: unittest1.c dominion.o rngs.o
	gcc -o testDiscard -g unittest1.c dominion.o rngs.o $(CFLAGS)

testDrawCard: unittest2.c dominion.o rngs.o
	gcc -o testDrawCard -g unittest2.c dominion.o rngs.o $(CFLAGS)

testScoreFor: unittest3.c dominion.o rngs.o
	gcc -o testScoreFor -g unittest3.c dominion.o rngs.o $(CFLAGS)

testGetCost: unittest4.c dominion.o rngs.o
	gcc -o testGetCost -g unittest4.c dominion.o rngs.o $(CFLAGS)

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

#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
#testDrawCard: testDrawCard.c dominion.o rngs.o
#	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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
#End random Card tests for 4 Cardsma

#Run tests for each function
runCardtest1: cardtest1
	./cardtest1 >> cardtest1.out
	gcov -b -c cardtest1.c  >> cardtest1.out
	gcov -b -c cardtest1.c  >> cardtestAll.out

runCardtest2: cardtest2
	./cardtest2 >> cardtest2.out
	gcov -b -c cardtest2.c >> cardtest2.out
	gcov -b -c cardtest2.c  >> cardtestAll.out

runCardtest3: cardtest3
	./cardtest3 >> cardtest3.out
	gcov -b -c cardtest3.c >> cardtest3.out
	gcov -b -c cardtest3.c  >> cardtestAll.out

runCardtest4: cardtest4
	./cardtest4 >> cardtest4.out
	gcov -b -c cardtest4.c >> cardtest4.out
	gcov -b -c cardtest4.c >> cardtestAll.out

runRandtest1: randtest1
	./randtest1 >> randomtestadventurer.out
	gcov -b -c randomtestcard1.c >> randomtestadventurer.out
	gcov -b -c randomtestcard1.c  >> cardtestAll.out

runRandtest2: randtest2
	./randtest2 >> randomcardtest2.out
	gcov -b -c randomtestcard2.c >> randomcardtest2.out
	gcov -b -c randomtestcard2.c  >> cardtestAll.out

runRandtest3: randtest3
	./randtest3 >> randomcardtest3.out
	gcov -b -c randomtestcard3.c >> randomcardtest3.out
	gcov -b -c randomtestcard3.c  >> cardtestAll.out

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

randomtestresults: runRandtest1 runRandtest2 runRandtest3 runCardtest1 runCardtest2 runCardtest3 runCardtest4

all: playdom player randomtestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
