CFLAGS  =
CFLAGS += -Iinclude
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic

vtest_example: vtest_example.o vtest.o
	$(CC) $^ -o $@

vtest.o: vtest.c include/vtest.h
	$(CC) -c $(CFLAGS) vtest.c -o $@

vtest_example.o: vtest_example.c include/vtest.h
	$(CC) -c $(CFLAGS) vtest_example.c -o $@

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) vtest_example

