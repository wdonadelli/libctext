#include "libctext.h"

/*.............................................................................
	funções de cabeçalho
.............................................................................*/

char *__ctext_set__ (ctextObject *self, char *str)
{
	printf("definiu\n");
	return "oi";
}

char *__ctext_get__ (ctextObject *self)
{
	printf("obteve\n");
	return "oi";
}

char *__ctext_ltrim__ (ctextObject *self)
{
	printf("esquerda\n");
	return "oi";
}

char *__ctext_rtrim__ (ctextObject *self)
{
	printf("direita\n");
	return "oi";
}

char *__ctext_trim__ (ctextObject *self)
{
	printf("trim\n");
	return "oi";
}

char *__ctext_clear__ (ctextObject *self)
{
	printf("limpou\n");
	return "oi";
}






char *__ctext_add__ (ctextObject *self, char *str)
{
	printf("adicionou\n");
	return "oi";
}




/*...........................................................................*/
int __ctext_len__ (ctextObject *self)
{
	printf("tamanho\n");
	return 10;
}


void __ctext_print__ (ctextObject *self)
{
	printf("imprimiu\n");
}


void __ctext_free__ (ctextObject *self)
{
	printf("liberou\n");
}
