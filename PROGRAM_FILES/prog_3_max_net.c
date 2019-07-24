// prog 3 - max

int max( int vet[], int size ){
    int idx; 
    int high;

    idx = 0;
    high = 0;
    while( idx < size ){
        if( high < vet[ idx ] ){
            high = vet[ idx ];
        }
        idx = idx + 1;
    }
    return high;
}

int main( void ) {
    int max_arr[ 5 ];
    int size;

    size = 5;
    max_arr[ 0 ] = 13;
    max_arr[ 1 ] = 9;
    max_arr[ 2 ] = 56;
    max_arr[ 3 ] = 45;
    max_arr[ 4 ] = 51;

    UART_output( max( max_arr, size ) );

    return;
}