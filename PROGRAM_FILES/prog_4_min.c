// x'xxprog 4 - max

int min( int vet[], int size ){
    int idx; 
    int low;

    idx = 0;
    low = vet[ idx ];
    while( idx < size ){
        if( low > vet[ idx ] ){
            low = vet[ idx ];
        }
        idx = idx + 1;
    }
    return low;
}

int main( void ) {
    int min_arr[ 4 ];
    int size; int idx;
    size = 4;
    idx = 0;
    
    min_arr[ 0 ] = 13;
    min_arr[ 1 ] = 33;
    min_arr[ 2 ] = 11;
    min_arr[ 3 ] = 75;

    output( min( min_arr, size ) );

    return;
}