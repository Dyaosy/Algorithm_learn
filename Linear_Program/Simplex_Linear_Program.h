#ifndef Simplex_Linear_Program_H
#define Simplex_Linear_Program_H

#include "Algebra_Expression.h"

#include <algorithm>
#include <iostream>

enum Result_Type { Normal ,No_Bound ,No_Solusion };
inline std::ostream& operator<< ( std::ostream& os ,Result_Type r ) {
    switch ( r ) {
    case Normal:
        os << "Normal" ;
        break ;
    case No_Bound:
        os << "No_Bound" ;
        break ;
    case No_Solusion:
        os << "No_Solusion" ;
    }
    return os ;
}

template < size_t X ,size_t CC >
struct Linear_Program_Solusion {
    double maxinum = 0.0 , arr1[X] = { 0.0 } ,*root = arr1-1 ;
    Result_Type result = Normal ;
};

void test_simplex() ;

template < size_t X ,size_t CC >
class Simplex_Linear_Program {
public:
    typedef Linear_Program_Solusion< X ,CC > Solusion ;
    class Relaxed {
    private:
        bool bool_arr[X+CC+1] = { 0 } ,*B = bool_arr-1 ;
        double chart[CC+X+1][CC+X+2] = { { 0.0 } } ,dr_arr[X+CC+1] = { 0.0 } ,
               (*a)[CC+X+2] = chart-1 ,*obj_fun = dr_arr ;
        size_t num_of_cc = 0 ;
        Result_Type _result = Normal ;
        //boolean initializing = false ;
        bool equal ( double d1 ,double d2 ) {
            double def = d1-d2 ;
            return def > -1e-10 && def < 1e-10 ;
        }
        void set_basic( size_t index ) {
            B[index] = true ;
        }
        void set_nonbasic( size_t index ) {
            B[index] = false ;
        }
        void pivot( size_t l ,size_t e ,size_t max_index ) ;
        void initialize( const Simplex_Linear_Program& ) ;
        void solve( size_t max_index = X+CC ) ;
    public:
        Relaxed() = default ;
        ~Relaxed() = default ;
        Relaxed( const Simplex_Linear_Program& L ,size_t n ): num_of_cc(n) {
            initialize( L ) ;
            if( _result != Normal )
                return ;
            solve() ;
        }
        Result_Type result() const { return _result ; }
        void build_solusion( Solusion& solusion ) const ;
    };
private:
    double cc_coe[CC][X+1] = { { 0.0 } } , obj_fun_coe[X+1] = { 0,0 } ;
    size_t num_of_cc = 0 ;
    mutable bool solved = false ;
    mutable Solusion solusion ;
    friend Relaxed ;
    void _set_cc( size_t pos ,const Linear::Constraint_Condition& c ) {
        size_t n = std::min( X ,c.max_index() ) ,i = 0 ;
        for( ; i <= n ; ++i )
            cc_coe[pos][i] = c[i] ;
        for( ; i <= X ; ++i )
            cc_coe[pos][i] = 0 ;
        solved = false ;
    }
public:
    Simplex_Linear_Program() = default ;
    ~Simplex_Linear_Program() = default ;
    const Solusion& solve() const ;
    double& obj( size_t pos ) { return obj_fun_coe[pos] ; }
    const double& obj( size_t pos ) const { return obj_fun_coe[pos] ; }
    Linear::Expression obj() const {
        return Linear::Expression( obj_fun_coe ,X+1 ) ;
    }
    size_t cc_num () const { return num_of_cc ; }
    Linear::Constraint_Condition cc( size_t n ) const {
        return Linear::Constraint_Condition( Linear::Expression( cc_coe[n] ,X+1 ) ) ;
    }
    void set_obj( const Linear::Expression& l ) {
        size_t n = std::min( double( X ) ,l.max_index() ) ;
        for( size_t i = 0 ; i <= n ; ++i )
            obj_fun_coe[i] = l[i] ;
        solved = false ;
    }
    void set_cc( size_t pos ,const Linear::Constraint_Condition& c ) {
        if( pos >= num_of_cc )
            return ;
        _set_cc( pos ,c ) ;
    }
    void add_cc( const Linear::Constraint_Condition& c ) {
        if( num_of_cc >= CC )
            return ;
        _set_cc( num_of_cc++ ,c ) ;
    }
    void clean_obj() { std::fill_n( obj_fun_coe ,X+1 ,0.0 ) ; }
    void clean_cc() { num_of_cc = 0 ; }
    void clean_all() { clean_cc() ,clean_obj() ; }
};


template < size_t X ,size_t CC >
void Simplex_Linear_Program< X ,CC >::Relaxed::
  pivot( size_t leave ,size_t enter ,size_t max_index ) {
    a[leave][leave] = -1.0 ,a[leave][enter] = -a[leave][enter] ;
    for( size_t i = 0 ; i <= max_index ; ++i )
        a[enter][i] = a[leave][i]/a[leave][enter] ;
    a[enter][enter] = 0.0 ;
    set_nonbasic( leave ) ;
    for( size_t i = 1 ; i <= max_index ; ++i )
        if( B[i] ) {
            double enter_coe = a[i][enter] ;
            a[i][enter] = 0.0 ;
            for( size_t j = 0 ; j <= max_index ; ++j )
                a[i][j] += a[enter][j]*enter_coe ;
        }
    double enter_coe = obj_fun[enter] ;
    for( size_t i = 0 ; i <= max_index ; ++i )
        obj_fun[i] += a[enter][i]*enter_coe ;
    obj_fun[enter] = 0.0 ;
    set_basic( enter ) ;
}

template < size_t X ,size_t CC >
void Simplex_Linear_Program< X ,CC >::Relaxed::
  initialize( const Simplex_Linear_Program< X ,CC >& L ) {
#define min_coe (L.cc_coe[min_index][0])
    size_t min_index = 0 ;
    for( size_t i = min_index + 1 ; i < num_of_cc ; ++i )
        if( L.cc_coe[i][0] < min_coe )
            min_index = i ;
    for( size_t i = 0 ; i < num_of_cc ; ++i )
        std::copy( L.cc_coe[i] ,L.cc_coe[i+1] ,a[X+1+i] ) ;
    std::copy( std::begin( L.obj_fun_coe ) ,std::end( L.obj_fun_coe ) ,obj_fun ) ;
    std::fill_n( B+X+1 ,CC ,true ) ;
    if( min_coe < 0.0 ) {
        constexpr size_t EXTRA = X+CC+1 ;
        for( size_t i = X+1 ; i <= X+CC ; ++i )
            a[i][EXTRA] = 1.0 ;
        double temp_obj[X+CC+2] = { 0.0 } ;
        temp_obj[EXTRA] = -1.0 ;
        obj_fun = temp_obj ;
        pivot( X+min_index+1 ,EXTRA ,EXTRA ) ;//here can make some improvement
        solve( EXTRA ) ;
        obj_fun = dr_arr ;
        if( B[EXTRA] && !equal( a[EXTRA][0] ,0.0 ) ) {
            _result = No_Solusion ;
            return ;
        }
        for( size_t i = 1 ; i <= X ; ++i )
            if( B[i] ) {
                double coe = obj_fun[i] ;
                obj_fun[i] = 0.0 ;
                for( size_t j = 0 ; j <= X+CC ; ++j )
                    obj_fun[j] += a[i][j]*coe ;
            }
    }
    _result = Normal ;
#undef min_coe
}

template < size_t X ,size_t CC >
void Simplex_Linear_Program< X ,CC >::Relaxed::
  solve( size_t max_index ) {
    size_t enter ,leave ;
    while( ( enter = std::find_if( obj_fun + 1 ,obj_fun + max_index + 1 ,
                                  []( double db ){ return db>0 ; } ) - obj_fun ) <= max_index ) {
        leave = std::find( B+1 ,B+max_index+1 ,true ) - B ;
        for( size_t i = leave + 1 ; i <= max_index ; ++i )
            if( B[i] ) {
                if( a[leave][enter] >= 0.0 ) {
                    leave = i ;
                    continue ;
                }
                if( a[i][enter] >= 0.0 )
                    continue ;
                if( -a[i][0]/a[i][enter] < -a[leave][0]/a[leave][enter] )
                    leave = i ;
            }

        if( a[leave][enter] > 0 || equal( a[leave][enter] ,0.0 ) ) {
            _result = No_Bound ;
            return ;
        }
        pivot( leave ,enter ,max_index ) ;
    }
    _result = Normal ;
}

template < size_t X ,size_t CC >
void Simplex_Linear_Program< X ,CC >::Relaxed::
  build_solusion( Solusion &solusion ) const {
    solusion.result = _result ;
    if( _result != Normal )
        return ;
    solusion.maxinum = obj_fun[0] ;
    size_t i = 1 ;
    for( ; i <= X ; ++i )
        if( B[i] )
            solusion.root[i] = a[i][0] ,
            solusion.maxinum += a[i][0]*obj_fun[i] ;
        else
            solusion.root[i] = 0.0 ;
    for( ; i <= X+CC ; ++i )
        if( B[i] )
            solusion.maxinum += a[i][0]*obj_fun[i] ;
}

template < size_t X ,size_t CC >
const typename Simplex_Linear_Program< X ,CC >::Solusion&
  Simplex_Linear_Program< X ,CC >::solve() const {
    if( solved )
        return solusion ;
    Relaxed relaxed( *this ,num_of_cc ) ;
    solusion.result = relaxed.result() ;
    if( solusion.result == Normal )
        relaxed.build_solusion( solusion ) ;
    solved = true ;
    return solusion ;
}

template < size_t X ,size_t CC >
std::ostream& operator<< ( std::ostream& os ,const Simplex_Linear_Program< X ,CC >& L ) {
    os << "Objective Function :\n" << L.obj() << std::endl
        << "Constraint Condition(s) :\n" ;
    if( L.cc_num() )
        for( size_t i = 0 ; i < L.cc_num() ; ++i )
            os << L.cc( i ) << std::endl ;
    else os << "NULL\n" ;
    return os ;
}

template < size_t X ,size_t CC >
std::ostream& operator<< ( std::ostream& os ,const Linear_Program_Solusion< X ,CC >& s ) {
    if( s.result == Normal ) {
        os << "Maxinum : " << s.maxinum << std::endl ;
        for( size_t i = 1 ; i <= X ; ++i )
            os << 'X' << i << " = " << s.root[i] << std::endl ;
    }
    else os << s.result ;
    return os ;
}

#endif // Simplex_Linear_Program_H
