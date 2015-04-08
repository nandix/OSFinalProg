
/**
	Name: mboxinit
	Description: Sets up shared memory
	
	Parameters:

	in:
		string command: the mboxinit command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
void mboxinit(string command){
	cout << "Made it to mboxinit!" << endl;
	return;
}

/**
	Name: mboxdel
	Description: Deletes mailboxes and cleans up
	
	Parameters:

	in:
		string command: the mboxdel command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
void mboxdel(){
	cout << "Made it to mboxdel!" << endl;
	return;
}

/**
	Name: mboxdel
	Description: Writes data to mailbox. Stops writing on ctrl-D
	
	Parameters:

	in:
		string command: the mboxwrite command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
void mboxwrite(string command){
	cout << "Made it to mboxwrite!" << endl;
	return;
}

/**
	Name: mboxdel
	Description: Reads values in a mailbox to end of string or
					end of mailbox.
	
	Parameters:

	in:
		string command: the mboxread command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
void mboxread(string command){
	cout << "Made it to mboxread!" << endl;
	return;
}

/**
	Name: mboxdel
	Description: Copies one mailbox to another
	
	Parameters:

	in:
		string command: the mboxcopy command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
void mboxcopy(string command){
	cout << "Made it to mboxcopy!" << endl;
}

