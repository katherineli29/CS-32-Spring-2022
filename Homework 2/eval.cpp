#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

//edit

int evaluate(string infix, string& postfix, bool& result) {
	// Evaluates a boolean expression
	//   If infix is a syntactically valid infix boolean expression,
	//   then set postfix to the postfix form of that expression, set
	//   result to the value of the expression, and return zero.  If
	//   infix is not a syntactically valid expression, return 1; in
	//   that case, postfix may or may not be changed, but result must
	//   be unchanged.

	postfix = "";
	stack<char> s;

	//create pf
	for (size_t i = 0; i < infix.size(); i++) {
		char check = infix.at(i);
		char temp; //top of stack
		if(!s.empty())
			temp = s.top();

		switch (check) {
		case 'T':
		case 'F':
			if (i != 0 && (infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F')) {
			return 1;
		}
			postfix += check;
			break;
		case '(':
			s.push(check);
			break;
		case ')':
			if (i == 0 || i != 0 && !(infix.at(i - 1) == 'T' || infix.at(i-1) == 'F' || infix.at(i-1) == ' ' || infix.at(i-1) == ')')) {
				return 1;
			}

			if (s.empty()) {
				return 1;
			}

			while (temp != '(' && !s.empty()) {
				postfix += temp;
				s.pop();

				if (s.empty()) {
					return 1;
				}
				else {
					temp = s.top();
				}
			}

			s.pop();
			break;
		case '|':
			if (i == 0 || i != 0 && !(infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F' || infix.at(i - 1) == ' ' || infix.at(i - 1) == ')')) {
				return 1;
			}

			while (!s.empty() && temp != '(') {
				postfix += temp;
				s.pop();

				if (s.empty()) {
					break;
				}
				else {
					temp = s.top();
				}
			}
			s.push(check);
			break;
		case '&':
			if (i == 0 || i != 0 && !(infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F' || 
				infix.at(i - 1) == ' ' || infix.at(i - 1) == ')')) {
				return 1;
			}

			while (!s.empty() && temp != '(' && (temp == '!' || temp == '&')) {
				postfix += temp;
				s.pop();

				if (s.empty()) {
					break;
				}
				else {
					temp = s.top();
				}
			}
			s.push(check);
			break;
		case '!':
			if (i != 0 && (infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F')
				|| i == infix.size() - 1) {
				return 1;
			}

			while (!s.empty() && temp != '(' && temp == '!') {
				postfix += temp;
				s.pop();

				if (s.empty()) {
					break;
				}
				else {
					temp = s.top();
				}
			}
			s.push(check);
			break;
		case ' ':
			break;
		default:
			return 1;
		}
	}

	while (!s.empty()) {
		postfix += s.top();
		s.pop();
	}

	//eval postfix
	for (size_t i = 0; i < postfix.size(); i++) {
		char check = postfix.at(i);

		switch (check) {
		case 'T':
		case 'F':
				s.push(check);
				break;
		case '!':
			if (s.empty()) {
				return 1;
			}

			if (s.top() == 'T') {
				s.pop();
				s.push('F');
			}
			else {
				s.pop();
				s.push('T');
			}
			break;
		default:
			if (s.size() < 2) {
				return 1;
			}
			
			bool operand2;
			if (s.top() == 'T') {
				operand2 = true;
			}
			else {
				operand2 = false;
			}
			s.pop();

			bool operand1;
			if (s.top() == 'T') {
				operand1 = true;
			}
			else {
				operand1 = false;
			}
			s.pop();

			switch (check) {
			case '|':
				if (operand1 || operand2) {
					s.push('T');
				}
				else {
					s.push('F');
				}
				break;
			case '&':
				if (operand1 && operand2) {
					s.push('T');
				}
				else {
					s.push('F');
				}
				break;
			}
		}
	}
	
	if (s.size() == 1) {
		if (s.top() == 'T') {
			result = true;
		}
		else if (s.top() == 'F') {
			result = false;
		}
		else {
			return 1;
		}
		return 0;
	}

	return 1;

}

int main() {
	string pf;
	bool answer;

	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("T+F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("F&T|!(T|F)", pf, answer) == 0 && !answer);
	assert(evaluate("TT", pf, answer) == 1);
	assert(evaluate("T&!T!", pf, answer) == 1);

	assert(evaluate("T", pf, answer) == 0 && answer);
	assert(evaluate("(F)", pf, answer) == 0 && !answer);
	assert(evaluate("T & (F)", pf, answer) == 0 && !answer);
	assert(evaluate("T & !F", pf, answer) == 0 && pf == "TF!&" && answer);
	assert(evaluate("!(F | T)", pf, answer) == 0 && pf == "FT|!" && !answer);
	assert(evaluate("!F | T", pf, answer) == 0 && answer);
	assert(evaluate("T | F & F", pf, answer) == 0 && answer);
	assert(evaluate("T & !(F | T & T | F) | !!!(F & T & F)", pf, answer) == 0 && answer);

	string cases[57] = {
	   "", "()", "(())", ")(", "))((",
	   "(T", "T)", "((T|F)", "(T|F))",
	   ")T(", ")F(", "))T((", "))F((",
	   "TT", "TF", "FT", "FF", "TTT", "TTF", "TFT", "FTT", "TFF", "FFT", "FTF", "FFF",
	   "T&&T", "T&|F", "T|&F", "T!&F", "T!|F", "T!!F",
	   "&", "&T", "&F", "|", "|T", "|F", "T&", "F&", "T|", "F|",
	   "(&T&T)", "(|T&T)", "(T&T!)", "(T&T&)", "(T&T|)", "(T&T)!",
	   "(&T)", "(&F)", "(|T)", "(|F)",
	   "T!T", "T!F", "F!T", "F!F",
	   "T!", "F!"
	};
	string postfix = "";
	bool result = false;
	for (string c : cases)
	{
		cout << "Case: " << c << endl;
		assert(evaluate(c, postfix, result) == 1);
		assert(result == false);
	}
	cout << "Passed all tests" << endl;

	evaluate("T&!(F|T&T|F)|!!!(F&T&F)	", pf, answer);

	cout << pf << " -- should be -- TFTT&|F|!&FT&F&!!!|" << endl;
	cout << answer << endl;

	return 0;
}