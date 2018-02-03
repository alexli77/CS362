CFLAGS = -Wall -fpic -coverage -lm

run_testme: testme.c
	gcc -o testme -g  testme.c $(CFLAGS)
	./testme

clean:
	-rm -f *.gcda *.gcno testme
