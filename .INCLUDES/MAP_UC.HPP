/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:46:39 by unknow            #+#    #+#             */
/*   Updated: 2021/12/18 13:07:44 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "algorithm.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include <memory>

namespace ft {
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T>>>
	class map {
		public:
            /* *********** member types *********** */
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<key_type, mapped_type>								value_type;
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
			// typedef typename ft::BST<value_type, key_compare>::node_type		node_type;
			typedef typename ft::BST<value_type, key_compare>::iterator			iterator;
			typedef typename ft::BST<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::difference_type					difference_type;

            /* *********** member functions *********** */


		private:
			allocator_type								_allocator;
			Compare										_compare;
			ft::RBT<key_type, mapped_type>				_bst;
	};

}

#endif