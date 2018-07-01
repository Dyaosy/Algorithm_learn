#ifndef STANDARD_LINEAR_PROGRAM_H
#define STANDARD_LINEAR_PROGRAM_H

#include <algorithm>

enum Result_Type { Normal ,No_Bound ,No_Solusion };

template < size_t X ,size_t CC >
class Standard_Linear_Program {
public:
    struct Solusion {
        double maxinum = 0.0 , root[X+1] = { 0.0 } ;
        Result_Type result = Normal ;
    };
    class Relaxed {
    private:
        bool arr1[X+CC+1] = { 0 } ,arr2[X+CC+1] = { 0 } ,
             *B = arr1-1 ,*N = arr2-1 ;
        double chart[CC+X+1][CC+X+2] = { { 0.0 } } ,
               (*a)[CC+X+2] = chart-1 ,obj_fun[X+CC+1] = { 0.0 } ;
        Result_Type _result = Normal ;
        //boolean initializing = false ;
        void set_basic( size_t index ) {
            B[index] = true ,
            N[index] = false ;
        }
        void set_nonbasic( size_t index ) {
            N[index] = true ,
            B[index] = false ;
        }
        void pivot( size_t l ,size_t e ) ;
        void initialize( const Standard_Linear_Program& ) ;
        Result_Type solve( double obj[] = nullptr ) ;
    public:
        Relaxed() = default ;
        ~Relaxed() = default ;
        Relaxed( const Standard_Linear_Program& L ) {
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
    mutable bool solved = false ;
    mutable Solusion solusion ;
    friend Relaxed ;
public:
    Standard_Linear_Program() = default ;
    ~Standard_Linear_Program() = default ;
    const Solusion& solve() const ;
};

template < size_t X ,size_t CC >
void Standard_Linear_Program< X ,CC >::Relaxed::
  pivot( size_t leave ,size_t enter ) {
    set_basic(enter) ;
    set_nonbasic(leave) ;
}

template < size_t X ,size_t CC >
void Standard_Linear_Program< X ,CC >::Relaxed::
  initialize( const Standard_Linear_Program< X ,CC >& L ) {
#define min_coe (L.cc_coe[min_index][0])
    size_t min_index = 1 ;
    for( size_t i = min_index + 1 ; i <= X ; ++i )
        if( L.cc_coe[i][0] < min_coe )
            min_index = i ;
    for( size_t i = 1 ; i <= CC ; ++i )
        std::copy( L.cc_coe[i] ,L.cc_coe[i+1] ,a[X+i] ) ;
    std::copy( std::begin( L.obj_fun_coe ) ,std::end( L.obj_fun_coe ) ,obj_fun ) ;
    std::fill( B+X+1 ,B+X+CC+1 ,true ) ;
    std::fill( N+1 , N+X+1 ,true ) ;
    if( min_coe < 0 ) {
        constexpr size_t EXTRA = X+CC+1 ;
        for( size_t i = X+1 ; i <= X+CC ; ++i )
            a[i][EXTRA] = 1.0 ;
        N[EXTRA] = true ;
        pivot( min_index ,EXTRA ) ;
    }

#undef min_coe
}


template < size_t X ,size_t CC >
Result_Type Standard_Linear_Program< X ,CC >::Relaxed::
  solve( double obj[] ) {
    //const size_t max_index = X + CC + size_t( obj!=nullptr ) ;
    if( !obj /* obj == nullptr */ ) {
        obj = obj_fun ;
    }
    return Normal ;
}

template < size_t X ,size_t CC >
void Standard_Linear_Program< X ,CC >::Relaxed::
  build_solusion( Solusion &solusion ) const {
    solusion.result = _result ;
    if( _result != Normal )
        return ;
    solusion.maxinum = obj_fun[0] ;
    for( size_t i = 1 ; i <= X ; ++i )
        if( B[i] )
            solusion.root[i] = a[i][0] ,
            solusion.maxinum += a[i][0]*obj_fun[i] ;
        else
            solusion.root[i] = 0.0 ;
}

template < size_t X ,size_t CC >
const typename Standard_Linear_Program< X ,CC >::Solusion&
  Standard_Linear_Program< X ,CC >::solve() const {
    if( solved )
        return solusion ;
    Relaxed relaxed( *this ) ;
    solusion.result = relaxed.result() ;
    if( solusion.result == Normal )
        relaxed.build_solusion( solusion ) ;
    solved = true ;
    return solusion ;
}



#endif // STANDARD_LINEAR_PROGRAM_H
