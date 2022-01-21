/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/01/21 18:01:50 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  map<char,int> foo,bar;
  foo['a']=100;
  foo['b']=200;
  bar['a']=10;
  bar['z']=1000;

  // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
  if (foo == bar) std::cout << "1 foo and bar are equal\n";
  if (foo != bar) std::cout << "2 foo and bar are not equal\n";
  if (foo < bar) std::cout << "3 foo is less than bar\n";
  if (foo > bar) std::cout << "4 foo is greater than bar\n";
  if (foo <= bar) std::cout << "5 foo is less than or equal to bar\n";
  if (foo >= bar) std::cout << "6 foo is greater than or equal to bar\n";

  return 0;
}
