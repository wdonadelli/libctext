#include "libctext.h"

#define MAXLEN 13
#define C_RESET  "\e[0m"
#define C_BASE   "\e[0;0;37;44m"
#define C_ACTION "\e[0;0;33;44m"
#define C_ENTER  "\e[0;0;32;44m"
#define C_TITLE  "\e[0;1;37;44m"
#define C_METHOD "\e[0;3;32;44m"
#define C_RETURN "\e[0;3;33;44m"

int main(int argc, char *argv[]) {

	/* variáveis locais */
	char input[81];
	int  menu = 1;
	char items[MAXLEN][10] = {
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
		"print"
	};


	/* definindo string inicial */
	printf("%s\n", C_BASE);
	system("clear");
	printf("%sEnter the initial value: %s", C_ACTION, C_ENTER);
	fflush(stdin);
	gets(input);
	new_STR(string, input);

	/* looping menu */
	while (menu) {

		system("clear");
		printf("%s>>> LIBCTEXT EXAMPLE <<<\n%s\n", C_TITLE, C_BASE);

		for (int i = 0; i < MAXLEN; i++) {
			printf("%d) %s\n", i,  items[i]);
		}

		fflush(stdin);	
		printf("\n%sChoose the method to be executed: %s", C_ACTION, C_ENTER);
		scanf("%d", &menu);

		printf("%s\n", C_BASE);
	
		switch(menu) {

			case 0:
				printf("%sstring.free()%s", C_METHOD, C_BASE);
				break;

			case 1:
				printf("%sstring.get();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.get(), C_BASE);
				break;
		
			case 2:
				printf("%sEnter the new value: %s", C_ACTION, C_ENTER);
				fflush(stdin);
				gets(input);
				fflush(stdin);
				gets(input);
				printf("%sstring.set(\"%s\");\n%s\"%s\"%s", C_METHOD, input, C_RETURN, string.set(input), C_BASE);
				break;
		
			case 3:
				printf("%sstring.add();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.get(), C_BASE);
				break;
		
			case 4:
				printf("%sstring.ltrim();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.ltrim(), C_BASE);
				break;
		
			case 5:
				printf("%sstring.rtrim();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.rtrim(), C_BASE);
				break;

			case 6:
				printf("%sstring.trim();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.trim(), C_BASE);
				break;

			case 7:
				printf("%sstring.clear();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.clear(), C_BASE);
				break;

			case 8:
				printf("%sstring.lower();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.lower(), C_BASE);
				break;

			case 9:
				printf("%sstring.upper();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.upper(), C_BASE);
				break;

			case 10:
				printf("%sstring.title();\n%s\"%s\"%s", C_METHOD, C_RETURN, string.title(), C_BASE);
				break;

			case 11:
				printf("%sstring.len();\n%s%d%s", C_METHOD, C_RETURN, string.len(), C_BASE);
				break;

			case 12:
				printf("%sstring.print();\n%s", C_METHOD, C_BASE);
				string.print();
				break;
		}

		/*aguardar um enter*/
		if (menu >= 0 && menu < MAXLEN) {
			printf("\n\nPress enter to continue...");
			fflush(stdin);
			getchar();
			getchar();
		}

	}

	/* saída */
	string.free();
	fflush(stdin);
	printf("%s\n", C_RESET);
	system("clear");
	exit(0);
}
