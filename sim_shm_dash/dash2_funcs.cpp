/**
 * Program: dash
 *
 * Author: Dan Nix
 *
 * Description: 
 *      The second implementation of Dash expands functionality to include:
 *          - Implement any system command with child process statistics      
 *          -  Implement the ``cd" command       
 *          -  Redirect input and output
 *          -  Pipe from one process to another
 *          -  Send and receive signals to and from other processes
 *      Detailed description of how each function is achieved is provided in
 *      prog2.pdf.
 */


/**
 * Function: print_2d_char_array
 *
 * Description: Prints a char** to the prompt for debugging
 *
 * Args:
 *     char** a: the array to print
 *
 * Return:
 *     none
 */
void print_2d_char_array(char** a)
{
	int i = 0;
	while(a[i] != NULL)
	{
		cout << a[i] << endl;
		i++;
	}
	cout << endl;
	return;
}

/**
 * Function: parse_args
 *
 * Description: parse_args turns a string of arguments
 *				into a 2d char array
 *
 * Args:
 *     string command: command to be parsed
 *
 * Return:
 *     char**: pointer to parsed args array
 */
char** parse_args(string command)
{
	int i, j, k, char_count, num_args, arg_num;
	char prev_char;
	char* temp;


	char ** args;

	// Count up the number of args
	num_args = 0;
	prev_char = ' ';
	for(i = 0; i < (int)command.length(); i++ ){
		if( prev_char == ' ' && command[i] != ' ')
			num_args++;
		prev_char = command[i];
	}
	// Allocate enough space for 2d array rows
	args = (char**)malloc((num_args+1)*sizeof(char*));

	// Store arguments 
	char_count = 0;
	prev_char = ' ';
	arg_num = 0;
	for(i = 0; i < (int)command.length(); i++ ){
		// If it's not a space, it's a character!
		if( command[i]!= ' ' && i != (int)command.length()-1)
		{
			char_count++;
			prev_char = command[i];
		}
		// If it is a space, see if the last thing we were at was a space
		else if( prev_char == ' ' )
			continue;
		else
		{
			temp = (char*) malloc(char_count*sizeof(char)*(char_count+2));
			for( j = i-char_count, k = 0; j < i; j++, k++ )
			{
				temp[k] = command[j];
			}
			temp[k] = '\0';
			args[arg_num] = temp;
			arg_num++;
			char_count = 0;

		}

	}
	args[arg_num] = NULL;

	return args;
}

// This function was added for part 3 as a helper when doing command
//	error checking.
char** parse_args_c(string command, int &num){

	char** args = parse_args( command );

	num = 0;
	while( args[num] != NULL ){
		num++;
	}

	return args;
}

/**
 * Function: run_sys_call
 *
 * Description: uses execvp to run a system command provided by the user
 *				Built off of sample code provided by Dr. Karlsson.
 *
 * Args:
 *     string command: command to be executed
 *
 * Return:
 *		none
 *     
 */
void run_sys_call( string command )
{
	// Karlsson's variables pasted in!
	char *line; 
	char *args[100]; 
	int   num_args; 
	int   childpid; 
	int   status; 
	struct rusage usage;

	// Convert to a c-style string because Karlsson is into that
	//	sort of stuff... and it means I don't need to modify the
	//	code hardly at all. :)
	line = (char*)command.c_str();

	num_args = 0; 
	args[num_args] = strtok(line, " "); 
	while (args[num_args] != NULL) 
	{ 
		num_args++; 
		args[num_args] = strtok(NULL, " "); 
	} 
	num_args--; 

	printf("\n"); 
	childpid = fork(); 
	if (childpid == 0) 
	{ 
		cout << DASHES;
		printf( "Child pid: %d\n\n", getpid() );
		cout << "Command output: " << endl;
		execvp(args[0], args); 
		cout << "No Output because '" << args[0] << "' could not be exec-ed" << endl;
		exit(5); 
	} 
	
	wait(&status); 
	if( status != 0 )
	{
		cout << "Invalid Command Provided!" << endl;
		cout << DASHES;
		return;
	}
	cout << DASHES;
	getrusage( RUSAGE_CHILDREN, &usage);

	cout << "Child statistics: " << endl << endl;
	printf("User Time: %ld.%ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec ); 							
    printf("System Time: %ld.%ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec ); 							      			
    printf("Soft Page Faults: %ld\n", usage.ru_minflt);     		
    printf("Hard Page Faults: %ld\n", usage.ru_majflt);     		
    printf("Swaps: %ld\n", usage.ru_nswap);   
    cout << DASHES;



	return;
} 

/**
 * Function: cd_command
 *
 * Description: implements our own cd command (NOT the system verison)
 *
 * Args:
 *     string command: cd command to be executed
 *
 * Return:
 *     none
 */
void cd_command(string command)
{
	string dir;
	int status = -1;

	// If there is no argument, change to the home directory like bash
	dir = parse_first_arg(command, "cd <dir>");

	if(dir.length() == 0)
	{
		status = chdir(getenv("HOME"));
		dir = "~";
	}
	// Otherwise, pass the path into chdir
	else
	{
		status = chdir(dir.c_str());
	}

	if(status == 0)
	{
		cout << "Changed to directory: " << dir << endl;
	}
	else
	{
		cout << "Failed to change directory: " << dir << endl;
	}

	return;
}

/**
 * Function: has_redirect
 *
 * Description: checks if there is a redirect in the command
 *
 * Args: 
 *     string command: command to check for redirect
 *
 * Return:
 *     	true: redirect present
 *		false: no redirect in statement
 */
bool has_redirect(string command)
{
	int red = command.find_first_of("<>");
	if(red == -1)
		return false;

	return true;
}

/**
 * Function: redirect
 *
 * Description: after a command is checked for a redirect, this function is called.
 *		After parsing the command line argument, it forks a child process and closes
 *		and redirects the child process's standard input or output (depending on the
 *		redirect direction) to send to or read from a file.
 *				Built off of sample code provided by Dr. Karlsson.
 *
 * Args:
 *     string command: command with redirect to run
 *
 * Return:
 *     none
 */
void redirect(string command)
{

	// Initialize variables
	int fpt1, fpt2, pid;
	int red;
	int status;
	string file_name;
	char ** args;
	char dir;

	// Parse the file name from the command
	red = command.find_first_of("<>", 0);
	file_name = command.substr(red+1);

	int first = file_name.find_first_not_of(" \n\t");
	int last =  file_name.find_last_not_of(" \n\t") + 1;

	if( last == 0 || first == -1 )
	{
		cout << "Need to supply a file name to redirect input/output!" << endl;
		return;
	}

	file_name = file_name.substr( first, last - first );

	
	// Get the redirect direction
	dir = command[red];

	// Chop the file off the redirect command and parse what remains.
	command = command.substr(0, red);
	args = parse_args(command);

  	pid = fork();
  	
  	if (pid == 0)
    {
    	
    	// Redirected input
    	if (dir == '<')
      	{
      		
      		fpt1 = open(file_name.c_str(), O_RDONLY, S_IWUSR|S_IRUSR);
      		if (fpt1 == -1)
        	{
        		printf("Unable to open %s for reading.\n", 
        			file_name.c_str());
        		exit(-1);
        	}
      		close(0);       // close child standard input
      		dup(fpt1);      // redirect the child input
      		close(fpt1);    // close unnecessary file descriptor
      	}

      	// Redirected output
  		else if (dir == '>')
    	{	
    		
    		fpt2 = open(file_name.c_str(), O_CREAT|O_WRONLY, S_IWUSR|S_IRUSR);
    		if (fpt2 == -1)
      		{
      			printf("Unable to open %s for writing.\n", file_name.c_str());
      			exit(-1);
      		}
      		
    		close(1);       // close child standard output 
    		dup(fpt2);      // redirect the child output 
    		close(fpt2);    // close unnecessary file descriptor
    	}
      	
    	// Run the command (now with redirected input or output)
    	execvp(	args[0], args);
    	exit(1);
    }

    // Parent waits for child process
    wait(&status);
  	
}

/**
 * Function: has_pipe
 *
 * Description: checks if a command has a pipe
 *
 * Args:
 *     string command: command to check
 *
 * Return:
 *     	true: command has pipe
 *		false: command has no pipe
 */
bool has_pipe(string command)
{
	int red = command.find_first_of("|");
	if(red == -1)
		return false;

	return true;
}

/**
 * Function: run_pipe
 *
 * Description: This function is called if a command has a pipe included.
 *		It forks a child process to run the command being piped to and 
 *		a grandchild process to run the command being piped from. 
 *				Built off of sample code provided by Dr. Karlsson.
 *
 * Args:
 *     string command: command with pipe to run
 *
 * Return:
 *     none
 */
void run_pipe( string command )
{

	// Initialize Variables
	int fd_pipe[2];
	int pid1;
  	int pid2;
  	int status;
  	int wpid;
  	int pipe_index;
  	string pipe_from_cmd;
  	string pipe_to_cmd;

  	char** pipe_from_args;
  	char** pipe_to_args;

  	// Find where the pipe is
  	pipe_index = command.find_first_of("|", 0);

  	// Substring the command to pipe from
	if( pipe_index != 0 )
	{
		pipe_from_cmd = command.substr(0, pipe_index);
		pipe_from_args = parse_args(pipe_from_cmd);
	}
	else
	{
		cout << "Need to provide a command on the left of pipe!" << endl;
		return;
	}

  	// Split off command to pipe into
  	if( (int)command.find_first_not_of(" \n\t", pipe_index+1) != -1 )
  	{
		pipe_to_cmd = command.substr(pipe_index+1);
		pipe_to_args = parse_args(pipe_to_cmd);
	}
	else
	{
		cout << "Need to provide a command on right side of pipe!" << endl;
		return;
	}

	// Fork the child
  	pid1 = fork();
  	if (pid1 == 0)
    {
    	// child process executes here for input side of pipe

    	pipe(fd_pipe);           // create pipe

    	// Fork the grandchild
    	pid2 = fork();
    	if (pid2 == 0)
      	{
      		// grandchild process executes here for output side of pipe
      		close(1);              // close standard output
      		dup(fd_pipe[1]);       // pipe_indexirect the output
      		close(fd_pipe[0]);     // close unnecessary file descriptor
      		close(fd_pipe[1]);     // close unnecessary file descriptor
      		execvp(pipe_from_args[0], pipe_from_args); // Run the program being piped from
	  		printf("execl of pipe-to failed\n");
      		exit(1);
      	}

    	// back to process for input side of pipe

	    close(0);              // close standard input
    	dup(fd_pipe[0]);       // redirect the input
    	close(fd_pipe[0]);     // close unnecessary file descriptor
    	close(fd_pipe[1]);     // close unnecessary file descriptor
    	// Wait for the grandchild process to finish
    	wait(&status);

    	execvp(pipe_to_args[0], pipe_to_args); // Run the program being piped to
		printf("execl of pipe-from failed\n");
    	exit(1);
    }
  	else
    {
    	// WAIT FOR THE CHILDREN!!!
    	wpid = wait(&status);
		printf("The child process id number is %d [%d]\n", pid1, wpid);
    }
    return;
}

/**
 * Function: singal_handler
 *
 * Description: Deals with signals received by the dash shell
 *
 * Args:
 *     int sig: signal number received
 *
 * Return:
 *     none
 */
void signal_handler(int sig)
{
	// Print the signal information to user
	printf("\nSignal %d received by dash shell!\n", sig);

	// I still want to be able to ctrl-C, so we'd better kill 
	//	dash if that comes in!
	if( sig == 2 || sig == 11 )
	{
		exit(1);
	}

}

/**
 * Function: signal_pid
 *
 * Description: signal_pid sends a signal to another process.
 *		Both the signal value and pid to send to are provided by user.
 *
 * Args:
 *     string command: command to be executed
 *
 * Return:
 *     none
 */
void signal_pid(string command)
{
	// Initiaize variables
	char** args;
	int signum, pid;

	// Parse the arguments
	args = parse_args(command);

	// Convert to integers
	signum = atoi(args[1]);
	pid = atoi(args[2]);

	// Send the signal!
	kill(pid, signum);

	return;
}