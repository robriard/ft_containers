/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:35:10 by unknow            #+#    #+#             */
/*   Updated: 2022/01/06 16:11:48 by unknow           ###   ########.fr       */
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
			Node() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {return;};
			Node(value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(RED) {return;};
			Node(const value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(RED) {return;};
			Node(const_node_reference src)
				: value(src.value), parent(src.parent), left(src.left), right(src.right), color(RED) {return;};
			virtual ~Node(void) {return;};

			node_reference operator=(const_node_reference rhs) {
				if (rhs == *this) return *this;
				this->value = rhs.value;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
				this->color = rhs.color;
				return *this;
			}
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
			RBT(const key_compare &cmp = key_compare()) : _root(NULL), _cmp(cmp), _allocator(node_allocator()) {return;};
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
			ft::pair<iterator, bool> insert( const value_type& value) {
				Node::node_pointer newNode(value);
				if (!this->_root) {
					this->_root = newNode;
					this->_root->color = BLACK;
					return make_pair<iterator, bool>(iterator(node), true);
				}
				Node::node_pointer x = this->_root;
				Node::node_pointer parent = NULL;
				while(x) {
					parent = x;
					if (this->_cmp(x->value.first, newNode->value.first))
						x = x->rigth;
					else if (this->_cmp(newNode->value.first, x->value.first))
						x = x->left;
					else
						return make_pair<iterator, bool>(NULL, false);
				}
				x = newNode;
				x->parent = parent;
				insertFix(x);
				return make_pair<iterator, bool>(x, true);
			}
			ft::pair<iteator, bool> erase(const value_type& value) {
				Node::node_pointer deletedNode = this->_root;
				while (deletedNode && deletedNode->value.first != value.first) {
					if (this->_cmp(value.first, deletedNode->value.first))
						deletedNode = deletedNode->left;
					else if (this->_cmp(deletedNode->value.first, value.first))
						deletedNode = deletedNode->right;
				}
				if (!deletedNode) return make_pair<iterator, bool>(this->_root, false);
				int originalColor = deletedNode->color;
				Node::node_pointer child;
				if (!deletedNode->left && deletedNode->right) {
					child = deletedNode->rigth;
					this->transplant(deletedNode, child)
				} else if (deletedNode->left && !deletedNode->right) {
					child = deletedNode->left;
				} else {
					
				}
			}

















			node_pointer	find(const key_type &to_find) const {return (this->valuefind(to_find, _root));};
			node_pointer	find(const node_pointer to_find) const {return (this->find(to_find->value, _root));};
			node_pointer	find(const node_pointer to_find, node_pointer node) const {return (this->find(to_find->value, node));};
			node_pointer	find(const value_type &to_find) const {return (this->find(to_find->value, _root));};
			

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
		};
		node_pointer 					find(const key_type to_find, Node::node_pointer node) {
			if (!node) return NULL;
			if (this->cmp(to_find, node->value.first)) return find(to_find, node->left);
			if (this->cmp(node->value.first, to_find)) return find(to_find, node->right);
			return node;
		};
			
		node_pointer					minValue(Node::node_pointer node) {
			if (!node) return NULL;
			if (node->left) return maxValue(node->left);
			return node;
		};
		node_pointer					maxValue(Node::node_pointer node) {
			if (!node) return NULL;
			if (node->right) return maxValue(node->right);
			return node;
		};
		
		void							clear(Node::node_pointer node) {
			if (!node) return;
			if (node->left) clear(node->left);
			if (node->right) clear(node->right);
			this->allocator.destroy(node);
			this->allocator.deallocate(node, 1);
			return;
		};
		
		void							leftRotate(Node::node_pointer node) {
			Node::node_pointer tmp = node->rigth;
			node->rigth = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				this->_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = x;
			node->parent = tmp;
			return;
		};
		void							rigthRotate(Node::node_pointer node) {
			Node::node_pointer tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				this->_root = tmp;
			else if (node == node->parent->rigth)
				node->parent->right = tmp;
			else
				node->parent->left = tmp;
			tmp->rigth = node;
			node->parent = tmp;
		};
		void							transplant(Node::node_pointer node1, Node::node_pointer ndoe2) {
			if (!node1->parent)
				this->_root = node2;
			else if (node1 == node1->parent->left);
				node1->parent->left = node2;
			else
				node->parent->right = node2;
			node2->parent = node1->parent;
		};
		void	insertFix(Node::node_pointer node){
			while (node->parent && node->parent->color == RED) {
				if (node->parent->parent->left == node->parent) {
					
					if (node->parent->parent->right == RED) {
						node->parent->parent->left->color = node->parent->parent->rigth->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->rigth) {
							node = node->parent;
							leftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rigthRotate(node->parent->parent);
					}
				
				} else {
					
					if (node->parent->parent->left == RED) {
						node->parent->parent->left->color = node->parent->parent->rigth->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							rigthRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						leftRotate(node->parent->parent);
					}
				}
			}
			this->_root->color = BLACK;
			return;
		};
	};
}

#endif


std::vector<int>;

//	finish: ✅		in progress: 🔄

/*
FIND ✅
INSERT ✅
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
