/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:03:37 by unknow            #+#    #+#             */
/*   Updated: 2021/12/15 11:02:49 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IERATOR_HPP
# define IERATOR_HPP

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
	struct iterator {
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
    struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits<Iterator*>{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits<const Iterator*>{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

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
			reverse_iterator() : _it(), {return;};
			explicit reverse_iterator (iterator_type it) : _it(it){return;};
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()){return;};

			/* ===== member functions ===== */
			template<class C>
			iterator_type base() const { return (this->_it); }
			reverse_iterator& operator=(const reverse_iterator<C>& src) {
				this->_it = src.base();
				return *this;
			}
			reference operator*() const {
				iterator_type tmp = this->_it;
				return (*--tmp);
			}

			reverse_iterator operator+(difference_type n) const {return reverse_iterator(this->_it - n)};
			reverse_iterator& operator++() {return (--this->_it);};
			reverse_iterator  operator++(int) {return (tmp = ++(*this));};
			reverse_iterator& operator+=(difference_type n) {
				this->_it -= n;
				return *this;
			};

			reverse_iterator operator-(difference_type n) const {return reverse_iterator(this->_it + n)};
			reverse_iterator& operator--() {return (++this->_it);};
			reverse_iterator  operator--(int) {return (tmp = --(*this));};;
			reverse_iterator& operator-=(difference_type n) {
				this->_it += n;
				return *this;
			};

			pointer operator->() const {return &(operator*());};
			reference operator[](difference_type n) const {return *(this->_it - n -1)};

		private:
			iterator_type	_it;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() == rhs.base());};

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() != rhs.base());};

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() > rhs.base());};

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() >= rhs.base());};

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() < rhs.base());};

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() <= rhs.base())};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {return (rev_it + n);};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs - rhs)};


	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last) {
		iterator_traits<InputIterator>::difference_type i = 0;
		for (; first != last; ++first, ++i)
		return (i);
	}
}

#endif