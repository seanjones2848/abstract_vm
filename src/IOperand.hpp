/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:16:21 by sjones            #+#    #+#             */
/*   Updated: 2018/02/14 13:56:38 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP
# include <string>
# include "eOperandType.hpp"

class IOperand
{
	public:
		virtual int getPrecision( void ) const = 0;
		virtual eOperandType getType( void ) const = 0;
		virtual IOperand const *	operator+( IOperand const & rhs) const = 0;
		virtual IOperand const *	operator-( IOperand const & rhs) const = 0;
		virtual IOperand const *	operator*( IOperand const & rhs) const = 0;
		virtual IOperand const *	operator/( IOperand const & rhs) const = 0;
		virtual IOperand const *	operator%( IOperand const & rhs) const = 0;
		virtual std::string const & toString( void ) const = 0;
		virtual ~IOperand() {}
};

#endif
