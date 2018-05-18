/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:46:06 by sjones            #+#    #+#             */
/*   Updated: 2018/02/16 19:41:01 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Exception.hpp"
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int ac, char **av)
{
	try
	{
		Lexer lexer(ac, av);
		Parser parser(lexer.lex());
	}
	catch (Exception& e) { std::cout << e.what() << std::endl; }
}
