/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:47:06 by unknow            #+#    #+#             */
/*   Updated: 2021/12/28 22:27:24 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "vector.hpp"

#ifndef STD
# define NAMESPACE ft
# define STATUS (std::string)"ft"
#else
# define NAMESPACE std
# define STATUS (std::string)"std"
#endif

using namespace NAMESPACE;

template <class T>
void	print(vector<vector<T> >& lst)
{
	for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
            std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void	print(vector<T>& lst)
{
	for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}
class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template <class T>
void	print_vector(vector<T> &test, int index = 0)
{
	typename vector<T>::iterator		beg = test.begin();
	typename vector<T>::iterator		end = test.end();
	std::cout << index << ": size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void	push_pop_back_tests(void)
{
    if (STATUS == (std::string)"ft") std::cout << std::endl << "FT PUSH BACK & POP BACK TESTS" << std::endl;
    else std::cout << std::endl << "STD PUSH BACK & POP BACK TESTS" << std::endl;
	vector<T> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(i);
		std::cout << test.size() << ": " << test.capacity() << " - ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	print_vector<T>(test);
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	print_vector<T>(test);
}

template <class T>
void	resize_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT RESIZE TESTS" << std::endl;
	else std::cout << std::endl << " STD RESIZE TESTS" << std::endl;
    vector<T> test(12, 12);
	std::cout << "12: s: " << test.size() << ", c: " << test.capacity() << std::endl;

	test.resize(72);
	std::cout << "72: s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "100: s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "4170: s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "171: s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "62: s: " << test.size() << ", c: " << test.capacity() << std::endl;
}

template <class T>
void	insert_tests()
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT INSERT TESTS" << std::endl;
	else std::cout << std::endl << "STD INSERT TESTS" << std::endl;
    vector<T> test(1, 1);
	vector<T> test2(5, 5);
	print_vector<T>(test, 0);
	
	test.insert(test.begin(), 200, 12);
	print_vector<T>(test, 1);
	test.insert(test.begin() + 12, 200, 30);
	print_vector<T>(test, 2);
	test.insert(test.end(), 12, 50);
	print_vector<T>(test, 3);
	test.insert(test.end() - 1, 0, 60);
	print_vector<T>(test, 4);
	test.insert(test.end() - 1, 1, 70);
	print_vector<T>(test, 5);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	print_vector<T>(test, 6);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	print_vector<T>(test, 7);
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<T>(test, 8);
}

template <class T>
void	reserve_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT RESERVE TESTS" << std::endl;
    else std::cout << std::endl << "STD RESERVE TESTS" << std::endl;
	vector<T> test(65, 7);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(66);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(128);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(1023);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(10252);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	try
	{
		test.reserve(test.max_size() + 1);
	}
	catch(std::length_error &le)
	{
		std::cout << "length error" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	print_vector<T>(test);
}

template <class T>
void	copy_swap_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT COPY && SWAP TESTS" << std::endl;
    else std::cout << std::endl << "STD COPY && SWAP TESTS" << std::endl;
	vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	print_vector<T>(test_copy);
	vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print_vector<T>(test_range);
	test_copy.swap(test);
	print_vector<T>(test);
	print_vector<T>(test_copy);
	test_copy.swap(test_range);
	print_vector<T>(test_range);
	print_vector<T>(test_copy);
	test.swap(test_copy);
	print_vector<T>(test);
	print_vector<T>(test_copy);
}

template <class T>
void	reverse_it_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT REVERSE IT TESTS" << std::endl;
    else std::cout << std::endl << "STD REVERSE IT TESTS" << std::endl;
	vector<T> test;
	for (size_t i = 0; i < 12; i++) { test.push_back(i); }
	typename vector<T>::reverse_iterator		revbeg = test.rbegin();
	for (typename vector<T>::reverse_iterator it = revbeg; it != test.rend(); it++)
	{
		std::cout << *it << " ";
		if (!((revbeg - it) % 10) && it != revbeg)
			std::cout << std::endl;
	}
	std::cout << *(test.rbegin() + 2) << std::endl;
	std::cout << *(test.rend() - 8) << std::endl;
	std::cout << (test.rbegin() == revbeg) << std::endl;
	revbeg++;
	std::cout << *revbeg << std::endl;
	std::cout << (test.rbegin() == test.rend()) << std::endl;
	std::cout << (test.rbegin() <= test.rbegin()) << std::endl;
	std::cout << (test.rbegin() < test.rend()) << std::endl;
	std::cout << (test.rbegin() >= test.rend()) << std::endl;
	revbeg += 3;
	std::cout << *revbeg << std::endl;
	std::cout << std::endl;
}

template <class T>
void	erase_clear_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT ERASE && CLEAR TESTS" << std::endl;
    else std::cout << std::endl << "STD ERASE && CLEAR TESTS" << std::endl;
	vector<T> test(31, 12);
	test.erase(test.begin(), test.begin() + 5);
	print_vector<T>(test);
	test.erase(test.begin() + 12, test.begin() + 16);
	print_vector<T>(test);
	test.clear();
	print_vector<T>(test);
}

void	max_size_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT MAX SIZE TESTS" << std::endl;
    else std::cout << std::endl << "STD MAX SIZE TESTS" << std::endl;
	vector<int> test(31, 12);
	vector<std::string> test2;
	vector<long long int> test3;
	vector<Awesome> test4;
	vector<unsigned int> test5(12, 340);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
}

void	awesome_tests(void)
{
	if (STATUS == (std::string)"ft") std::cout << std::endl << "FT AWESOME TESTS" << std::endl;
    else std::cout << std::endl << "STD AWESOME TESTS" << std::endl;
	vector<Awesome> test(21, 12);
	print_vector<Awesome>(test);
	vector<Awesome> test2;
	print_vector<Awesome>(test2);
	test2.push_back(12);
	test2.push_back(8);
	test2.push_back(16);
	print_vector<Awesome>(test2);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.assign(test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test = test2;
	print_vector<Awesome>(test);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test.insert(test.begin(), test2.begin(), test2.end());
	test2 = test;
	print_vector<Awesome>(test);
	std::cout << "end awesome test" << std::endl;
}

int main()
{
	push_pop_back_tests<int>();
	resize_tests<int>();
	insert_tests<int>();
	reserve_tests<int>();
	copy_swap_tests<int>();
	reverse_it_tests<int>();
	erase_clear_tests<int>();
	max_size_tests();
	awesome_tests();
	push_pop_back_tests<Awesome>();
	resize_tests<Awesome>();
	insert_tests<Awesome>();
	reserve_tests<Awesome>();
	copy_swap_tests<Awesome>();
	reverse_it_tests<Awesome>();
	erase_clear_tests<Awesome>();
}