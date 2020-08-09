/* 
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/* Returns a string consists only of the bracketing charaters */
string operatorsOnly(string s) {
    if (s.length() == 0) {
        return s;
    } else {
        if (s[0] == '(' || s[0] == ')' || s[0] == '{' || s[0] == '}' || s[0] == '[' || s[0] == ']') {
            return s[0] + operatorsOnly(s.substr(1));
        } else {
            return operatorsOnly(s.substr(1));
        }
    }

}

/* Recursively checks to see if the brackets in the string are balance */
bool checkOperators(string s) {
    if (s.length() == 0) {
        return true;
    } else {
        if (s.find("()") != string::npos) {
            int pos = s.find("()");
            s = s.substr(0, pos) + s.substr(pos+2);
            return checkOperators(s);
        } else if (s.find("[]") != string::npos) {
            int pos = s.find("[]");
            s = s.substr(0, pos) + s.substr(pos+2);
            return checkOperators(s);
        } else if (s.find("{}") != string::npos) {
            int pos = s.find("{}");
            s = s.substr(0, pos) + s.substr(pos+2);
            return checkOperators(s);
        } else {
            return false;
        }
    }
}

/* 
 * This function assumes correct implementation of the previous 
 * two functions. It uses the operatorsOnly function to strip out
 * all characters from the provided string and then checks to see
 * whether the remaining operators are balanced by using the 
 * checkOperators function. All in all, this function is able to 
 * correctly determine whether a snippet of code has correctly
 * balanced bracketing operators. You should not need to modify this
 * function if the previous two functions have been implemented
 * correctly. 
 */
bool isBalanced(string str) {
    string ops = operatorsOnly(str);
    return checkOperators(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsOnly on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    string only = "(){([])(())}";
    EXPECT_EQUAL(operatorsOnly(example), only);
}

STUDENT_TEST("Additional tests to validate operatorsOnly") {
    string example = "A fjas - , fasjf 0 Hfjsf { fha> aj] fds(";
    string only = "{](";
    EXPECT_EQUAL(operatorsOnly(example), only);

    string example1 = "{}[]()[)(]{}[]";
    string only1 ="{}[]()[)(]{}[]";
    EXPECT_EQUAL(operatorsOnly(example1), only1);

    string example2 = "";
    string only2 = "";
    EXPECT_EQUAL(operatorsOnly(example2), only2);

}
PROVIDED_TEST("checkOperators on example from writeup") {
    string only = "(){([])(())}";
    EXPECT(checkOperators(only));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on illegal examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("Additional tests to validate chechOperators") {
    string example = "{](";
    EXPECT(!isBalanced(example));
    string example2 = "[({}{[]})]";
    EXPECT(isBalanced(example2));
    string example3 = "[({}}{[]})]";
    EXPECT(!isBalanced(example3));
    string example4 = "[]{}()[({})]{}";
    EXPECT(isBalanced(example4));

}
