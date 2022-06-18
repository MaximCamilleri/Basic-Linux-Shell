# Basic Linux Shell
This is a basic implementation of a Linux shell. Coded in Linux, 
the shell delimited and tokenizes the input to execute a command. Additionally, 
it internally stores a set of environment variables initialized at start-up. 
The values of these variables are retrieved from the system kernel. These variables are:


Markup : 
* USER
* HOME
* PROMPT
* CWD
* SHELL
* TERMINAL
* EXITCODE


The program accepts the following commands:
Command      | Funciton
-------------|-------------
`exit`| exits the shell
`<VarName>=<Value>` | This is the shell variable creation system. To create a variable the user provides a name on the LHS and a value on the RHS. The value can be a string if the delimiting characters are escaped. This can be done with \ for one character, or “ ” for multiple.
`Echo` | prints out the tokens following it to the terminal. Can also be used with variables
`Cd` | used to change the current working directory.
`showvar` | can be ran with or without a variable name following the command. If a variable name is provided, then the command will print the value of the variable. If no variable is provided the function will retrieve all variables in the environment. 
`Export` | Sets a shell variable as an environment variable
`Unset` | Requires a variable name to follow it. Deletes the variable form the shell.
`Showenv` | Works the same as ‘showvar’ but for environment variables.
`Source` | Takes as input a file path containing a series of commands. Executes the commands in the file using the shell.
`Popd` | Works in context of the directory stack. Removes the last pushed directory from the stack, updating the current directory.
`Pushd` | Works in context of the directory stack and takes a path as a parameter. Sets the path to the current directory and pushes it to the directory stack.
`Dirs` | prints the directory stack.


If a command is run that is not an internal shell command, the shell will attempt to run it as an external command.
The shell also supports input and output redirection through the `<` (input redirection), `>` (output redirection), `>>` (output redirection appending to the end of file) commands. 

Finally, the shell also supports pipes as a way of allowing two separate processes to communicate with one another by establishing a connection between the input of one process and the output of another. 
Example:
```
Ping -c 3 google.com | grep “rtt”
```
