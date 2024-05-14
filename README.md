# Minishell

El shell es un programa que interactúa con el usuario a través de una terminal o toma la entrada de un archivo y ejecuta una secuencia de comandos que se pasan al Sistema Operativo. En este capítulo aprenderás a escribir tu propio programa de shell.

# Programas de Shell

## Análisis de Comillas Dobles ("") y Comillas Simples ('')

En Bash, las comillas dobles ("") y las comillas simples ('') tienen significados diferentes y afectan cómo el shell interpreta el contenido que está entre ellas.

### Comillas Dobles (""):

- Permite la expansión de variables: Dentro de las comillas dobles, Bash interpreta y expande las variables. Por ejemplo, si tienes una variable $VAR y la usas dentro de comillas dobles ("$VAR"), Bash sustituirá el valor de $VAR en la cadena.

- Permite la interpretación de algunos caracteres de escape: Dentro de las comillas dobles, Bash interpreta y procesa algunos caracteres de escape especiales, como \n para nueva línea o \t para tabulación.

**EJEMPLO:**

```bash
VAR="mundo"
echo "Hola $VAR"  # Salida: Hola mundo
```
### Comillas Simples (''):

- No permite la expansión de variables: Dentro de las comillas simples, Bash trata el contenido de manera literal y no expande ninguna variable.

- No interpreta caracteres de escape: Bash trata todos los caracteres dentro de las comillas simples como caracteres literales. No interpreta ni procesa ningún carácter de escape.

**EJEMPLO:**

```bash
VAR="mundo"
echo 'Hola $VAR'  # Salida: Hola $VAR
```
