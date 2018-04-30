#ifndef QUEUE_H
#define QUEUE_H

template < typename T ,int SIZE >
class Queue
{
    using data_type = T ;
    data_type arr[SIZE] ;
    int first = 0 ,last = 0 ;
    int n = 0 ;
    inline int pplus ( int &n ) { int temp = n ; n = (n+1)%SIZE ; return temp ; }
public:
    bool empty() { return !n ; }
    bool full() { return n==SIZE ; }
    void push( const data_type& d ) {
        full() || ( arr[ pplus(last) ] = d ,++n ) ;//equal to " if( !full() ) ( arr[ pplus(last) ] = d ,++n ) "
    }
    data_type& pop() { return empty() ? arr[ first ] : ( --n ,arr[ pplus(first) ] ) ; }
    data_type& front() const { arr[ first ] ; }
    int size() { return n ; }
};

#endif // QUEUE_H
