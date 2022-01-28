/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:31:59 by unknow            #+#    #+#             */
/*   Updated: 2022/01/28 11:04:38 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "red_black_tree.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include <memory>

namespace ft {
	template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set {
		public:
			/* ************************************************************************** */
			/*			MEMBER TYPES                                                      */
            /* ************************************************************************** */
			typedef T																value_type;
			typedef T																key_type;
			typedef Compare															key_compare;
			typedef Compare															value_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename ft::setRBT<value_type, key_compare>::iterator			iterator;
			typedef typename ft::setRBT<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef typename allocator_type::difference_type						difference_type;
			typedef typename allocator_type::size_type								size_type;

			/* ************************************************************************** */
			/*			MEMBER FUNCTIONS                                                  */
            /* ************************************************************************** */
			/* ========== Constructors ========== */
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _compare(comp), _rbt(comp), _size(0) {return;};
			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _compare(comp), _rbt(comp), _size(0) {
				for (; first != last; ++first)
					insert(*first);
				return;
			};	
			set (const set& x) {*this = x;};
			virtual ~set(void) {return;};

			set& operator= (const set& x) {
				this->_allocator = x._allocator;
				this->_compare = x._compare;
				this->_rbt.clear();
				this->insert(x.begin(), x.end());
				this->_size = x._size;
				return *this;
			};

			/* ========== Iterators ========== */
			const_iterator			begin(void) const {return this->_rbt.begin();};
			iterator				begin(void) {return this->_rbt.begin();};
			
			const_iterator			end(void) const {return this->_rbt.end();};
			iterator				end(void) {return this->_rbt.end();};
			
			const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(this->_rbt.end());};
			reverse_iterator		rbegin(void) {return reverse_iterator(this->_rbt.end());};

			reverse_iterator		rend(void) {return reverse_iterator(this->_rbt.begin());};
			const_reverse_iterator	rend(void) const {return const_reverse_iterator(this->_rbt.begin());};

			/* ========== Capacity ========== */
			bool		empty(void) const {return (this->_size == 0);};
			size_type	size(void) const {return this->_size;};
			size_type	max_size() const {return this->_allocator.max_size();};

			/* ========== Modifiers ========== */
			ft::pair<iterator,bool>		insert(const value_type& val) {
				ft::pair<iterator, bool> res = this->_rbt.insert(val);
				if (res.second)
					++this->_size;
				return (res);
			};
			iterator 					insert(iterator position, const value_type& val) {
				(void)position;
				return this->insert(val).first;
			};
			template <class InputIterator>
			void						insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first)
					this->insert(*first);
			};

			size_type 					erase(const value_type& k) {
				ft::pair<iterator, bool> res = this->_rbt.erase(k);
				if (res.second) {
					--this->_size;
					return 1;
				}
				return 0; 
			};
			void						erase(iterator position) {this->erase(*position);};
			void						erase(iterator first, iterator last) {
				iterator tmp;
				while (first != last) {
					tmp = first;
					first++;
					this->erase(*tmp);
				}
			};

			void						swap (set& x) {
				this->_rbt.swap(x._rbt);
				ft::swap(this->_allocator, x._allocator);
				ft::swap(this->_compare, x._compare);
				ft::swap(this->_size, x._size);
			};
			void						clear(void) {
				if (this->_size != 0) {
					this->_rbt.clear();
					this->_size = 0;
				}
			}

			/* ========== Observers ========== */
			key_compare		key_comp(void) const {return this->_compare;};
			value_compare	value_comp(void) const {return this->_compare;};

			/* ========== Operations ========== */
			iterator					find(const value_type& val) {return this->_rbt.find(val);};
			const_iterator				find(const value_type& val) const {return this->_rbt.find(val);};
			size_type					count(const value_type& k) const {return (this->_rbt.find(k) != this->end());};

			iterator		lower_bound (const key_type& k) {return this->_rbt.lower_bound(k);};
			const_iterator	lower_bound (const key_type& k) const {return this->_rbt.lower_bound(k);};
		
			iterator		upper_bound (const key_type& k) {return this->_rbt.upper_bound(k);};
			const_iterator	upper_bound (const key_type& k) const {return this->_rbt.upper_bound(k);};
		
			pair<iterator, iterator> equal_range (const key_type& k) {return ft::make_pair(this->lower_bound(k), this->upper_bound(k));};
			pair<const_iterator, const_iterator> equal_range (const key_type& k) const {return ft::make_pair(this->lower_bound(k), this->upper_bound(k));};
			/* ========== Allocator ========== */
			allocator_type	get_allocator(void) const {return this->_allocator;};


		private:
			allocator_type								_allocator;
			Compare										_compare;
			ft::setRBT<value_type, key_compare>	_rbt;
			size_type									_size;	
	};

	template< class Key, class Compare, class Alloc >
	bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
		typename ft::set<Key, Compare, Alloc>::const_iterator	it = lhs.begin();
		typename ft::set<Key, Compare, Alloc>::const_iterator	ite = lhs.end();
		typename ft::set<Key, Compare, Alloc>::const_iterator	it2 = rhs.begin();
		while (it != ite && it2 != rhs.end()) {
			if (*it != *it2)
				return (false);
			it++;
			it2++;
		}
		return (it == ite && it2 == rhs.end());
	};
	template< class Key, class Compare, class Alloc >
	bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return (!(lhs == rhs));};

	template< class Key, class Compare, class Alloc >
	bool operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
		typename ft::set<Key, Compare, Alloc>::const_iterator	it = lhs.begin();
		typename ft::set<Key, Compare, Alloc>::const_iterator	ite = lhs.end();
		typename ft::set<Key, Compare, Alloc>::const_iterator	it2 = rhs.begin();

		while (it != ite && it2 != rhs.end()) {
			if (*it != *it2)
				return (*it < *it2);
			it++;
			it2++;
		}
		return (it == ite && it2 != rhs.end());
	};
	template< class Key, class Compare, class Alloc >
	bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return ((lhs < rhs) or (lhs == rhs));};
	template< class Key, class Compare, class Alloc >
	bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return (not (lhs < rhs) and not (lhs == rhs));};
	template< class Key, class Compare, class Alloc >
	bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return not(lhs < rhs);};

	template< class Key, class Compare, class Alloc >
	void swap(ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs) {lhs.swap(rhs);};
}

#endif