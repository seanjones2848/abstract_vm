/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:38:59 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 16:08:00 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP
# include <string>
# include <list>
# include <cstdio>
# include "Exception.hpp"

enum token {
	PUSH = 258,
	POP = 259,
	DUMP = 260,
	ASSERT = 261,
	ADD = 262,
	SUB = 263,
	MUL = 264,
	DIV = 265,
	MOD = 266,
	PRINT = 267,
	EXIT = 268,
	END = 269,
	COMMENT = 270,
	EOL = 271,
	INT8 = 272,
	INT16 = 273,
	INT32 = 274,
	FLOAT = 275,
	DOUBLE = 276,
	ERROR = 278
};

struct Lex
{
	token				type;
	const std::string	val;
};

class Lexer
{
	public:
		Lexer();
		~Lexer();
		Lexer(int ac, char **av);
		Lexer(const Lexer&);
		const Lexer& operator=(const Lexer&);
		void run();
		std::list<Lex>& lex();
	private:
		class LexerException : public Exception
		{
			public:
				LexerException(const std::string& msg) : Exception(), _msg(msg) {}
				virtual const char * what() const throw() { return _msg.c_str(); }
				virtual ~LexerException() throw() {}
			private:
				std::string	_msg;
		};
		std::list<Lex>	_lex;
};

#endif
