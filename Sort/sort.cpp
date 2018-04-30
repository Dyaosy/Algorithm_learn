#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include "..\sort\sort.h"

// Test the sort algorithm
void test_sort( int*(* const sort)( int[] ,int ) ) {

    srand( time( nullptr ) ) ;
    int arr[ l ] ;
    // Input
    std::cout << "Input:\n" ;
    for( int &n : arr ) {
        n = rand()%201 + -100 ;// Creat random number between -100 and 100
        std::cout << n << ' ';
    }
    // sort
    std::cout << "\nSorting...\n" ;
    sort( arr ,l ) ;
    // Output
    std::cout << "\nOutput:\n" ;
    for( int n : arr ) {
        std::cout << n << ' ' ;
    }
    std::cout << "\nFinish\n" ;
}

// exchange function
inline void exchange( int &a ,int &b ) {
    int temp = a ;
    a = b ;
    b = temp ;
}

/////////////////// Insert Sort ///////////////////////

int* insert_sort ( int arr[] ,int l ) {

    for( int i = 1 ; i < l ; ++i ) {
        int temp = arr[i] ,j = i-1 ;
        while ( arr[j] > temp && j >= 0 ) {
            arr[j+1] = arr[j] ;
            --j ;
        }
        arr[j+1] = temp ;
    }
    return arr ;
}

/////////////////////// Merge Sort //////////////////////////

int* merge_sort ( int arr[] ,int l ) {
    // check the length of the array
    if( l <= 1 ) return arr ;
    // creat the subarrays
    int *arr1 = arr ,l1 = l/2 , *arr2 = arr + l1 ,l2 = l - l1 ;
    // sort the subarrays
    merge_sort( arr1 ,l1 ) ;
    merge_sort( arr2 ,l2 ) ;
    // copy the subarrays
    int *temp1 = new int[l1+1] , *temp2 = new int[l2+1] ;
    for( int i = 0 ; i < l1 ; ++i )
        temp1[i] = arr1[i] ;
    for( int i = 0 ; i < l2 ; ++i )
        temp2[i] = arr2[i] ;
    temp1[l1] = temp2[l2] = INT_MAX ;
    // merge the subarrays
    int i = 0 ,i1 = 0 ,i2 = 0 ;
    while( i < l ) {
        if( temp1[i1] <= temp2[i2] ) {
            arr[i] = temp1[i1] ;
            ++i1 ;
        }
        else {
            arr[i] = temp2[i2] ;
            ++i2 ;
        }
        ++i ;
    }
    delete[] temp1 ;
    delete[] temp2 ;
    return arr ;
}

///////////////////// Heap Sort ///////////////////////////

typedef int* HEAP ;// a HEAP == an array begin with 1 instead of 0
inline int parent ( int son ) { return son/2 ; }
inline int left ( int p ) { return p*2 ; }
inline int right ( int p ) { return p*2 +1 ; }

void max_heapify( HEAP heap ,int n ,int size ) {

    int p = n ,l = left(p) ,r = right(p) ,max = p ;
    // select the maxinum
    if( r <= size && heap[max] < heap[r] )
        max = r ;
    if( l <= size && heap[max] < heap[l] )
        max = l ;

    while( p != max ) {
        exchange( heap[p] ,heap[max] ) ;

        p = max ,l = left(p) ,r = right(p) ;
        // select the maxinum
        if( r <= size && heap[max] < heap[r] )
            max = r ;
        if( l <= size && heap[max] < heap[l] )
            max = l ;
    }
}

void build_max_heap( HEAP heap ,int size ) {
    for( int n = size/2 ; n > 0 ; --n )
        max_heapify( heap ,n ,size ) ;
}

int* heap_sort( int arr[] ,int l ) {
    HEAP heap = arr - 1 ;
    build_max_heap( heap , l ) ;
    exchange( heap[l] ,heap[1] ) ;
    for( int size = l - 1 ; size > 1 ; --size ) {
        max_heapify( heap ,1 ,size );
        exchange( heap[size] ,heap[1] ) ;
    }
    return arr ;
}

///////////////// Fast Sort ///////////////////////

int* fast_sort( int arr[] ,int l ) {
    if( l <= 1 ) return arr ;

    int end = l-1 ,mid = arr[ end ] ,i = 0 ,j = 0;
    // divide array into 2 parts : { smaller than mid / bigger than or equal to mid }
    for( ; j < end ; ++j ) {
        if( arr[j] < mid ) {
            exchange( arr[j] , arr[i] ) ;
            ++i ;
        }
    }
    exchange( arr[i] ,arr[j] ) ;

    fast_sort( arr ,i ) ;
    fast_sort( arr+i+1 , j-i ) ;

    return arr ;
}

int* fast_sort_senior( int arr[] ,int l ) {
    if( l <= 1 ) return arr ;
    // choose the mid in random
    exchange( arr[ l-1 ] ,arr[ rand()%l ] ) ;

    int mid = arr[ l-1 ] ,i = 0 ,j = 0 ,k = 0 ;
    // divide array into 3 parts : { smaller than mid / equal to mid / bigger than mid }
    for( ; k < l ; ++k ) {
        if( arr[k] == mid ) {
            exchange( arr[k] ,arr[j] );
            ++j ;
        }
        else if( arr[k] < mid ) {
            int temp = arr[k] ;
            arr[k] = arr[j] ,arr[j] = arr[i] ,arr[i] = temp ;
            ++i ,++j ;
        }
    }

    fast_sort_senior( arr ,i ) ;
    fast_sort_senior( arr+j , k-j ) ;

    return arr ;
}

///////////////////Bubble sort/////////////////////

int* bubble_sort( int arr[] ,int l ) {
    for( int i = l-1 ; i >= 0 ; --i )
        for( int j = 0 ; j < i ; ++j )
            if( arr[j] > arr [j+1] )
                exchange( arr[j] ,arr[j+1] );
    return arr ;
}
