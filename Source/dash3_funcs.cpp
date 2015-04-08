
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Helpers for part 3 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

char* box_num_to_addr(int box_num, int box_size ){
	
	int shmid = shmget(SHMKEY, 0, 0666);
	char* addr = (char*) shmat(shmid, 0, 0);
	addr += 2*sizeof(int) + box_num * box_size * KB;

	return addr;
}

void write_block( char* addr, int box_size, char* msg ){

	int msg_size = strlen(msg);
	int i;

	if( msg_size > (box_size*KB - 1)){
		msg_size = box_size*KB - 1;
	}

	for( i = 0; i < msg_size; i++ ){
		*(addr + i) = msg[i];
		cout << msg[i];
	}
cout << endl;
	*(addr + i) = '\0';

	return;
}

char* read_block( char* addr, int box_size ){
	char* msg = (char*) malloc(box_size*KB);
	int i = 0;

	while( *(addr + i) != '\0' ){
		msg[i] = *(addr+i);
		i++;
	}
	msg[i] = '\0';

	return msg;
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Helpers for part 3 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



/**
	Name: mboxinit
	Description: Sets up shared memory
	
	Parameters:

	in:
		string command: the mboxinit command to carry out
						The command is not guaranteed to be correct
						so error checking should be done

*/
bool mboxinit(string command){
	//cout << "Made it to mboxinit!" << endl;

	int argc;
	int num_boxes;
	int box_size;

	int shmid;
	int* pint;

	char ** args = parse_args_c( command, argc );

	if( argc != 3){
		cout << "mboxinit usage: mboxinit <num_boxes> <box_size>" << endl;
		return false;
	}

	// Error check the comands
	num_boxes = atoi(args[1]);
	box_size = atoi(args[2]);

	// Check if shared memory is already set up. If it is, return -1.
	shmid = shmget(SHMKEY, 2*sizeof(int) + num_boxes*box_size*KB, 
						IPC_CREAT | IPC_EXCL | 0666);

	if( shmid < 0 ){
		cout << "Shared memory already set up!" << endl;
		return false;
	}


	// Otherwise, the correct number of mailboxes were created
	cout << "shmid = " << shmid << endl;

	// Write the number of boxes and box size to the first block
	pint = (int*) shmat(shmid, 0, 0);
	*(pint) = num_boxes;
	*(pint + 1) = box_size;


	return true;
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
bool mboxdel(bool my_mem){
	//cout << "Made it to mboxdel!" << endl;
	int shmid;
	shmid = shmget(SHMKEY, 0, 0666);

	if( shmid == -1 ){
		cout << "Shared memory not set up. No need to delete!" << endl;
		return false;
	}
	else if( my_mem == false ){
		cout << "Memory not set up by this shell. Cannot delete!" << endl;
		return false;
	}

	shmctl(shmid, IPC_RMID, 0);

	return false;
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
	//cout << "Made it to mboxwrite!" << endl;
	int argc;
	int shmid;
	char* addr;
	int num_boxes;
	int box_size;
	int write_box;


	char ** args = parse_args_c( command, argc );
	if( argc != 3 ){
		cout << "mboxwrite usage: mboxwrite <box_number> <message>" << endl;
	}


	shmid = shmget(SHMKEY, 0, 0666 );

	if( shmid == -1 ){
		cout << "Shared memory not set up. Use mboxinit first!" << endl;
	}


	int* pint = (int*) shmat( shmid, 0, 0 );
	num_boxes = *(pint);
	box_size = *(pint + 1);

	cout << "Num_boxes: " << num_boxes << endl;
	cout << "Box_size: " << box_size << endl;

	write_box = atoi( args[1] );

	addr = box_num_to_addr( write_box, box_size );

	write_block( addr, box_size, args[2] );

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
	//cout << "Made it to mboxread!" << endl;
	int argc;
	int read_box;
	int num_boxes;
	int box_size;
	int shmid;
	char* msg;
	char* addr;

	char ** args = parse_args_c( command, argc );

	if( argc != 2 ){
		cout << "mboxread usage: mboxread <box_number>" << endl;
		return;
	}

	shmid = shmget(SHMKEY, 0, 0666 );

	if( shmid == -1 ){
		cout << "Shared memory not set up. Use mboxinit first!" << endl;
		return;
	}


	int* pint = (int*) shmat( shmid, 0, 0 );
	num_boxes = *(pint);
	box_size = *(pint + 1);

	read_box = atoi(args[1]);

	addr = box_num_to_addr( read_box, box_size );

	msg = read_block(addr, box_size);
	cout << "MSG: " << msg << endl;
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

	int argc;
	int copy_to;
	int copy_from;
	int shmid;
	int num_boxes;
	int box_size;

	char* addr;
	char* temp;
	char ** args = parse_args_c( command, argc );

	if( argc != 3){
		cout << "mboxcopy usage: mboxcopy <copy_from> <copy_to>" << endl;
		return;
	}

	shmid = shmget(SHMKEY, 0, 0666 );

	if( shmid == -1 ){
		cout << "Shared memory not set up. Use mboxinit first!" << endl;
		return;
	}

	copy_from = atoi( args[1] );
	copy_to = atoi( args[2] );


	int* pint = (int*) shmat( shmid, 0, 0 );
	num_boxes = *(pint);
	box_size = *(pint + 1);

	temp = read_block( box_num_to_addr( copy_from , box_size ), copy_from);
	write_block( box_num_to_addr( copy_to , box_size ), box_size, temp );

	return;
}



