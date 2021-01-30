#include "libctext.h"

/*
128 64 32 16 8 4 2 1
00101001 = 61

128 64 32 16 8 4 2 1
01111111 = 127


*/

int main(int argc, char *argv[]) {
	new_STR(string, "Initial value");







	printf("-> get:     |%s|\n", string.get());

	printf("-> set:     |%s|\n", string.set("     é      animal     é   "));

	printf("-> get:     |%s|\n", string.get());

	printf("-> ltrim:   |%s|\n", string.ltrim());

	printf("-> rtrim:   |%s|\n", string.rtrim());

	printf("-> trim:    |%s|\n", string.trim());

	printf("-> clear:   |%s|\n", string.clear());

	printf("-> add:     |%s|\n", string.add(" É GATO"));

	printf("-> lower:   |%s|\n", string.lower());
	
	printf("-> upper:   |%s|\n", string.upper());

	printf("-> title:   |%s|\n", string.title());

	printf("-> len:     %d\n", string.len());

//	printf("-> print:   ");
//	string.print();

//	printf("-> free: ");
	string.free();
	string.print();

	exit(0);
}
