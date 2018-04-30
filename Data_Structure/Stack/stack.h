#ifndef STACK_H
#define STACK_H

template < typename T , int SIZE >
class Stack
{
    using data_type = T ;

    data_type arr[SIZE] ;
    int n = 0 ;

public:

    bool empty() { return !n ; }
    bool full() { return n==SIZE ; }
    void push( const data_type& d ) { full() ? /*do nothing*/ : arr[n++] = d ; }
    data_type& pop() { return empty() ? arr[0] : arr[--n] ; }
    data_type& top() const { return empty() ? arr[0] : arr[n-1] ; }
    int size() { return n ; }
};

#endif // STACK_H
