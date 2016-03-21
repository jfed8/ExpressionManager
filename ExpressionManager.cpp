/*
 * ExpressionManager.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: jjfeddock
 */


#include "ExpressionManager.h"
#include <string>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;

const string OPEN = "([{"; // Opening parenthesis
const string CLOSE = ")]}"; // Closing parenthesis
const string NUMBER = "0123456789"; // All numbers
const string OPERATOR = "+-*/%"; // All valid operators
const string POINT = ".";


bool isLeftParen(string t)
{
	return OPEN.find(t) != string::npos;
}

bool isRightParen(string t)
{
	return CLOSE.find(t) != string::npos;
}

bool isPair(string left, string right)
{
	return true;
}

bool isOperator(string t)
{
	return OPERATOR.find(t) != string::npos;
}

bool isNumber(string s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

int precedence(string oper)
{
	if (oper == ")" || oper == "]" || oper == "}")
		return 3;

	else if (oper == "*" || oper == "/" || oper == "%")
		return 2;

	else if (oper == "+" || oper == "-")
		return 1;

	else
		return 0;
}

string solver(string first, string second, string oper)
{
	if (oper == "+")
	{
		int one;
		int two;
		one = stoi(first);
		two = stoi(second);
		return to_string(one + two);
	}
	else if (oper == "-")
	{
		int one;
		int two;
		one = stoi(first);
		two = stoi(second);
		return to_string(one - two);
	}
	else if (oper == "*")
	{
		int one;
		int two;
		one = stoi(first);
		two = stoi(second);
		return to_string(one * two);
	}
	else if (oper == "/")
	{
		int one;
		int two;
		one = stoi(first);
		two = stoi(second);

		if (two == 0)
			return "invalid";

		return to_string(one / two);
	}
	else if (oper == "%")
	{
		int one;
		int two;
		one = stoi(first);
		two = stoi(second);
		return to_string(one % two);
	}
	else
		return "invalid";
}

bool ExpressionManager::isBalanced(string expression)
{
	stack<char> s;
	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end()))
	{
		char next_ch = *iter;
		if (isLeftParen(string(1,next_ch)))
		{
			s.push(next_ch);
		}
		else if (isRightParen(string(1,next_ch)))
		{
			if (s.empty())
			{
				balanced = false;
			}
			else
			{
				char top_ch = s.top();
				s.pop();
				balanced = (OPEN.find(top_ch) == CLOSE.find(next_ch));
			}
		}
		iter++;
	}
	return balanced && s.empty();
}

string ExpressionManager::postfixToInfix(string postfixExpression)
{
	stack<string> s;
	stringstream stream;
	string answer = "";

	stream << postfixExpression;
	string current;
	string old = "";


    if (!isBalanced(postfixExpression))
        return "invalid";


	while (stream >> current)
	{
		if (!isLeftParen(current) && !isRightParen(current) && !isNumber(current) && !isOperator(current))
			return "invalid";


		if (isNumber(current))
		{
			s.push(current);
		}
		else if (isOperator(current))
		{
			string first;
			string second;

			if (s.empty())
				return "invalid";
			second = s.top();
			s.pop();
			if (s.empty())
				return "invalid";
			first = s.top();
			s.pop();

			string solution;
			solution = "( " + first + " " + current + " " + second + " )";

			if (solution == "invalid")
				return "invalid";

			s.push(solution);
		}
		else if (isRightParen(current))
			return "invalid";
		else if (isLeftParen(current))
			return "invalid";
		old = current;
	}
	answer = s.top();
	s.pop();
	if (!s.empty())
		return "invalid";

	return answer;
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
	stack<string> s;
	stringstream stream;
	string answer = "";

	stream << infixExpression;
	string current;
	string old = "";

    if (!isBalanced(infixExpression))
        return "invalid";

	while (stream >> current)
	{
		if (!isLeftParen(current) && !isRightParen(current) && !isNumber(current) && !isOperator(current))
			return "invalid";

		if (isLeftParen(current))
			{
				s.push(current);
			}
		else if (isRightParen(current))
		{
			if (isOperator(old))
				return "invalid";

			while (!isLeftParen(s.top()))
			{
				answer = answer + s.top() + " ";
				s.pop();
			}
			s.pop();
		}
		else if (isNumber(current))
		{
			answer = answer + current + " ";
		}
		else if (isOperator(current))
		{
			if (isOperator(old))
				return "invalid";

			if (s.empty())
				s.push(current);
			else if (precedence(current) > precedence(s.top()))
			{
				s.push(current);
			}
			else
			{
				while (precedence(current) <= precedence(s.top()))
				{
					answer = answer + s.top() + " ";
					s.pop();
					if (s.empty())
						break;
				}
				s.push(current);
			}
		}
		old = current;
	}
	while (!s.empty())
		{
			answer = answer + s.top() + " ";
			s.pop();
		}
	answer = answer.substr(0, answer.length()-1);


	return answer;
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
	stack<string> s;
	stringstream stream;
	string answer = "";

	stream << postfixExpression;
	string current;
	string old = "";


	while (stream >> current)
	{
		if (!isLeftParen(current) && !isRightParen(current) && !isNumber(current) && !isOperator(current))
			return "invalid";


		if (isNumber(current))
		{
			s.push(current);
		}
		else if (isOperator(current))
		{
			string first;
			string second;

			if (s.empty())
				return "invalid";
			second = s.top();
			s.pop();
			if (s.empty())
				return "invalid";
			first = s.top();
			s.pop();

			string solution;
			solution = solver(first, second, current);

			if (solution == "invalid")
				return "invalid";

			s.push(solution);
		}
		else if (isRightParen(current))
			return "invalid";
		else if (isLeftParen(current))
			return "invalid";
		old = current;
	}
	answer = s.top();
	s.pop();

	return answer;
}


