// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "timer.h"
using namespace std;

/* This function takes in a number n and calculates the sum
 * of all proper divisors of n, excluding itself.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function is provided a number n and returns a boolean
 * (true/false) value representing whether or not the number is
 * perfect. A perfect number is a non-zero positive number whose
 * sum of its proper divisors is equal to itself.
 */
bool isPerfect (long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function performs an exhaustive search for perfect numbers.
 * It takes as input a number called `stop` and searches for perfect
 * numbers between 1 and `stop`. Any perfect numbers that are found will
 * be printed out to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush;
    }
    cout << "Done searching up to " << stop << endl;
}

/* This function takes in a number n and calculates the sum
 * of all proper divisors of n, excluding itself.
 */
long smarterSum(long n){
    if (n == 1) {
        return 0;
    }
    long m = sqrt(n);
    long total = 1;
    for (long i = 2; i <= m; i++) {
        if (n % i == 0) {
            long j = n / i;
            if (j == i) {
                total += i;
            } else {
                total += (i + j);
            }
        }
    }
    return total;
}


/* This function is provided a number n and returns a boolean
 * (true/false) value representing whether or not the number is
 * perfect. A perfect number is a non-zero positive number whose
 * sum of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n){
    return (n != 0) && (n == smarterSum(n));
}


/* This function performs an exhaustive search for perfect numbers.
 * It takes as input a number called `stop` and searches for perfect
 * numbers between 1 and `stop`. Any perfect numbers that are found will
 * be printed out to the console.
 */
void findPerfectsSmarter(long stop){
    for (long i = 1; i <= stop; i++) {
        if(isPerfectSmarter(i)) {
            cout << "Found perfect number " << i << endl;
        }
        if (i % 10000 == 0) {
            cout << "." << flush;
        }
    }
    cout << "Done searching up to " << stop << endl;
}

/* This function checks whether a number is
 * prime or not
 */
bool isPrime(long n) {
    if (n < 2) {
        return false;
    }
    for (long i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/* This function returns the nth perfect number using
 * Euclid-Euler theorem
 */
long findNthPerfectEuclid(long n){
    long k = 1;
    long m = pow(2, k) - 1;
    long i = 0;
    long l;
    while (i < n) {
        if (isPrime(m)) {
            l = (pow(2, k - 1) * (pow(2, k) - 1));
            i++;
        }
        k++;
        m = pow(2, k) - 1;
    }
    return l;
}




/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Time multiple trials of findPerfects function on doubling input sizes."){
    cout << endl;
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
    TIME_OPERATION(80000, findPerfects(80000));
//    TIME_OPERATION(160000, findPerfects(160000));
//    TIME_OPERATION(320000, findPerfects(320000));
//    TIME_OPERATION(640000, findPerfects(640000));
}

PROVIDED_TEST("Check divisor sums of small numbers") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Check 6 and 28, should be perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Imperfect numbers") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Oddballs, zero, one, negative") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
    EXPECT(!isPerfect(-6));
}

PROVIDED_TEST("33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

STUDENT_TEST("Check smarter sum of 10") {
    EXPECT_EQUAL(smarterSum(10), 8);
}

STUDENT_TEST("Check smarter sum of 25") {
    EXPECT_EQUAL(smarterSum(25), 6);
}

STUDENT_TEST("Check smarter sum of 1") {
    EXPECT_EQUAL(smarterSum(1), 0);
}

STUDENT_TEST("Check isPerfectSmarter") {
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
    EXPECT(!isPerfectSmarter(10));
}

STUDENT_TEST("Time multiple trials of findPerfectsSmarter function on doubling input sizes."){
    cout << endl;
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
    TIME_OPERATION(80000, findPerfectsSmarter(80000));
//    TIME_OPERATION(160000, findPerfectsSmarter(160000));
//    TIME_OPERATION(320000, findPerfectsSmarter(320000));
//    TIME_OPERATION(640000, findPerfectsSmarter(640000));
}

STUDENT_TEST("Check findNthPerfectEuclid") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(7), 137438691328);

}
