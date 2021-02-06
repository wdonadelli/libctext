#include "libctext.h"


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
		self->_string = malloc(
			(strlen(str) + 1) * sizeof(char)
		);

		/* verificando problema na alocação da memória */
		if (self->_string == NULL) {
			printf("Memory allocation error!");
			exit(1);
		}

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

char *__ctext_add__ (ctextObject *self, char *str)
{
	/* definindo variáveis locais*/
	char *temp = self->_string;

	/* definir apenas se o valor de str for diferente de NULL */
	if (str != NULL) {

		/* alocando memória */
		self->_string = malloc(
			(strlen(str) + strlen(temp) + 1) * sizeof(char)
		);

		/* verificando problema na alocação da memória */
		if (self->_string == NULL) {
			printf("Memory allocation error!");
			exit(1);
		}

		/* definindo valor de _string */
		strcpy(self->_string, temp);
		strcat(self->_string, str);
	}

	return self->get();
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
void __ctext_print__ (ctextObject *self)
{
	printf("%s\n", (self->_string == NULL ? "" : self->_string));
}

/*----------------------------------------------------------------------------*/
void __ctext_free__ (ctextObject *self)
{
	if (self->_string != NULL) {
		free(self->_string);
	}
}
