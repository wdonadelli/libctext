#include "libctext.h"

int main(int argc, char *argv[]) {
	new_STR(string, "Willian");

	printf("-> initial: ");
	string.print();

	printf("-> set:     |%s|\n", string.set("     willian      donadelli  o       lindo  "));

//	printf("-> get:     |%s|\n", string.get());

//	printf("-> ltrim:   |%s|\n", string.ltrim());

//	printf("-> rtrim:   |%s|\n", string.rtrim());

//	printf("-> trim:    |%s|\n", string.trim());

	printf("-> clear:   |%s|\n", string.clear());

	printf("-> add:     |%s|\n", string.add(" linduuuuu"));

	printf("-> len:     %d\n", string.len());

	printf("-> print:   ");
	string.print();

	printf("-> free: ");
	string.free();
	string.print();

	exit(0);
}
