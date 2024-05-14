# Minishell

The shell is a program that interacts with the user through a terminal or takes input from a file and executes a sequence of commands that are passed to the Operating System. In this chapter, you are going to learn how to write your own shell program.

# Shell Programs

## Parsing Double Quotes ("") and Single Quotes ('')

In Bash, double quotes ("") and single quotes ('') have different meanings and affect how the shell interprets the content that is between them.

### Double Quotes (""):

- Allows variable expansion: Within double quotes, Bash interprets and expands variables. For example, if you have a variable $VAR and use it within double quotes ("$VAR"), Bash will substitute the value of $VAR in the string.

- Interprets some escape characters: Within double quotes, Bash interprets and processes some special escape characters, such as \n for newline or \t for tab.

**Example:**

```bash
VAR="world"
echo "Hello $VAR"  # Output: Hello world
