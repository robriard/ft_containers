/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:35:10 by unknow            #+#    #+#             */
/*   Updated: 2022/02/01 16:50:28 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <functional>
# include "utility.hpp"
# include "algorithm.hpp"
# include "RBT_iterator.hpp"

namespace ft {
	# define RED 1
	# define BLACK 2
/* ************************************************************************** */
/*            NODE CLASS                                                      */
/* ************************************************************************** */
	template <class Type>
	class mapNode {
		public:
            /* *********** member types *********** */
			typedef Type				value_type;
			typedef mapNode*			node_pointer;
			typedef const mapNode*		const_node_pointer;
			typedef mapNode&			node_reference;
			typedef const mapNode&		const_node_reference;
			value_type		value;
			node_pointer	parent;
			node_pointer	left;
			node_pointer	right;
			int				color;

            /* *********** member functions *********** */
			mapNode() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {return;};
			mapNode(const value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(RED) {return;};
			mapNode(const_node_reference src)
				: value(src.value), parent(src.parent), left(src.left), right(src.right), color(RED) {return;};
			virtual ~mapNode(void) {return;};

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
	
	template <class Type>
	class setNode {
		public:
            /* *********** member types *********** */
			typedef const Type		value_type;
			typedef setNode*		node_pointer;
			typedef const setNode*	const_node_pointer;
			typedef setNode&		node_reference;
			typedef const setNode&	const_node_reference;
			value_type				value;
			node_pointer			parent;
			node_pointer			left;
			node_pointer			right;
			int						color;

            /* *********** member functions *********** */
			setNode() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {return;};
			setNode(const value_type v, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL)
				: value(v), parent(parent), left(left), right(right), color(RED) {return;};
			setNode(const_node_reference src)
				: value(src.value), parent(src.parent), left(src.left), right(src.right), color(RED) {return;};
			virtual ~setNode(void) {return;};

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
/*             MAP RED_BLACK_TREE CLASS                                       */
/* ************************************************************************** */
	template <class Type, class Compare, class Node = mapNode<Type>, class Type_Alloc = std::allocator<Type>, class Node_Alloc = std::allocator<Node> >
	class mapRBT {
		public:
            /* *********** member types *********** */
			typedef Type													value_type;
			typedef typename value_type::first_type							key_type;
			typedef typename value_type::second_type						mapped_type;
			typedef Compare													key_compare;
			typedef	Type_Alloc												type_allocator;
            typedef typename type_allocator::size_type						size_type;
			typedef Node_Alloc												node_allocator;
			typedef typename ft::MAP_iterator<Node, key_compare>			iterator;
			typedef typename ft::MAP_const_iterator<Node, key_compare>		const_iterator;
			typedef typename Node::node_pointer								node_pointer;
			typedef typename Node::const_node_pointer						const_node_pointer;
			typedef typename Node::node_reference							node_reference;
			typedef typename Node::const_node_reference						const_node_reference;

			/* *********** constructor *********** */
			mapRBT(void)  : _root(NULL), _cmp(key_compare()), _allocator(node_allocator()){return;};
			explicit mapRBT(const key_compare &cmp)  : _root(NULL), _cmp(cmp), _allocator(node_allocator()){return;};
			mapRBT(const mapRBT &src) : _root(src._root), _cmp(src._cmp), _allocator(src._allocator) {return;};
			~mapRBT(void) {this->_clear(this->_root); return;};

			/* *********** operators *********** */
			mapRBT &operator=(mapRBT const &other) {
				if (this != &other)
					this->_root = other._root;
				return (*this);
			};
			node_reference operator*(void) const {return ((this->_root));};
			node_pointer operator->(void) const {return (&(this->_root));};

			/* *********** publics members functions *********** */
			ft::pair<iterator, bool> insert(const value_type& value) {
				if (not this->_root) {
					this->_root = this->_allocator.allocate(1);
					this->_allocator.construct(this->_root, Node(value));
					this->_root->color = BLACK;
					return ft::make_pair<iterator, bool>(iterator(this->_root, NULL), true);
				}
				node_pointer x = this->_root;
				node_pointer parent = NULL;
				while(x) {
					parent = x;
					if (this->_cmp(x->value.first, value.first))
						x = x->right;
					else if (this->_cmp(value.first, x->value.first))
						x = x->left;
					else {
						return ft::make_pair<iterator, bool>(iterator(x, NULL), false);
					}
				}
				x = this->_allocator.allocate(1);
				this->_allocator.construct(x, Node(value));
				x->parent = parent;
				if (this->_cmp(parent->value.first, x->value.first))
					parent->right = x;
				else
					parent->left = x;
				this->_insertFix(x);
				return ft::make_pair<iterator, bool>(iterator(x, NULL), true);
			}
			ft::pair<iterator, bool> erase(const key_type& value) {
				node_pointer deletedNode = this->_root;
				node_pointer x, y;
				while (deletedNode and deletedNode->value.first != value) {
					if (this->_cmp(value, deletedNode->value.first))
						deletedNode = deletedNode->left;
					else if (this->_cmp(deletedNode->value.first, value))
						deletedNode = deletedNode->right;
				}
				if (not deletedNode) return ft::make_pair<iterator, bool>(this->end(), false);
				y = deletedNode;
				int y_original_color = y->color;
				if (deletedNode->left == NULL) {
					x = deletedNode->right;
					this->_transplant(deletedNode, deletedNode->right);
				} else if (deletedNode->right == NULL) {
					x = deletedNode->left;
					this->_transplant(deletedNode, deletedNode->left);
				} else {
					y = this->_minValue(deletedNode->right);
					y_original_color = y->color;
					x = y->right;
					if (x and y->parent == deletedNode) {
						x->parent = y;
					} else {
						this->_transplant(y, y->right);
						y->right = deletedNode->right;
						if (y->right) y->right->parent = y;
					}
					this->_transplant(deletedNode, y);
					y->left = deletedNode->left;
					if (y->left) y->left->parent = y;
					y->color = deletedNode->color;
				}
				this->_allocator.destroy(deletedNode);
				this->_allocator.deallocate(deletedNode, 1);
				if (y_original_color == BLACK)
					this->_deleteFix(x);
				return ft::make_pair<iterator, bool>(this->end(), true);
			};

			iterator		upper_bound(const key_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite)
				{
					if (this->_cmp(key, it->first))
						return (it);
					it++;
				}
				return (it);
			};
			const_iterator	upper_bound(const key_type& key) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite)
				{
					if (this->_cmp(key, it->first))
						return (it);
					it++;
				}
				return (it);
			};

			iterator		lower_bound(const key_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite) {
					if (not this->_cmp(it->first, key))
						break;
					it++;
				}
				return (it);
			};
			const_iterator	lower_bound(const key_type& key) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite)
				{
					if (not this->_cmp(it->first, key))
						break;
					it++;
				}
				return (it);
			};

			iterator		find (const key_type& k) {return this->_find(k, this->_root);};
			const_iterator	find (const key_type& k) const {return this->_cfind(k, this->_root);};

			void swap(mapRBT& other) {
				ft::swap(this->_root, other._root);
				ft::swap(this->_cmp, other._cmp);
				ft::swap(this->_allocator, other._allocator);
			}
			node_pointer	minValue(void) const {return this->_minValue(this->_root);};
			node_pointer	maxValue(void) const {return this->_maxValue(this->_root);};
			
			void			clear(void) {this->_root = this->_clear(this->_root);};
			size_type		max_size(void) const {return this->_allocator.max_size();};
			
			/* *********** iterators *********** */
			iterator begin(void) {return (iterator(minValue(), NULL));};
			const_iterator begin(void) const {return (const_iterator(minValue(), NULL));};
			
			iterator end(void) {return (iterator(NULL, maxValue()));};			
			const_iterator end(void) const {return (const_iterator(NULL, maxValue()));};



		private:
			node_pointer	_root;
			key_compare		_cmp;
			node_allocator	_allocator;
		
		/* *********** privates members functions *********** */
		iterator		_find(const key_type& to_find, node_pointer node) {
			if (not node) return this->end();
			if (this->_cmp(to_find, node->value.first)) return this->_find(to_find, node->left);
			if (this->_cmp(node->value.first, to_find)) return this->_find(to_find, node->right);
			return iterator(node, node->parent);
		};
		const_iterator	_cfind(const key_type& to_find, const node_pointer node) const {
			if (not node) return this->end();
			if (this->_cmp(to_find, node->value.first)) return this->_cfind(to_find, node->left);
			if (this->_cmp(node->value.first, to_find)) return this->_cfind(to_find, node->right);
			return iterator(node, node->parent);
		};
			
		node_pointer	_minValue(node_pointer node) const {
			if (not node) return NULL;
			if (node->left) return _minValue(node->left);
			return node;
		};
		node_pointer	_maxValue(node_pointer node) const {
			if (not node) return NULL;
			if (node->right) return _maxValue(node->right);
			return node;
		};
		
		node_pointer	_clear(node_pointer node) {
			if (not node) return NULL;
			if (node->left) this->_clear(node->left);
			if (node->right) this->_clear(node->right);
			this->_allocator.destroy(node);
			this->_allocator.deallocate(node, 1);
			return NULL;
		};
		
		void			_leftRotate(node_pointer node) {
			node_pointer tmp = node->right;
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (not node->parent)
				this->_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
			return;
		};
		void			_rightRotate(node_pointer node) {
			node_pointer tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (not node->parent)
				this->_root = tmp;
			else if (node == node->parent->right)
				node->parent->right = tmp;
			else
				node->parent->left = tmp;
			tmp->right = node;
			node->parent = tmp;
		};
		void			_transplant(node_pointer node1, node_pointer node2) {
			if (not node1->parent)
				this->_root = node2;
			else if (node1 == node1->parent->left)
				node1->parent->left = node2;
			else
				node1->parent->right = node2;
			if (node2) node2->parent = node1->parent;
		};
		void			_insertFix(node_pointer node){
			while (node->parent and node->parent->color == RED) {
				if (node->parent->parent->left == node->parent) {	
					if (node->parent->parent->right and node->parent->parent->right->color == RED) {
						node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->right) {
							node = node->parent;
							this->_leftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						this->_rightRotate(node->parent->parent);
					}
				} else {
					if (node->parent->parent->left and node->parent->parent->left->color == RED) {
						node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							this->_rightRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						this->_leftRotate(node->parent->parent);
					}
				}
			}
			this->_root->color = BLACK;
			return;
		};
		void			_deleteFix(node_pointer node) {
			node_pointer sibling;
			while (node and node != this->_root and node->color == BLACK) {
				if (node->parent->left == node) {
					sibling = node->parent->right;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						this->_leftRotate(node->parent);
						sibling = node->parent->right;
					}
					if ((not sibling->left or sibling->left->color == BLACK) and (not sibling->right or sibling->right->color == BLACK)) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (not sibling->right or sibling->right->color == BLACK) {
							sibling->left->color = BLACK;
							sibling->color = RED;
							this->_rightRotate(sibling);
							sibling = node->parent->right;
						}
						sibling->color = node->parent->color;
						node->parent->parent->color = BLACK;
						if (sibling->right) sibling->right->color = BLACK;
						this->_leftRotate(node->parent);
						node = this->_root;
					}
				} else {
					sibling = node->parent->right;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						this->_rightRotate(node->parent);
						sibling = node->parent->left;
					}
					if ((not sibling->left or sibling->left->color == BLACK) and (not sibling->right or sibling->right->color == BLACK)) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (not sibling->left or sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							this->_leftRotate(sibling);
							sibling = node->parent->left;
						}
						sibling->color = node->parent->color;
						if (node->parent->parent) node->parent->parent->color = BLACK;
						if (sibling->left) sibling->left->color = BLACK;
						this->_rightRotate(node->parent);
						node = this->_root;
					}
				}
			}
			if (node) node->color = BLACK;
		};
	};

/* ************************************************************************** */
/*             SET RED_BLACK_TREE CLASS                                       */
/* ************************************************************************** */
	template <class Type, class Compare, class Node = setNode<Type>, class Type_Alloc = std::allocator<Type>, class Node_Alloc = std::allocator<Node> >
	class setRBT {
		public:
            /* *********** member types *********** */
			typedef const Type												value_type;
			typedef Compare													key_compare;
			typedef	Type_Alloc												type_allocator;
            typedef typename type_allocator::size_type						size_type;
			typedef Node_Alloc												node_allocator;
			typedef typename ft::SET_iterator<Node, key_compare>			iterator;
			typedef typename ft::SET_const_iterator<Node, key_compare>		const_iterator;
			typedef typename Node::node_pointer								node_pointer;
			typedef typename Node::const_node_pointer						const_node_pointer;
			typedef typename Node::node_reference							node_reference;
			typedef typename Node::const_node_reference						const_node_reference;

			/* *********** constructor *********** */
			setRBT(void)  : _root(NULL), _cmp(key_compare()), _allocator(node_allocator()){return;};
			explicit setRBT(const key_compare &cmp)  : _root(NULL), _cmp(cmp), _allocator(node_allocator()){return;};
			setRBT(const setRBT &src) : _root(src._root), _cmp(src._cmp), _allocator(src._allocator) {return;};
			~setRBT(void) {this->_clear(this->_root); return;};

			/* *********** operators *********** */
			setRBT &operator=(setRBT const &other) {
				if (this != &other)
					this->_root = other._root;
				return (*this);
			};
			const_node_reference operator*(void) const {return ((*this->_root));};
			node_pointer operator->(void) const {return (&(this->_root));};

			/* *********** publics members functions *********** */
			ft::pair<iterator, bool> insert( const value_type& value) {
				if (not this->_root) {
					this->_root = this->_allocator.allocate(1);
					this->_allocator.construct(this->_root, Node(value));
					this->_root->color = BLACK;
					return ft::make_pair<iterator, bool>(iterator(this->_root, NULL), true);
				}
				node_pointer x = this->_root;
				node_pointer parent = NULL;
				while(x) {
					parent = x;
					if (this->_cmp(x->value, value))
						x = x->right;
					else if (this->_cmp(value, x->value))
						x = x->left;
					else {
						return ft::make_pair<iterator, bool>(iterator(x, NULL), false);
					}
				}
				x = this->_allocator.allocate(1);
				this->_allocator.construct(x, Node(value));
				x->parent = parent;
				if (this->_cmp(parent->value, x->value))
					parent->right = x;
				else
					parent->left = x;
				this->_insertFix(x);
				return ft::make_pair<iterator, bool>(iterator(x, NULL), true);
			}
			ft::pair<iterator, bool> erase(const value_type& value) {
				node_pointer deletedNode = this->_root;
				node_pointer x, y;
				while (deletedNode and deletedNode->value != value) {
					if (this->_cmp(value, deletedNode->value))
						deletedNode = deletedNode->left;
					else if (this->_cmp(deletedNode->value, value))
						deletedNode = deletedNode->right;
				}
				if (not deletedNode) return ft::make_pair<iterator, bool>(this->end(), false);
				y = deletedNode;
				int y_original_color = y->color;
				if (deletedNode->left == NULL) {
					x = deletedNode->right;
					this->_transplant(deletedNode, deletedNode->right);
				} else if (deletedNode->right == NULL) {
					x = deletedNode->left;
					this->_transplant(deletedNode, deletedNode->left);
				} else {
					y = this->_minValue(deletedNode->right);
					y_original_color = y->color;
					x = y->right;
					if (x and y->parent == deletedNode) {
						x->parent = y;
					} else {
						this->_transplant(y, y->right);
						y->right = deletedNode->right;
						if (y->right) y->right->parent = y;
					}
					this->_transplant(deletedNode, y);
					y->left = deletedNode->left;
					if (y->left) y->left->parent = y;
					y->color = deletedNode->color;
				}
				this->_allocator.destroy(deletedNode);
				this->_allocator.deallocate(deletedNode, 1);
				if (y_original_color == BLACK)
					this->_deleteFix(x);
				return ft::make_pair<iterator, bool>(this->end(), true);
			};

			iterator		upper_bound(const value_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite)
				{
					if (this->_cmp(key, *it))
						return (it);
					it++;
				}
				return (it);
			};
			const_iterator	upper_bound(const value_type& key) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite)
				{
					if (this->_cmp(key, *it))
						return (it);
					it++;
				}
				return (it);
			};

			iterator		lower_bound(const value_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite) {
					if (not this->_cmp(*it, key))
						break;
					it++;
				}
				return (it);
			};
			const_iterator	lower_bound(const value_type& key) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite)
				{
					if (not this->_cmp(*it, key))
						break;
					it++;
				}
				return (it);
			};

			iterator		find (const value_type& k) {return this->_find(k, this->_root);};
			const_iterator	find (const value_type& k) const {return this->_cfind(k, this->_root);};

			void swap(setRBT& other) {
				ft::swap(this->_root, other._root);
				ft::swap(this->_cmp, other._cmp);
				ft::swap(this->_allocator, other._allocator);
			}
			node_pointer	minValue(void) const {return this->_minValue(this->_root);};
			node_pointer	maxValue(void) const {return this->_maxValue(this->_root);};
			
			void			clear(void) {this->_root = this->_clear(this->_root);};
			size_type		max_size(void) const {return this->_allocator.max_size();};
			
			/* *********** iterators *********** */
			iterator begin(void) {return (iterator(minValue(), NULL));};
			const_iterator begin(void) const {return (const_iterator(minValue(), NULL));};
			
			iterator end(void) {return (iterator(NULL, maxValue()));};			
			const_iterator end(void) const {return (const_iterator(NULL, maxValue()));};



		private:
			node_pointer					_root;
			key_compare						_cmp;
			node_allocator					_allocator;
		
		/* *********** privates members functions *********** */
		iterator		_find(const value_type& to_find, node_pointer node) {
			if (not node) return this->end();
			if (this->_cmp(to_find, node->value)) return this->_find(to_find, node->left);
			if (this->_cmp(node->value, to_find)) return this->_find(to_find, node->right);
			return iterator(node, node->parent);
		};
		const_iterator	_cfind(const value_type& to_find, const node_pointer node) const {
			if (not node) return this->end();
			if (this->_cmp(to_find, node->value)) return this->_cfind(to_find, node->left);
			if (this->_cmp(node->value, to_find)) return this->_cfind(to_find, node->right);
			return iterator(node, node->parent);
		};
			
		node_pointer	_minValue(node_pointer node) const {
			if (not node) return NULL;
			if (node->left) return _minValue(node->left);
			return node;
		};
		node_pointer	_maxValue(node_pointer node) const {
			if (not node) return NULL;
			if (node->right) return _maxValue(node->right);
			return node;
		};
		
		node_pointer	_clear(node_pointer node) {
			if (not node) return NULL;
			if (node->left) this->_clear(node->left);
			if (node->right) this->_clear(node->right);
			this->_allocator.destroy(node);
			this->_allocator.deallocate(node, 1);
			return NULL;
		};
		
		void			_leftRotate(node_pointer node) {
			node_pointer tmp = node->right;
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (not node->parent)
				this->_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
			return;
		};
		void			_rightRotate(node_pointer node) {
			node_pointer tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (not node->parent)
				this->_root = tmp;
			else if (node == node->parent->right)
				node->parent->right = tmp;
			else
				node->parent->left = tmp;
			tmp->right = node;
			node->parent = tmp;
		};
		void			_transplant(node_pointer node1, node_pointer node2) {
			if (not node1->parent)
				this->_root = node2;
			else if (node1 == node1->parent->left)
				node1->parent->left = node2;
			else
				node1->parent->right = node2;
			if (node2) node2->parent = node1->parent;
		};
		void			_insertFix(node_pointer node){
			while (node->parent and node->parent->color == RED) {
				if (node->parent->parent->left == node->parent) {	
					if (node->parent->parent->right and node->parent->parent->right->color == RED) {
						node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->right) {
							node = node->parent;
							this->_leftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						this->_rightRotate(node->parent->parent);
					}
				} else {
					if (node->parent->parent->left and node->parent->parent->left->color == RED) {
						node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							this->_rightRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						this->_leftRotate(node->parent->parent);
					}
				}
			}
			this->_root->color = BLACK;
			return;
		};
		void			_deleteFix(node_pointer node) {
			node_pointer sibling;
			while (node and node != this->_root and node->color == BLACK) {
				if (node->parent->left == node) {
					sibling = node->parent->right;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						this->_leftRotate(node->parent);
						sibling = node->parent->right;
					}
					if ((not sibling->left or sibling->left->color == BLACK) and (not sibling->right or sibling->right->color == BLACK)) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (not sibling->right or sibling->right->color == BLACK) {
							sibling->left->color = BLACK;
							sibling->color = RED;
							this->_rightRotate(sibling);
							sibling = node->parent->right;
						}
						sibling->color = node->parent->color;
						node->parent->parent->color = BLACK;
						if (sibling->right) sibling->right->color = BLACK;
						this->_leftRotate(node->parent);
						node = this->_root;
					}
				} else {
					sibling = node->parent->right;
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						this->_rightRotate(node->parent);
						sibling = node->parent->left;
					}
					if ((not sibling->left or sibling->left->color == BLACK) and (not sibling->right or sibling->right->color == BLACK)) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (not sibling->left or sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							this->_leftRotate(sibling);
							sibling = node->parent->left;
						}
						sibling->color = node->parent->color;
						if (node->parent->parent) node->parent->parent->color = BLACK;
						if (sibling->left) sibling->left->color = BLACK;
						this->_rightRotate(node->parent);
						node = this->_root;
					}
				}
			}
			if (node) node->color = BLACK;
		};
	};
}

#endif