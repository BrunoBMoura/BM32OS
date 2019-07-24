// bios code
// 22 - ______BIOS__________STARTING____
// 23 - Enter number 13
// 24 - Please enter the required value!
// 25 - Memory access working
// 26 - Logical componentes working
// 27 - OS will now be loaded from HD
// 28 - System will now be deployed :D

int main( void ) {
    int idx;
    int M;
    int proc_region;
    int STOP_BASH;
    int bios_io;

    write_lcd( 22 ); // bios running
    STOP_BASH = input( );
    M = 2048;
    proc_region = 0;
    write_lcd( 23 ); // Enter number 13
    bios_io = input( );
    while( bios_io != 13 ) {
        write_lcd( 24 ); // Please enter the required value! 
        UART_output( bios_io );
        bios_io = input( );
    }

    write_lcd( 25 ); // Memory access working
    STOP_BASH = input( );

    if( bios_io * 3 == 39 ) {
        write_lcd( 26 ); // Logical componentes working
        STOP_BASH = input( );   
    }
    write_lcd( 27 ); // OS will now be loaded from HD
    STOP_BASH = input();
    idx = 0;
    while( idx < M ) {
        // proc_region, hd_line, memory_line
        load_os( proc_region, idx, idx ); 
        idx = idx + 1;
    }
    write_lcd( 28 ); // System will now be deployed
    STOP_BASH = input( );
    end_bios( );
    return;
}


