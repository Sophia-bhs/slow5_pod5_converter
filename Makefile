CC = g++
p2s:
	$(CC) src/main.c src/pod5_reader.c -o p2s -I src/pod5-format/include/ src/pod5-format/lib64/libpod5_format.a src/pod5-format/lib64/libarrow.a src/pod5-format/lib64/libzstd.a -lz -lpthread

clean:
	rm *.o p2s