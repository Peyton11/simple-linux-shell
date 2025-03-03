# Makefile for running ulimit -u before starting the shell

# Target to run ulimit and then start the shell
run:
	@echo "Setting ulimit -u 100"
	@ulimit -u 100  # You can change the value 100 to whatever you need
	@echo "Starting the shell..."
	@./simple-linux-shell  # Replace with the name of your compiled shell program

# The target to build the shell program
build:
	gcc -o simple-linux-shell simple-linux-shell.c

# Clean up the generated files
clean:
	rm -f simple-linux-shell
