/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:30:30 by sjones            #+#    #+#             */
/*   Updated: 2018/02/14 16:49:33 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
# include <string>

class Exception : public std::exception
{
	public:
		Exception() {};
		Exception(const Exception&);
		virtual ~Exception() throw() {};
		const Exception & operator=(const Exception &);
		virtual const char * what() const throw() { return _msg.c_str(); }
	private:
		std::string		_msg;
};

#endif
