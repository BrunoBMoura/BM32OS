// Bash messages:
// 0 = Welcome to BM32OS System
// 1 = Operations: 1-proc, 2-file
// 2 = How many files to execute?
// 3 = This file does not exist!
// 4 = Running processes...
// 5 = All processes finished running
// 6 = Choose your file operation 
// 7 = 1 - create, 2 - rename, 3 - delete 
// 8 = Too bad, hd is full!
// 9 = Enter file's instruction amount
// 10 = Instruction's first 16 bits 
// 11 = Instruction's last 16 bits 
// 12 = Insert a ID for the new file
// 13 = New ID can't already exist!
// 14 = File created succesfully
// 15 = Choose a file to be renamed
// 16 = Chose a existent file!
// 17 = Choose the new file ID
// 18 = Chosen ID must be unique!
// 19 = File was succesfully renamed
// 20 = Choose a file to be deleted
// 21 = File was succesfully deleted
// 29 = Insert the file's ID's
// 30 = Process requires input...
// 31 = Process requires output... 
// 32 = A process finished running
// 33 = A process requires uart input
// 34 = A process requires uart output

/**** OS related values ****/

// maximum number of processes suported by the system
int MAX_PROC_NUM;

// maximum number of files suported by the system
int MAX_FILE_NUM;

// actual number of files stored on hd
int FILE_AMOUNT;

// special register interruption value
int INTERRUPTION;

// HD region for each file
int HD_REGION;

// data memory region size
int MEM_REGION;

// yolo variable for bash freezing
int STOP_BASH;

/**** File data structure ****/

// file ID's
int file_IDS[15];

// file initial HD position
int file_begin[15];

// file final HD position
int file_end[15];

/**** Processes data structure ****/

// process state related to it's execution | 1 - finished, 0 - ready to be executed
int proc_state[15];

// process queue for round robin
int proc_queue[15];

// processes respective program counters
int proc_PCS[15];

/**** Process related functions ****/

void reset_program_counters( void ) {

    int idx;

    idx = 1;
    while( idx < MAX_PROC_NUM ) {
        proc_PCS[ idx ] = 0;
        idx = idx + 1;
    }
    return;
}

// resets the process queue for future process executions
void reset_process_queue( void ) {

    int idx;

    idx = 0;
    while( idx < MAX_PROC_NUM ) {
        proc_queue[ idx ] = 0;
        idx = idx + 1;
    }
    return;
}

// checks the file ID, returns 1 case it's found and 0 otherwise
int check_ID( int ID ) {

    int idx;
    int ret_value;

    idx = 1;
    ret_value = 0;
    while( idx < MAX_PROC_NUM ) {
        if( file_IDS[ idx ] == ID ) {
            ret_value = 1;
            idx = MAX_PROC_NUM;
        }
        else {
            idx = idx + 1;
        }
    }
    return ret_value;
}

// given an process ID, returns it's respective index on the process (file) array
int get_proc_idx( int proc_ID ) {

    int idx;
    int proc_idx;   

    idx = 1;
    while( idx < MAX_PROC_NUM ) {
        if( file_IDS[ idx ] == proc_ID ) {
            proc_idx = idx;
            idx = MAX_PROC_NUM;
        }
        else {
            idx = idx + 1;
        }
    }
    return proc_idx;
}

void load_proc_context( int proc_idx ) {

    int transfer_iterations;
    int transfer_idx;

    transfer_iterations = file_end[ proc_idx ] - file_begin[ proc_idx ];
    transfer_idx = 0;
    while( transfer_idx < transfer_iterations ) {
        // proc_num, track_line, mem_line
        move_HD_mem( proc_idx, transfer_idx, transfer_idx ); 
        transfer_idx = transfer_idx + 1;
    }
    transfer_idx = proc_idx * MEM_REGION;
    load_reg_context( 1, transfer_idx, 1 ); 
    load_reg_context( 2, transfer_idx, 2 ); 
    load_reg_context( 3, transfer_idx, 3 ); 
    load_reg_context( 4, transfer_idx, 4 ); 
    load_reg_context( 5, transfer_idx, 5 ); 
    load_reg_context( 6, transfer_idx, 6 ); 
    load_reg_context( 7, transfer_idx, 7 ); 
    load_reg_context( 8, transfer_idx, 8 ); 
    load_reg_context( 9, transfer_idx, 9 ); 
    load_reg_context( 10, transfer_idx, 10 ); 
    load_reg_context( 11, transfer_idx, 11 ); 
    load_reg_context( 12, transfer_idx, 12 ); 
    load_reg_context( 13, transfer_idx, 13 ); 
    load_reg_context( 14, transfer_idx, 14 ); 
    load_reg_context( 15, transfer_idx, 15 ); 
    load_reg_context( 16, transfer_idx, 16 ); 
    load_reg_context( 17, transfer_idx, 17 ); 
    load_reg_context( 18, transfer_idx, 18 ); 
    load_reg_context( 19, transfer_idx, 19 ); 
    load_reg_context( 20, transfer_idx, 20 ); 
    load_reg_context( 21, transfer_idx, 21 ); 
    load_reg_context( 22, transfer_idx, 22 ); 
    load_reg_context( 23, transfer_idx, 23 ); 
    load_reg_context( 24, transfer_idx, 24 ); 
    load_reg_context( 25, transfer_idx, 25 ); 
    load_reg_context( 26, transfer_idx, 26 ); 
    load_reg_context( 27, transfer_idx, 27 ); 
    load_reg_context( 28, transfer_idx, 28 ); 
    load_reg_context( 29, transfer_idx, 29 ); 
    load_reg_context( 30, transfer_idx, 30 ); 
    load_reg_context( 31, transfer_idx, 31 ); 
    return;
}

void store_proc_context( int proc_idx ) {

    int transfer_idx;   

    transfer_idx = proc_idx * MEM_REGION;
    store_reg_context( 1, transfer_idx, 1 ); 
    store_reg_context( 2, transfer_idx, 2 ); 
    store_reg_context( 3, transfer_idx, 3 ); 
    store_reg_context( 4, transfer_idx, 4 ); 
    store_reg_context( 5, transfer_idx, 5 ); 
    store_reg_context( 6, transfer_idx, 6 ); 
    store_reg_context( 7, transfer_idx, 7 ); 
    store_reg_context( 8, transfer_idx, 8 ); 
    store_reg_context( 9, transfer_idx, 9 ); 
    store_reg_context( 10, transfer_idx, 10 ); 
    store_reg_context( 11, transfer_idx, 11 ); 
    store_reg_context( 12, transfer_idx, 12 ); 
    store_reg_context( 13, transfer_idx, 13 ); 
    store_reg_context( 14, transfer_idx, 14 ); 
    store_reg_context( 15, transfer_idx, 15 ); 
    store_reg_context( 16, transfer_idx, 16 ); 
    store_reg_context( 17, transfer_idx, 17 ); 
    store_reg_context( 18, transfer_idx, 18 ); 
    store_reg_context( 19, transfer_idx, 19 ); 
    store_reg_context( 20, transfer_idx, 20 ); 
    store_reg_context( 21, transfer_idx, 21 ); 
    store_reg_context( 22, transfer_idx, 22 ); 
    store_reg_context( 23, transfer_idx, 23 ); 
    store_reg_context( 24, transfer_idx, 24 );
    store_reg_context( 25, transfer_idx, 25 ); 
    store_reg_context( 26, transfer_idx, 26 ); 
    store_reg_context( 27, transfer_idx, 27 ); 
    store_reg_context( 28, transfer_idx, 28 ); 
    store_reg_context( 29, transfer_idx, 29 ); 
    store_reg_context( 30, transfer_idx, 30 ); 
    store_reg_context( 31, transfer_idx, 31 ); 
    return;
}

// round robin algorithm for process scheduling
void round_robin( int proc_amount ) {

    int proc_ID;
    int finished_procs;
    int queue_idx;
    int proc_idx;
    int io_var;
    int proc_pc;

    finished_procs = 0;
    queue_idx = 0;
    proc_pc = 0;
    write_lcd( 4 ); 
    STOP_BASH = input( );
    while( finished_procs < proc_amount ) {
        proc_ID = proc_queue[ queue_idx ];
        proc_idx = get_proc_idx( proc_ID );
        // checking if the selected process has already finished executing
        if( proc_state[ proc_idx ] == 0 ) {
            //output( proc_idx );
            proc_pc = proc_PCS[ proc_idx ];
            set_proc_pc( proc_pc );
            load_proc_context( proc_idx );
            swap_process( proc_idx );
            recover_OS( );
            // get_interruption returns the value from register[28]
            INTERRUPTION = get_interruption( ); 
            proc_PCS[ proc_idx ] = get_proc_pc( );
            // input interruption 
            if( INTERRUPTION == 2 ) {
                write_lcd( 30 );
                io_var = input( );
                output( io_var );
                // moves data from io_var, which belongs to OS, to process at register[27]
                move_reg_OS_proc( io_var, 27 ); 
            }
            // output interruption 
            if( INTERRUPTION == 3 ) {
                write_lcd( 31 );
                // moves data from register[27], which belongs to process, to io_var from OS
                move_reg_proc_OS( 27, io_var ); 
                output( io_var );
            }
            // end program interruption
            if( INTERRUPTION == 4 ) {
                write_lcd( 32 );
                output( proc_idx );
                proc_state[ proc_idx ] = 1;
                finished_procs = finished_procs + 1;
            }
            // receive interruption     
            if( INTERRUPTION == 5 ) {
                write_lcd( 33 );
                io_var = UART_input( );
                output( io_var );
                // moves data from io_var, which belongs to OS, to process at register[27]
                move_reg_OS_proc( io_var, 27 );
            }
            // send interruption
            if( INTERRUPTION == 6 ) {
                write_lcd( 34 );
                // moves data from register[27], which belongs to process, to io_var from OS
                move_reg_proc_OS( 27, io_var );
                UART_output( io_var );
            }
            store_proc_context( proc_idx );
        }
        // determinating next process and ensuring queue circularity
        if( queue_idx < proc_amount - 1 ) {             
            queue_idx = queue_idx + 1;
        }
        else {
            queue_idx = 0;
        }
    }
    write_lcd( 5 ); 
    STOP_BASH = input( );
    return;
}

// process operation for schedulling setup
void process_operation( void ) {

    int proc_amount;
    int queue_idx;
    int proc_ID;

    write_lcd( 2 ); 
    proc_amount = input( );
    output( proc_amount );
    queue_idx = 0;
    write_lcd( 29 );
    while( queue_idx < proc_amount ) {
        proc_ID = input( );
        while( check_ID( proc_ID ) != 1 ) {
            write_lcd( 3 ) ; 
            proc_ID = input( );
        }
        output( proc_ID );
        proc_queue[ queue_idx ] = proc_ID;
        proc_state[ queue_idx ] = 0;
        queue_idx = queue_idx + 1;
    }
    round_robin( proc_amount );
    reset_process_queue( );
    reset_program_counters( );
    return;
}

 /**** File related functions ****/

// get next free position on the file array
int get_free_file_position( void ) {

    int idx; 
    int ret_idx;

    idx = 1;
    ret_idx = 0;
    while( idx < MAX_FILE_NUM ) {
        if( file_IDS[ idx ] == 99 ) {
                ret_idx = idx;
                idx = MAX_FILE_NUM;
        }
        else {
            idx = idx + 1;
        }
    }
    return ret_idx;
}

// create file 
void create_file( int file_idx ) {

    int file_ID;
    int file_instructions;
    int idx;
    int first_bits;
    int last_bits;
    int instruction;

    write_lcd( 9 );
    file_instructions = input( );
    output( file_instructions );
    idx = 0;
    while( idx < file_instructions ) {
        write_lcd( 10 );
        first_bits = input( );
        write_lcd( 11 );
        last_bits = input( );
        instruction = concatenate( first_bits, last_bits );
        // file_num, track_line, data
        store_HD( file_idx, idx, instruction );
        idx = idx + 1;
    }
    // naming the file
    write_lcd( 12 );
    file_ID = input( );
    output( file_ID );
    while( check_ID( file_ID ) == 1 ) {
        write_lcd( 13 );
        file_ID = input();
    }
    file_IDS[ file_idx ] = file_ID;
    file_begin[ file_idx ] = 0;
    file_end[ file_idx ] = file_instructions;
    write_lcd( 14 );
    STOP_BASH = input( );
    return;
}

// file renaming 
void rename_file( void ) {

    int idx;
    int file_ID;
    int new_ID;

    write_lcd( 15 );
    file_ID = input( );
    output( file_ID );
    while( check_ID( file_ID ) != 1 ) {
        write_lcd( 16 );
        file_ID = input( );
    }
    write_lcd( 17 );
    new_ID = input( );
    output( new_ID );
    while( check_ID( new_ID ) == 1 ) {
        write_lcd( 18 ); 
        new_ID = input( );
    }
    idx = 1;
    while( idx < MAX_PROC_NUM ) {
        if( file_IDS[ idx ] == file_ID ) {
            file_IDS[ idx ] = new_ID;
            idx = MAX_PROC_NUM;
        }
        else {
            idx = idx + 1;
        }
    }
    write_lcd( 19 );
    STOP_BASH = input( );
    return;
}

// file deletion
void delete_file( void ) {

    int idx;
    int file_ID;

    write_lcd( 20 );
    file_ID = input( );
    output( file_ID );
    while( check_ID( file_ID ) != 1 ) {
        write_lcd( 16 );
        file_ID = input( );
    }
    idx = 1;
    while( idx < MAX_PROC_NUM ) {
        if( file_IDS[ idx ] == file_ID ) {
            // erase HD references to file
            file_IDS[ idx ] = 99;
            file_begin[ idx ] = 0;
            file_end[ idx ] = 0;
            idx = MAX_PROC_NUM;
        }
        else {
            idx = idx + 1;
        }
    }
    write_lcd( 21 );
    STOP_BASH = input( );
    return;
}

// file operation for file creating/renaming/deleting
void file_operation( void ) {

    int file_idx;
    int file_ID;
    int file_position;
    int file_option;

    write_lcd( 6 );
    STOP_BASH = input( );
    write_lcd( 7 );
    file_option = input( );
    output( file_option );
    // create files 
    if( file_option == 1 ) {
        if ( MAX_FILE_NUM == FILE_AMOUNT ) {
            write_lcd( 8 );
            STOP_BASH = input( );
        }   
        else {
            file_idx = get_free_file_position( );
            create_file( file_idx );
            FILE_AMOUNT = FILE_AMOUNT + 1;
        }
    }
    // rename files
    if( file_option == 2 ){
        rename_file( );
    }
    // delete files
    if( file_option == 3 ){
        delete_file( );
        FILE_AMOUNT = FILE_AMOUNT - 1;
    }
    return;
}

 /**** Main functions ****/

void bash( void ) {

    int bash_option;

    write_lcd( 1 );
    bash_option = input( );
    output( bash_option );
    if( bash_option == 1 ) {
        process_operation( );
    }
    if( bash_option == 2 ) {
        file_operation( );
    }
    return;
}

void init( void ) {

    int idx;
    // setting up system variables
    MAX_PROC_NUM = 15;
    MAX_FILE_NUM = 15;
    FILE_AMOUNT = 10;
    HD_REGION = 1024; 
    MEM_REGION = 252; 
    
    idx = 1;
    // naming known files to it's respecctive index
    while( idx < MAX_PROC_NUM ) {
        if( idx < 10) {
            // if it is known, file_IDS[ idx ] = idx
            file_IDS[ idx ] = idx;
        }
        else {
            // if it isn't know, file_IDS[ idx ] = 99
            file_IDS[ idx ] = 99;
        }
        // reseting all of the processes program counters
        proc_PCS[ idx ] = 0;
        idx = idx + 1;  
    }
    // programming good manners
    file_begin[ 0 ] = 0; 
    file_end[ 0 ] = 0;
    // program 1 (pow) default information - net
    file_begin[ 1 ] = 0; 
    file_end[ 1 ] = 51;
    // program 2 (fib) default information - net
    file_begin[ 2 ] = 0; 
    file_end[ 2 ] = 68;
    // program 3 (max) default information - net
    file_begin[ 3 ] = 0; 
    file_end[ 3 ] = 75;
    // program 4 (min) default information 
    file_begin[ 4 ] = 0; 
    file_end[ 4 ] = 76;
    // program 5 (selection_sort) default information 
    file_begin[ 5 ] = 0;
    file_end[ 5 ] = 154;
    // program 6 (array average) default information 
    file_begin[ 6 ] = 0;
    file_end[ 6 ] = 72;
    // program 7 () default information
    file_begin[ 7 ] = 0;
    file_end[ 7 ] = 0;
    // program 8 () default information
    file_begin[ 8 ] = 0;
    file_end[ 8 ] = 0;
    // program 9  () default information
    file_begin[ 9 ] = 0;
    file_end[ 9 ] = 0;
    return;
}

void main( void ) {

    init( );
    write_lcd( 0 ); 
    STOP_BASH = input( );
    while( 1 < MAX_PROC_NUM ) {
        bash( );
    }
    return;
}