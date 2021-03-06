/* 
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "error.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This 
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
void drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order < 0) {
        error("Order should not be less than 0");
    }
    if (order == 0) {
        return fillBlackTriangle(window, one, two, three);
    } else {
        drawSierpinskiTriangle(window, one, {((one.getX() + two.getX()) / 2), (one.getY() + two.getY()) / 2}, {((one.getX() + three.getX()) / 2), ((one.getY() + three.getY()) / 2)}, order - 1);
        drawSierpinskiTriangle(window, {((one.getX() + two.getX()) / 2), ((one.getY() + two.getY()) / 2)}, two, {((three.getX() + two.getX()) / 2), ((three.getY() + two.getY()) / 2)}, order - 1);
        drawSierpinskiTriangle(window,{((one.getX() + three.getX()) / 2), ((one.getY() + three.getY()) / 2)}, {((three.getX() + two.getX()) / 2), ((three.getY() + two.getY()) / 2)}, three, order - 1);
    }
}

/* * * * * * Test Cases * * * * * */

/* 
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo. 
 */

void runDemos();

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runDemos();
}

