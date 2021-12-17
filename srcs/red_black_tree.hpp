/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:35:10 by unknow            #+#    #+#             */
/*   Updated: 2021/12/17 11:01:38 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <functional>
# include "utility.hpp"
# include "iterator.hpp"
#include <vector>

# define b BLACK;
# define r RED; 

namespace ft {
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
			int				key;
			node_pointer	parent;
			node_pointer	left;
			node_pointer	rigth;
			char			color;

            /* *********** member functions *********** */
			Node() : value(), parent(NULL), left(NULL), rigth(NULL), color(BLACK) {return;};
			Node(value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer rigth = NULL)
				: value(v), parent(parent), left(left), rigth(rigth), color(BLACK) {return;};
			Node(const value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer rigth = NULL)
				: value(v), parent(parent), left(left), rigth(rigth), color(BLACK) {return;};
			Node(const_node_reference src)
				: value(src.value), parent(src.parent), left(src.left), rigth(src.rigth), color(BLACK) {return;};
			virtual ~Node(void) {return;};

			node_reference operator=(const_node_reference rhs) {
				if (rhs == *this) return *this;
				this->value = rhs.value;
				this->value = rhs.value;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->rigth = rhs.rigth;
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
			typedef RBT							self;
			typedef self*						self_pointer;
			typedef self&						self_reference;
			typedef const self*					const_self_pointer;
			typedef const self&					const_self_reference;
			typedef Type						value_type;
			typedef	Type_Alloc					Alloc;
            typedef typename Alloc::size_type	size_type;
			typedef Compare						key_compare;

            /* *********** member functions *********** */
			RBT(const key_compare &cmp = key_compare()) : _allocator(Alloc()), _root(NULL), _end(this->_allocator.allocate(1)), _cmp(cmp) {return;};
			RBT(RBTree const & src) : _allocator(Alloc()), _root(NULL), _end(this->_allocator._allocate(1)), _cmp(src._cmp) {
				this->insert(src.begin(), src.end)());
				return;
			};
			virtual ~RBT(void) {
				this->clear();
				this->_allocator.deallocate(this->_end, 1);
				return;
			};

			RBT &operator=(RBT const & rhs) {
				if (this != &rhs) this->_root = rhs._root;
				return (*this);
			};

			void insert(Node::const_node_reference new) {};
			void clear(void) {this->_root = this->clear(this->_root);};

            /* *********** capacity *********** */
			size_type	max_size(void) {return this->_allocator.max_size()}
			
		protected:
			Node::node_pointer clear(Node::node_pointer node) {
				if (node->left) node->left = this->clear(node->left);
				if (node->rigth) node->rigth = this->clear(node->rigth);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				return NULL;
			}
		private:
			Alloc  				_allocator;
			Node::node_pointer	_root;
			key_compare 		_cmp;
	};
}

#endif