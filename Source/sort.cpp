#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include "..\Header\sort.h"

//Test the sort algorithm
void test_sort( int*(* const f)( int[] ,int ) ) {

    srand( time( nullptr ) ) ;
    int arr[ l ] ;
    //Input
    std::cout << "Input:\n" ;
    for ( int &n : arr ) {
        n = rand()%201 + -100 ;//Creat random number between -100 and 100
        //std::cout << n << ' ';
    }
    //sort
    std::cout << "\nSorting...\n" ;
    f( arr ,l ) ;
    //Output
    std::cout << "\nOutput:\n" ;
    for ( int n : arr ) {
        //std::cout << n << ' ' ;
    }
    std::cout << "\nFinish\n" ;
}

//Insert Sort
int* insert_sort ( int arr[] ,int l ) {

    for ( int i = 1 ; i < l ; ++i ) {
        int temp = arr[i] ,j = i-1 ;
        while ( arr[j] > temp && j >= 0 ) {
            arr[j+1] = arr[j] ;
            --j ;
        }
        arr[j+1] = temp ;
    }
    return arr ;
}

//Merge Sort
int* merge_sort ( int arr[] ,int l ) {
    //check the length of the array
    if ( l <= 1 ) return arr ;
    //creat the subarrays
    int *arr1 = arr ,l1 = l/2 , *arr2 = arr + l1 ,l2 = l - l1 ;
    //sort the subarrays
    merge_sort( arr1 ,l1 ) ;
    merge_sort( arr2 ,l2 ) ;
    //copy the subarray
    int *temp1 = new int[l1+1] , *temp2 = new int[l2+1] ;
    for ( int i = 0 ; i < l1 ; ++i )
        temp1[i] = arr1[i] ;
    for ( int i = 0 ; i < l2 ; ++i )
        temp2[i] = arr2[i] ;
    temp1[l1] = temp2[l2] = INT_MAX ;
    //merge the subarrays
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

