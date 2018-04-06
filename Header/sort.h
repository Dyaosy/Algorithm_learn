#ifndef SORT_H
#define SORT_H

const int l = 100000 ;
//test the algorithm
void test_sort( int*(* const f)( int[] ,int ) ) ;

//the algorithms
int* insert_sort ( int arr[] ,int l ) ;
int* merge_sort ( int arr[] ,int l ) ;
#endif // SORT_H
