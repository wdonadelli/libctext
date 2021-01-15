#include "libctext.h"

int main(int argc, char *argv[]) {
	new_STR(string, "Valor");
	string.set("oioi");
	string.get();
	string.ltrim();
	string.rtrim();
	string.trim();
	string.clear();
	string.add("oioi");	

	printf("----\n");
	string.len();
	string.print();
	string.free();

}
