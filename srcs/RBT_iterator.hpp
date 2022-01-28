/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:33:49 by unknow            #+#    #+#             */
/*   Updated: 2022/01/28 14:06:23 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

	/* ************************************************************************** */
	/*           MAP_ITERATOR                                                     */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class MAP_const_iterator;
	template <typename T, class Compare>
	class MAP_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			MAP_iterator(void) : _node(NULL), _parent(NULL) {return;};
			MAP_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			MAP_iterator(const MAP_iterator &it) : _node(it._node), _parent(it._parent) {return;};
			virtual ~MAP_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			MAP_iterator &operator=(const MAP_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			MAP_iterator &operator++(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->right) {
						this->_node = this->_node->right;
						while (this->_node->left)
							this->_node = this->_node->left;
					}
					else {
						while (this->_node->parent and this->_node->parent->right == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			};
			MAP_iterator operator++(int) {
				MAP_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			MAP_iterator &operator--(void) {	
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left) {
						this->_node = this->_node->left;
						while (this->_node->right)
							this->_node = this->_node->right;
					} else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			MAP_iterator operator--(int) {
				MAP_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const MAP_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const MAP_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};

	/* ************************************************************************** */
	/*           MAP_CONST_ITERATOR                                               */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class MAP_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type const															value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			MAP_const_iterator(void) : _node(NULL), _parent(NULL) {return;};
			MAP_const_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			MAP_const_iterator(const MAP_const_iterator &it) : _node(it._node), _parent(it._parent) {return;};
			MAP_const_iterator(const MAP_iterator<T, Compare> &it) : _node(it.getNode()), _parent(it.getParent()) {return;};
			virtual ~MAP_const_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			MAP_const_iterator &operator=(const MAP_const_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			MAP_const_iterator &operator++(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->right) {
						this->_node = this->_node->right;
						while (this->_node->left)
							this->_node = this->_node->left;
					}
					else {
						while (this->_node->parent and this->_node->parent->right == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			};
			MAP_const_iterator operator++(int) {
				MAP_const_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			MAP_const_iterator &operator--(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left) {
						this->_node = this->_node->left;
						while (this->_node->right)
							this->_node = this->_node->right;
					} else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			MAP_const_iterator operator--(int) {
				MAP_const_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const MAP_const_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const MAP_const_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};






	/* ************************************************************************** */
	/*           SET_ITERATOR                                                     */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class SET_const_iterator;
	template <typename T, class Compare>
	class SET_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			SET_iterator(void) : _node(NULL), _parent(NULL) {return;};
			SET_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			SET_iterator(const SET_iterator<T, Compare> &it) : _node(it._node), _parent(it._parent) {return;};
			SET_iterator(const SET_const_iterator<T, Compare> &it) : _node(it.getNode()), _parent(it.getParent()) {return;};
			virtual ~SET_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			SET_iterator &operator=(const SET_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			SET_iterator &operator++(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->right) {
						this->_node = this->_node->right;
						while (this->_node->left)
							this->_node = this->_node->left;
					}
					else {
						while (this->_node->parent and this->_node->parent->right == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			};
			SET_iterator operator++(int) {
				SET_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			SET_iterator &operator--(void) {	
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left) {
						this->_node = this->_node->left;
						while (this->_node->right)
							this->_node = this->_node->right;
					} else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			SET_iterator operator--(int) {
				SET_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const SET_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const SET_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};

	/* ************************************************************************** */
	/*           SET_CONST_ITERATOR                                               */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class SET_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type const															value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			SET_const_iterator(void) : _node(NULL), _parent(NULL) {return;};
			SET_const_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			SET_const_iterator(const SET_const_iterator &it) : _node(it._node), _parent(it._parent) {return;};
			SET_const_iterator(const SET_iterator<T, Compare> &it) : _node(it.getNode()), _parent(it.getParent()) {return;};
			virtual ~SET_const_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			SET_const_iterator &operator=(const SET_const_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			SET_const_iterator &operator++(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->right) {
						this->_node = this->_node->right;
						while (this->_node->left)
							this->_node = this->_node->left;
					}
					else {
						while (this->_node->parent and this->_node->parent->right == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			};
			SET_const_iterator operator++(int) {
				SET_const_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			SET_const_iterator &operator--(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left) {
						this->_node = this->_node->left;
						while (this->_node->right)
							this->_node = this->_node->right;
					} else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			SET_const_iterator operator--(int) {
				SET_const_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const SET_const_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const SET_const_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};
}
#endif