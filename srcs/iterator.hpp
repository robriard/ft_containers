/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:03:37 by unknow            #+#    #+#             */
/*   Updated: 2022/01/25 12:37:52 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IERATOR_HPP
# define IERATOR_HPP

# include "utility.hpp"
# include <cstddef>

namespace ft {
/* ************************************************************************** */
/*                           ITERATORS                                        */
/* ************************************************************************** */
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
	};



/* ************************************************************************** */
/*                           ITERATOR_TRAITS                                  */
/* ************************************************************************** */
	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

/* ************************************************************************** */
/*                           RANDOM_ACCESS_ITERATOR                           */
/* ************************************************************************** */

	template <class Iterator>
	class random_access_iterator : ft::iterator<random_access_iterator_tag, Iterator> {
		public:
			typedef Iterator																			iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::reference			reference;

			/* ===== member functions ===== */
			random_access_iterator(void) : _it() {return;};
			random_access_iterator(pointer it) : _it(it) {return;};
			random_access_iterator(const random_access_iterator& op) : _it(op._it) {return;};
			pointer base(void) const {return this->_it;};

			/* ===== operators ===== */
			reference operator*(void) const {return *this->_it;};
			pointer operator->(void) const {return &(this->operator*());};

			random_access_iterator &operator=(const random_access_iterator& rhs) {
				if (*this == rhs)
					return (*this);
				this->_it = rhs._it;
				return (*this);
			};
			random_access_iterator& operator++(void) {
				++this->_it;
				return (*this);
			};
			random_access_iterator operator++(int) {
				random_access_iterator tmp(*this);
				operator++();
				return (tmp);
			};
			random_access_iterator& operator+=(const difference_type n) {
				this->_it += n;
				return (*this);
			};
			random_access_iterator operator+(const difference_type n) const {return (this->_it + n);};
			
			
			random_access_iterator& operator-=(const difference_type n) {
				this->_it -= n;
				return (*this);
			};
			random_access_iterator operator-(const difference_type n) const {return(this->_it - n);};
			random_access_iterator& operator--(void) {
				--this->_it;
				return (*this);
			};
			random_access_iterator operator--(int) {
				random_access_iterator tmp(*this);
				operator--();
				return (tmp);
			};
			difference_type operator-(const random_access_iterator& op) const {return (this->_it - op._it);};
			
			bool operator==(const random_access_iterator& op) const {return (_it == op._it);};
			bool operator!=(const random_access_iterator& op) const {return (_it != op._it);};
			bool operator<(const random_access_iterator& op) const {return (_it < op._it);};
			bool operator<=(const random_access_iterator& op) const {return (_it <= op._it);};
			bool operator>(const random_access_iterator& op) const {return (_it > op._it);};
			bool operator>=(const random_access_iterator& op) const {return (_it >= op._it);};

			reference operator[](const difference_type n) const {return (_it[n]);};
			operator random_access_iterator<const value_type>() const {return (random_access_iterator<const value_type>(_it));};

		private:
			pointer _it;
	};

	template <class Iterator>
	bool operator<(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs < rhs);};
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() < rhs.base());};
	
	template <class Iterator>
	bool operator>(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs > rhs);};
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() > rhs.base());};

	template <class Iterator>
	bool operator>=(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs >= rhs);};
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() >= rhs.base());};

	template <class Iterator>
	bool operator<=(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs <= rhs);};
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() <= rhs.base());};

	template <class Iterator>
	bool operator==(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs == rhs);};
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() == rhs.base());};

	template <class Iterator>
	bool operator!=(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs != rhs);};
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() != rhs.base());};

	template <class Iterator>
	typename ft::random_access_iterator<Iterator>::difference_type operator-(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs - rhs);};
	template <class Iterator1, class Iterator2>
	typename ft::random_access_iterator<Iterator1>::difference_type operator-(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() - rhs.base());};
	template <typename Iterator>
	ft::random_access_iterator<Iterator> operator-(typename random_access_iterator<Iterator>::difference_type n, const ft::random_access_iterator<Iterator>& lhs) {return (lhs - n);};

	template <class Iterator>
	typename ft::random_access_iterator<Iterator>::difference_type operator+(const ft::random_access_iterator<Iterator>& lhs, const ft::random_access_iterator<Iterator>& rhs) {return (lhs + rhs);};
	template <class Iterator1, class Iterator2>
	typename ft::random_access_iterator<Iterator1>::difference_type operator+(const ft::random_access_iterator<Iterator1> lhs, const ft::random_access_iterator<Iterator2> rhs) {return (lhs.base() + rhs.base());};
	template <typename Iterator>
	ft::random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n, const ft::random_access_iterator<Iterator>& lhs) {return (lhs + n);};

/* ************************************************************************** */
/*                           REVERSE_ITERATOR                                 */
/* ************************************************************************** */
	template <class Iterator>
	class reverse_iterator {
		public:
			/* ===== typedef ===== */
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
	
			/* ===== constructor ===== */
			reverse_iterator() : _it() {return;};
			explicit reverse_iterator (iterator_type it) : _it(it) {return;};
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {return;};

			/* ===== member functions ===== */
			iterator_type base() const {return (this->_it);};
			template<class C>
			reverse_iterator& operator=(const reverse_iterator<C>& src) {
				this->_it = src.base();
				return *this;
			};
			reference operator*() const {
				iterator_type tmp = this->_it;
				return (*--tmp);
			};

			reverse_iterator operator+(difference_type n) const {return reverse_iterator(this->_it - n);};
			reverse_iterator& operator++(void) {
				--this->_it;
				return (*this);
			};
			reverse_iterator  operator++(int) {
				reverse_iterator tmp(*this);
				++(*this);
				return (tmp);
			};
			reverse_iterator& operator+=(difference_type n) {
				this->_it -= n;
				return *this;
			};

			difference_type operator-(const reverse_iterator<Iterator>& rhs) {return (rhs.base() - this->_it);};
			reverse_iterator operator-(difference_type n) const {return reverse_iterator(this->_it + n);};
			reverse_iterator& operator--() {
				++this->_it;
				return (*this);
			};
			reverse_iterator  operator--(int) {
				reverse_iterator tmp(*this);
				operator--();
				return (tmp);
			};
			reverse_iterator& operator-=(difference_type n) {
				this->_it += n;
				return *this;
			};

			pointer operator->() const {return &(operator*());};
			reference operator[](difference_type n) const {return *(this->_it - n -1);};

		private:
			iterator_type	_it;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() == rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1> lhs, const ft::reverse_iterator<Iterator2> rhs) {return (lhs.base() == rhs.base());};

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() != rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1> lhs, const ft::reverse_iterator<Iterator2> rhs) {return (lhs.base() != rhs.base());};

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() > rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() > rhs.base());};


	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() >= rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() >= rhs.base());};
	
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() < rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() < rhs.base());};

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() <= rhs.base());};
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() <= rhs.base());};


	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {return (rev_it + n);};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (rhs.base() - lhs.base());};


	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type i = 0;
		for (; first != last; ++first, ++i);
		return (i);
	}
}

#endif