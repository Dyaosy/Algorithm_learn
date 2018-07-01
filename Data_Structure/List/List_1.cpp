#ifdef TEST_LIST_1
#include "List_1.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std ;

const int s = 100 ;
using int_list = List_1< int ,s > ;

int_list::NODE rand_node( const int_list& l ) {
    int s = l.size() ;
    if( s == 0 )
        return l.begin() ;
    int p = rand()%s ;
    auto n = l.begin() ;
    while ( p > 0 )
        --p ,n.go_forward() ;
    return n ;
}

void test_List_1() {
    cout.sync_with_stdio( false ) ;

    srand( 21331519 ) ;
    int_list l ;
    for( int i = 0 ; i < 3*s ; ++i ) {
        cout << i << ": " ;
        auto n = rand_node(l) ;
        switch ( rand()%7 ) {
        case 0 :
            cout << "run erase ( " << n.pos << " )\n" ;
            l.erase(n) ;
            break ;
        case 1 :
            cout << "run pop_back()" << l.pop_back() << endl ;
            break ;
        case 2 :
            cout << "run pop_front()" << l.pop_front() << endl ;
            break ;
        case 3 :
            cout << "run insert( " << n.pos << ',' << i << " )\n" ;
            l.insert( n ,i ) ;
            break ;
        case 4 :
            cout << "run push_front( " << i << " )\n" ;
            l.push_front( i ) ;
            break ;
        default :
            cout << "run push_back( " << i << " )\n" ;
            l.push_back( i ) ;
        }
    }
    int_list::NODE n = l.begin() ;
    for ( ; n != l.end() ; n.go_forward() )
        cout << "[Node:" << n.pos << ",Data:" << n.data() << "] -> " ;
    for ( ; n.pos != l.P_NIL ; n.go_forward() )
        cout << "[Node:" << n.pos << ",Data:#NULL#] -> " ;
    cout << "NIL" ;
}

#endif
