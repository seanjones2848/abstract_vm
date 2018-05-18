/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:21:40 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 19:40:35 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <iostream>

extern int		yylex();
extern FILE*	yyin;
extern char*	yytext;
extern int		yyleng;

Lexer::Lexer(int ac, char **av) : _lex(0)
{
	if (ac > 2)
		throw LexerException("Lexer: Too many arguments!");
	if (ac == 2)
	{
		yyin = fopen(av[1], "r");
		if (!yyin)
			throw LexerException("Lexer: Cannot open file!");
	}
	run();
}

void	Lexer::run()
{
	int tok;

	while ((tok = yylex()))
	{
		if (tok == ERROR)
			throw LexerException("Lexer: Illegal instruction!");
		if (tok == END)
			break;
		const std::string val = yytext;
		_lex.push_back({static_cast<token>(tok), val});
	}
}

std::list<Lex>&	Lexer::lex() { return (_lex); }

Lexer::~Lexer() {}
