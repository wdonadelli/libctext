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
	#include <stdarg.h>
	#include <string.h>

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
		ctextObject (*set)();   /* define uma string */
		ctextObject (*ltrim)(); /* apara o lado esquerdo */
		ctextObject (*rtrim)(); /* apara o lado direito */
		ctextObject (*trim)();  /* apara ambos os lados */
		ctextObject (*clear)(); /* remove os espaços extras */
		ctextObject (*add)();   /* acrescenta string */
		ctextObject (*print)(); /* imprimi a string na tela */
		ctextObject (*lower)(); /* caixa baixa */
		ctextObject (*upper)(); /* caixa alta */
		ctextObject (*title)(); /* caixa alta apenas na letras iniciais */

		int (*len)();   /* devolve o tamanho da string */
		char *(*get)(); /* retorna a string */
		void (*free)(); /* libera memória */
	} ctextObject;

/*-----------------------------------------------------------------------------
	__ctext_set__ ()
		Define o valor da string
		str: valor da string a ser definida
-----------------------------------------------------------------------------*/
	int __ctext_set__ (ctextObject *self, char *str);

	#define __CTEXT_SQL__(SELF)                    \
		ctextObject __ctext_set__##SELF (char *str) \
		{                                           \
			__ctext_set__(&SELF, str);               \
			return SELF;                             \
		}                                           \
		SELF.set = __ctext_set__##SELF;             \

/*-----------------------------------------------------------------------------
	__ctext_ltrim__ ()
		Elimina os espaços à esquerda
-----------------------------------------------------------------------------*/
	int __ctext_ltrim__ (ctextObject *self);

	#define __CTEXT_LTRIM__(SELF)           \
		ctextObject __ctext_ltrim__##SELF () \
		{                                    \
			__ctext_ltrim__(&SELF);           \
			return SELF;                      \
		}                                    \
		SELF.ltrim = __ctext_ltrim__##SELF;  \

/*-----------------------------------------------------------------------------
	__ctext_rtrim__ ()
		Elimina os espaços à direita
-----------------------------------------------------------------------------*/
	int __ctext_rtrim__ (ctextObject *self);

	#define __CTEXT_RTRIM__(SELF)           \
		ctextObject __ctext_rtrim__##SELF () \
		{                                    \
			__ctext_rtrim__(&SELF);           \
			return SELF;                      \
		}                                    \
		SELF.rtrim = __ctext_rtrim__##SELF;  \

/*-----------------------------------------------------------------------------
	__ctext_trim__ ()
		Elimina os espaços à esquerda e à direita
-----------------------------------------------------------------------------*/
	int __ctext_trim__ (ctextObject *self);

	#define __CTEXT_TRIM__(SELF)           \
		ctextObject __ctext_trim__##SELF () \
		{                                   \
			return __ctext_trim__(&SELF);    \
			return SELF;                     \
		}                                   \
		SELF.trim = __ctext_trim__##SELF;   \

/*-----------------------------------------------------------------------------
	__ctext_clear__ ()
		Elimina os espaços extras
-----------------------------------------------------------------------------*/
	int __ctext_clear__ (ctextObject *self);

	#define __CTEXT_CLEAR__(SELF)           \
		ctextObject __ctext_clear__##SELF () \
		{                                    \
			return __ctext_clear__(&SELF);    \
			return SELF;                      \
		}                                    \
		SELF.clear = __ctext_clear__##SELF;  \

/*-----------------------------------------------------------------------------
	__ctext_add__ ()
		Acrescenta a String ao fim
-----------------------------------------------------------------------------*/
	int __ctext_add__ (ctextObject *self);

	#define __CTEXT_ADD__(SELF)           \
		ctextObject __ctext_add__##SELF () \
		{                                  \
			return __ctext_add__(&SELF);    \
			return SELF;                    \
		}                                  \
		SELF.add = __ctext_add__##SELF;    \



/*
		int (*print)();
		int (*lower)();
		int (*upper)();
		int (*title)();
*/




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
	__ctext_len__ ()
		Retorna o tamanho da String do "objeto"
-----------------------------------------------------------------------------*/
	int __ctext_len__ (ctextObject *self);

	#define __CTEXT_LEN__(SELF)        \
		int __ctext_len__##SELF ()    \
		{                               \
			return __ctext_len__(&SELF); \
		}                               \
		SELF.len = __ctext_len__##SELF; \

/*-----------------------------------------------------------------------------
	__ctext_free__ ()
		libera memória
-----------------------------------------------------------------------------*/
	void __ctext_free__ (ctextObject *self);

	#define __CTEXT_FREE__(SELF)         \
		void __ctext_free__##SELF ()      \
		{                               \
			__ctext_free__(&SELF);  \
		}                               \
		SELF.free = __ctext_free__##SELF; \

/*-----------------------------------------------------------------------------
	new_CSR () construtor da estrutura
-----------------------------------------------------------------------------*/
	#define new_CSR(OBJECT, FILE) \
                                 \
		ctextObject OBJECT;		      \
		OBJECT.file    = FILE;     \
		OBJECT.message = NULL;     \
		OBJECT.code    = CSR_OK;   \
		OBJECT.print   = 1;        \
		OBJECT.row     = 0;        \
		OBJECT.len     = 0;        \
		OBJECT.data    = NULL;     \
		OBJECT.col     = NULL;     \
		OBJECT.val     = NULL;     \
		OBJECT.reader  = NULL;     \
                                 \
		__ctext_SQL__(OBJECT);       \
		__ctext_INSERT__(OBJECT);    \
		__ctext_REPLACE__(OBJECT);   \
		__ctext_UPDATE__(OBJECT);    \
		__ctext_DELETE__(OBJECT);    \
		__ctext_SELECT__(OBJECT);    \
		__ctext_CREATE__(OBJECT);    \
		__ctext_DROP__(OBJECT);      \
		__ctext_ADD__(OBJECT);       \
		__ctext_CLEAR__(OBJECT);     \
		__ctext_FETCH__(OBJECT);     \
		__ctext_STATUS__(OBJECT);    \
		__ctext_INFO__(OBJECT);      \
		__ctext_DEBUG__(OBJECT);     \
		__ctext_FREE__(OBJECT);      \

#endif
