/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:07:40 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 19:38:57 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP
# include <iomanip>
# include <iostream>
# include <string>
# include <sstream>
# include <float.h>
# include <limits.h>
# include <math.h>
# include "Exception.hpp"
# include "IOperand.hpp"
# include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
	public:
		Operand();
		~Operand() {};
		Operand(const Operand&);
		const Operand & operator=(const Operand&);
		std::string const & toString() const { return (_str); }
		int getPrecision() const { return _prec; }
		eOperandType getType() const { return _type; }
		Operand(std::string const & val, eOperandType type, int prec, const OperandFactory* fact)
			: _type(type), _prec(prec), _fact(fact)
		{
			try
			{
				std::stringstream ss(std::stringstream::out);
				long long i = std::stoll(val);
				long double d = std::stold(val);
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				_val = type <= Int32 ? static_cast<T>(i) : static_cast<T>(d);
				type <= Int32 ? ss << std::setprecision(prec) << i :  ss << std::setprecision(prec) << d;
				_str = ss.str();
			}
			catch(const std::out_of_range& oor) { oor.what(); }
		}
		IOperand const * operator+( IOperand const & rhs ) const
		{
			eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
			int prec = ( _prec >= rhs.getPrecision() ) ? _prec : rhs.getPrecision();
			try
			{
				std::stringstream ss(std::stringstream::out);
				long long i = std::stoll(_str) + std::stoll(rhs.toString());
				long double d = std::stold(_str) + std::stold(rhs.toString());
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				type <= Int32 ? ss << i : ss << std::setprecision(prec) << d;
				return (_fact->createOperand(type, ss.str()));
			}
			catch(const std::out_of_range& oor) { oor.what(); }
			return (0);
		}
		IOperand const * operator-( IOperand const & rhs ) const
		{
			eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
			int prec = ( _prec >= rhs.getPrecision() ) ? _prec : rhs.getPrecision();
			try
			{
				std::stringstream ss(std::stringstream::out);
				long long i = std::stoll(_str) - std::stoll(rhs.toString());
				long double d = std::stold(_str) - std::stold(rhs.toString());
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				type <= Int32 ? ss << i : ss << std::setprecision(prec) << d;
				return (_fact->createOperand(type, ss.str()));
			}
			catch(const std::out_of_range& oor) { oor.what(); }
			return (0);
		}
		IOperand const * operator*( IOperand const & rhs ) const
		{
			eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
			int prec = ( _prec >= rhs.getPrecision() ) ? _prec : rhs.getPrecision();
			try
			{
				std::stringstream ss(std::stringstream::out);
				long long i = std::stoll(_str) * std::stoll(rhs.toString());
				long double d = std::stold(_str) * std::stold(rhs.toString());
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				type <= Int32 ? ss << i : ss << std::setprecision(prec) << d;
				return (_fact->createOperand(type, ss.str()));
			}
			catch(const std::out_of_range& oor) { oor.what(); }
			return (0);
		}
		IOperand const * operator/( IOperand const & rhs ) const
		{
			eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
			int prec = ( _prec >= rhs.getPrecision() ) ? _prec : rhs.getPrecision();
			try
			{
				if (std::stold(rhs.toString()) == 0)
					throw OperandException("Division by zero!");
				std::stringstream ss(std::stringstream::out);
				long long i = std::stoll(_str) / std::stoll(rhs.toString());
				long double d = std::stold(_str) / std::stold(rhs.toString());
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				type <= Int32 ? ss << i : ss << std::setprecision(prec) << d;
				return (_fact->createOperand(type, ss.str()));
			}
			catch(const std::out_of_range& oor) { oor.what(); }
			return (0);
		}
		IOperand const * operator%( IOperand const & rhs ) const
		{
			eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
			int prec = ( _prec >= rhs.getPrecision() ) ? _prec : rhs.getPrecision();
			try
			{
				if (std::stold(rhs.toString()) == 0)
					throw OperandException("Division by zero!");
				std::stringstream ss(std::stringstream::out);
				long long i = fmod(std::stoll(_str), std::stoll(rhs.toString()));
				long double d = fmod(std::stold(_str), std::stold(rhs.toString()));
				if (hasOverflow<long long>(i, type) || hasOverflow<long double>(d, type))
					throw OperandException("Overflow or underflow detected!");
				type <= Int32 ? ss << i : ss << std::setprecision(prec) << d;
				return (_fact->createOperand(type, ss.str()));
			}
			catch(const std::out_of_range& oor) { oor.what(); }
			return (0);
		}
		template <typename U>
		bool hasOverflow(U r, eOperandType type) const
		{
			switch (type)
			{
				case (Int8):
					return (r < SCHAR_MIN || r > SCHAR_MAX);
				case (Int16):
					return (r < SHRT_MIN || r > SHRT_MAX);
				case (Int32):
					return (r < INT_MIN || r > INT_MAX);
				case (Float):
					return (r < -FLT_MAX || r > FLT_MAX);
				case (Double):
					return (r < -DBL_MAX || r > DBL_MAX);
				break;
			}
			return (true);
		}
	private:
		class OperandException : public Exception
		{
			public:
				OperandException(const std::string & msg) : Exception(), _msg(msg) {}
				virtual const char * what() const throw() { return _msg.c_str(); }
				virtual ~OperandException() throw() {}
			private:
				std::string		_msg;
		};
		std::string				_str;
		T						_val;
		eOperandType			_type;
		int						_prec;
		const OperandFactory	*_fact;
};

#endif
