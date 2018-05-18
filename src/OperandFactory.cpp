/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:32:02 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 19:42:48 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
{
	create[Int8] = &OperandFactory::createInt8;
	create[Int16] = &OperandFactory::createInt16;
	create[Int32] = &OperandFactory::createInt32;
	create[Float] = &OperandFactory::createFloat;
	create[Double] = &OperandFactory::createDouble;
}

OperandFactory::~OperandFactory() {}

IOperand const*	OperandFactory::createOperand(eOperandType type, std::string const& val) const
{
	IOperand const* (OperandFactory::*f)(std::string const & val) const;
	f = create.at(type);
	return ((*this.*f)(val));
}

IOperand const*	OperandFactory::createInt8(std::string const & val) const
{ return (new Operand<char>(val, Int8, 0, this)); }

IOperand const*	OperandFactory::createInt16(std::string const & val) const
{ return (new Operand<short int>(val, Int16, 0, this)); }

IOperand const*	OperandFactory::createInt32(std::string const & val) const
{ return (new Operand<int>(val, Int32, 0, this)); }

IOperand const*	OperandFactory::createFloat(std::string const & val) const
{ return (new Operand<float>(val, Float, 7, this)); }

IOperand const*	OperandFactory::createDouble(std::string const & val) const
{ return (new Operand<double>(val, Double, 14, this)); }
