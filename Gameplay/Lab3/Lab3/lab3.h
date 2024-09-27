#pragma once
#include <iostream>
// josh C00285802
void FindAllVariables(char variables[1000], char code[1000])
{
	for (int i = 0; i < 1000; i++)
	{
		if (code[i] == ' ' && code[i-1] == 't' && code[i-2] == 'n' && code[i-3] == 'i')
		{
			for (int currentchar = i; currentchar < 1000; currentchar++)
			{
				variables[currentchar - 1] = code[currentchar];

				if (code[currentchar] == '=')
				{
					variables[currentchar -1 ] = ',';
					break;
				}
			}
				
		}
	
	}
	for (int i = 0; i < 1000; i++)
	{
		std::cout << variables[i];
	}
}
void FindAllVariablesInScope(char variables[1000], char code[1000], int lineNumber)
{

}
//variables[i] = code[i];
//code[i]++;