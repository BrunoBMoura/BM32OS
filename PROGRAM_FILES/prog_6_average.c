// prog 6 - average

int average( int arr[], int size ) {
    int idx;
    int sum;
    idx = sum = 0;
    while( idx < size ) {
        sum = sum + arr[ idx ];
        idx = idx + 1;
    }
    sum = sum / size;
    return sum;
}

int main( void ) {
    int avrg_array[ 5 ];
    int size;
    int idx;
    size = 5;
    idx = 0;
    while( idx < size ) {
        avrg_array[ idx ] = ( idx + 1 ) * 10;
        idx = idx + 1;
    }
    output( average( avrg_array, size ) );
    return;
}