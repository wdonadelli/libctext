#include "libctext.h"

/*-- Limpar tela --*/
#define CLEAR ((argc > 1 && strcmp(argv[1], "show") == 0) ? 0 : 1)
#define CLEAR_SCREEN if (CLEAR) system("clear");

/*-- Cores --*/
#define STYLE_RESET   "\e[0m"         /* limpa a formatação */
#define STYLE_DEFAULT "\e[0;0;37;44m" /* estilo principal */
#define STYLE_TITLE   "\e[0;1;34;47m" /* estilo do título */
#define STYLE_METHOD  "\e[0;2;37;44m" /* estilo da aplicaçãop */
#define STYLE_VALUE   "\e[0;3;33;44m" /* estilo do valor */
#define STYLE_PROMPT  "\e[0;0;32;44m" /* estilo do questionamento */

/*-- Frases --*/
#define INPUT_INITIAL STYLE_PROMPT "Initial value: " STYLE_VALUE
#define INPUT_USER    STYLE_DEFAULT "\n>"
#define INPUT_SET     STYLE_PROMPT "New value: " STYLE_VALUE
#define INPUT_ADD     STYLE_PROMPT "Addition value: " STYLE_VALUE
#define INPUT_FILE    STYLE_PROMPT "File path: " STYLE_VALUE
#define INPUT_INPUT   STYLE_PROMPT "Message: " STYLE_VALUE
#define INPUT_CHECK   STYLE_PROMPT "Text to check: " STYLE_VALUE
#define INPUT_OLD     STYLE_PROMPT "Text to replace: " STYLE_VALUE
#define INPUT_NEW     STYLE_PROMPT "Replacement text: " STYLE_VALUE

/*-- Complementos --*/
#define MAIN "myString"

#define VALUE(RETURN, TYPE) \
	printf( \
		( \
			TYPE == 'c' ? "%s\'%c\'" : ( \
			TYPE == 's' ? "%s\"%s\"" : ( \
			TYPE == 'd' ? "%s%d" : ( \
			TYPE == 'l' ? "\n%s%ld" : \
			"%s%s" ))) \
		), \
		STYLE_VALUE, RETURN \
	)


#define METHOD(NAME) \
	printf("%s%s.%s();\n", STYLE_METHOD, MAIN, NAME )

#define METHODI(NAME, ATTR) \
	printf("%s%s.%s(%s\"%s\"%s);\n", \
		STYLE_METHOD, MAIN, NAME, \
		STYLE_VALUE, ATTR, STYLE_METHOD \
	)

#define METHOD0(NAME, RETURN, TYPE) \
	printf( \
		( \
			TYPE == 'c' ? "%s%s.%s();\n%s\'%c\'%s" : ( \
			TYPE == 's' ? "%s%s.%s();\n%s\"%s\"%s" : ( \
			TYPE == 'd' ? "%s%s.%s();\n%s%d%s" : ( \
			TYPE == 'l' ? "%s%s.%s();\n%s%ld%s" : \
			              "%s%s.%s();\n%s%s%s" ))) \
		), \
		STYLE_METHOD, MAIN, NAME, STYLE_VALUE, RETURN, STYLE_DEFAULT\
	)
	
#define METHOD1(NAME, ATTR, RETURN, TYPE) \
	printf( \
		( \
			TYPE == 's' ? "%s%s.%s(%s\"%s\"%s);\n%s\"%s\"%s" : ( \
			TYPE == 'd' ? "%s%s.%s(%s\"%s\"%s);\n%s%d%s" : ( \
			TYPE == 'l' ? "%s%s.%s(%s\"%s\"%s);\n%s%ld%s" : \
			              "%s%s.%s(%s\"%s\"%s);\n%s%s%s" )) \
		), \
		STYLE_METHOD, MAIN, NAME, \
		STYLE_VALUE, ATTR, STYLE_METHOD, \
		STYLE_VALUE, RETURN, STYLE_DEFAULT \
	)

#define METHOD2(NAME, ATTR1, ATTR2, RETURN) \
	printf("%s%s.%s(%s\"%s\"%s, %s\"%s\"%s);\n%s\"%s\"", \
		STYLE_METHOD, MAIN, NAME, \
		STYLE_VALUE, ATTR1, STYLE_METHOD, \
		STYLE_VALUE, ATTR2, STYLE_METHOD, \
		STYLE_VALUE, RETURN \
	)


/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {

	/* variáveis locais */
	int quit = 0;
	new_String(data, ""); /* registra a entrada de dados do usuário */
	new_String(attr, ""); /* registra o valor do atributo do método */

	/* iniciar */
	puts(STYLE_DEFAULT);
	CLEAR_SCREEN;
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
			METHOD0("get", myString.get(), 's');
		} else if (data.match("lower")) {
			METHOD0("lower", myString.lower(), 's');
		} else if (data.match("upper")) {
			METHOD0("upper", myString.upper(), 's');
		} else if (data.match("title")) {
			METHOD0("title", myString.title(), 's');
		} else if (data.match("trim")) {
			METHOD0("trim", myString.trim(), 's');
		} else if (data.match("rtrim")) {
			METHOD0("rtrim", myString.rtrim(), 's');
		} else if (data.match("ltrim")) {
			METHOD0("ltrim", myString.ltrim(), 's');
		} else if (data.match("clear")) {
			METHOD0("clear", myString.clear(), 's');
		} else if (data.match("len")) {
			METHOD0("len", myString.len(), 'l');
		} else if (data.match("write")) {
			METHOD0("write", "", 'x');
			VALUE(myString.write(), 'd');
		} else if (data.match("set")) {
			data.read(INPUT_SET);
			METHOD1("set", data.get(), myString.set(data.get()), 's');
		} else if (data.match("add")) {
			data.read(INPUT_ADD);
			METHOD1("add", data.get(), myString.add(data.get()), 's');
		} else if (data.match("read")) {
			data.read(INPUT_INPUT);
			printf(STYLE_DEFAULT);
			METHOD1("read", data.get(), myString.read(data.get()), 'd');
		} else if (data.match("fwrite")) {
			data.read(INPUT_FILE);
			METHOD1("fwrite", data.get(), myString.fwrite(data.get()), 'd');
		} else if (data.match("fread")) {
			data.read(INPUT_FILE);
			METHOD1("fread", data.get(), myString.fread(data.get()), 'd');
		} else if (data.match("match")) {
			data.read(INPUT_CHECK);
			METHOD1("match", data.get(), myString.match(data.get()), 'd');
		} else if (data.match("index")) {
			data.read(INPUT_CHECK);
			METHOD1("index", data.get(), myString.index(data.get()), 'l');
		} else if (data.match("replace")) {
			data.read(INPUT_OLD);
			attr.read(INPUT_NEW);
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
	printf("%s\n\nPress enter to exit...", STYLE_DEFAULT);
	fgetc(stdin);
	puts("\a");
	puts(STYLE_RESET);
	CLEAR_SCREEN;
	exit(0);
}
