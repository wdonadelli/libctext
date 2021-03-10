#include "libctext.h"

/*-- Cores --*/
#define STYLE_RESET   "\e[0m"         /* limpa a formatação */
#define STYLE_DEFAULT "\e[0;0;37;44m" /* estilo principal */
#define STYLE_TITLE   "\e[0;1;34;47m" /* estilo do título */
#define STYLE_METHOD  "\e[0;0;37;44m" /* estilo da aplicaçãop */
#define STYLE_VALUE   "\e[0;3;33;44m" /* estilo do valor */
#define STYLE_PROMPT  "\e[0;0;33;44m" /* estilo do questionamento */

/*-- Frases --*/
#define INPUT_INITIAL STYLE_PROMPT "Initial value: " STYLE_VALUE
#define INPUT_USER    STYLE_DEFAULT "\n>"
#define INPUT_SET     STYLE_PROMPT "New value: " STYLE_VALUE
#define INPUT_ADD     STYLE_PROMPT "Addition value: " STYLE_VALUE
#define INPUT_FILE    STYLE_PROMPT "File path: " STYLE_VALUE
#define INPUT_INPUT   STYLE_PROMPT "Message: " STYLE_VALUE
#define INPUT_CHECK   STYLE_PROMPT "Text to check: " STYLE_VALUE

/*-- Complementos --*/
#define MAIN "myString"

#define QUOTES(VALUE)\
	STYLE_VALUE "\"" #VALUE "\"" STYLE_DEFAULT

#define METHOD(NAME)\
	STYLE_METHOD NAME() STYLE_DEFAULT

#define METHOD(NAME, ATTR) STYLE_METHOD #MAIN.#NAME#(QUOTES(ATTR)STYLE_METHOD); STYLE_DEFAULT

/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {

	/* variáveis locais */
	int quit = 0;
	new_String(data, ""); /* registra a entrada de dados do usuário */
	new_String(attr, ""); /* registra o valor do atributo do método */

	/* iniciar */
	puts(STYLE_DEFAULT);
	//system("clear"); /* limpar tela */
	printf("%s%48s%32s%s\n\n", STYLE_TITLE, "LIBCTEXT EXAMPLE", " ", STYLE_DEFAULT);

	/* valor inicial */	
	data.read(INPUT_INITIAL);
	new_String(myString, data.get());
	printf("%snew_String(myString, %s\"%s\"%s);\n",
		STYLE_METHOD, STYLE_VALUE, data.get(), STYLE_METHOD
	);

	/* looping */
	while (!quit) {
		data.read(INPUT_USER);
		data.clear();
		data.lower();

		/* checando menu */
		if (
			data.match("free") ||
			data.match("quit") ||
			data.match("exit") ||
			data.match("q")
		) {
			myString.free();
			printf("%smyString.free();", STYLE_METHOD);
			quit = 1;
		} else if (data.match("get")) {
			printf("%s\n%s",
				METHOD("get"), QUOTES(myString.get())
			);
		} else if (data.match("lower")) {
			printf("%smyString.lower();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.lower()
			);
		} else if (data.match("upper")) {
			printf("%smyString.upper();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.upper()
			);
		} else if (data.match("title")) {
			printf("%smyString.title();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.title()
			);
		} else if (data.match("trim")) {
			printf("%smyString.trim();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.trim()
			);
		} else if (data.match("rtrim")) {
			printf("%smyString.rtrim();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.rtrim()
			);
		} else if (data.match("ltrim")) {
			printf("%smyString.ltrim();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.ltrim()
			);
		} else if (data.match("clear")) {
			printf("%smyString.clear();\n%s\"%s\"",
				STYLE_METHOD, STYLE_VALUE, myString.clear()
			);
		} else if (data.match("len")) {
			printf("%smyString.len();\n%s%ld ",
				STYLE_METHOD, STYLE_VALUE, myString.len()
			);
		} else if (data.match("write")) {
			printf("%smyString.write();\n", STYLE_METHOD);
			printf("%s%d", STYLE_VALUE, myString.write());
		} else if (data.match("set")) {
			data.read(INPUT_SET);
			printf("%smyString.set(%s\"%s\"%s);\n%s\"%s\"",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.set(data.get())
			);
		} else if (data.match("add")) {
			data.read(INPUT_ADD);
			printf("%smyString.add(%s\"%s\"%s);\n%s\"%s\"",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.add(data.get())
			);
		} else if (data.match("read")) {
			int check;
			data.read(INPUT_INPUT);
			printf("%smyString.read(%s\"%s\"%s);\n%s",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_DEFAULT
			);
			check = myString.read(data.get());
			printf("%s%d", STYLE_VALUE, check);
		} else if (data.match("fwrite")) {
			data.read(INPUT_FILE);
			printf("%smyString.fwrite(%s\"%s\"%s);\n%s%d",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.fwrite(data.get())
			);
		} else if (data.match("fread")) {
			data.read(INPUT_FILE);
			printf("%smyString.fread(%s\"%s\"%s);\n%s%d",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.fread(data.get())
			);
		} else if (data.match("match")) {
			data.read(INPUT_CHECK);
			printf("%smyString.match(%s\"%s\"%s);\n%s%d",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.match(data.get())
			);
		} else if (data.match("index")) {
			data.read(INPUT_CHECK);
			printf("%smyString.index(%s\"%s\"%s);\n%s%ld",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.index(data.get())
			);
		} else if (data.match("replace")) {
			data.read(INPUT_CHECK);
			attr.read(INPUT_CHECK);
			printf("%smyString.replace(%s\"%s\"%s, %s\"%s\"%s);\n%s%d",
				STYLE_METHOD, 
				STYLE_VALUE,
				data.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				attr.get(),
				STYLE_METHOD,
				STYLE_VALUE,
				myString.replace(data.get(), attr.get())
			);
		} else {
			int j = 0;
			char *methods[] = {
				"get",
				"set",
				"add",

				"write",
				"read",

				"fwrite",
				"fread",

				"ltrim",
				"rtrim",
				"trim",
				"clear",
				"lower",
				"upper",
				"title",

				"len",
				"match",
				"index",
				"replace",
				"free",
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
