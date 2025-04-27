CC = g++

INCLUDE = -Iinclude -IMy_logging_system/include -IList/include

CFLAGS_DEBUG = -lm -D _DEBUG -ggdb3 -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
CFLAGS = -lm -DNDEBUG

SRC_FILES_2 = $(wildcard src/*.cpp) $(wildcard List/src/*.cpp)
SRC_FILES = $(filter-out List/src/main.cpp, $(SRC_FILES_2))

BUILD_FILES   = $(wildcard build/*.o)

MY_LIBS = My_logging_system/log_lib.a

all: hashtable.out

hashtable.out:$(SRC_FILES) $(BUILD_FILES)
	nasm src/my_hash.asm -o build/my_hash.o -f elf64
	@$(CC) $(CFLAGS_DEBUG) $(INCLUDE) $(SRC_FILES) build/my_hash.o $(MY_LIBS) -o hashtable.out -O0 -g -march=native

full_optimise:
	nasm src/my_hash.asm -o build/my_hash.o -f elf64
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRC_FILES) build/my_hash.o My_logging_system/src/my_log.cpp $(MY_LIBS) -o hashtable.out -O3 -ggdb -march=native

library:
	@$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC_FILES) My_logging_system/log_lib.a -o $(BUILD_FILES)

run:
	./hashtable.out

perf:
	perf record --call-graph dwarf -c 10 ./hashtable.out
	hotspot ./perf.data

clean:
	rm -rf build
	mkdir build
	rm hashtable.out
