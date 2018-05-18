/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:22:18 by sjones            #+#    #+#             */
/*   Updated: 2018/02/14 11:28:52 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP
# include <string>
# include <map>
# include "IOperand.hpp"

class OperandFactory
{
	public:
		OperandFactory();
		OperandFactory(const OperandFactory&);
		~OperandFactory();
		OperandFactory const & operator=(const OperandFactory&);
		IOperand const * createOperand(eOperandType type, std::string const & val) const;
	private:
		IOperand const * createInt8(std::string const & val) const;
		IOperand const * createInt16(std::string const & val) const;
		IOperand const * createInt32(std::string const & val) const;
		IOperand const * createFloat(std::string const & val) const;
		IOperand const * createDouble(std::string const & val) const;
		std::map<eOperandType, IOperand const * (OperandFactory::*)(std::string const & val) const> create;
};

#endif
