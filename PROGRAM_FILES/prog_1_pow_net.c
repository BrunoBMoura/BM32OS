// prog 1 - pow

int pow( int a, int b ) {
    int aux; int val;
    val = 1;
    aux = 0;
    while( aux < b ) {
       val = val * a;
       aux = aux + 1;
    }
    return val;
}

void main(void){
    int a; 
    int b; 
    a = UART_input( );
    b = input( );
    a = pow( a, b );
    UART_output( a );
    return;
}