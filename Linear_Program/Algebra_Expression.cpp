#include "Algebra_Expression.h"


inline bool equal ( double d1 ,double d2 ) {
    double def = d1-d2 ;
    return def > -1e-10 && def < 1e-10 ;
}

inline std::ostream& print_coe( std::ostream& os ,double db ) {
    if( equal( db ,1.0 ) )
        os << '+' ;
    else if( equal( db ,-1.0 ) )
        os << '-' ;
    else os << db << '*' ;

    return os ;
}

namespace Linear {

const Expression Expression::ZERO( { 0.0 } ) ;
const Constraint_Condition Constraint_Condition::ZERO( { 0.0 } ) ;

std::ostream& operator<< ( std::ostream& os ,const Expression& l ) {
    l.set_max_index() ;
    bool not_first = false ;
    os << std::noshowpos ;
    if( !l.max_index() )
        return os << l.coefficients[0] << std::noshowpos ;
    Expression::size_type i = 1 ;
    while( equal( l.coefficients[i] , 0.0 ) )
        ++i ;
    if( i )
        print_coe( os ,l.coefficients[i] ) << "X" << i ,++i ;
    else os << l.coefficients[i++] ;
    os << std::showpos ;
    for( ; i <= l._max_index ; ++i )
        if( !equal( l.coefficients[i] ,0.0 ) )
            print_coe( os << ' ' ,l.coefficients[i] ) << "X" << i ;
    if( !equal( l.coefficients[0] ,0.0 ) )
        os << ' ' << l.coefficients[0] ;
    return os << std::noshowpos ;
}


inline Constraint_Condition operator>= ( const Expression& l1 ,const Expression& l2 ) {
    return Constraint_Condition( l1 - l2 ) ;
}
inline Constraint_Condition operator>= ( const Expression& l ,double db ) {
    return Constraint_Condition( l - db ) ;
}
inline Constraint_Condition operator>= ( double db ,const Expression& l ) {
    return Constraint_Condition( db - l ) ;
}
inline Constraint_Condition operator<= ( const Expression& l1 ,const Expression& l2 ) {
    return Constraint_Condition( l2 - l1 ) ;
}
inline Constraint_Condition operator<= ( const Expression& l ,double db ) {
    return Constraint_Condition( db - l ) ;
}
inline Constraint_Condition operator<= ( double db ,const Expression& l ) {
    return Constraint_Condition( l - db ) ;
}


bool Basic_Algebra::x_is_defined = false ;

namespace Algebra {
const Basic_Algebra x ;
}//namespace Algebra

}//namespace Linear
