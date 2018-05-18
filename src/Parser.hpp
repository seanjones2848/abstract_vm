/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:06:59 by sjones            #+#    #+#             */
/*   Updated: 2018/02/15 13:13:57 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP
# include <map>
# include <list>
# include <iostream>
# include "Exception.hpp"
# include "Lexer.hpp"
# include "OperandFactory.hpp"
# include "IOperand.hpp"

class Parser
{
	public:
		Parser();
		Parser(const Parser&);
		Parser(std::list<Lex>& lex);
		~Parser();
		const Parser& operator=(const Parser&);
		void run();
		void push(std::list<Lex>::iterator& i);
		void pop(std::list<Lex>::iterator& i);
		void dump(std::list<Lex>::iterator& i);
		void assert(std::list<Lex>::iterator& i);
		void add(std::list<Lex>::iterator& i);
		void sub(std::list<Lex>::iterator& i);
		void mul(std::list<Lex>::iterator& i);
		void div(std::list<Lex>::iterator& i);
		void mod(std::list<Lex>::iterator& i);
		void print(std::list<Lex>::iterator& i);
		void exit(std::list<Lex>::iterator& i);
		void end(std::list<Lex>::iterator& i);
	private:
		class ParserException : public Exception
		{
			public:
				ParserException(const std::string& msg) : Exception(), _msg(msg) {}
				virtual const char * what() const throw() { return _msg.c_str(); }
				virtual ~ParserException() throw() {}
			private:
				std::string _msg;
		};
		std::list<Lex>&												_lex;
		std::list<const IOperand*>									_stack;
		std::map<int, void (Parser::*)(std::list<Lex>::iterator&)>	_ops;
		OperandFactory												_fact;
};

#endif
