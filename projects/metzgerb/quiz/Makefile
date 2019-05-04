CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o $@ $^ $(CFLAGS)
	./$@

clean:
	rm -f testme *.gcov *.gcda *.gcno
