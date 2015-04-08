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

// dirent.h is used for directories
#include "dash.h"
#include "dash1_funcs.cpp"
#include "dash2_funcs.cpp"
#include "dash3_funcs.cpp"


/**
 * Function: main
 *
 * Description: Main holds the loop to keep the shell running until
 *              "exit" is entered. 
 *
 * Args:
 *      argc: number of args
 *      argv: command line params (none for this program)
 */
int main(int argc, char const *argv[])
{
    // Initialize variable to use
    string command = "";
    string output = "";
    bool invalid = true;
    int first_char;
    int i;

    // Start signal catching for signals 0 to 50
    for (i = 0; i <= 50; i++)
    {
        signal(i,signal_handler);
    }

    // Check for the command "exit" anywhere in line
    while( !exit_command(command) )
    {
        // Print the prompt
        cout << "dash> ";

        // Get the command from user
        getline(cin, command);

        if (cin.eof()==1) {
            cin.clear();
            cin.ignore();
            cout << endl;
            continue;
        }

        command.append(" ");

        // Chop off leading whitespace
        if(command.find_first_not_of(" \t\n") != string::npos ){
            first_char = command.find_first_not_of(" \t\n");
            command = command.substr(first_char);
        }
        
        // See if the user tried to run cmdnm
        if(command.substr(0, 5) == "cmdnm")
        {
            if( command[5] == ' ' || command[5] == '\t' || command.size() == 5 )
            {
                cmdnm(command);
                invalid = false;
            }
        }
        // See if the user tried to run pid
        else if(command.substr(0,3) == "pid")
        {
            if(command[3] == ' ' || command[3] == '\t' || command.size() == 3 )
            {
                pid(command);
                invalid = false;
            }
        }
        // See if the user tried to run systat
        else if(command.substr(0,6) == "systat")
        {
            if(command[6] == ' ' || command[6] == '\t' || command.size() == 6 )
            {
                systat();
                invalid = false;
            }
        }
        // See if the user tried to run cd
        else if(command.substr(0,2) == "cd")
        {
            if(command[2] == ' ' || command[2] == '\t' || command.size() == 2 )
            {
                cd_command(command);
                invalid = false;
            }
        }
        else if(command.substr(0,6) == "signal")
        {
            if(command[6] == ' ' || command[6] == '\t' || command.size() == 6 )
            {
                signal_pid(command);
                invalid = false;
            }
        }

        else if(command.substr(0,8) == "mboxinit")
        {
            if(command[8] == ' ' || command[8] == '\t' || command.size() == 8 )
            {
                mboxinit(command);
                invalid = false;
            }
        }

        else if(command.substr(0,7) == "mboxdel")
        {
            if(command[7] == ' ' || command[7] == '\t' || command.size() == 7 )
            {
                mboxdel();
                invalid = false;
            }
        }
        else if(command.substr(0,9) == "mboxwrite")
        {
            if(command[9] == ' ' || command[9] == '\t' || command.size() == 9 )
            {
                mboxwrite(command);
                invalid = false;
            }
        }
        else if(command.substr(0,8) == "mboxread")
        {
            if(command[8] == ' ' || command[8] == '\t' || command.size() == 8 )
            {
                mboxread(command);
                invalid = false;
            }
        }

        else if(command.substr(0,8) == "mboxcopy")
        {
            if(command[8] == ' ' || command[8] == '\t' || command.size() == 8 )
            {
                mboxcopy(command);
                invalid = false;
            }
        }

        else if( has_redirect(command) ){
            redirect(command);
            invalid = false;
        }

        else if( has_pipe(command) ){
            run_pipe(command);
            invalid = false;
        }

        // If the command wasn't one that we implemented or "exit", try to fork a  
        //  child process and run it.
        else if( !exit_command(command) && command.length()!=0
                    && (int)command.find_first_not_of(" \t\n") != -1 )
        {
            run_sys_call(command);
            //cout << output << endl;
            
            invalid = false;
        }

        // If we need to print the usage message, do it in a function
        print_usage_if_needed(invalid, command);

        // Assume the user's input is invalid by default
        invalid = true;

    }
    
    return 0;
}
