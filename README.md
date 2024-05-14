# Minishell

The shell is a program that interacts with the user through a terminal or takes the input from a file and executes a sequence of commands that are passed to the Operating System. In this chapter you are going to learn how to write your own shell program.

# Shell Programas

# Parse Comillas Dobles ("") y Comillas Simples (''):

1. `readline`: Esta función se utiliza para leer una línea de entrada desde la terminal. Proporciona características como el historial de comandos y la edición de líneas.

2. `rl_clear_history`: Borra el historial de comandos que se ha acumulado utilizando la función `readline`.

3. `rl_on_new_line`: Esta función notifica a `readline` que se ha completado una nueva línea y que debe empezar a leer la entrada del usuario desde el principio.

4. `rl_replace_line`: Reemplaza la línea actual en la terminal con una nueva línea proporcionada como argumento.

5. `rl_redisplay`: Esta función redibuja la línea actual en la terminal. Se utiliza después de modificar la línea utilizando otras funciones de `readline`.

6. `add_history`: Agrega una línea al historial de comandos que se puede acceder y navegar utilizando `readline`.

7. `printf`: Imprime texto formateado en la salida estándar.

8. `malloc`: Reserva un bloque de memoria en el montículo.

9. `free`: Libera un bloque de memoria previamente asignado dinámicamente con `malloc`.

10. `write`: Escribe datos en un descriptor de archivo, como la salida estándar.

11. `access`: Comprueba si el usuario tiene permisos de acceso a un archivo.

12. `open`: Abre un archivo o crea uno nuevo si no existe.

13. `read`: Lee datos desde un archivo abierto.

14. `close`: Cierra un descriptor de archivo abierto.

15. `fork`: Crea un nuevo proceso hijo del proceso actual.

16. `wait`, `waitpid`, `wait3`, `wait4`: Se utilizan para esperar a que un proceso hijo termine y recopilar su estado de salida.

17. `signal`, `sigaction`, `kill`: Se utilizan para manejar señales del sistema, como SIGINT (interrupción de terminal) o SIGTERM (terminación).

18. `exit`: Termina la ejecución del programa actual y devuelve un valor de salida al sistema operativo.

19. `getcwd`, `chdir`: Se utilizan para obtener y cambiar el directorio de trabajo actual.

20. `stat`, `lstat`, `fstat`: Se utilizan para obtener información sobre archivos, como los permisos o el tamaño.

21. `unlink`: Elimina un archivo del sistema de archivos.

22. `execve`: Ejecuta un programa en el contexto del proceso actual.

23. `dup`, `dup2`: Duplica un descriptor de archivo.

24. `pipe`: Crea un par de descriptores de archivo conectados a través de una tubería.

25. `opendir`, `readdir`, `closedir`: Se utilizan para abrir, leer y cerrar directorios.

26. `strerror`, `perror`: Se utilizan para convertir códigos de error en cadenas de caracteres legibles.

27. `isatty`, `ttyname`, `ttyslot`: Se utilizan para obtener información sobre dispositivos de terminal.

28. `ioctl`: Controla el comportamiento de dispositivos de E/S, como terminales.

29. `getenv`: Obtiene el valor de una variable de entorno.

30. `tcsetattr`, `tcgetattr`: Configura y obtiene los atributos del terminal.

31. `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`: Se utilizan para interactuar con la base de datos de términos de la biblioteca de control de pantalla `termcap`. Estas funciones son utilizadas principalmente para controlar la terminal y realizar operaciones como obtener la capacidad de borrar la pantalla o mover el cursor.
