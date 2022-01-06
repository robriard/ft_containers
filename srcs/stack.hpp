/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unknow <unknow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:14:21 by unknow            #+#    #+#             */
/*   Updated: 2021/12/30 16:43:41 by unknow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include "vector.hpp"

namespace ft {
	template <class T, class Container = vector<T> >
	class stack {
		public:
            /* *********** member types *********** */
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;
			typedef typename Container::value_type	value_type;
	
            /* *********** member functions *********** */
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {return;};
			bool empty(void) const {return this->c.empty();};
			size_type size(void) const {return this->c.size();};
			value_type& top(void) {return this->c.back();};
			const value_type& top(void) const {return this->c.back();};
			void push(const value_type& val) {this->c.push_back(val);};
			void pop(void){this->c.pop_back();};

            /* *********** non-member functions *********** */
			template <class T2, class Container2>
			friend bool operator== (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			template <class T2, class Container2>
			friend bool operator!= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			template <class T2, class Container2>
			friend bool operator< (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			template <class T2, class Container2>
			friend bool operator<= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			template <class T2, class Container2>
			friend bool operator> (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);
			template <class T2, class Container2>
			friend bool operator>= (const ft::stack<T2, Container2>& lhs, const ft::stack<T2, Container2>& rhs);

		protected:
			container_type	c;
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c == rhs.c);};

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c != rhs.c);};    

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c < rhs.c);};

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c > rhs.c);};

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c <= rhs.c);};

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c >= rhs.c);};
}

#endif