// prog 5 - sort

int minloc( int a[], int low, int high ){   
    int i; int x; int k;
    k = low;
    x = a[ low ];
    i = low + 1;
    while( i < high ) {
        if( a[ i ] < x ){
            x = a[ i ];
            k = i;
        }
        i = i + 1;
    }
    return k;
}

void sort( int a[], int low, int high){
    int i; int k;
    i = low;
    while( i < high - 1 ) {
        int t;
        k = minloc( a, i, high );
        t = a[ k ];
        a[ k ] = a[ i ];
        a[ i ] = t;
        i = i + 1;
    }
    return;
}

int main( void ) {
    int sort_array[ 5 ];
    int size;
    int idx;
    int in_var;
    size = 5;
    idx = 0;
    while( idx < size ) {
        in_var = input( );
        sort_array[ idx ] = in_var;
        idx = idx + 1;
    }
    sort( sort_array, 0, size );
    idx = 0;
    while( idx < size ) {
        output( sort_array[ idx ] );
        idx = idx + 1;
    }
    return;
}