//
//  lost.h
//  mycoin
//
//  Created by lx on 13-12-21.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef mycoin_lost_h
#define mycoin_lost_h
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#include <stdlib.h>
using namespace std;

template <typename Map, typename F>
void map_erase_if(Map& m, F pred)
{
    for (typename Map::iterator i = m.begin();
         (i = find_if(i, m.end(), pred)) != m.end();
         m.erase(i++));
}

template <typename F,typename G>
class Compose_F_Gx : public std::unary_function<typename G::argument_type,typename F::result_type>
{
public:
    Compose_F_Gx(const F& _f,const G& _g):f(_f),g(_g)
    {
    }
    typename F::result_type
    operator()(const typename G::argument_type& x) const
    {
        return f(g(x));
    }
private:
    F f;
    G g;
};

template <typename F,typename G>
inline Compose_F_Gx<F,G> compose1(const F& f,const G& g)
{
    return Compose_F_Gx<F,G>(f,g);
}
 

template< typename Pair >
struct select1st:public unary_function<Pair, typename Pair::second_type>
 {
 
 const typename Pair::first_type & operator()(const Pair & p ) const
 {
 return p.first;
 }
 };

template< typename Pair >
 struct select2nd:public unary_function<Pair,typename Pair::second_type>
 {
 
 const typename Pair::second_type & operator()(const Pair & p) const
 {
 return p.second;
 }
 };



#endif
