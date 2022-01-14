/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:35:10 by unknow            #+#    #+#             */
/*   Updated: 2022/01/14 16:42:10 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <functional>
# include "utility.hpp"
# include "RBT_iterator.hpp"

namespace ft {
	# define RED 1
	# define BLACK 2
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
	template <class Type, class Compare = ft::less<typename Type::first_type>, class Node = Node<Type>, class Type_Alloc = std::allocator<Type>, class Node_Alloc = std::allocator<Node> >
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
			typedef typename Node::node_pointer							node_pointer;
			typedef typename Node::const_node_pointer					const_node_pointer;
			typedef typename Node::node_reference						node_reference;
			typedef typename Node::const_node_reference					const_node_reference;

			/* *********** constructor *********** */
			RBT(const key_compare &cmp = key_compare()) : _root(NULL), _cmp(cmp), _allocator(node_allocator()) {return;};
			RBT(const RBT &src) : _root(src._root), _cmp(src._cmp), _allocator(src._allocator) {return;};
			~RBT(void) {this->_clear(this->_root); return;};

			/* *********** operators *********** */
			RBT &operator=(RBT const &other) {
				if (this != &other)
					this->_root = other._root;
				return (*this);
			};
			node_reference operator*() const {return ((this->_root));};
			node_pointer operator->() const {return (&(this->_root));};

			/* *********** publics members functions *********** */
			
			// Preorder
			void	preOrderHelper(void) {this->preOrderHelper(this->_root);};
			void	preOrderHelper(node_pointer node) {
    			if (node) {
     				std::cout << "----------" << std::endl;
					std::cout << node->value.first<<":"<<node->value.second << std::endl;
					if (node->color == BLACK) std::cout << "BLACK" << std::endl; else std::cout << "RED" << std::endl;
					if (node->parent) std::cout << "parent = " << node->parent->value.first<<":"<<node->parent->value.second << std::endl;
					else std::cout << "parent = NULL" << std::endl;
					if (node->left) std::cout << "left = " << node->left->value.first<<":"<<node->left->value.second << std::endl;
					else std::cout << "left = NULL" << std::endl;
					if (node->right) std::cout << "right = " << node->right->value.first<<":"<<node->right->value.second << std::endl;
					else std::cout << "right = NULL" << std::endl;
      			preOrderHelper(node->left);
      			preOrderHelper(node->right);
    			}
  			};
  			// Inorder
			void	inOrderHelper(void) {this->inOrderHelper(this->_root);};
			void	inOrderHelper(node_pointer node) {
				if (node) {
					inOrderHelper(node->left);
					std::cout << "----------" << std::endl;
					std::cout << node->value.first<<":"<<node->value.second << std::endl;
					if (node->color == BLACK) std::cout << "BLACK" << std::endl; else std::cout << "RED" << std::endl;
					if (node->parent) std::cout << "parent = " << node->parent->value.first<<":"<<node->parent->value.second << std::endl;
					else std::cout << "parent = NULL" << std::endl;
					if (node->left) std::cout << "left = " << node->left->value.first<<":"<<node->left->value.second << std::endl;
					else std::cout << "left = NULL" << std::endl;
					if (node->right) std::cout << "right = " << node->right->value.first<<":"<<node->right->value.second << std::endl;
					else std::cout << "right = NULL" << std::endl;
					inOrderHelper(node->right);
				}
			};
			
			ft::pair<iterator, bool> insert( const value_type& value) {
				node_pointer newNode = this->_allocator.allocate(1);
				this->_allocator.construct(newNode, Node(value));
				if (not this->_root) {
					this->_root = newNode;
					this->_root->color = BLACK;
					return ft::make_pair<iterator, bool>(iterator(newNode, NULL), true);
				}
				node_pointer x = this->_root;
				node_pointer parent = NULL;
				while(x) {
					parent = x;
					if (this->_cmp(x->value.first, newNode->value.first))
						x = x->right;
					else if (this->_cmp(newNode->value.first, x->value.first))
						x = x->left;
					else {
						this->_allocator.destroy(newNode);
						this->_allocator.deallocate(newNode, 1);
						return ft::make_pair<iterator, bool>(iterator(newNode, NULL), false);
					}
				}
				x = newNode;
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
				while (deletedNode and deletedNode->value.first != value) {
					if (this->_cmp(value, deletedNode->value.first))
						deletedNode = deletedNode->left;
					else if (this->_cmp(deletedNode->value.first, value))
						deletedNode = deletedNode->right;
				}
				if (not deletedNode) return ft::make_pair<iterator, bool>(this->end(), false);
				int originalColor = deletedNode->color;
				node_pointer child;
				if (not deletedNode->left) {
					child = deletedNode->right;
					this->_transplant(deletedNode, child);
				} else if (not deletedNode->right) {
					child = deletedNode->left;
				} else {
					node_pointer tmp = this->_minValue(deletedNode->right);
					originalColor = tmp->color;
					child = tmp->right;
					if (tmp->parent == deletedNode)
						tmp->parent = tmp;
					else {
						this->_transplant(tmp, tmp->right);
						tmp->right = deletedNode->right;
						tmp->right->parent = tmp;
					}
					this->_transplant(deletedNode, tmp);
					tmp->left = deletedNode->left;
					tmp->left->parent = tmp;
					tmp->color = deletedNode->color;
				}
				this->_allocator.destroy(deletedNode);
				this->_allocator.deallocate(deletedNode, 1);
				if (originalColor == BLACK)
					this->_deleteFix(child);
				return ft::make_pair<iterator, bool>(iterator(deletedNode, NULL), true);
			}

			iterator		upper_bound(const key_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite)
				{
					if (this->_cmp(key, it->first))
						break;
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
						break;
					it++;
				}
				return (it);
			};

			iterator		lower_bound(const key_type& key) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite)
				{
					if (not this->_cmp(key, it->first))
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
					if (not this->_cmp(key, it->first))
						break;
					it++;
				}
				return (it);
			};

			iterator		find (const key_type& k) {return this->_find(k, this->_root);};
			const_iterator	find (const key_type& k) const {return this->_cfind(k, this->_root);};


			node_pointer	minValue(void) const {return this->_minValue(this->_root);};
			node_pointer	maxValue(void) const {return this->_maxValue(this->_root);};
			
			void			clear(void) {this->_root = this->_clear(this->_root);};
			size_type		max_size(void) const {return this->_allocator.max_size();};
			
			/* *********** iterators *********** */
			// iterator begin(void) {return iterator(minValue(), NULL);};
			iterator begin(void) {return (iterator(minValue(), NULL));};
			
			
			// const_iterator begin(void) const {return const_iterator(minValue(), NULL);};
			const_iterator begin(void) const {return (const_iterator(minValue(), NULL));};
			
			
			// iterator end(void) {return iterator(NULL, maxValue());};
			iterator end(void) {return (iterator(NULL, maxValue()));};
			
			
			// const_iterator end(void) const {return const_iterator(NULL, maxValue());};
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
					if (sibling->left->color == BLACK and sibling->right->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (sibling->right->color == BLACK) {
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
					if (sibling->right->color == BLACK and sibling->left->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						if (sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							this->_leftRotate(sibling);
							sibling = node->parent->left;
						}
						sibling->color = node->parent->color;
						node->parent->parent->color = BLACK;
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