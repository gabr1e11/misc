/**
 * Program to transform a given number into words according to UK spelling rules
 * Some information obtained from http://en.wikipedia.org/wiki/English_numerals
 *
 * @author Roberto Sosa Cano
 * @date   6-May-2014
 *
 * @details The first version of this program was a manual approximation of the
 * spell out that only accepted numbers up to 99999. The calculations of the
 * first hundred numbers was inlined and the dictionary used diretly to generate
 * the hundreds and the thousands.
 *
 * It immediately become apparent the generic use of the function to generate
 * the numbers form 1 to 99, and it was refactored into the method _towords.
 *
 * Succesive refactors followed by including the label to be printed out as
 * a parameter of the method _towords and then the generalization of the method
 * toString to be able to easily add bigger numbers.
 *
 * TOTAL WORKING TIME: 3 hours
 */
#include <map>
#include <string>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

/**
 * @class Number
 * @brief Class that accepts a number in the constructor and allows to transform
 *        the number into its spelled out words
 */
class Number
{
public:

	/**
	 * Constructor
	 *
	 * Initializes the dictionary map with the names and prefixes
	 * to be used for the first 99 numbers
	 *
	 * @param	number	The param to be spelled out
	 */
	Number(uint32_t number) : _number(number)
	{
		_dictionary[0] = "";
		_dictionary[1] = "one";
		_dictionary[2] = "two";
		_dictionary[3] = "three";
		_dictionary[4] = "four";
		_dictionary[5] = "five";
		_dictionary[6] = "six";
		_dictionary[7] = "seven";
		_dictionary[8] = "eight";
		_dictionary[9] = "nine";
		_dictionary[10] = "ten";
		_dictionary[11] = "eleven";
		_dictionary[12] = "twelve";
		_dictionary[13] = "thirteen";
		_dictionary[14] = "fourteen";
		_dictionary[15] = "fifteen";
		_dictionary[16] = "sixteen";
		_dictionary[17] = "seventeen";
		_dictionary[18] = "eighteen";
		_dictionary[19] = "nineteen";
		_dictionary[20] = "twenty";
		_dictionary[30] = "thirty";
		_dictionary[40] = "fourty";
		_dictionary[50] = "fifty";
		_dictionary[60] = "sixty";
		_dictionary[70] = "seventy";
		_dictionary[80] = "eighty";
		_dictionary[90] = "ninety";
	}

	/**
	 * Returns the spell out in words of the number represented by this object
	 *
	 * Please note the string could have a trailing space depending on the given
	 * number.
	 *
	 * @return A reference to a string containig the spell out in words. Please
	 *         note the returned string is a reference so subsequent calls of this
	 *         method will destroy the previous returned value
	 */
	string &toString() throw(string &)
	{
		if (_number > 999999999) {
			throw string("Number too big");
		}
		if (_number == 0) {
			_words = "zero";
			return _words;
		}

		bool force = false;
		_words = "";

		/* The below lines can also be optimized to not to call the method if the number
		 * is already zero, but it is more readable like this.
		 *
		 * The return value of the function is used to determine in some cases wether
		 * the label must be printed out any way. This is for cases like "hundred thousand"
		 * or "hundred million"
		 *
		 * As it can be seen this code is easily upgradable to include bigger numbers,
		 * so...give it a try!
		 */
		force = _towords(_number/100000000 % 10,  "hundred",  false);
		        _towords(_number/1000000   % 100, "million",  force);
		force = _towords(_number/100000    % 10,  "hundred",  false);
		        _towords(_number/1000      % 100, "thousand", force);
		        _towords(_number/100       % 10,  "hundred",  false);

		if (_number>100 && _number%100!=0) {
			_words += "and ";
		}

		_towords(_number%100, "", false);
		return _words;
	}

private:
	/**
	 * Appends the words for the given number
	 *
	 * This method accepts numbers from 0 to 99 and spells out its name,
	 * appending the words into the class attribute _words. Then, if the
	 * value was not zero, appends as well the given label that indicates
	 * the units. If zero is passed no word is appended
	 *
	 * Please be aware that no error checking is performed in this function
	 * to check the valid range of the param number as this is used as an
	 * internal method
	 *
	 * @param	number	The number to be spelled out from 0 to 99
	 * @param   label	The label to be appended after the number
	 * @param   force   Forces the printout of the label
	 *
	 * @return Wether the function appended something new to the string or not
	 */
	bool _towords(uint32_t number, string label, bool force)
	{
		if (number<20 || number%10==0) {
			_words += _dictionary[number];
		} else {
			_words += _dictionary[number/10*10];
			_words += "-";
			_words += _dictionary[number%10];
		}
		if (number!=0) {
			_words += " ";
			_words += label;
			_words += " ";
		} else if (force) {
			_words += label;
			_words += " ";
		}
		return number!=0;
	}

	uint32_t _number;				/**< Number to be converted */
	map<int, string> _dictionary;	/**< Dictionary with the words and prefixes for the range 1-99 */
	string _words;					/**< Actual string containing the spell out */
};

/**
 * Operator to use the cout facilities with Number
 */
ostream &operator<<(ostream &os, Number &number)
{
	os << number.toString();
	return os;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage:\n\t%s <number>\n\n", argv[0]);
		exit(-1);
	}

	/* Some exception handling just for fun */
	try {
		Number number(strtol(argv[1], NULL, 10));
		cout << number << endl;
	} catch (string &e) {
		cout << "ERROR calling Number.toString(): " << e << endl;
		exit(1);
	}

	exit(0);
}
