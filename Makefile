$(CC) = gcc
converter:
	$(CC) src/main.c src/p2s_converter.c -o converter

Clean:
	rm *.o converter