#include "Simplex_Linear_Program.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std ;

using namespace Linear::Algebra ;

//template ostream& operator<< < 4 ,3 > ( std::ostream& os ,const typename Simplex_Linear_Program< 4 ,3 >::Solusion& s ) ;

constexpr size_t X = 3 ;
constexpr size_t CC = 2 ;

constexpr int N = 10 ;
double e[N][N] ;
auto& h = x ;

void test_simplex() {
    default_random_engine e( time(0) ) ;
    uniform_int_distribution< int > u( 1 ,99 ) ;
    bernoulli_distribution add_edge( 0.5 ) ;
    Simplex_Linear_Program< N ,(N-1)*N*6/10 > a ;
    a.set_obj( h[N] ) ;
    //set edge from source point
    for( int i = 1 ; i < N-1 ; ++i )
        if( add_edge(e) )
            ::e[0][i] = u(e) ,a.add_cc( h[i+1] <= 0 + ::e[0][i] ) ;
    //set edge from non-source point
    for( int i = 1 ; i < N ; ++i )
        for( int j = 0 ; j < N ; ++j )
            if( i != j ) {
                if( add_edge(e) )
                    ::e[i][j] = u(e) ,a.add_cc( h[j+1] <= h[i+1] + ::e[i][j] ) ;
            }
    cout << "Press Enter to start " ;
    cin.get() ;
    cout << a << a.solve() ;
}

