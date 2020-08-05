/**
 * File: warmup.cpp
 * ----------------
 * @author Julie Zelenski, Spring 2020
 * This code is provided as part of an exercise to practice using a
 * debugger. This program has buggy use of recursion.
 */

#include <iostream>    // for cout, endl
#include "error.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;


/* This is a recursive implementation of a function to calculate
 * factorials. This function works correctly for positive values
 * of n whose computed factorial value does not overflow the int
 * data type (n <= 12).
 *
 * As currently written, this function does not correctly handle
 * negative inputs.
 */
int factorial(int n) {
    if (n < 0) {
        error("Input cannot be less than 0");
    }
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}


/* This is an iterative implementation of a function that calculates
 * the exponentiation operation to raise a base to an exponent.
 *
 * This function works correctly for both positive and negative
 * exponents. This function has return type double to correctly return
 * floating point values instead of integer values for better precision.
 */
double iterativePower(int base, int exp) {
    double result = 1;

    if (base == 0) {
      return 0;
    }
    for (int i = 0; i < abs(exp); i++) {
        result *= base;
    }
    if (exp < 0) {
        result = 1/result; // calculate the reciprocal for negative exponent
    }
    return result;
}

/* This is an iterative implementation of a function that calculates
 * the exponentiation operation to raise a base to an exponent.
 *
 * Warning: This is a buggy implementation! It works mostly correctly
 * but it has some bugs that you should find and fix. Refer to the
 * writeup for further instructions on how to do so.
 */
double power(int base, int exp) {
    if (base == 0 && exp == 0) {
        error("Both exponent and base cannot be 0");
    }
    if (base == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
//    } else if (exp == 1) {
//        return base;
//    } else if (exp == -1) {
//        return 1/base;
    } else if (exp < 0) {
        return 1/power(base, -exp);
    } else {
        return base*power(base, exp-1);
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test factorial function on simple input") {
    EXPECT_EQUAL(factorial(7), 7*6*5*4*3*2);
}

PROVIDED_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(1, 20);
        int exp = randomInteger(0, 10);
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test factorial function on negative case") {
    EXPECT_ERROR(factorial(-7));
}

STUDENT_TEST("Test recursive power against iterative, random negative input for base") {
    for (int i = 0; i < 20; i++) {
        int base = randomInteger(-20, -1);
        int exp = randomInteger(1, 20);
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test recursive power against iterative, random negative input for exponent") {
    for (int i = 0; i < 20; i++) {
        int base = randomInteger(1, 20);
        int exp = randomInteger(-20, -1);
        cout << "Base: " << base << " exp: " << exp << endl;
        cout << "Recursive result: " << power(base, exp) << endl;
        cout << "Iterative result: " << iterativePower(base, exp) << endl;
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test that will reproduce the failure of power function") {
    int base = randomInteger(-20, 20);
    int exp = -1;
    EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
}

STUDENT_TEST("Test power function: zero raise to any number would be zero") {
    for (int i = 0; i < 20; i++) {
        int exp = randomInteger(1, 20);
        EXPECT_EQUAL(power(0, exp), 0);
    }
}

STUDENT_TEST("Test case for power function when both exponent and base are 0") {
    EXPECT_ERROR(power(0, 0));
}
