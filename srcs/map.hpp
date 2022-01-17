/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:46:39 by unknow            #+#    #+#             */
/*   Updated: 2022/01/17 16:03:46 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "red_black_tree.hpp"
# include "algorithm.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include <memory>

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
		public:
            /* ************************************************************************** */
			/*			MEMBER TYPES                                                      */
            /* ************************************************************************** */
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			class value_compare : ft::binary_function<value_type, value_type, bool> {
				friend class map<Key, T, Compare, Alloc>;
				protected:
					key_compare		_comp;

					value_compare(key_compare c) : _comp(c) {return;}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type &x, const value_type &y) const {return _comp(x.first, y.first);};
			};
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename ft::RBT<value_type>::iterator						iterator;
			typedef typename ft::RBT<value_type>::const_iterator				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::difference_type					difference_type;

            /* ************************************************************************** */
			/*			MEMBER FUNCTIONS                                                  */
            /* ************************************************************************** */
			/* ========== Constructors ========== */
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _compare(comp), _rbt(), _size(0) {return;};
			
			
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _allocator(alloc), _compare(comp), _rbt(comp), _size(0) {
				for (; first != last; ++first)
					insert(*first);
				return;
			};
			map (const map& src) : _allocator(src._allocator), _compare(src._compare), _rbt(src._rbt), _size(src._size) {return;};
			~map(void){return;};
			
			map& operator= (const map& rhs) {
				if (this == rhs)
					return *this;
				this->_allocator = rhs._allocator;
				this->_compare = rhs._compare;
				this->_rbt = rhs._rbt;
				this->_size = rhs._size;
				return *this;
			};
			
			/* ========== Iterators ========== */
			iterator begin(void) {return this->_rbt.begin();};
			const_iterator begin(void) const {return this->_rbt.begin();};
			
			iterator end(void) {return this->_rbt.end();};
			const_iterator end(void) const {return this->_rbt.end();};
			
			reverse_iterator rbegin(void) {return reverse_iterator(this->end());};
			const_reverse_iterator rbegin(void) const {return const_reverse_iterator(this->end());};

			reverse_iterator rend(void) {return reverse_iterator(this->begin());};
			const_reverse_iterator rend(void) const {return const_reverse_iterator(this->begin());};

			/* ========== Capacity ========== */
			bool 		empty(void) const {return (this->_size == 0);};
			size_type	size() const {return this->_size;};
			size_type	max_size(void) const {return this->_rbt.max_size();};

			/* ========== Element access ========== */
			mapped_type& operator[] (const key_type& k) {
				iterator it = find(k);
				if (it == this->end())
					it = this->insert(ft::make_pair(k, mapped_type())).first;
				return (it->second);
			};

			/* ========== Modifiers ========== */
			pair<iterator,bool>		insert (const value_type& val) {
				ft::pair<iterator, bool> res = this->_rbt.insert(val);
				if (res.second)
					++this->_size;
				return (res);
			};
			iterator insert			(iterator position, const value_type& val) {
				(void)position;
				return this->insert(val).first;
			};
			template <class InputIterator>
			void insert				(InputIterator first, InputIterator last) {
				for (; first != last; ++first)
					this->insert(*first);
			};

			size_type erase			(const key_type& k) {
				ft::pair<iterator, bool> res = this->_rbt.erase(k);
				if (res.second)
					--this->_size;
				return 1;
			};
			void erase				(iterator position) {this->erase(position->first);};
			void erase				(iterator first, iterator last) {
				for (; first != last; ++first)
					this->erase(first->first);
			};

			void					swap (map& x) {
				map<key_type, mapped_type> tmp = *this;
				*this = x;
				x = tmp;
			};

			void					clear(void) {
				this->_rbt.clear();
				this->_size = 0;
			}

			/* ========== Observers ========== */
			key_compare		key_comp(void) const {return this->_compare;};
			value_compare	value_comp(void) const {return (value_compare(this->_compare));};
			
			/* ========== Operations ========== */
			iterator		find (const key_type& k) {return this->_rbt.find(k);};
			const_iterator	find (const key_type& k) const {return this->_rbt.find(k);};
			
			size_type		count (const key_type& k) const {return (this->_rbt.find(k) != this->end());};

			iterator		lower_bound (const key_type& k) {return this->_rbt.lower_bound(k);};
			const_iterator	lower_bound (const key_type& k) const {return this->_rbt.lower_bound(k);};
		
			iterator		upper_bound (const key_type& k) {return this->_rbt.upper_bound(k);};
			const_iterator	upper_bound (const key_type& k) const {return this->_rbt.upper_bound(k);};
		
			pair<iterator, iterator> equal_range (const key_type& k) {return ft::make_pair(this->lower_bound(k), this->upper_bound(k));};
			pair<const_iterator, const_iterator> equal_range (const key_type& k) const {return ft::make_pair(this->lower_bound(k), this->upper_bound(k));};

			/* ========== Operations ========== */
			allocator_type get_allocator(void) const {return this->_allocator;};

		private:
			allocator_type			_allocator;
			Compare					_compare;
			ft::RBT<value_type>		_rbt;
			size_type				_size;
	};

}

#endif