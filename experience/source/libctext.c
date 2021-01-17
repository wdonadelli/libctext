#include "libctext.h"

typedef struct
{
	unsigned int isLower: 1;
	unsigned int isUpper: 1;
	char lower;
	char upper;
} _structChar;


static void _case(char vChar, _structChar *sChar) {

	/* variáveis locais e valores iniciais */
	char upper[] = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞŸ";
	char lower[] = "àáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ";
	sChar->isLower = 0;
	sChar->isUpper = 0;
	sChar->lower = vChar;
	sChar->upper = vChar;

	/* verificando casos */
	if (vChar >= 65 && vChar <= 90) {
		sChar->lower = tolower(vChar);
		sChar->isUpper = 1;
		return;
	} else if (vChar >= 97 && vChar <= 122) {
		sChar->upper = toupper(vChar);
		sChar->isLower = 1;
		return;
	} else {
		for (int i = 0; i < strlen(upper); i++) {
			if (upper[i] == vChar) {
				sChar->lower = lower[i];
				sChar->isUpper = 1;
				return;
			} else if (lower[i] == vChar) {
				sChar->upper = upper[i];
				sChar->isLower = 1;
				return;
			}
		}
	}
	return;
}





















char *__ctext_set__ (ctextObject *self, char *str)
{
	for (int i = 192; i < 256; i++) printf("----\n%d = %c\n", i, i);



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
	char *temp;
	char str[(strlen(self->_string)+1)];
	int  space;
	temp  = self->_string;
	space = 0;
	strcpy(str, "");

	while (*temp) {
		if (*temp > 32) {
			/* se não for vazio, adicionar */
			str[strlen(str)+1] = '\0';
			str[strlen(str)]   = temp[0];
			space = 0;
		} else if (space == 0){
			/* se for vazio, mas o anterior não, adcionar */
			str[strlen(str)+1] = '\0';
			str[strlen(str)] = temp[0];
			space = 1;
		}
		temp++;
	}

	return self->set(str);
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

char *__ctext_lower__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variável temporária e um contador*/
	char *temp;
	char str[(strlen(self->_string)+1)];
	temp = self->_string;
	strcpy(str, "");

	_structChar schar;


	/* alterando caixa */
	while (*temp) {
	
		_case(temp[0], &schar);
		
		printf("--------é fantástico\nLower/Upper: %d/%d | lower/upper: %c/%c\n", schar.isLower, schar.isUpper, 201, schar.upper);
		
	
		str[strlen(str)+1] = '\0';
		str[strlen(str)]   = tolower(temp[0]);
		temp++;
	}

	return self->set(str);
}
/*----------------------------------------------------------------------------*/

char *__ctext_upper__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variável temporária e um contador*/
	char *temp;
	char str[(strlen(self->_string)+1)];
	temp = self->_string;
	strcpy(str, "");

	/* alterando caixa */
	while (*temp) {
		str[strlen(str)+1] = '\0';
		str[strlen(str)]   = toupper(temp[0]);
		temp++;
	}

	return self->set(str);
}
/*----------------------------------------------------------------------------*/

char *__ctext_title__ (ctextObject *self)
{
	/* verificando memória alocada */
	if (self->_string == NULL) {return self->get();}

	/* definindo variável temporária e um contador*/
	char *temp;
	char str[(strlen(self->_string)+1)];
	int  space;
	temp = self->_string;
	strcpy(str, "");
	space = 1;

	/* alterando caixa */
	while (*temp) {
		str[strlen(str)+1] = '\0';
		str[strlen(str)]   = space == 0 ? tolower(temp[0]) : toupper(temp[0]);
		space = *temp <= 32 ? 1 : 0;
		temp++;
	}

	return self->set(str);
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
