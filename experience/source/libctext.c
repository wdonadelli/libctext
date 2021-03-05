#include "libctext.h"

/* Mensagem de erro na alocação de memória */
#define MEMORY_ERROR "Memory allocation error!"

/* Checa a memória alocada e sai em caso de erro */
#define CHECK_MEMORY(VAR) if (VAR == NULL) {puts(MEMORY_ERROR); exit(1);}

/* Aloca memória de caracteres e checa o resultado */
#define STR_SET_MEMORY(VAR,LEN) \
	VAR = malloc((LEN + 1) * sizeof(char)); \
	CHECK_MEMORY(VAR)

static char _ctext_case(char value, int type)
/* Devolve a caixa solicitada do caractere, type: 0 lowercase, 1 uppercase */
{
	/* variáveis locais e valores iniciais */
	char _upper[] = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞŸ";
	char _lower[] = "àáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ";
	char *upper   = _upper;
	char *lower   = _lower;

	/* verificando tabelas */
	if (value >= 0 && value <= 255) {/* tabela ASCII (padrão) */
		value = type == 0 ? tolower(value) : toupper(value);
	} else { /* verificação manual (latim) */
		while (*upper && *lower) {
			if (type == 0 && value == *upper) {
				value = lower[0];
				break;
			} else if (type != 0 && value == *lower) {
				value = upper[0];
				break;
			}
			upper++;
			lower++;
		}
	}

	return value;
}
/*----------------------------------------------------------------------------*/

/*= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

char *__ctext_set__ (ctextObject *self, char *str)
{

	/* definir apenas se o valor de str for diferente de NULL */
	if (str != NULL) {

		/* alocando memória */
		STR_SET_MEMORY(self->_string, strlen(str));

		/* definindo valor de _string */
		strcpy(self->_string, str);
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__ctext_get__ (ctextObject *self)
{
	return self->_string == NULL ? "" : self->_string;
}

/*----------------------------------------------------------------------------*/

char *__ctext_add__ (ctextObject *self, char *str)
{
	/* definindo variáveis locais*/
	char *temp = self->_string;

	/* definir apenas se o valor de str for diferente de NULL */
	if (str != NULL) {

		/* alocando memória */
		STR_SET_MEMORY(self->_string, strlen(str) + strlen(temp));

		/* definindo valor de _string */
		strcpy(self->_string, temp);
		strcat(self->_string, str);
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

int __ctext_write__ (ctextObject *self)
{
	/* definindo variáveis locais e valores iniciais */
	int check;

	/* imprimindo */
	check = puts(self->_string == NULL ? "" : self->_string);
	if (check < 0 || check == EOF) {return 1;}

	return 0;
}

/*----------------------------------------------------------------------------*/

int __ctext_read__ (ctextObject *self, char *msg)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return 1;}

	/* definindo variáveis locais e valores iniciais */
	char temp[2];
	char c;
	strcpy(temp, "");

	/* exibindo a mensagem */
	printf("%s", msg);

	/* obtendo caracteres */
	self->set("");
	while((c = fgetc(stdin)) != '\n') {
		if (ferror(stdin)) {return 2;}
		temp[0] = c;
		self->add(temp);
	}

	return 0;
}

/*----------------------------------------------------------------------------*/

int __ctext_fwrite__ (ctextObject *self, char *file)
{
	/* verificando memória alocada */
	if (self->_string == NULL || file == NULL) {return 1;}

	/* definindo variáveis locais e valores iniciais */
	FILE *path;
	int check;

	/* Tentando abri o arquivo para leitura */
	if ((path = fopen(file, "w")) == NULL) {return 2;}

	/* escrevendo caracteres */
	check = fputs(self->_string, path);
	if (check < 0 || check == EOF) {return 3;}

	/* fechando arquivo */
	if (fclose(path) != 0) {return 4;};

	return 0;
}

/*----------------------------------------------------------------------------*/

int __ctext_fread__ (ctextObject *self, char *file)
{
	/* verificando memória alocada */
	if (self->_string == NULL || file == NULL) {return 1;}

	/* definindo variáveis locais e valores iniciais */
	FILE *path;
	char temp[2];
	char c;
	strcpy(temp, "");

	/* Tentando abri o arquivo para leitura */
	if ((path = fopen(file, "r")) == NULL) {return 2;}

	/* obtendo caracteres */
	self->set("");
	while((c = fgetc(path)) != EOF) {
		if (ferror(path)) {return 3;}
		temp[0] = c;
		self->add(temp);
	}

	/* fechando arquivo */
	if (fclose(path) != 0) {return 4;};
	
	return 0;
}

/*----------------------------------------------------------------------------*/

char *__ctext_ltrim__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variáveis locais*/
	char *temp = self->_string;

	/* buscando valores imprimíveis a partir do início */
	while (*temp) {
		if (*temp < 0 || *temp > 32) {break;} else {temp++;}
	}

	return self->set(temp);
}

/*----------------------------------------------------------------------------*/

char *__ctext_rtrim__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variáveis locais*/
	char *temp = self->_string;
	int  count = strlen(temp);

	/* acrescentando nulos ao final se valor não imprimível */
	while (count > 0 && temp[count-1] >= 0 && temp[count-1] <= 32) {
		temp[count-1] = '\0';
		count = strlen(temp);
	}

	return self->set(temp);
}

/*----------------------------------------------------------------------------*/

char *__ctext_trim__ (ctextObject *self)
{
	self->ltrim();
	self->rtrim();
	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__ctext_clear__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* pré-requisito */
	self->trim();

	/* definindo variáveis locais*/
	char *temp = self->_string;
	int  space = 0;
	char str[(strlen(self->_string)+1)];
	strcpy(str, "");

	while (*temp) {
		if (*temp > 32 || *temp < 0) {
			/* se não for vazio, adicionar caractere à variável str */
			str[strlen(str)+1] = '\0';
			str[strlen(str)]   = temp[0];
			space = 0;
		} else if (space == 0){
			/* se for vazio, mas o anterior não, adicionar espaço à variável str */
			str[strlen(str)+1] = '\0';
			str[strlen(str)] = ' ';
			space = 1;
		}
		temp++;
	}

	return self->set(str);
}

/*----------------------------------------------------------------------------*/

char *__ctext_lower__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variáveis locais*/
	char *temp = self->_string;

	while (*temp) {
		temp[0] = _ctext_case(*temp, 0);
		temp++;
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__ctext_upper__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variáveis locais*/
	char *temp = self->_string;

	while (*temp) {
		*temp = _ctext_case(*temp, 1);
		temp++;
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__ctext_title__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* pré-requisito */
	self->lower();

	/* definindo variáveis locais*/
	char *temp = self->_string;
	int  empty = 1;
	int  ascii = 1;

	while (*temp) {
		if (*temp <= 32 && *temp >= 0) {
			/* não imprimíveis */
			empty = 1;
			ascii = 1;
		} else if (*temp > 32 && *temp <= 255 && empty == 1) {
			/* não imprimíveis ascii (padrão) */
			*temp = _ctext_case(*temp, 1);
			empty = 0;
			ascii = 1;
		} else if (empty == 1 && ascii == 1) {
			/* primeiro byte */
			*temp = _ctext_case(*temp, 1);
			ascii = 0;
		} else if (empty == 1 && ascii == 0) {
			/* segundo byte */
			*temp = _ctext_case(*temp, 1);
			empty = 0;
		}
		temp++;
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

int __ctext_len__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return 0;}

	/* definindo variáveis locais*/
	float len  = 0;
	char *temp = self->_string;

	while(*temp) {
		len += (*temp >= 0 && *temp <= 255) ? 1 : 0.5;
		temp++;
	}

	return (int)len;
}

/*----------------------------------------------------------------------------*/

void __ctext_free__ (ctextObject *self)
{
	if (self->_string != NULL) {
		free(self->_string);
	}
}
