#include "functions.h"
// Test for Questions 1 to 8
int main()
{
	std::cout << "Leapyear" << std::endl;

	if (!isLeapYear(1700)) {
		std::cout << "not a leap year" << std::endl;
	}
	else {
		std::cout << " is a leap year" << std::endl;
	}

	if (isLeapYear(1600)) {
		std::cout << "is a leap year" << std::endl;
	}
	else {
		std::cout << "not a leap year" << std::endl;
	}

	if (isLeapYear(2016)) {
		std::cout << " a leap year" << std::endl;
	}
	else {
		std::cout << "not a leap year" << std::endl;
	}

	std::cout << "Palindrome" << std::endl;

	if (isAPalindrome(1))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isAPalindrome(121))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isAPalindrome(1213))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	std::cout << "Prime Number" << std::endl;

	if (isAPrimeNumber(3))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isAPrimeNumber(2147483647))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (!isAPrimeNumber(4))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	std::cout << "Binary to Decimal" << std::endl;

	if (convertBinarytoDecimal(110) == 6)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (convertBinarytoDecimal(111) == 7)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	std::cout << "5 chars to int" << std::endl;
	int convertedInt = input5CharsConvertToInt();
	std::cout << convertedInt << std::endl;

	std::cout << "Triangles" << std::endl;
	drawRightAngledTriangle();
	drawIsocelesTriangle();

}