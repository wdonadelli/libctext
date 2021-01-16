#include "libctext.h"

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

	/* definindo variável temporária */
	char *temp;
	temp = self->_string;

	/* buscando valores imprimíveis a partir do início */
	while (*temp) {
		if (*temp > 32) {break;} else {temp++;}
	}

	return self->set(temp);
}
/*----------------------------------------------------------------------------*/

char *__ctext_rtrim__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variável temporária e um contador*/
	char *temp;
	int   count;
	temp  = self->_string;
	count = strlen(temp);

	/* acrescentando nulos ao final se valor não imprimível */
	while (count > 0 && temp[count-1] <= 32) {
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

	/* definindo variáveis temporárias e um identificador */
/*	char *left;
	char *right;
	left  = self->_string;
	right = self->_string;*/	


	return self->get();
}
/*----------------------------------------------------------------------------*/

char *__ctext_add__ (ctextObject *self, char *str)
{
	/* definindo variável temporária */
	char *temp;
	temp = self->_string;

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

int __ctext_len__ (ctextObject *self)
{
	return self->_string == NULL ? 0 : strlen(self->_string);
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
