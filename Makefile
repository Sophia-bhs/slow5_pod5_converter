# CC = g++
# p2s: src/main.c src/pod5_reader.c src/pod5_reader.h
# 	$(CC) src/main.c src/pod5_reader.c -o p2s -I src/pod5-format/include/ src/pod5-format/lib64/libpod5_format.a src/pod5-format/lib64/libarrow.a src/pod5-format/lib64/libzstd.a -lz -lpthread

# clean:
# 	rm p2s

CC       = cc
CXX      = g++
CPPFLAGS += -I slow5lib/include/ -I src/pod5-format/include/
CFLAGS   += -g -Wall -O2
LDFLAGS  += $(LIBS) -lz
BUILD_DIR = build

ifeq ($(zstd),1)
LDFLAGS		+= -lzstd
endif

BINARY = p2s
OBJ = $(BUILD_DIR)/main.o \
    $(BUILD_DIR)/pod5_reader.o \
    $(BUILD_DIR)/slow5_writer.o \

PREFIX = /usr/local
VERSION = `git describe --tags`

ifdef asan
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

.PHONY: clean test

$(BINARY): $(OBJ) slow5lib/lib/libslow5.a src/pod5-format/lib64/libpod5_format.a src/pod5-format/lib64/libarrow.a src/pod5-format/lib64/libzstd.a -lz -lpthread
	$(CXX) $(CFLAGS) $(OBJ) slow5lib/lib/libslow5.a src/pod5-format/lib64/libpod5_format.a src/pod5-format/lib64/libarrow.a src/pod5-format/lib64/libzstd.a -lz -lpthread -ljemalloc $(LDFLAGS) -o $@

$(BUILD_DIR)/main.o: src/main.c
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LANGFLAG) $< -c -o $@

$(BUILD_DIR)/pod5_reader.o: src/pod5_reader.c src/pod5_reader.h 
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LANGFLAG) $< -c -o $@

$(BUILD_DIR)/slow5_writer.o: src/slow5_writer.c src/slow5_writer.h 
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LANGFLAG) $< -c -o $@

slow5lib/lib/libslow5.a:
	$(MAKE) -C slow5lib zstd=$(zstd) no_simd=$(no_simd) zstd_local=$(zstd_local) lib/libslow5.a

clean:
	rm -rf $(BINARY) $(BUILD_DIR)/*.o
	make -C slow5lib clean

test: $(BINARY)
	./test/test.sh

