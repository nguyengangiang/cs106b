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

/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
string operatorsOnly(string s) {
    /* TODO: Fill in the remainder of this function. */
    return s;
}

/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool checkOperators(string s) {
    /* TODO: Fill in the remainder of this function. */
    return false;
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
