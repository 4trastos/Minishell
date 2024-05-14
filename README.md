# Minishell

The shell is a program that interacts with the user through a terminal or takes the input from a file and executes a sequence of commands that are passed to the Operating System. In this chapter you are going to learn how to write your own shell program.

# Shell Programas

# Parse Comillas Dobles ("") y Comillas Simples (''):

En Bash, las comillas dobles ("") y las comillas simples ('') tienen significados diferentes y afectan cómo el shell interpreta el contenido que está entre ellas.

'Comillas Dobles (""):'

* Permite la expansión de variables: Dentro de las comillas dobles, Bash interpreta y expande las variables. Por ejemplo, si tienes una variable $VAR y la usas dentro de comillas dobles ("$VAR"), Bash sustituirá el valor de $VAR en la cadena.
* Permite la interpretación de algunos caracteres de escape: Dentro de las comillas dobles, Bash interpreta y procesa algunos caracteres de escape especiales, como \n para nueva línea o \t para tabulación.

EJEMPLO:
+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+--+-+-+-+-+-+-+-+
|   VAR="world"                                 |
|   echo "Hello $VAR"  # Salida: Hello world    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Comillas Simples (''):
No permite la expansión de variables: Dentro de las comillas simples, Bash trata el contenido de manera literal y no expande ninguna variable.
No interpreta caracteres de escape: Bash trata todos los caracteres dentro de las comillas simples como caracteres literales. No interpreta ni procesa ningún carácter de escape.
bash
Copiar código
VAR="world"
echo 'Hello $VAR'  # Salida: Hello $VAR
En resumen, las comillas dobles permiten la expansión de variables y la interpretación de algunos caracteres de escape, mientras que las comillas simples evitan la expansión de variables y la interpretación de caracteres de escape, tratando todo el contenido de manera literal.
