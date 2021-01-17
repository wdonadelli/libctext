/*-----------------------------------------------------------------------------
Library CText (v1.0.0) <wdonadelli@gmail.com>

	This is a library written in C language designed to work with character lists 
	(Strings) in a similar way to object-oriented programming.

GitHub:
	https://github.com/wdonadelli/libctext
	https://github.com/wdonadelli/libctext.wiki

GCC compilation:
	gcc -c libctext.c

-------------------------------------------------------------------------------
MIT License

Copyright (c) 2020 Willian Donadelli

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------*/

#ifndef LIBRARY_CTEXT_H

	#define LIBRARY_CTEXT_H

/*-----------------------------------------------------------------------------
	Bibliotecas necessárias: FIXME precisa de tudo isso mesmo?
-----------------------------------------------------------------------------*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <locale.h>

/*-----------------------------------------------------------------------------
	Macros de respostas:
-----------------------------------------------------------------------------*/
	#define CTEXT_OK  0
	#define CTEXT_ERR 1

/*-----------------------------------------------------------------------------
	Estrutura do objeto
-----------------------------------------------------------------------------*/
	typedef struct
	{
		/*-- Métodos/Atributos internos */
		char *_string; /* registra a String */

		/*-- Métodos/Atributos acessíveis ao usuário --*/
		char *(*set)();   /* define uma string */
		char *(*get)();   /* retorna a string */
		char *(*ltrim)(); /* apara o lado esquerdo */
		char *(*rtrim)(); /* apara o lado direito */
		char *(*trim)();  /* apara ambos os lados */
		char *(*clear)(); /* remove os espaços extras */
		char *(*add)();   /* acrescenta string */
		char *(*lower)(); /* caixa baixa */
		char *(*upper)(); /* caixa alta */
		char *(*title)(); /* caixa alta apenas na letras iniciais */

		int   (*len)();   /* devolve o tamanho da string */
		void  (*print)(); /* imprimi a string na tela */
		void  (*free)();  /* libera memória */
	} ctextObject;

/*-----------------------------------------------------------------------------
	__ctext_set__ ()
		Define o valor da string
		str: valor da string a ser definida
-----------------------------------------------------------------------------*/
	char * __ctext_set__ (ctextObject *self, char *str);

	#define __CTEXT_SET__(SELF)               \
		char * __ctext_set__##SELF (char *str) \
		{                                      \
			return __ctext_set__(&SELF, str);   \
		}                                      \
		SELF.set = __ctext_set__##SELF;        \

/*-----------------------------------------------------------------------------
	__ctext_get__ ()
		Retorna o valor da String do "objeto"
-----------------------------------------------------------------------------*/
	char *__ctext_get__ (ctextObject *self);

	#define __CTEXT_GET__(SELF)        \
		char *__ctext_get__##SELF ()    \
		{                               \
			return __ctext_get__(&SELF); \
		}                               \
		SELF.get = __ctext_get__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_ltrim__ ()
		Elimina os espaços à esquerda
-----------------------------------------------------------------------------*/
	char * __ctext_ltrim__ (ctextObject *self);

	#define __CTEXT_LTRIM__(SELF)          \
		char * __ctext_ltrim__##SELF ()     \
		{                                   \
			return __ctext_ltrim__(&SELF);   \
		}                                   \
		SELF.ltrim = __ctext_ltrim__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_rtrim__ ()
		Elimina os espaços à direita
-----------------------------------------------------------------------------*/
	char *__ctext_rtrim__ (ctextObject *self);

	#define __CTEXT_RTRIM__(SELF)          \
		char *__ctext_rtrim__##SELF ()      \
		{                                   \
			return __ctext_rtrim__(&SELF);   \
		}                                   \
		SELF.rtrim = __ctext_rtrim__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_trim__ ()
		Elimina os espaços à esquerda e à direita
-----------------------------------------------------------------------------*/
	char *__ctext_trim__ (ctextObject *self);

	#define __CTEXT_TRIM__(SELF)         \
		char *__ctext_trim__##SELF ()     \
		{                                 \
			return __ctext_trim__(&SELF);  \
		}                                 \
		SELF.trim = __ctext_trim__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_clear__ ()
		Elimina os espaços extras
-----------------------------------------------------------------------------*/
	char *__ctext_clear__ (ctextObject *self);

	#define __CTEXT_CLEAR__(SELF)          \
		char *__ctext_clear__##SELF ()      \
		{                                   \
			return __ctext_clear__(&SELF);   \
		}                                   \
		SELF.clear = __ctext_clear__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_add__ ()
		Acrescenta a String ao fim
		str: string a ser adicionar ao final
-----------------------------------------------------------------------------*/
	char *__ctext_add__ (ctextObject *self, char *str);

	#define __CTEXT_ADD__(SELF)              \
		char *__ctext_add__##SELF (char *str) \
		{                                     \
			return __ctext_add__(&SELF, str);  \
		}                                     \
		SELF.add = __ctext_add__##SELF;       \

/*-----------------------------------------------------------------------------
	__ctext_lower__ ()
		Caixa baixa
-----------------------------------------------------------------------------*/
	char *__ctext_lower__ (ctextObject *self);

	#define __CTEXT_LOWER__(SELF)          \
		char *__ctext_lower__##SELF ()      \
		{                                   \
			return __ctext_lower__(&SELF);   \
		}                                   \
		SELF.lower = __ctext_lower__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_upper__ ()
		Caixa alta
-----------------------------------------------------------------------------*/
	char *__ctext_upper__ (ctextObject *self);

	#define __CTEXT_UPPER__(SELF)          \
		char *__ctext_upper__##SELF ()      \
		{                                   \
			return __ctext_upper__(&SELF);   \
		}                                   \
		SELF.upper = __ctext_upper__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_title__ ()
		Primeira maiúscula apenas
-----------------------------------------------------------------------------*/
	char *__ctext_title__ (ctextObject *self);

	#define __CTEXT_TITLE__(SELF)          \
		char *__ctext_title__##SELF ()      \
		{                                   \
			return __ctext_title__(&SELF);   \
		}                                   \
		SELF.title = __ctext_title__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_len__ ()
		Retorna o tamanho da String do "objeto"
-----------------------------------------------------------------------------*/
	int __ctext_len__ (ctextObject *self);

	#define __CTEXT_LEN__(SELF)        \
		int __ctext_len__##SELF ()      \
		{                               \
			return __ctext_len__(&SELF); \
		}                               \
		SELF.len = __ctext_len__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_print__ ()
		Imprime na tela a string
-----------------------------------------------------------------------------*/
	void __ctext_print__ (ctextObject *self);

	#define __CTEXT_PRINT__(SELF)          \
		void __ctext_print__##SELF ()       \
		{                                   \
			__ctext_print__(&SELF);          \
		}                                   \
		SELF.print = __ctext_print__##SELF; \


/*-----------------------------------------------------------------------------
	__ctext_free__ ()
		libera memória
-----------------------------------------------------------------------------*/
	void __ctext_free__ (ctextObject *self);

	#define __CTEXT_FREE__(SELF)         \
		void __ctext_free__##SELF ()      \
		{                                 \
			__ctext_free__(&SELF);         \
		}                                 \
		SELF.free = __ctext_free__##SELF; \

/*-----------------------------------------------------------------------------
	new_CSR () construtor da estrutura
-----------------------------------------------------------------------------*/
	#define new_STR(OBJECT, STRING)              \
      setlocale(LC_ALL, "");                                          \
		ctextObject OBJECT;	                     \
		OBJECT._string = NULL;                    \
                                                \
		__CTEXT_SET__(OBJECT);                    \
		__CTEXT_GET__(OBJECT);                    \
		__CTEXT_LTRIM__(OBJECT);                  \
		__CTEXT_RTRIM__(OBJECT);                  \
		__CTEXT_TRIM__(OBJECT);                   \
		__CTEXT_CLEAR__(OBJECT);                  \
		__CTEXT_ADD__(OBJECT);                    \
		__CTEXT_LOWER__(OBJECT);                  \
		__CTEXT_UPPER__(OBJECT);                  \
		__CTEXT_TITLE__(OBJECT);                  \
		__CTEXT_LEN__(OBJECT);                    \
		__CTEXT_PRINT__(OBJECT);                  \
		__CTEXT_FREE__(OBJECT);                   \
                                                \
		OBJECT.set(STRING == NULL ? "" : STRING); \

#endif
