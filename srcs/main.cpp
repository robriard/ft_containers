/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:07:47 by hbaudet           #+#    #+#             */
/*   Updated: 2022/01/27 12:03:44 by unknow           ###   ########.fr       */
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
		std::cout << *it << ' ';
	std::cout << '\n';
}

int main()
{
	pair<int, std::string>			my_pair(8, "salut");
	map<int, std::string>			test;
	map<int, std::string>::iterator	it;

	test.insert(my_pair);
	test.insert(pair<int, std::string>(-4, "bar"));
	test.insert(pair<int, std::string>(2, "machin"));
	test.insert(pair<int, std::string>(3, "foo"));
	test.insert(pair<int, std::string>(746, "Marcel"));
	test.insert(pair<int, std::string>(1, "truc"));
	it = test.begin();
	std::cout << '\n';

	while (it != test.end())
	{
		// std::cout << "start of while\n";
		std::cout << it->first << ", " << it->second << '\n';
		it++;
// 		std::cout << "iterator incremented\n";

// #ifndef STD
// 		std::cout << it.getPointer() << '\n';
// 		std::cout << test.end().getPointer() << '\n';
// #endif

	}
	std::cout << "End of display loop\n";
}
