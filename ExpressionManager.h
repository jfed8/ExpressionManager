/*
 * ExpressionManager.h
 *
 *  Created on: Feb 9, 2016
 *      Author: jjfeddock
 */

#ifndef EXPRESSIONMANAGER_H_
#define EXPRESSIONMANAGER_H_

#include "ExpressionManagerInterface.h"
#include <stack>

using namespace std;

class ExpressionManager : public ExpressionManagerInterface

{
public:
	ExpressionManager() {}
	~ExpressionManager() {}

	bool isBalanced(string expression);
	string postfixToInfix(string postfixExpression);
	string infixToPostfix(string infixExpression);
	string postfixEvaluate(string postfixExpression);




};



#endif /* EXPRESSIONMANAGER_H_ */
