#include "libctext.h"

/*-- Cores --*/
#define STYLE_RESET   "\e[0m"
#define STYLE_DEFAULT "\e[0;0;37;44m"
#define STYLE_TITLE   "\e[0;1;34;47m"
#define STYLE_EXIT    "\e[0;0;37;44m"
#define STYLE_VALUE   "\e[0;3;33;44m"
#define STYLE_PROMPT  "\e[0;0;33;44m"

/*-- Frases --*/
#define INPUT_INITIAL STYLE_PROMPT "Initial value: " STYLE_VALUE
#define INPUT_USER    STYLE_DEFAULT "\n: "
#define INPUT_SET     STYLE_PROMPT "New value: " STYLE_VALUE
#define INPUT_ADD     STYLE_PROMPT "Addition value: " STYLE_VALUE
#define INPUT_FILE    STYLE_PROMPT "File name: " STYLE_VALUE
#define INPUT_INPUT   STYLE_PROMPT "Message: " STYLE_VALUE


/*-- Protótipos --*/
void options();

/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {

	/* variáveis locais */
	int quit = 0;
	new_STR(data, ""); /* registra a entrada de dados do usuário */
	new_STR(attr, ""); /* registra o valor do atributo do método */

	/* iniciar */
	puts(STYLE_DEFAULT);
	system("clear");
	printf("%s%48s%32s%s\n\n", STYLE_TITLE, "LIBCTEXT EXAMPLE", " ", STYLE_DEFAULT);

	/* valor inicial */	
	data.input(INPUT_INITIAL);
	new_STR(myString, data.get());
	printf("%snew_STR(myString, %s\"%s\"%s);\n",
		STYLE_EXIT, STYLE_VALUE, data.get(), STYLE_EXIT
	);
	

	/* looping */
	while (!quit) {
		data.input(INPUT_USER);
		data.clear();
		data.lower();


		/* checando menu */
		if (
			strcmp(data.get(), "free") == 0 ||
			strcmp(data.get(), "quit") == 0 ||
			strcmp(data.get(), "exit") == 0 ||
			strcmp(data.get(), "q") == 0
		) {
			myString.free();
			printf("%smyString.free();", STYLE_EXIT);
			quit = 1;
		} else if (strcmp(data.get(), "get") == 0) {
			printf("%smyString.get();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.get()
			);
		} else if (strcmp(data.get(), "lower") == 0) {
			printf("%smyString.lower();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.lower()
			);
		} else if (strcmp(data.get(), "upper") == 0) {
			printf("%smyString.upper();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.upper()
			);
		} else if (strcmp(data.get(), "title") == 0) {
			printf("%smyString.title();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.title()
			);
		} else if (strcmp(data.get(), "trim") == 0) {
			printf("%smyString.trim();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.trim()
			);
		} else if (strcmp(data.get(), "rtrim") == 0) {
			printf("%smyString.rtrim();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.rtrim()
			);
		} else if (strcmp(data.get(), "ltrim") == 0) {
			printf("%smyString.ltrim();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.ltrim()
			);
		} else if (strcmp(data.get(), "clear") == 0) {
			printf("%smyString.clear();\n%s\"%s\"",
				STYLE_EXIT, STYLE_VALUE, myString.clear()
			);
		} else if (strcmp(data.get(), "len") == 0) {
			printf("%smyString.len();\n%s%d ",
				STYLE_EXIT, STYLE_VALUE, myString.len()
			);
		} else if (strcmp(data.get(), "print") == 0) {
			printf("%smyString.print();\n", STYLE_EXIT);
			myString.print();
		} else if (strcmp(data.get(), "set") == 0) {
			data.input(INPUT_SET);
			printf("%smyString.set(%s\"%s\"%s);\n%s\"%s\"",
				STYLE_EXIT, 
				STYLE_VALUE,
				data.get(),
				STYLE_EXIT,
				STYLE_VALUE,
				myString.set(data.get())
			);
		} else if (strcmp(data.get(), "add") == 0) {
			data.input(INPUT_ADD);
			printf("%smyString.add(%s\"%s\"%s);\n%s\"%s\"",
				STYLE_EXIT, 
				STYLE_VALUE,
				data.get(),
				STYLE_EXIT,
				STYLE_VALUE,
				myString.add(data.get())
			);
		} else if (strcmp(data.get(), "input") == 0) {
			int check;
			data.input(INPUT_INPUT);
			printf("%smyString.input(%s\"%s\"%s);\n%s",
				STYLE_EXIT, 
				STYLE_VALUE,
				data.get(),
				STYLE_EXIT,
				STYLE_DEFAULT
			);
			check = myString.input(data.get());
			printf("%s%d", STYLE_VALUE, check);
		} else if (strcmp(data.get(), "fget") == 0) {
			data.input(INPUT_FILE);
			printf("%smyString.fget(%s\"%s\"%s);\n%s%d",
				STYLE_EXIT, 
				STYLE_VALUE,
				data.get(),
				STYLE_EXIT,
				STYLE_VALUE,
				myString.fget(data.get())
			);
		} else if (strcmp(data.get(), "fset") == 0) {
			data.input(INPUT_FILE);
			printf("%smyString.fset(%s\"%s\"%s);\n%s%d",
				STYLE_EXIT, 
				STYLE_VALUE,
				data.get(),
				STYLE_EXIT,
				STYLE_VALUE,
				myString.fset(data.get())
			);
		}
		else {
			int j = 0;
			char *methods[] = {
				"free",
				"get",
				"set",
				"add",
				"ltrim",
				"rtrim",
				"trim",
				"clear",
				"lower",
				"upper",
				"title",
				"len",
				"print",
				"input",
				"fget",
				"fset",
				NULL
			};
			printf(STYLE_VALUE);
			while(methods[j]) {
				if (methods[j+1] == NULL) {
					printf("%-10s", methods[j]);
					j = j + 1;
				} else if (methods[j+2] == NULL) {
					printf("%-10s%-10s", methods[j], methods[j+1]);
					j = j + 2;
				} else {
					printf("%-10s%-10s%-10s%s", 
						methods[j], methods[j+1], methods[j+2],
						(methods[j+2] ==  NULL ? "" : "\n")
					);
					j = j + 3;
				}
			}
		}
	}



	/* sair */
	data.free();
	attr.free();
	printf("\n\nPress enter to exit...");
	fgetc(stdin);
	puts(STYLE_RESET);
	system("clear");
	exit(0);
}
