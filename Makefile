$(CC) = gcc
converter:
# 	$(CC) src/main.c src/p2s_converter.c -o converter
	$(CC) src/main.c src/p2s_converter.c -o converter -I src/pod5-format/include/ src/pod5-format/lib/libpod5_format.so

clean:
	rm converter