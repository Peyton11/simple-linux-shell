# Simple Linux Shell

This project is a simple shell program that supports several built-in commands and allows execution of external programs.

## Compilation and Setup

Follow the steps below to compile the source code and run the shell:

### Build and Run the Shell Program

```bash
make build
```

This will compile the source code into an executable called simple-linux-shell.

```bash
make run
```
This target executes `ulimit -u 100` to set the user process limit and runs the shell.

Alternatively, you can compile the code with:
```bash
gcc -o simple-linux-shell simple-linux-shell.c
```

... and run the code with:
```bash
./simple-linux-shell
```

### Running the shell

The shell will display a prompt like:

```
<hostname> (<username>) |>
```

This indicates the shell is ready to accept commands.

## Commands

- C file1 file2: Copy; create file2, copy all bytes of file1 to file2 without deleting file1.

- D file: Delete the named file

- E comment: Echo; display comment on screen followed by a new line

- H: Help; display the user manual

- L: List the contents of the current directory

- M file: Make; create the named text file by launching a text editor

- P file: Print; display the contents of the named file on screen

- Q: Quit the shell

- W: Wipe; clear the screen

- X program: Execute the named program

## Functions

- parseCommand()
- printPrompt()
- readCommand()
- printHelp()
- main()

## Citations

- [https://stackoverflow.com/questions/27541910/how-to-use-execvp](https://stackoverflow.com/questions/27541910/how-to-use-execvp)

- Operating System Concepts, 8th Edition Abraham Silberschatz, Peter Baer Galvin, Greg Gagne

- Lecture notes
