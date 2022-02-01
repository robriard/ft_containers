/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/02/01 16:37:31 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifdef FT
# include "vector.hpp"
# include "stack.hpp"
# include "map.hpp"
# include "set.hpp"
# define NAMESPACE ft
#elif STD
# include <vector>
# include <stack>
# include <map>
# include <set>
# define NAMESPACE std
#else
# error NAMESPACE not define.
#endif

using namespace NAMESPACE;

template <class InputIterator>
void Printelem(InputIterator first, InputIterator last) {
	for (; first != last; first++)
		std::cout << "[" << *first << "]" << std::endl;
	std::cout << "===============================================\n";
}

template <class InputIterator>
void Printmap(InputIterator first, InputIterator last) {
	for (; first != last; first++)
		std::cout << "[" << first->first << "] => [" << first->second << "]" <<std::endl;
	std::cout << "===============================================\n";
}

int main(void) {
/* ************************************************************************** */
/*                VECTOR                                                      */
/* ************************************************************************** */
	std::cout << std::boolalpha;
	{
		std::cout << "/* ************************************************************************** */" << std::endl;
		std::cout << "/*                VECTOR                                                      */" << std::endl;
		std::cout << "/* ************************************************************************** */" << std::endl;
		
		NAMESPACE::vector<int> vec;
		std::cout << "max_size = " << vec.max_size() << std::endl;
		
		std::cout << "empty ? " << vec.empty() << std::endl;
		std::cout << "size = " << vec.size() << std::endl;
		vec.insert(vec.begin(), 42);
		std::cout << "empty ? " << vec.empty() << std::endl;
		std::cout << "size = " << vec.size() << std::endl;
		Printelem(vec.begin(), vec.end());

		vec.assign(10, 21);
		Printelem(vec.rbegin(), vec.rend());

		vec.insert(vec.end(), -1);
		std::cout << "front = " << vec.front() << std::endl;
		std::cout << "back = " << vec.back() << std::endl;
		std::cout << vec.at(10) << std::endl;
	

		std::cout << "Test of assignation operator\n";
		NAMESPACE::vector<int> vec2 = vec;
		Printelem(vec2.begin(), vec2.end());

		std::cout << "Test of clear()\n";
		vec.clear();
		Printelem(vec.begin(), vec.end());

		std::cout << "Test of swap()\n";
		vec.swap(vec2);
		std::cout << "VEC\n";
		Printelem(vec.begin(), vec.end());
		std::cout << "VEC2\n";
		Printelem(vec2.begin(), vec2.end());




		std::cout << "Test of erase()\n";
		vec.erase(vec.begin(), --vec.end());
		Printelem(vec.begin(), vec.end());

		vec.erase(vec.begin());
		Printelem(vec.begin(), vec.end());
	};
	

/* ************************************************************************** */
/*                STACK                                                       */
/* ************************************************************************** */
	{
		std::cout << "\n\n";
		std::cout << "/* ************************************************************************** */" << std::endl;
		std::cout << "/*                STACK                                                       */" << std::endl;
		std::cout << "/* ************************************************************************** */" << std::endl;
		NAMESPACE::stack<char> mystack;
		std::cout << "empty ? " << mystack.empty() << std::endl;
		std::cout << "size = " << mystack.size() << std::endl;
		mystack.push('*');
		std::cout << "top = " << mystack.top() << std::endl;
		std::cout << "size = " << mystack.size() << std::endl;
		mystack.pop();
		std::cout << "size = " << mystack.size() << std::endl;
		std::cout << mystack.size() << std::endl;
	};

/* ************************************************************************** */
/*                MAP                                                         */
/* ************************************************************************** */
	{
		std::cout << "\n\n";
		std::cout << "/* ************************************************************************** */" << std::endl;
		std::cout << "/*                MAP                                                         */" << std::endl;
		std::cout << "/* ************************************************************************** */" << std::endl;
		NAMESPACE::map<float, short unsigned> mymap;
		std::cout << "max size = " << mymap.max_size() << std::endl << std::endl;

		std::cout << "empty ? " << mymap.empty() << std::endl;
		std::cout << "size = " << mymap.size() << std::endl;

		mymap.insert(pair<float, short unsigned>(3.14, 18));
		mymap.insert(pair<float, short unsigned>(101.1337, 42000));
		mymap.insert(pair<float, short unsigned>(2.99792458, 0));
		mymap.insert(pair<float, short unsigned>(-12.30, 1906));
		mymap.insert(pair<float, short unsigned>(69.42069, 42069));
		mymap.insert(pair<float, short unsigned>(8, 42));
		pair<NAMESPACE::map<float, short unsigned>::iterator, bool> ret1 = mymap.insert(pair<float, short unsigned>(1, 18));
		pair<NAMESPACE::map<float, short unsigned>::iterator, bool> ret2 = mymap.insert(pair<float, short unsigned>(3.14, 18));




		std::cout << "test for double mapped_type : " << ret1.second << std::endl;
		std::cout << "test for double key_type : " << ret2.second << std::endl;
		Printmap(mymap.begin(), mymap.end());

		std::cout << "size = " << mymap.size() << std::endl;
		std::cout << "mymap[-12.30] = " <<mymap[-12.30] << std::endl;
		std::cout << "find(3.14) = " << mymap.find(3.14)->second << '\n';
		std::cout << "test find(0) : ";
		if (mymap.find(0) == mymap.end())
			std::cout << "find\n";
		else
			std::cout << "not find\n";


		std::cout << "test copy\n";
		NAMESPACE::map<float, short unsigned> copy(mymap);
		Printmap(copy.rbegin(), copy.rend());

		std::cout << "test cleat mymap\n";
		mymap.clear();
		Printmap(mymap.begin(), mymap.end());

		std::cout << "test swap\n";
		mymap.swap(copy);
		std::cout << "MYMAP\n";
		Printmap(mymap.begin(), mymap.end());
		std::cout << "MYMAP\n";
		Printmap(copy.begin(), copy.end());
		
		
		std::cout << "TEST ERASE" << std::endl;
		std::cout << "erase a non-Node :\n";
		mymap.erase(42);
		Printmap(mymap.begin(), mymap.end());
		std::cout << "erase Node 8 :\n";
		mymap.erase(8);
		Printmap(mymap.begin(), mymap.end());
		std::cout << "erase from begin() to end() :\n";
		mymap.erase(mymap.begin(), mymap.end());
		Printmap(mymap.begin(), mymap.end());
	};
	
	/* ************************************************************************** */
	/*                set                                                         */
	/* ************************************************************************** */
	{
		std::cout << "\n\n";
		std::cout << "/* ************************************************************************** */" << std::endl;
		std::cout << "/*                set                                                         */" << std::endl;
		std::cout << "/* ************************************************************************** */" << std::endl;
		NAMESPACE::set<float> myset;
		std::cout << "max size() = " << myset.max_size() << std::endl << std::endl;

		std::cout << "empty ? " << myset.empty() << std::endl;
		std::cout << "size = " << myset.size() << std::endl;

		myset.insert(3.14);
		myset.insert(101.1337);
		myset.insert(2.99792458);
		myset.insert(12.30);
		myset.insert(69.42069);
		myset.insert(42);
		pair<NAMESPACE::set<float>::iterator, bool> ret = myset.insert(18);
		std::cout << "insert double key : " << ret.second << std::endl;
		Printelem(myset.begin(), myset.end());

		std::cout << "size = " << myset.size() << std::endl;
		std::cout << "try find(0) : ";
		if (myset.find(0) == myset.end())
			std::cout << "not found\n";
		else
			std::cout << "found\n";

		std::cout << "test copy\n";
		NAMESPACE::set<float> copy(myset);
		Printelem(copy.begin(), copy.end());

		std::cout << "test clear mymset\n";
		myset.clear();
		Printelem(myset.begin(), myset.end());
		
		std::cout << "test swap\n";
		myset.swap(copy);
		std::cout << "MYSET\n";
		Printelem(myset.begin(), myset.end());
		std::cout << "COPY\n";
		Printelem(copy.begin(), copy.end());

		std::cout << "test erase 42 :\n";
		myset.erase(42);
		Printelem(myset.begin(), myset.end());
		std::cout << "test erase 8 :\n";
		myset.erase(8);
		Printelem(myset.begin(), myset.end());
		std::cout << "test erase from begin() to end() :\n";
		myset.erase(myset.begin(), myset.end());
		Printelem(myset.begin(), myset.end());
	};
}