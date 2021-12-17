/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:47:13 by unknow            #+#    #+#             */
/*   Updated: 2021/12/14 21:43:33 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft {
/* ************************************************************************** */
/*               PAIR                                                         */
/* ************************************************************************** */
template <class T1, class T2>
struct pair {
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;

        pair() : first(), second(){return;};
        template<class U, class V>
        pair(const pair<U,V>& pr) : first(pr.first), second(pr.second){return;};
        pair(const first_type& a, const second_type& b) : first(a), second(b){return;};

        pair& operator=(const pair& pr) {
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        };

    private:
    
};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return lhs.first==rhs.first && lhs.second==rhs.second;}
template <class T1, class T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(lhs==rhs);}
template <class T1, class T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);}
template <class T1, class T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(rhs<lhs);}
template <class T1, class T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return rhs<lhs;}
template <class T1, class T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(lhs<rhs);}

/* ************************************************************************** */
/*               MAKE_PAIR                                                    */
/* ************************************************************************** */
    template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {return (pair<T1, T2>(x, y));}
}

#endif