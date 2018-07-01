#ifndef List_1_H
#define List_1_H

#include <initializer_list>
#include <algorithm>

template < typename T , int SIZE >
class List_1{
    public:
        class NODE ;
    private:
        friend NODE ;
        using data_type = T ;

        static const int P_NIL = SIZE ;

        int next[ SIZE+1 ] ,last[ SIZE+1 ] ;
        data_type data[SIZE] ;
        int &p_beg = next[P_NIL] ,p_end = 0 ;

        void link( int p1 ,int p2 )  {
            next[p1] = p2 ,last[p2] = p1 ;
        }
        void connect( int p1 ,int p2 ,int p3 ) { link( p1 ,p2 ) ,link( p2 ,p3 ) ; }
        void add_back( const data_type& d ) {
            data[p_end] = d ;
            p_end = next[p_end] ;
        }
        void remove_back() {
            p_end = last[p_end] ;
        }
    public:
        class NODE {
        private:
            friend List_1 ;
            const List_1* p_list ;
            int pos ;
#ifdef TEST_LIST_1
            friend void test_List_1 () ;
#endif // TEST_LIST_1
        public:
            NODE( const List_1* p_l ,int p ) :p_list(p_l) ,pos(p) {}
            NODE( const NODE& n ) :p_list(n.p_list) ,pos(n.pos) {}
            NODE next() const { return NODE( p_list ,p_list->next[pos] ) ; }
            NODE last() const { return NODE( p_list ,p_list->last[pos] ) ; }
            NODE& go_forward() { pos = p_list->next[pos] ; return *this ; }
            NODE& go_backward() { pos = p_list->last[pos] ; return *this ; }
            const data_type& data() const { return p_list->data[pos] ; }
            bool operator==( const NODE& n ) const { return p_list == n.p_list && pos == n.pos ; }
            bool operator!=( const NODE& n ) const { return !(*this == n ) ; }
        };


        static const NODE NIL ;
        List_1() {
            for( int i = 0 ; i <= SIZE ; ++i )
                next[i] = i+1 ,last[i] = i-1 ;
            last[0] = SIZE ,next[SIZE] = 0 ;
        }
        List_1( std::initializer_list< data_type > l ) : List_1() {
            int i = 0 ;
            for( const data_type &n : l )
                data[i++] = n ;
            p_end = i ;
        }
        virtual ~List_1() = default ;
        bool empty() const { return p_beg == p_end ; }
        bool full() const { return p_end == P_NIL ; }
        int size() const {
            int s = 0 ,p = p_beg ;
            while ( p != p_end )
                p = next[p] ,++s ;
            return s ;
        }
        NODE begin() const { return NODE( this ,p_beg ) ; }
        NODE end() const { return NODE( this ,p_end ) ; }
        const data_type& front() const { return data[p_beg] ; }
        const data_type& back() const { return data[ last[p_end] ] ; }
        data_type& front() { return data[p_beg] ; }
        data_type& back() { return data[ last[p_end] ] ; }
        void push_front( const data_type& d ) {
            if( full() )
                return ;
            if( empty() )
                add_back( d ) ;
            int new_pos = p_end ;
            p_end = next[p_end] ;
            data[new_pos] = d ;
            link( last[new_pos] , p_end ) ;
            connect( P_NIL ,new_pos ,p_beg ) ;
        }
        void push_back( const data_type& d ) {
            if( full() )
                return ;
            add_back( d ) ;
        }
        NODE insert( const NODE& pos ,const data_type& d ) {
            if( pos.p_list != this || full() )
                return List_1::NIL ;
            if( pos.pos == p_end )
                add_back( d ) ;
            int new_pos = p_end ;
            p_end = next[p_end] ;
            link( last[new_pos] ,p_end ) ;
            connect( last[pos.pos] ,new_pos ,pos.pos ) ;
            return NODE( this ,new_pos ) ;
        }
        data_type&& pop_back() {
            if( empty() )
                return std::move(data_type()) ;
            remove_back() ;
            return std::move(data[p_end]) ;
        }
        data_type&& pop_front() {
            if( empty() )
                return std::move(data_type()) ;
            if( next[p_beg] == p_end )
                return pop_back() ;
            int new_beg = next[p_beg] ;
            connect( last[P_NIL] ,p_beg ,P_NIL ) ;
            link ( P_NIL ,new_beg ) ;
            return std::move(data[ last[P_NIL] ]) ;
        }
        NODE erase( const NODE& pos ) {
            if( pos.p_list != this || empty() || pos.pos == P_NIL || pos.pos == p_end )
                return NIL ;
            auto ret = next[pos.pos] ;
            link ( last[pos.pos] ,next[pos.pos] ) ;
            connect( last[P_NIL] ,pos.pos ,P_NIL ) ;
            return NODE( this ,ret ) ;
        }
        NODE erase( const NODE& n_beg ,const NODE& n_end ) {
            if( empty() || n_beg.p_list != this || n_end.p_list != this
               || n_beg.pos == P_NIL )
                return NIL ;
            if( n_beg.pos == n_end.pos )
                return n_end ;
            int real_end = last[ n_end.pos ] ;
            link( last[n_beg.pos] , n_end.pos ) ;
            link( last[P_NIL] ,n_beg.pos ) ;
            link( real_end ,P_NIL ) ;
        }
#ifdef TEST_LIST_1
        friend void test_List_1 () ;
#endif // TEST_LIST_1
};


template< typename T , int SIZE >
const typename List_1< T,SIZE >::NODE
    List_1< T,SIZE >::NIL( nullptr , List_1< T,SIZE >::P_NIL ) ;

#ifdef TEST_LIST_1
void test_List_1 () ;
#endif // TEST_LIST_1

#endif // List_1_H
