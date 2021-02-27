#include "libctext.h"

/*-- Cores --*/
#define STYLE_RESET     "\e[0m"
#define STYLE_DEFAULT   "\e[0;0;37;44m"
#define STYLE_TITLE     "\e[0;1;34;47m"

#define STYLE_METHOD    "\e[0;0;37;44m"
#define STYLE_VALUE     "\e[0;3;33;44m"

#define STYLE_QUESTION  "\e[0;0;33;44m"
#define STYLE_GET_VALUE "\e[0;3;30;44m"

/*-- Comandos --*/
#define M_LINE "---------------------------------------------------------------"

#define MAIN_TITLE "LIBCTEXT EXAMPLE"

#define CLEAR_SCREEN \
	printf("%s\n", STYLE_DEFAULT); \
	//system("clear");

#define PRINT_TITLE \
	printf("%s%48s%32s%s\n\n", STYLE_TITLE, MAIN_TITLE, " ", STYLE_DEFAULT);

/*-- Protótipos --*/
int get_menu(char *action, char *output);

void get_value(char *msg, char *var);

void set_string(ctextObject *var, char *value);

void set_integer(ctextObject *var, int value);

void set_action(ctextObject *var, char *pre, char *attr);


/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {


	//teste
	
	new_STR(loko, "bunda");
	loko.print();
	loko.input("questão?\n");
	loko.print();
	loko.free();
















	/* variáveis locais */
	char input[81];   /* registra a entrada de dados do usuário */
	int  menu = 1;    /* registra a opção de menu */
	new_STR(act, ""); /* registra a última ação efetuada */
	new_STR(att, ""); /* registra o valor do atributo do máetodo */
	new_STR(out, ""); /* registra o valor da saída do método */

	/* início */
	CLEAR_SCREEN;
	get_value("Enter the initial value:", input);
	new_STR(myString, input);
	set_string(&att, input);
	set_action(&act, "new_STR(myString, ", att.get());


	/* looping menu */
	while (menu) {

		CLEAR_SCREEN;
		PRINT_TITLE;
		menu = get_menu(act.get(), out.get());
		
		switch(menu) {

			case 1:
				set_action(&act, "myString.get(", NULL);
				set_string(&out, myString.get());
				break;
			case 2:
				get_value("Enter the new value:", input);
				get_value("", input);
				set_string(&att, input);
				set_action(&act, "myString.set(", att.get());
				set_string(&out, myString.set(input));
				break;
			case 3:
				get_value("Enter additional text:", input);
				get_value("", input);
				set_string(&att, input);
				set_action(&act, "myString.add(", att.get());
				set_string(&out, myString.add(input));
				break;
			case 4:
				set_action(&act, "myString.ltrim(", NULL);
				set_string(&out, myString.ltrim());
				break;

			case 5:
				set_action(&act, "myString.rtrim(", NULL);
				set_string(&out, myString.rtrim());
				break;

			case 6:
				set_action(&act, "myString.trim(", NULL);
				set_string(&out, myString.trim());
				break;

			case 7:
				set_action(&act, "myString.clear(", NULL);
				set_string(&out, myString.clear());
				break;

			case 8:
				set_action(&act, "myString.lower(", NULL);
				set_string(&out, myString.lower());
				break;

			case 9:
				set_action(&act, "myString.upper(", NULL);
				set_string(&out, myString.upper());
				break;

			case 10:
				set_action(&act, "myString.title(", NULL);
				set_string(&out, myString.title());
				break;

			case 11:
				set_action(&act, "myString.len(", NULL);
				set_integer(&out, myString.len());
				break;

			case 12:
				set_action(&act, "myString.print(", NULL);
				out.set(myString.get());
				myString.print();
				get_value("Press enter to continue...", input);
				get_value("", input);
				break;
			case 13:
				get_value("Enter message text:", input);
				get_value("", input);
				set_string(&att, input);
				set_action(&act, "myString.input(", att.get());
				set_string(&out, (myString.input(input) == 0 ? "0" : "1"));
				break;
		}

	}

	/* saída */
	act.free();
	att.free();
	out.free();
	printf("%s\n", STYLE_RESET);
	system("clear");
	printf("\n%s\n", M_LINE);
	printf("myString.free();");
	printf("\n%s\n\n", M_LINE);
	exit(0);
}

/*----------------------------------------------------------------------------*/
int get_menu(char *action, char *output)
{

	/* variáveis locais */
	int value = 0;
	register int j = 0;
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

	/* looping do menu */
	while(methods[j]) {
		if (methods[j+1] == NULL) {
			printf("%3d) %-10s\n", j, methods[j]);
			j++;
		} else {
			printf("%3d) %-10s %25d) %-10s\n", j, methods[j], j+1, methods[j+1]);
			j = j + 2;
		}
	}

	/* imprimindo a última ação */
	printf("\n%s\n", M_LINE);
	printf(" %s\n %s", action, output);
	printf("\n%s\n", M_LINE);

	/* obtendo o valor */
	printf("\n%s %s %s", STYLE_QUESTION, "Choose the method:", STYLE_GET_VALUE);
	scanf("%d", &value);
	printf("%s", STYLE_DEFAULT);
	
	return (value >= 0 && value < j ? value : -1);
};



/*----------------------------------------------------------------------------*/
void get_value(char *msg, char *var) {
	printf("%s %s %s", STYLE_QUESTION, msg, STYLE_GET_VALUE);
	
	fgets(var, 7, stdin);

	printf("tamanho: %ld, last: %c (%s)\n", strlen(var), var[strlen(var)-1], var);

	if (var[0] == '\n') {printf(">string vazia\n");
		var[0] = '\0';
	} else if (var[strlen(var)-1] == '\n') {printf(">string com quebra\n");
		var[strlen(var)-1] = '\0';
	}
	printf("%s", STYLE_DEFAULT);
}

/*----------------------------------------------------------------------------*/
void set_string(ctextObject *var, char *value)
{
	var->set(STYLE_VALUE);
	var->add("\"");
	var->add(value);
	var->add("\"");
	var->add(STYLE_DEFAULT);
}

/*----------------------------------------------------------------------------*/
void set_integer(ctextObject *var, int value)
{
	char number[80];
	sprintf(number, "%d", value);
	var->set(STYLE_VALUE);
	var->add(number);
	var->add(STYLE_DEFAULT);
}

/*----------------------------------------------------------------------------*/
void set_action(ctextObject *var, char *pre, char *attr)
{
	var->set(STYLE_METHOD);
	var->add(pre);
	if (attr != NULL) {
		var->add(attr);
		var->add(STYLE_METHOD);
	}
	var->add(");");
	var->add(STYLE_DEFAULT);
}

