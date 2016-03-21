/*
 * Factory.h
 *
 *  Created on: Feb 9, 2016
 *      Author: jjfeddock
 */

#pragma once
#include "ExpressionManagerInterface.h"
#include <stack>

using namespace std;


/*
	createExpressionManager()
*/
class Factory
{
	public:
		static ExpressionManagerInterface * createManager();
};
//=======================================================================================
