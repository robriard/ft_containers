/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:27:02 by unknow            #+#    #+#             */
/*   Updated: 2021/12/28 23:47:40 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "vector.hpp"

template <class T>
void	print_vector(ft::vector<T> &test, int index)
{
	// typename ft::vector<T>::iterator		beg = test.begin();
	// typename ft::vector<T>::iterator		end = test.end();
	std::cout << index << ": size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	// for (typename ft::vector<T>::iterator it = beg; it != end; it++)
	// {
	// 	std::cout << *it << " ";
	// 	if (((it - beg) % 10 == 9) && it > beg)
	// 		std::cout << std::endl;
	// }
	// std::cout << std::endl;
}

template <class T>
void	print_vector(std::vector<T> &test, int index)
{
	// typename std::vector<T>::iterator		beg = test.begin();
	// typename std::vector<T>::iterator		end = test.end();
	std::cout << index << ": size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	// for (typename std::vector<T>::iterator it = beg; it != end; it++)
	// {
	// 	std::cout << *it << " ";
	// 	if (((it - beg) % 10 == 9) && it > beg)
	// 		std::cout << std::endl;
	// }
	// std::cout << std::endl;
}

int main(){
    std::cout << "FT" << std::endl;
    {
        ft::vector<int> test2(5, 5);
        
        
        ft::vector<int> test(1, 1);
        print_vector<int>(test, 0);
        
        test.insert(test.begin(), 200, 12);
        print_vector<int>(test, 1);
        test.insert(test.begin() + 12, 210, 30);
        print_vector<int>(test, 2);
        test.insert(test.end(), 12, 50);
        print_vector<int>(test, 3);
        test.insert(test.end() - 1, 0, 60);
        print_vector<int>(test, 4);
        test.insert(test.end() - 1, 1, 70);
        print_vector<int>(test, 5);
        test.insert(test.begin() + 412, test2.begin(), test2.end());
        print_vector<int>(test, 6);
        test.insert(test.begin() + 6, test2.begin(), test2.end());
        print_vector<int>(test, 7);
        test.insert(test.end(), test2.begin(), test2.end());
        print_vector<int>(test, 8);
    }
    std::cout << std::endl << "STD" << std::endl;
    {
        std::vector<int> test2(5, 5);
        
        
        std::vector<int> test(1, 1);
        print_vector<int>(test, 0);
        
        test.insert(test.begin(), 200, 12);
        print_vector<int>(test, 1);
        test.insert(test.begin() + 12, 210, 30);
        print_vector<int>(test, 2);
        test.insert(test.end(), 12, 50);
        print_vector<int>(test, 3);
        test.insert(test.end() - 1, 0, 60);
        print_vector<int>(test, 4);
        test.insert(test.end() - 1, 1, 70);
        print_vector<int>(test, 5);
        test.insert(test.begin() + 412, test2.begin(), test2.end());
        print_vector<int>(test, 6);
        test.insert(test.begin() + 6, test2.begin(), test2.end());
        print_vector<int>(test, 7);
        test.insert(test.end(), test2.begin(), test2.end());
        print_vector<int>(test, 8);
    }
}