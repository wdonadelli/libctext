/*-----------------------------------------------------------------------------
Library CText (v0.0.0) <wdonadelli@gmail.com>

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

	/* -- Define a biblioteca -- */
	#define LIBRARY_CTEXT_H

	/* -- Define o nome do objeto -- */
	#define CTEXT_MAIN_TYPE NewTextObject

	/* -- Define os construtores dos métodos -- */

	/*: Método com retorno e sem atributo */
	#define CTEXT_NEW_TYPE_METHOD(SELF, NAME, TYPE) \
		SELF.NAME = NULL; \
		TYPE __NewTextObject_##NAME##_##SELF () { \
			return __NewTextObject_##NAME(&SELF); \
		} \
		SELF.NAME = __NewTextObject_##NAME##_##SELF;

	/*: Método com retorno e com um atributo */
	#define CTEXT_NEW_TYPE_ATTR_METHOD(SELF, NAME, TYPE, ATYPE, ATTR) \
		SELF.NAME = NULL; \
		TYPE __NewTextObject_##NAME##_##SELF (ATYPE ATTR) { \
			return __NewTextObject_##NAME(&SELF, ATTR); \
		} \
		SELF.NAME = __NewTextObject_##NAME##_##SELF;

	/*: Método com retorno e com dois atributos */
	#define CTEXT_NEW_TYPE_ATTRS_METHOD(SELF, NAME, TYPE, ATYPE, ATTR, ATYPE2, ATTR2) \
		SELF.NAME = NULL; \
		TYPE __NewTextObject_##NAME##_##SELF (ATYPE ATTR, ATYPE2 ATTR2) { \
			return __NewTextObject_##NAME(&SELF, ATTR, ATTR2); \
		} \
		SELF.NAME = __NewTextObject_##NAME##_##SELF;

	/*: Método sem e sem atributo */
	#define CTEXT_NEW_VOID_METHOD(SELF, NAME) \
		SELF.NAME = NULL; \
		void __NewTextObject_##NAME##_##SELF () { \
			__NewTextObject_##NAME(&SELF); \
		} \
		SELF.NAME = __NewTextObject_##NAME##_##SELF;

	/* -- Define o construtor da estrutura/objeto */
	#define new_String(OBJECT, INITIAL) \
		CTEXT_MAIN_TYPE OBJECT;	\
		OBJECT._string = NULL; \
\
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, set, char *, char *, str); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, get, char *); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, add, char *, char *, str); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, write, int); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, read, int, char *, msg); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, fwrite, int, char *, file); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, fread, int, char *, file); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, ltrim, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, rtrim, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, trim, char *);  \
		CTEXT_NEW_TYPE_METHOD(OBJECT, clear, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, lower, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, upper, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, title, char *); \
		CTEXT_NEW_TYPE_METHOD(OBJECT, len, long int); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, match, int, char *, str); \
		CTEXT_NEW_TYPE_ATTR_METHOD(OBJECT, index, long int, char *, str); \
		CTEXT_NEW_TYPE_ATTRS_METHOD(OBJECT, replace, int, char *, str1, char *, str2); \
		CTEXT_NEW_VOID_METHOD(OBJECT, free); \
\
		OBJECT._string = (char *) malloc(2 * sizeof(char)); \
		if (OBJECT._string == NULL) { \
			puts("Memory allocation error!"); \
			exit(1); \
		} \
		strcpy(OBJECT._string, ""); \
		if (INITIAL != NULL) {OBJECT.set(INITIAL);} \

/*-----------------------------------------------------------------------------
	Bibliotecas necessárias: FIXME precisa de tudo isso mesmo?
-----------------------------------------------------------------------------*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <locale.h>

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
		char *(*add)();   /* acrescenta string */

		int  (*write)();  /* escreve a string na entrada padrão */
		int  (*read)();   /* lê e define a string pela entrada padrão */

		int  (*fwrite)(); /* escreve a string em um arquivo */
		int  (*fread)();  /* Lê um arquivo e define a string pelo seu conteúdo */

		char *(*ltrim)(); /* apara o lado esquerdo */
		char *(*rtrim)(); /* apara o lado direito */
		char *(*trim)();  /* apara ambos os lados */
		char *(*clear)(); /* remove os espaços extras */
		char *(*lower)(); /* caixa baixa */
		char *(*upper)(); /* caixa alta */
		char *(*title)(); /* caixa alta apenas na letras iniciais */

		long int (*len)();   /* devolve o tamanho da string */
		long int (*index)(); /* informa a posição da substring */
		int   (*match)();             /* compara strings e diz se são iguais */
		int (*replace)();             /* informa a posição da substring */
		void  (*free)();              /* libera memória */
	} CTEXT_MAIN_TYPE;

/*-----------------------------------------------------------------------------
	__NewTextObject_set ()
		Define o valor da string
		str: valor da string a ser definida
		Retorna o valor da nova string
-----------------------------------------------------------------------------*/
	char * __NewTextObject_set (CTEXT_MAIN_TYPE *self, char *str);

/*-----------------------------------------------------------------------------
	__NewTextObject_get ()
		Retorna o valor da String
-----------------------------------------------------------------------------*/
	char *__NewTextObject_get (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_add ()
		Acrescenta a String ao fim
		str: string a ser adicionar ao final
		Retorna o valor da nova string
-----------------------------------------------------------------------------*/
	char *__NewTextObject_add (CTEXT_MAIN_TYPE *self, char *str);

/*-----------------------------------------------------------------------------
	__NewTextObject_write ()
		Imprime na tela a string
		Retorna um número diferente de zero se ocorreu um erro
-----------------------------------------------------------------------------*/
	int __NewTextObject_write (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_read ()
		Define o valor da string a partir da entrada padrão
		msg: Texto a ser exibido para obtenção dos dados
		Retorna um número diferente de zero se um erro ocorreu
-----------------------------------------------------------------------------*/
	int __NewTextObject_read (CTEXT_MAIN_TYPE *self, char *msg);

/*-----------------------------------------------------------------------------
	__NewTextObject_fwrite ()
		Atribui o valor da string a um arquivo
		file: Endereço do arquivo
		Retorna um número diferente de zero se um erro ocorreu
-----------------------------------------------------------------------------*/
	int __NewTextObject_fwrite (CTEXT_MAIN_TYPE *self, char *file);

/*-----------------------------------------------------------------------------
	__NewTextObject_fread ()
		Define o valor da string a partir do conteúdo do arquivo de texto
		file: Endereço do arquivo
		Retorna um número diferente de zero se um erro ocorreu
-----------------------------------------------------------------------------*/
	int __NewTextObject_fread (CTEXT_MAIN_TYPE *self, char *file);

/*-----------------------------------------------------------------------------
	__NewTextObject_ltrim ()
		Elimina os espaços à esquerda
-----------------------------------------------------------------------------*/
	char * __NewTextObject_ltrim (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_rtrim ()
		Elimina os espaços à direita
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_rtrim (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_trim ()
		Elimina os espaços à esquerda e à direita
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_trim (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_clear ()
		Elimina os espaços extras
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_clear (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_lower ()
		Caixa baixa
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_lower (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_upper ()
		Caixa alta
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_upper (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_title ()
		Primeira maiúscula apenas
		Retorna a string modificada
-----------------------------------------------------------------------------*/
	char *__NewTextObject_title (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_len ()
		Retorna o tamanho da String
-----------------------------------------------------------------------------*/
	long int __NewTextObject_len (CTEXT_MAIN_TYPE *self);

/*-----------------------------------------------------------------------------
	__NewTextObject_match ()
		Informa se a string do objeto é igual à sting informada
		str: string a ser comparada
		Retorna 0 para falso e 1 para verdadeiro
-----------------------------------------------------------------------------*/
	int __NewTextObject_match (CTEXT_MAIN_TYPE *self, char *str);

/*-----------------------------------------------------------------------------
	__NewTextObject_index ()
		Informa a posiçao da primeira ocorrência de uma substring
		str: substring a ser localizada
		Retorna -1 quando não encontrada ou a posição da substring
-----------------------------------------------------------------------------*/
	long int __NewTextObject_index (CTEXT_MAIN_TYPE *self, char *str);

/*-----------------------------------------------------------------------------
	__NewTextObject_replace ()
		Substitui a primeira ocorrência de uma substring por outra
		str1: substring a ser substituída
		str2: nova substring
		Retorna 0 em caso de sucesso
-----------------------------------------------------------------------------*/
	int __NewTextObject_replace (CTEXT_MAIN_TYPE *self, char *str1, char *str2);

/*-----------------------------------------------------------------------------
	__NewTextObject_free ()
		libera memória
-----------------------------------------------------------------------------*/
	void __NewTextObject_free (CTEXT_MAIN_TYPE *self);

#endif
