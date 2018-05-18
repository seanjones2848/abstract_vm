/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:13:02 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 19:57:07 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(std::list<Lex>& lex) : _lex(lex)
{
	_ops[0] = &Parser::push;
	_ops[1] = &Parser::pop;
	_ops[2] = &Parser::dump;
	_ops[3] = &Parser::assert;
	_ops[4] = &Parser::add;
	_ops[5] = &Parser::sub;
	_ops[6] = &Parser::mul;
	_ops[7] = &Parser::div;
	_ops[8] = &Parser::mod;
	_ops[9] = &Parser::print;
	_ops[10] = &Parser::exit;
	run();
}

void Parser::run()
{
	for (std::list<Lex>::iterator i = _lex.begin(); i != _lex.end(); i++)
	{
		if (i->type > END)
			continue;
		(this->*_ops.at(i->type - PUSH))(i);
	}
	throw ParserException("Parser: Missing exit instruction at end!");
}

void Parser::push(std::list<Lex>::iterator& i)
{
	std::list<Lex>::iterator next = ++i;
	_stack.push_front(_fact.createOperand(static_cast<eOperandType>(next->type - INT8), next->val));
}

void Parser::pop(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() == 0)
		throw ParserException("Parser: Pop instruction on empty stack!");
	_stack.pop_front();
}

void Parser::dump(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() == 0)
		throw ParserException("Parser: Dump instruction on empty stack!");
	std::list<const IOperand*>::iterator it;
	for (it = _stack.begin(); it != _stack.end(); ++it)
		std::cout << (*it)->toString() << std::endl;
}

void Parser::assert(std::list<Lex>::iterator& i)
{
	if (_stack.size() == 0)
		throw ParserException("Parser: Assert instruction on empty stack!");
	std::list<Lex>::iterator next = ++i;
	const IOperand* op = *(_stack.begin());
	if (op->toString() != next->val)
		throw ParserException("Parser: Assert instruction has different value!");
	if (op->getType() != next->type - INT8)
		throw ParserException("Parser: Assert instruction has different type!");
}

void Parser::add(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() < 2)
		throw ParserException("Parser: Add on stack with less than two values!");
	const IOperand* op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* op2 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* r = *op2 + *op1;
	delete op1;
	delete op2;
	_stack.push_front(r);
}

void Parser::sub(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() < 2)
		throw ParserException("Parser: Sub on stack with less than two values!");
	const IOperand* op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* op2 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* r = *op2 - *op1;
	delete op1;
	delete op2;
	_stack.push_front(r);
}

void Parser::mul(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() < 2)
		throw ParserException("Parser: Mul on stack with less than two values!");
	const IOperand* op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* op2 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* r = *op2 * *op1;
	delete op1;
	delete op2;
	_stack.push_front(r);
}

void Parser::div(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() < 2)
		throw ParserException("Parser: Div on stack with less than two values!");
	const IOperand* op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* op2 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* r = *op2 / *op1;
	delete op1;
	delete op2;
	_stack.push_front(r);
}

void Parser::mod(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() < 2)
		throw ParserException("Parser: Mod on stack with less than two values!");
	const IOperand* op1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* op2 = *(_stack.begin());
	_stack.pop_front();
	const IOperand* r = *op2 % *op1;
	delete op1;
	delete op2;
	_stack.push_front(r);
}

void Parser::print(std::list<Lex>::iterator& i)
{
	(void)i;
	if (_stack.size() == 0)
		throw ParserException("Parser: Print instruction on empty stack!");
	const IOperand* op = *(_stack.begin());
	if (op->getType() != Int8)
		throw ParserException("Parser: Print instruction on non 8-bit integer!");
	std::cout << static_cast<char>(std::stoi(op->toString())) << std::endl;
}

void Parser::exit(std::list<Lex>::iterator& i)
{
	(void)i;
	std::exit(0);
}

Parser::~Parser() {}
