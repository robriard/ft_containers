/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:06:21 by unknow            #+#    #+#             */
/*   Updated: 2022/01/10 16:29:54 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utility.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include <memory>
# include <stdexcept>

namespace ft {
    template <class Type, class Allocator = std::allocator<Type> >
    class vector {
        public:

            /* *********** member types *********** */
            typedef Type       									    value_type;
            typedef Allocator                         			    allocator_type;
            typedef typename allocator_type::reference			    reference;
            typedef typename allocator_type::const_reference	    const_reference;
            typedef typename allocator_type::pointer			    pointer;
            typedef typename allocator_type::const_pointer		    const_pointer;
            typedef ft::random_access_iterator<value_type>		    iterator;
            typedef ft::random_access_iterator<const value_type>    const_iterator;
            typedef ft::reverse_iterator<iterator>		            reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>	        const_reverse_iterator;
            typedef typename Allocator::size_type                   size_type;
            typedef typename Allocator::difference_type             difference_type;

            /* *********** member functions *********** */ 
            explicit vector (const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _vector(NULL), _size(0), _capacity(0) {return;};
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _vector(NULL), _size(n), _capacity(n) {
				if (n)
					this->_vector = this->_allocator.allocate(n);
				for (size_type i = 0; i < n; i++) this->_allocator.construct(&this->_vector[i], val);
			};
            template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _allocator(alloc), _vector(NULL), _size(0), _capacity(ft::distance(first, last)) {
				if (this->_capacity)
					this->_vector = this->_allocator.allocate(this->_capacity);
				for (; first != last; first++) this->_allocator.construct(&this->_vector[this->_size++], *first);
			};
            vector (const vector& x) : _allocator(x._allocator), _size(x._size), _capacity(x._size) {
				if (this->_capacity)
					this->_vector = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++) this->_allocator.construct(&this->_vector[i], x._vector[i]);
			};
            ~vector (void) {
				for (size_type i = 0; i < this->_size; i++) this->_allocator.destroy(&this->_vector[i]);
				if (this->_vector != NULL) this->_allocator.deallocate(this->_vector, this->_capacity);
			};
            vector& operator=(const vector& x) {
                if (x == *this)
					return *this;
				this->clear();
				this->insert(begin(), x.begin(), x.end());
				return (*this);
            };

            /* *********** iterators *********** */
            iterator 				begin(void) {return iterator(this->_vector);};
			const_iterator			begin(void) const {return const_iterator(_vector);};
			iterator				end(void) {return iterator(this->_vector + this->_size);};
			const_iterator			end(void) const {return const_iterator(this->_vector + this->_size);};
			reverse_iterator		rbegin(void) {return reverse_iterator(this->_vector + this->_size);};
			const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(this->_vector + this->_size);};
			reverse_iterator		rend(void) {return reverse_iterator(this->_vector);};
			const_reverse_iterator	rend(void) const {return const_reverse_iterator(this->_vector);};
            
            /* *********** capacity *********** */
            size_type size(void) const {return this->_size;};
            size_type max_size(void) const {return this->_allocator.max_size();};
            void resize (size_type n, value_type val = value_type()) {
                if (n < this->_size) {
					for (size_type i = n; i < this->_size; i++)
						this->_allocator.destroy(&this->_vector[i]);
					this->_size = n;
				}
				else if (n > this->_size) {
					if (n > this->_size * 2)
						this->reserve(n);
					else this->reserve (this->_size * 2);
					for (size_type i = this->_size; i < n; i++)
						this->_allocator.construct(&this->_vector[i], val);
					this->_size = n;
				}
            };
            size_type capacity(void) const {return this->_capacity;};
            bool empty(void) const {return (this->_size == 0);};
            void reserve(size_type n) {
				if (n > this->max_size()) throw std::length_error("vector::reserve");
				else if (n > this->_capacity) {
					pointer tmp = this->_allocator.allocate(n);
					if (this->_capacity > 0) {
						for (size_type i = 0; i < this->_size; i++) {
							this->_allocator.construct(&tmp[i], this->_vector[i]);
							this->_allocator.destroy(&this->_vector[i]);
						}
						this->_allocator.deallocate(this->_vector, this->_capacity);
					}
					this->_capacity = n;
					this->_vector = tmp;
				}
			};

            /* *********** element access *********** */
            reference operator[](size_type n) {return this->_vector[n];};
            const_reference operator[](size_type n) const {return this->_vector[n];};
            reference at (size_type n) {
                if (n > this->_size) throw std::out_of_range("vector::at");
                return this->_vector[n];
            };
            const_reference at (size_type n) const {
                if (n > this->size) throw std::out_of_range("vector::at");
                return this->vector[n];
            };
            reference front(void) {return this->_vector[0];};
            const_reference front(void) const {return this->_vector[0];};
            reference back(void) {return this->_vector[this->_size -1];};
            const_reference back(void) const {return this->_vector[this->_size -1];};

            /* *********** modifiers *********** */
			void assign (size_type n, const value_type& val) {
				this->clear();
				this->reserve(n);
				this->insert(this->begin(), n, val);
			};
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				this->clear();
				this->reserve(ft::distance(first, last));
				this->insert(this->begin(), first, last);
			};
			void push_back (const value_type& val) {
				if (this->_capacity > 0 && this->_size == this->_capacity) {
					pointer new_vector = this->_allocator.allocate(this->_capacity * 2);
					for (size_type i = 0; i < this->_size; i++) {
						this->_allocator.construct(&new_vector[i], this->_vector[i]);
						this->_allocator.destroy(&this->_vector[i]);
					}
					this->_allocator.deallocate(this->_vector, this->_capacity);
					this->_capacity *= 2;
					this->_vector = new_vector;
				}
				else if (this->_capacity == 0) {
					this->_capacity = 1;
					this->_vector = this->_allocator.allocate(this->_capacity);
				}
				this->_allocator.construct(&this->_vector[this->_size], val);
				this->_size++;
			};
			void pop_back(void) {
				if (this->_size > 0) {
					this->_allocator.destroy(&this->_vector[this->_size - 1]);
					this->_size--;
				}
			};
			iterator insert(iterator position, const value_type& val) {
				difference_type pos = position - this->_vector;
				this->reserve(this->_size + 1);
				for (difference_type i = this->_size; i > pos; i--) {
					this->_allocator.construct(&this->_vector[i], this->_vector[i - 1]);
					this->_allocator.destroy(&this->_vector[i - 1]);
				}
				this->_allocator.construct(&this->_vector[pos], val);
				this->_size++;
				return (&this->_vector[pos]);
			};
			void insert(iterator position, size_type n, const value_type& val) {
				difference_type pos = position - this->_vector;
				if (n + this->_size > this->_capacity) {
					if (this->_size + n > this->_size * 2)
						this->reserve(this->_size + n);
					else this->reserve (this->_size * 2);
				}
				for (difference_type i = this->_size; i > pos; i--) {
					this->_allocator.construct(&this->_vector[i + n - 1], this->_vector[i - 1]);
					this->_allocator.destroy(&this->_vector[i - 1]);
				}
				for (size_type i = 0; i < n; i++) this->_allocator.construct(&this->_vector[pos + i], val);
				this->_size += n;
			};
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				size_type pos = position - this->_vector;
				size_type n = ft::distance(first, last);
				if (n + this->_size > this->_capacity) {
					if (this->_size + n > this->_size * 2)
						this->reserve(this->_size + n);
					else this->reserve (this->_size * 2);
				}
				for (size_type i = this->_size; i > pos; i--) {
					this->_allocator.construct(&this->_vector[i + n - 1], this->_vector[i - 1]);
					this->_allocator.destroy(&this->_vector[i - 1]);
				}
				for (size_type i = 0; first != last; first++, i++)
					this->_allocator.construct(&this->_vector[pos + i], *first);
				this->_size += n;
			};
			iterator erase(iterator position) {
				for (size_type i = position - this->_vector; i < this->_size - 1; i++) {
					this->_allocator.destroy(&this->_vector[i]);
					this->_allocator.construct(&this->_vector[i], this->_vector[i + 1]);
				}
				this->_allocator.destroy(&this->_vector[this->_size - 1]);
				this->_size--;
				return (iterator(position));
			};
			iterator erase(iterator first, iterator last) {
				size_type n = last - first;
				for (size_type i = first - this->_vector; i < this->_size - n; i++) {
					this->_allocator.destroy(&this->_vector[i]);
					this->_allocator.construct(&this->_vector[i], this->_vector[i + n]);
				}
				for (size_type i = this->_size - n; i < this->_size; i++) this->_allocator.destroy(&this->_vector[i]);
				this->_size -= n;
				return (iterator(first));
			};
			void swap (vector& x) {
				ft::swap(_vector, x._vector);
				ft::swap(_size, x._size);
				ft::swap(_capacity, x._capacity);
			};
			void clear(void) {
				if (this->_vector)
					for (size_type i = 0; i < this->_size; i++) this->_allocator.destroy(&this->_vector[i]);
				this->_size = 0;
			}

            /* *********** allocator *********** */
			allocator_type get_allocator() const {return this->_allocator;};

        private:
            allocator_type  _allocator;
            pointer         _vector;
            size_type       _size;
            size_type       _capacity;



    };

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		if (x.size() != y.size()) return false;
		for (size_t i = 0; i < x.size(); i++) if (x[i] != y[i]) return false;
		return true;
	};
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {return !(x == y);};
	
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());};
	
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {return !(y < x);};

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {return y < x;};

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {return !(x < y);};

	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {x.swap(y);}
}

#endif