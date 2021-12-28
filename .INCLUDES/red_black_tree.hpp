/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:35:10 by unknow            #+#    #+#             */
/*   Updated: 2021/12/27 16:01:42 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <functional>
# include "utility.hpp"
# include "iterator.hpp"
# include <vector>


namespace ft {
	# define RED 1; 
	# define BLACK 2;
/* ************************************************************************** */
/*             NODE CLASS                                                     */
/* ************************************************************************** */
	template <class Type>
	class Node {
		public:
            /* *********** member types *********** */
			typedef Type			value_type;
			typedef Node*			node_pointer;
			typedef const Node*		const_node_pointer;
			typedef Node&			node_reference;
			typedef const Node&		const_node_reference;
			value_type		value;
			node_pointer	parent;
			node_pointer	left;
			node_pointer	right;
			int				color;

            /* *********** member functions *********** */
			Node() : value(), parent(NULL), left(NULL), right(NULL), color(BLACK) {return;};
			Node(value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(BLACK) {return;};
			Node(const value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(BLACK) {return;};
			Node(const_node_reference src)
				: value(src.value), parent(src.parent), left(src.left), right(src.right), color(BLACK) {return;};
			virtual ~Node(void) {return;};

			node_reference operator=(const_node_reference rhs) {
				if (rhs == *this) return *this;
				this->value = rhs.value;
				this->value = rhs.value;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
				return *this;
			}
			std::vector()
			bool operator==(const_node_reference rhs) {return (this->value == rhs.value);};
	};

/* ************************************************************************** */
/*             RED_BLACK_TREE CLASS                                           */
/* ************************************************************************** */
	template <class Type, class Compare = std::less<Type>, class Node = Node<Type>, class Type_Alloc = std::allocator<Type>, class Node_Alloc = std::allocator<Node>>
	class RBT {
		public:
            /* *********** member types *********** */
			typedef Type												value_type;
			typedef typename value_type::first_type						key_type;
			typedef typename value_type::second_type					mapped_type;
			typedef Compare												key_compare;
			typedef	Type_Alloc											type_allocator;
            typedef typename type_allocator::size_type					size_type;
			typedef Node_Alloc											node_allocator;
			typedef typename ft::RBT_iterator<Node, key_compare>		iterator;
			typedef typename ft::RBT_const_iterator<Node, key_compare>	const_iterator;
            
			/* *********** constructor *********** */
			RBT(const key_compare &cmp = key_compare()) : _root(NULL), _cmp(cmp), _allocator(allocator_type()) {return;};
			RBT(const RBT &src) : _root(src._root), _cmp(src._cmp), _allocator(src._allocator) {return;};
			~RBT(void) {return;};

			/* *********** operators *********** */
			RBT &operator=(RBT const &other) {
				if (this != &other)
					this->_root = other._root;
				return (*this);
			};
			node_reference operator*() const {return ((this->_root));};
			node_pointer operator->() const {return (&(this->_root));};

			/* *********** publics members functions *********** */
			node_pointer	find(const key_type &to_find) const {return (find(to_find, _root));};
			node_pointer	find(const node_pointer to_find) const {return (find(to_find->value, _root));};
			node_pointer	find(const node_pointer to_find, node_pointer node) const {return (find(to_find->value, node));};
			node_pointer	find(const value_type &to_find) const {return (find(to_find->value, _root));};
			bool erase(const value_type &to_find) {
				ft::pair<node_pointer, bool> ret = erase(to_find, _root);
				if ((_root = ret.first))
					_root->parent = NULL;
				return (ret.second);
			}
			bool erase(node_pointer node) {
				ft::pair<node_pointer,bool> ret = erase(node->value, _root);
				if ((_root = ret.first))
					_root->parent = NULL;
				return (ret.second);
			}
			node_pointer	minValue(void) {return this->minValue(this->_root);};
			node_pointer	maxValue(void) {return this->maxValue(this->_root);};
			void			clear(void) {this->clear(this->_root);};
			size_type		max_size(void) const {return this->allocator.max_size();};
			
			/* *********** iterators *********** */
			iterator begin(void) {return iterator(minValue(), NULL);};
			const_iterator cbegin(void) {return const_iterator(minValue(), NULL);};
			iterator end(void) {return iterator(NULL, maxValue());};
			const__iterator cend(void) {return iterator(NULL, maxValue());};

		private:
			Node::node_pointer		_root;
			key_compare				_cmp;
			node_allocator			_allocator;
		
		/* *********** privates members functions *********** */
		node_pointer 					find(const Node::value_type to_find, Node::node_pointer node) {
			if (!node) return NULL;
			if (this->cmp(to_find.first, node->value.first)) return find(to_find, node->left);
			if (this->cmp(node->value.first, to_find.first)) return find(to_find, node->right);
			return node;
		}
		node_pointer 					find(const key_type to_find, Node::node_pointer node) {
			if (!node) return NULL;
			if (this->cmp(to_find, node->value.first)) return find(to_find, node->left);
			if (this->cmp(node->value.first, to_find)) return find(to_find, node->right);
			return node;
		}
		ft::pair<node_pointer, bool>	erase(const Node::value_type &to_find, node_pointer node) {
			if (!node) return ft::make_pair(node, false);
			if (this->cmp(to_find.first, node->value.first)) return erase(to_find, node->left);
			if (this->cmp(node->value.first, to_find.first)) return erase(to_find, node->right);
			if (to_find.first == node->value.first) {
				if (node->parent && to_find.first == node->parent->left.first)
					node->parent->left = NULL;
				if (node->parent && to_find.first == node->parent->right.first)
					node->parent->right = NULL;
				this->allocator.destroy(node);
				this->allocator.deallocate(node, 1);
			}
		}
		node_pointer					minValue(Node::node_pointer node) {
			if (!node) return NULL;
			if (!node->left) return maxValue(node->left);
			return node;
		}
		node_pointer					maxValue(Node::node_pointer node) {
			if (!node) return NULL;
			if (!node->right) return maxValue(node->right);
			return node;
		}
		void							clear(Node::node_pointer node) {
			if (!node) return;
			if (node->left) clear(node->left);
			if (node->right) clear(node->right);
			this->allocator.destroy(node);
			this->allocator.deallocate(node, 1);
			return;
		};
		
	};
}

#endif

//	finish: ✅		in progress: 🔄

/*
FIND ✅
INSERT 🔄
ERASE 🔄
MIN_VALUE ✅
MAX_VALUE ✅
UPPER_BOUND 🔄
LOWER_BOUND 🔄
CLEAR ✅
MAX_SIZE ✅

BEGIN ✅
END ✅
CBEGIN ✅
CEND ✅
*/