// prog 2 - fib

void fib( int fibvet[ ], int tam ) {
    int i;
    i = 2;
    fibvet[ 0 ] = 0;
    fibvet[ 1 ] = 1;
    while( i < tam ) {
        fibvet[ i ] = fibvet[ i - 1 ] + fibvet[ i - 2 ];
        i = i + 1;
    }
    return;
}

void main( void ) {
    int size;
    int idx;
    int arr[ 10 ];
    size = 10;
    fib( arr, size );
    idx = UART_input( );
    UART_output( arr[ idx ] );
    return;
}