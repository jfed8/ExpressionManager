/*
 * Factory.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: jjfeddock
 */

#include "Factory.h"
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"

#include <stack>

using namespace std;


/*
	createManager()


*/
ExpressionManagerInterface* Factory::createManager()
{
	return new ExpressionManager();//Modify this line
}
//=======================================================================================
