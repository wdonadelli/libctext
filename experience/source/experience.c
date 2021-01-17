#include "libctext.h"

int main(int argc, char *argv[]) {
	new_STR(string, "Initial value");

	printf("-> initial: ");
	string.print();

	printf("-> set:     |%s|\n", string.set(" É o Will Donadelli Amanhã"));

//	printf("-> get:     |%s|\n", string.get());

//	printf("-> ltrim:   |%s|\n", string.ltrim());

//	printf("-> rtrim:   |%s|\n", string.rtrim());

//	printf("-> trim:    |%s|\n", string.trim());

//	printf("-> clear:   |%s|\n", string.clear());

//	printf("-> add:     |%s|\n", string.add(" É GATO, AMANHÃ, DELÍCIA Á"));

	printf("-> lower:   |%s|\n", string.lower());
	
//	printf("-> upper:   |%s|\n", string.upper());

//	printf("-> title:   |%s|\n", string.title());

//	printf("-> len:     %d\n", string.len());

//	printf("-> print:   ");
	string.print();

	printf("-> free: ");
	string.free();
	string.print();

	exit(0);
}
