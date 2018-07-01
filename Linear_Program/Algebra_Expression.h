#ifndef ALGEBRA_EXPRESSION_H
#define ALGEBRA_EXPRESSION_H

#include <bits/move.h>
#include <iostream>
#include <initializer_list>
#include <algorithm>

namespace Linear {

class Expression ;
class Basic_Algebra ;
class Constraint_Condition ;

class Expression {
public :
    typedef unsigned int size_type ;
    static const size_t Max_Index = 100 ;
private :
    double coefficients[ Max_Index + 1 ] = { 0.0 } ;
    mutable size_type _max_index = 0 ;
    void set_max_index() const {
        static double def ;
        while( _max_index > 0 && ( def = coefficients[_max_index] - 0.0 , def > -1e-14 && def < 1e-14 ) )
            --_max_index ;
    }
    friend Basic_Algebra ;
    friend Constraint_Condition ;
public :
    static const Expression ZERO ;
    Expression() = default ;
    ~Expression() = default ;
    double max_index () const { set_max_index() ; return _max_index ; }
    Expression( const Expression& l ) : _max_index(l._max_index) {
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] = l.coefficients[i] ;
    }
    explicit Expression( const std::initializer_list< double >& l ) {
        size_t n = std::min( Max_Index + 1 , l.size() ) ;
        std::copy_n( l.begin() ,n ,coefficients ) ;
        n != 0 && --n , _max_index = n ;
    }
    template < typename T >
    explicit Expression( T arr[] ,size_t s ) {
        size_t n = std::min( Max_Index + 1 , s ) ;
        std::copy_n( arr ,n ,coefficients ) ;
        n != 0 && --n , _max_index = n ;
    }
    Expression& operator= ( const Expression& l ) {
        for( size_type i = 0 ; i <= Max_Index ; ++i )
            coefficients[i] = l.coefficients[i] ;
        _max_index = l._max_index ;
        return *this ;
    }
    Expression operator+ ( const Expression& l ) && {
        if( l._max_index > _max_index )
            _max_index = l._max_index ;
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] += l.coefficients[i] ;
        set_max_index() ;
        return *this ;
    }
    Expression operator+ ( const Expression& l ) const & {
        return Expression(*this) + l ;
    }
    Expression operator+ ( double db ) && {
        coefficients[0] += db ;
        return *this ;
    }
    Expression operator+ ( double db ) const & {
        return Expression(*this) + db ;
    }
    Expression& operator+= ( const Expression& l ) {
        if( l._max_index > _max_index )
            _max_index = l._max_index ;
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] += l.coefficients[i] ;
        set_max_index() ;
        return *this ;
    }
    Expression& operator+= ( double db ) {
        coefficients[0] += db ;
        return *this ;
    }
    Expression operator- ( const Expression& l ) && {
        if( l._max_index > _max_index )
            _max_index = l._max_index ;
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] -= l.coefficients[i] ;
        set_max_index() ;
        return *this ;
    }
    Expression operator- ( const Expression& l ) const & {
        return Expression(*this) - l ;
    }
    Expression operator- ( double db ) && {
        coefficients[0] -= db ;
        return *this ;
    }
    Expression operator- ( double db ) const & {
        return Expression(*this) - db ;
    }
    Expression& operator-= ( const Expression& l ) {
        if( l._max_index > _max_index )
            _max_index = l._max_index ;
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] -= l.coefficients[i] ;
        set_max_index() ;
        return *this ;
    }
    Expression& operator-= ( double db ) {
        coefficients[0] -= db ;
        return *this ;
    }
    Expression operator* ( double db ) && {
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] *= db ;
        set_max_index() ;
        return *this ;
    }
    Expression operator* ( double db ) const & {
        return Expression(*this) * db ;
    }
    Expression operator*= ( double db ) {
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] *= db ;
        set_max_index() ;
        return *this ;
    }
    Expression operator/ ( double db ) && {
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] /= db ;
        set_max_index() ;
        return *this ;
    }
    Expression operator/ ( double db ) const & {
        return Expression(*this) / db ;
    }
    Expression operator/= ( double db ) {
        for( size_type i = 0 ; i <= _max_index ; ++i )
            coefficients[i] /= db ;
        set_max_index() ;
        return *this ;
    }
    Expression operator+ () const & {
        return *this ;
    }
    Expression operator- () const & {
        Expression temp( *this ) ;
        for( auto& n : temp.coefficients )
            n = -n ;
        return temp ;
    }
    double& operator[] ( size_type pos ) {
        if( pos > max_index() )
            _max_index = pos ;
        return coefficients[pos] ;
    }
    const double& operator[] ( size_type pos ) const {
        return coefficients[pos] ;
    }
    friend Expression operator+ ( double db ,Expression&& l ) {
        return l + db ;
    }
    friend Expression operator+ ( double db ,const Expression& l ) {
        return l + db ;
    }
    friend Expression operator- ( double db ,Expression&& l ) {
        return -l + db ;
    }
    friend Expression operator- ( double db ,const Expression& l ) {
        return -l + db ;
    }
    friend Expression operator* ( double db ,Expression&& l ) {
        return l * db ;
    }
    friend Expression operator* ( double db ,const Expression& l ) {
        return l * db ;
    }
    friend std::ostream& operator<< ( std::ostream& os ,const Expression& l ) ;
};

/*class Single_Algebra {
public:
    typedef unsigned int size_type ;
private:
    size_type index ;
    double coefficent = 1.0 ;
    Single_Algebra( size_type n ) : index( n )
public:
    Expression operator+ ( const Single_Algebra& ) {
        Expression l ;

    }
    Expression operator+ ( Expression&& ) ;
    Expression operator+ ( const Expression& ) ;
    Expression operator+ ( double db ) ;
    Expression operator- ( const Single_Algebra& ) ;
    Expression operator- ( Expression&& ) ;
    Expression operator- ( const Expression& ) ;
    Expression operator- ( double db ) ;
    Single_Algebra operator* ( double db ) ;
    Single_Algebra operator/ ( double db ) ;
    friend operator+ ( Expression&& ,const Single_Algebra& ) ;
    friend operator+ ( const Expression& ,const Single_Algebra& ) ;
    friend operator+ ( double ,const Single_Algebra& ) ;
    friend operator- ( Expression&& ,const Single_Algebra& ) ;
    friend operator- ( const Expression&,const Single_Algebra& ) ;
    friend operator- ( double ,const Single_Algebra& ) ;
    friend operator* ( double ,const Single_Algebra& ) ;
};*/

class Basic_Algebra {
private:
    static bool x_is_defined ;
    public:
    Basic_Algebra() {
        if( x_is_defined ) {
            std::cerr << "BAN : Define another Basic_Algebra \n" ;
            throw( "BAN : Define another Basic_Algebra \n" ) ;
        }
        else x_is_defined = true ;
    }
    Expression operator[] ( Expression::size_type pos ) const {
        if( pos < 1 || pos > Expression::Max_Index ) {
            std::cerr << "BAN : The subscript is beyond the range ( 1 ~ " << Expression::Max_Index << " )\n" ;
            throw ( "BAN : The subscript is beyond the range " ) ;
        }
        Expression l ;
        l.coefficients[pos] = 1.0 ;
        l._max_index = pos ;
        return l ;
    }
};

namespace Algebra {
extern const Basic_Algebra x ;
}

class Constraint_Condition {
private:
    Expression limit ; //To keep limit >= 0
public:
    static const Constraint_Condition ZERO ;
    Constraint_Condition() = default ;
    Constraint_Condition( const Constraint_Condition& l ) : limit( l.limit ) {}
    explicit Constraint_Condition( const Expression& l ) : limit( l ) {}
    explicit Constraint_Condition( const std::initializer_list< double >& l ) : limit( l ) {}
    size_t max_index() const { return limit.max_index() ; } ;
    //double& operator[] ( size_t s ) { return limit[s] ; }
    const double& operator[] ( size_t s ) const { return limit[s] ; }
    friend std::ostream& operator<< ( std::ostream& os ,const Constraint_Condition& l ) {
        os << l.limit << " >= 0" ;
        return os ;
    }
};

} // name space Linear

inline Linear::Constraint_Condition operator>= ( const Linear::Expression& l1 ,const Linear::Expression& l2 ) {
    return Linear::Constraint_Condition( l1 - l2 ) ;
}
inline Linear::Constraint_Condition operator>= ( const Linear::Expression& l ,double db ) {
    return Linear::Constraint_Condition( l - db ) ;
}
inline Linear::Constraint_Condition operator>= ( double db ,const Linear::Expression& l ) {
    return Linear::Constraint_Condition( db - l ) ;
}
inline Linear::Constraint_Condition operator<= ( const Linear::Expression& l1 ,const Linear::Expression& l2 ) {
    return Linear::Constraint_Condition( l2 - l1 ) ;
}
inline Linear::Constraint_Condition operator<= ( const Linear::Expression& l ,double db ) {
    return Linear::Constraint_Condition( db - l ) ;
}
inline Linear::Constraint_Condition operator<= ( double db ,const Linear::Expression& l ) {
    return Linear::Constraint_Condition( l - db ) ;
}


#endif // ALGEBRA_EXPRESSION_H
