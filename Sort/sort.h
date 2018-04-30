#ifndef SORT_H
#define SORT_H

const int l = 100 ;
//test the algorithm
void test_sort( int*(* const f)( int[] ,int ) ) ;

//the algorithms
int* insert_sort ( int arr[] ,int l ) ;
int* merge_sort ( int arr[] ,int l ) ;
int* heap_sort( int arr[] ,int l ) ;
int* fast_sort( int arr[] ,int l ) ;
int* fast_sort_senior( int arr[] ,int l ) ;
int* bubble_sort( int arr[] ,int l ) ;
#endif // SORT_H
