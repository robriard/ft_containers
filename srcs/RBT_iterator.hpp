/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:33:49 by unknow            #+#    #+#             */
/*   Updated: 2022/01/19 15:59:23 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	/* ************************************************************************** */
	/*           RBT_ITERATOR                                                     */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class RBT_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			RBT_iterator(void) : _node(NULL), _parent(NULL) {return;};
			RBT_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			RBT_iterator(const RBT_iterator &it) : _node(it._node), _parent(it._parent) {return;};
			virtual ~RBT_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			RBT_iterator &operator=(const RBT_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			RBT_iterator &operator++(void) {
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
			RBT_iterator operator++(int) {
				RBT_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			RBT_iterator &operator--(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left)
						this->_node = this->_node->left;
					else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			RBT_iterator operator--(int) {
				RBT_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const RBT_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const RBT_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};

	/* ************************************************************************** */
	/*           RBT_CONST_ITERATOR                                               */
	/* ************************************************************************** */
	template <typename T, class Compare>
	class RBT_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T *																						node_ptr;
			typedef typename T::value_type const															value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			
            /* *********** constructors *********** */
			RBT_const_iterator(void) : _node(NULL), _parent(NULL) {return;};
			RBT_const_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {return;};
			RBT_const_iterator(const RBT_const_iterator &it) : _node(it._node), _parent(it._parent) {return;};
			RBT_const_iterator(const RBT_iterator<T, Compare> &it) : _node(it.getNode()), _parent(it.getParent()) {return;};
			virtual ~RBT_const_iterator(void) {return;};

            /* *********** operators *********** */
			reference operator*(void) const {return(this->_node->value);};
			pointer operator->(void) const {return(&(this->_node->value));};
			RBT_const_iterator &operator=(const RBT_const_iterator &it) {
				this->_node = it._node;
				this->_parent = it._parent;
				return (*this);
			};
			RBT_const_iterator &operator++(void) {
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
			RBT_const_iterator operator++(int) {
				RBT_const_iterator tmp = *this;
				operator++();
				return (tmp);
			};
			RBT_const_iterator &operator--(void) {
				if (this->_node) {
					this->_parent = this->_node;
					if (this->_node->left)
						this->_node = this->_node->left;
					else {
						while (this->_node->parent and this->_node->parent->left == this->_node)
							this->_node = this->_node->parent;
						this->_node = this->_node->parent;
					}
				}
				else
					this->_node = this->_parent;
				return (*this);
			};
			RBT_const_iterator operator--(int) {
				RBT_const_iterator tmp = *this;
				operator--();
				return (tmp);
			};
			bool operator==(const RBT_const_iterator &it) const {return(this->_node == it._node);};
			bool operator!=(const RBT_const_iterator &it) const {return(this->_node != it._node);};

            /* *********** member functions *********** */
			node_ptr	getNode(void) const {return(this->_node);};
			node_ptr	getParent(void) const {return(this->_parent);};

		
        private:
			node_ptr	_node;
			node_ptr	_parent;
	};
}
#endif