// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed: Peyton Gardner Date: 3/2/2025

// 3460:426 Lab 1 - Basic C shell rev. 9/10/2020

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

 #include <stdio.h>
 #include <string.h>
 #include <unistd.h>
 #include <limits.h>
 #include <sys/wait.h>
 #include <stdlib.h>

 #define MAX_ARGS		64
 #define MAX_ARG_LEN		16
 #define MAX_LINE_LEN	80
 #define WHITESPACE		" ,\t\n"

 struct command_t {
    char *name;
    int argc;
    char *argv[MAX_ARGS];
 };

 /* Function prototypes */
 int parseCommand(char *, struct command_t *);
 void printPrompt();
 void readCommand(char *);
 void printHelp();

 int main(int argc, char *argv[]) {
    int pid;
    int status;
    char cmdLine[MAX_LINE_LEN];
    struct command_t command;

    while (1) {

        printPrompt();
        readCommand(cmdLine);
        parseCommand(cmdLine, &command);
        command.argv[command.argc] = NULL;

        // These shell commands don't require execvp(). Do not need to fork a child process
        if (strcmp(command.name, "Q") == 0) {
            break;
        }
        else if (strcmp(command.name, "") == 0) {
            continue;
        }

        // Create a child process to execute the command
        if ((pid = fork()) == 0) {

            if (strcmp(command.name, "W") == 0) {
				execvp("clear", command.argv);
			}
			else if (strcmp(command.name, "C") == 0) {
				execvp("cp", command.argv);
            }
			else if (strcmp(command.name, "D") == 0) {
				execvp("rm", command.argv);
            }
			else if (strcmp(command.name, "M") == 0) {
				execvp("nano", command.argv);
            }
			else if (strcmp(command.name, "X") == 0) {
                if (command.argc < 2) {
                    printf("Usage: X <program> [args]\n");
                }
				execvp(command.argv[1], &command.argv[1]);
            }
			else if (strcmp(command.name, "P") == 0) {
				execvp("more", command.argv);
            }
            else if (strcmp(command.name, "L") == 0) {
                char *args[] = {"ls", "-l", NULL};
                execvp("ls", args);
            }
            else if (strcmp(command.name, "E") == 0) {
                if (command.argc == 1) {
                    exit(0);
                }
                for (int i = 1; i < command.argc; i++) {
                    printf("%s ", command.argv[i]);
                }
                printf("\n");
            }
            else if(strcmp(command.name,"H") == 0) {
                printHelp();
            }
			else {
				printf("Unrecognized command, type H for a list of commands\n");
            }

            // Ensure the child process exits
            exit(0);
        }

        /* Wait for the child to terminate*/
        wait(&status);
    }

    /* Shell termination */
    printf("\n\n shell: Terminating successfully\n");
    return 0;
}

 /* End basic shell */

 /* Parse Command function */

 /* Determine command name and construct the parameter list.
  * This function will build argv[] and set the argc value.
  * argc is the number of "tokens" or words on the command line
  * argv[] is an array of strings (pointers to char *). The last
  * element in argv[] must be NULL. As we scan the command line
  * from the left, the first token goes in argv[0], the second in
  * argv[1], and so on. Each time we add a token to argv[],
  * we increment argc.
  */
 int parseCommand(char *cLine, struct command_t *cmd) {
    int argc;
    char **clPtr;
    /* Initialization */
    clPtr = &cLine;	/* cLine is the command line */
    argc = 0;
    cmd->argv[argc] = (char *) malloc(MAX_ARG_LEN);
    /* Fill argv[] */
    while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {
       cmd->argv[++argc] = (char *) malloc(MAX_ARG_LEN);
    }

    /* Set the command name and argc */
    cmd->argc = argc-1;
    cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
    strcpy(cmd->name, cmd->argv[0]);
    return 1;
 }

 /* End parseCommand function */

 /* Print prompt and read command functions - Nutt pp. 79-80 */

 void printPrompt() {
    /* Build the prompt string to have the machine name,
     * current directory, or other desired information
     */

    char hostname[64]; // HOST_NAME_MAX
    char cwd[PATH_MAX];
    char *username = "prg21";

    // Get the hostname
    gethostname(hostname, sizeof(hostname));

    // Get the current working directory
    getcwd(cwd, sizeof(cwd));

    // Print the prompt
    printf("%s (%s) |> ", hostname, username);
 }

 void readCommand(char *buffer) {
    /* This code uses any set of I/O functions, such as those in
     * the stdio library to read the entire command line into
     * the buffer. This implementation is greatly simplified,
     * but it does the job.
     */
    fgets(buffer, 80, stdin);
 }

/* End printPrompt and readCommand */

// Display the user manual
void printHelp() {
    printf("Shell commands:\n");
    printf("C file1 file2: Copy; create file2, copy all bytes of file1 to file2 without deleting file1\n");
    printf("D file: Delete the named file\n");
    printf("E comment: Echo; display comment on screen followed by a new line\n");
    printf("H: Help; display the user manual, described below\n");
    printf("L: List the contents of the current directory\n");
    printf("M file: Make; create the named text file by launching a text editor\n");
    printf("P file: Print; display the contents of the named file on the screen\n");
    printf("Q: Quit the shell\n");
    printf("W: Wipe; clear the screen\n");
    printf("X program: Execute the named program\n");
}
