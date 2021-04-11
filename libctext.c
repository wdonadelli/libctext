#include "libctext.h"

/* Mensagem de erro na alocação de memória */
#define MEMORY_ERROR "Memory allocation error!"

/* Checa a memória alocada e sai em caso de erro */
#define CHECK_MEMORY(VAR) if (VAR == NULL) {puts(MEMORY_ERROR); exit(1);}

/* Aloca memória de caracteres e checa o resultado */
#define STR_SET_MEMORY(VAR, LEN) \
	if (strlen(VAR) != LEN) { \
		VAR = (char *) realloc(VAR, (LEN + 1) * sizeof(char)); \
		CHECK_MEMORY(VAR) \
	}




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

char *__NewTextObject_set (CTEXT_MAIN_TYPE *self, char *str)
{
	/* verificando memória alocada e atributo */
	if (self->_string == NULL || str == NULL) return self->get();

	/* alocando memória */
	STR_SET_MEMORY(self->_string, strlen(str));

	/* definindo valor de _string */
	if (!self->match(str)) {strcpy(self->_string, str);}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_get (CTEXT_MAIN_TYPE *self)
{
	return self->_string == NULL ? "" : self->_string;
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_add (CTEXT_MAIN_TYPE *self, char *str)
{
	/* verificando memória alocada e atributo */
	if (
		self->_string == NULL ||
		str == NULL ||
		strlen(str) == 0
	) return self->get();

	/* alocando memória */
	STR_SET_MEMORY(self->_string, (strlen(self->_string) + strlen(str)));

	/* definindo valor de _string */
	strcat(self->_string, str);

	return self->get();
}

/*----------------------------------------------------------------------------*/

int __NewTextObject_write (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return 1;

	/* definindo variáveis locais e valores iniciais */
	int check;

	/* imprimindo */
	check = puts(self->_string == NULL ? "" : self->_string);
	if (check < 0 || check == EOF) {return 2;}

	return 0;
}

/*----------------------------------------------------------------------------*/

int __NewTextObject_read (CTEXT_MAIN_TYPE *self, char *msg)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return 1;

	/* definindo variáveis locais e valores iniciais */
	char temp[2] = {'\0', '\0'};
	char c;

	/* exibindo a mensagem e zerando string*/
	printf("%s", msg);
	self->set("");

	/* obtendo caracteres */
	while((c = fgetc(stdin)) != '\n') {
		if (ferror(stdin)) {return 2;}
		temp[0] = c;
		self->add(temp);
	}

	return 0;
}

/*----------------------------------------------------------------------------*/

int __NewTextObject_fwrite (CTEXT_MAIN_TYPE *self, char *file)
{
	/* verificando memória alocada */
	if (self->_string == NULL || file == NULL) return 1;

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

int __NewTextObject_fread (CTEXT_MAIN_TYPE *self, char *file)
{
	/* verificando memória alocada */
	if (self->_string == NULL || file == NULL) return 1;

	/* definindo variáveis locais e valores iniciais */
	FILE *path;
	char temp[256+2];

	/* Tentando abri o arquivo para leitura e zerando string */
	if ((path = fopen(file, "r")) == NULL) {return 2;}
	self->set("");

	while (!feof(path)) {
		if (fgets(temp, 256, path)) self->add(temp);
		if (ferror(path)) return 3;
	}

	/* fechando arquivo */
	if (fclose(path) != 0) {return 4;};
	
	return 0;
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_ltrim (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* definindo variáveis locais*/
	char value[strlen(self->_string)+1], *temp;
	strcpy(value, self->_string);
	temp = value;

	/* buscando valores imprimíveis a partir do início */
	while (*temp) {
		if (*temp < 0 || *temp > 32) {break;} else {temp++;}
	}

	return self->set(temp);
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_rtrim (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* definindo variáveis locais*/
	char value[strlen(self->_string)+1], *temp;
	int  count;
	strcpy(value, self->_string);
	temp = value;
	count = strlen(self->_string);

	/* acrescentando nulos ao final se valor não imprimível */
	while (count > 0 && temp[count-1] >= 0 && temp[count-1] <= 32) {
		temp[count-1] = '\0';
		count = strlen(temp);
	}

	return self->set(temp);
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_trim (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* aparando */
	self->ltrim();
	self->rtrim();
	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_clear (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* pré-requisito */
	self->trim();

	/* definindo variáveis locais*/
	char value[strlen(self->_string)+1], *temp;
	int  space = 0;
	char str[(strlen(self->_string)+1)];
	strcpy(value, self->_string);
	strcpy(str, "");
	temp = value;

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

char *__NewTextObject_lower (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* definindo variáveis locais*/
	char *temp = self->_string;

	while (*temp) {
		temp[0] = _ctext_case(*temp, 0);
		temp++;
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_upper (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

	/* definindo variáveis locais*/
	char *temp = self->_string;

	while (*temp) {
		*temp = _ctext_case(*temp, 1);
		temp++;
	}

	return self->get();
}

/*----------------------------------------------------------------------------*/

char *__NewTextObject_title (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return self->get();

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

long int __NewTextObject_len (CTEXT_MAIN_TYPE *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return 0;

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

int __NewTextObject_match (CTEXT_MAIN_TYPE *self, char *str)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return 0;

	/* comparando */
	return (strcmp(self->_string, str) == 0) ? 1 : 0;
}

/*----------------------------------------------------------------------------*/

long int __NewTextObject_index (CTEXT_MAIN_TYPE *self, char *str)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return -1;

	/* variáveis locais */
	char *point;
	char *temp = self->_string;
	long int index = 0;
	point = strstr(temp, str);

	/* testes */
	if (str == NULL || point == NULL) {return -1;}

	while (strcmp(temp, point) != 0) {
		temp++;
		index++;
	}
	
	return index;
}

/*----------------------------------------------------------------------------*/

int __NewTextObject_replace (CTEXT_MAIN_TYPE *self, char *str1, char *str2)
{
	/* verificando memória alocada */
	if (self->_string == NULL) return 1;

	/* variáveis locais */
	long int lenght = strlen(self->_string);
	long int index  = self->index(str1);
	char temp1[lenght];
	char temp3[lenght];

	/* verificações */
	if (index < 0 || str2 == NULL) {return 2;}
	if (strcmp(str1, str2) == 0)   {return 0;}

	/* fragmentações */
	strcpy(temp1, self->_string);
	strcpy(temp3, &self->_string[index + strlen(str1)]);
	temp1[index] = '\0';

	/* manipulações */
	self->set(temp1);
	self->add(str2);
	self->add(temp3);

	return 0;
}

/*----------------------------------------------------------------------------*/

void __NewTextObject_free (CTEXT_MAIN_TYPE *self)
{
	if (self->_string != NULL) free(self->_string);
}

/*----------------------------------------------------------------------------*/
