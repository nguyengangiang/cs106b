/* 
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Iterative merge */
Queue<int> merge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    while (!a.isEmpty() || !b.isEmpty()) {
        if (b.isEmpty() || (!a.isEmpty() &&a.peek() < b.peek())) {
            int cur = a.dequeue();
            if (!result.isEmpty() && !a.isEmpty() && a.peek() < cur) {
                error("Queue is not in sorted order");
            }
            result.add(cur);
        } else {
            int cur = b.dequeue();
            if (!result.isEmpty() && !b.isEmpty() && b.peek() < cur) {
                error("Queue is not in sorted order");
            }
            result.add(cur);
        }
    }
    return result;
}

/* 
 * This function assumes correct functionality of the previously
 * defined merge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented – 
 * it does not need to modified at all.
 */
Queue<int> multiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    for (Queue<int>& q : all) {
        result = merge(q, result);
    }
    return result;
}

/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result = Queue<int>();
    int length = all.size() / 2;
    if (length > 0) {
        Vector<Queue<int>> lo = all.subList(0, length);
        Vector<Queue<int>> hi = all.subList(length, all.size() - length);
        Queue<int> low = recMultiMerge(lo);
        Queue<int>high = recMultiMerge(hi);
        return result = merge(high, low);
    } else {
        return all[0];
    }
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

STUDENT_TEST("Test recursive mulri merge") {
    Vector<Queue<int>> all = {{2},
                             {1, 3},
                            };
    Queue<int> expected = {1, 2, 3};
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

PROVIDED_TEST("Test binary merge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(merge(a, b), expected);
    EXPECT_EQUAL(merge(b, a), expected);
}

PROVIDED_TEST("Test multiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(multiMerge(all), expected);
}

PROVIDED_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

PROVIDED_TEST("Time binary merge operation") {
    int n = 1500000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size(), merge(a, b));
}

PROVIDED_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].add(input.dequeue());
    }
}

STUDENT_TEST("Test binary merge with error") {
    Queue <int> a = {2, 4, 3};
    Queue <int> b = {3, 4, 5};
    EXPECT_ERROR(merge(a, b));

    Queue <int> c = {5, 4, 3, 2, 1};
    Queue <int> d = {0};
    EXPECT_ERROR(merge(c, d));
}

STUDENT_TEST("Test binary merge") {
    Queue<int> a = {14, 155, 233};
    Queue<int> b = {14, 155, 233};
    Queue<int> expect = {14, 14, 155, 155, 233, 233};
    EXPECT_EQUAL(merge(a, b), expect);
    EXPECT_EQUAL(merge(b, a), expect);


    Queue<int> c = {1, 3, 5, 7, 9};
    Queue<int> d = {2, 4, 8};
    Queue<int> expect1 = {1, 2, 3, 4, 5, 7, 8, 9};
    EXPECT_EQUAL(merge(c, d), expect1);

    Queue<int> e = {};
    Queue<int> f = {};
    Queue<int> expect2 = {};
    EXPECT_EQUAL(merge(f, e), expect2);

    Queue<int> g = {};
    Queue<int> h = {-1, 2, 3, 4, 5, 6, 7, 8, 9};
    Queue<int> expect3 = {-1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQUAL(merge(h, g), expect3);
}

STUDENT_TEST("Time binary merge operation") {
    Queue<int> a = createSequence(1022);
    Queue<int> b = createSequence(1026);
    TIME_OPERATION(a.size() + b.size(), merge(a, b));

    Queue<int> c = createSequence(5822);
    Queue<int> d = createSequence(5426);
    TIME_OPERATION(c.size() + d.size(), merge(c, d));

    Queue<int> e = createSequence(58228);
    Queue<int> f = createSequence(54260);
    TIME_OPERATION(e.size() + f.size(), merge(e, f));

    Queue<int> g = createSequence(1582284);
    Queue<int> h = createSequence(1542609);
    TIME_OPERATION(g.size() + h.size(), merge(g, h));
}

STUDENT_TEST("Compare time muliti merge and recursive operation with the same n") {
    int a = 2000;

    int b = a/5;
    Queue<int> input = createSequence(a);
    Vector<Queue<int>> all(b);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
    TIME_OPERATION(input.size(), recMultiMerge(all));
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));

    int c = a/10;
    Vector<Queue<int>> all0(c);
    distribute(input, all0);
    TIME_OPERATION(input.size(), multiMerge(all0));
    TIME_OPERATION(input.size(), recMultiMerge(all0));
    EXPECT_EQUAL(multiMerge(all0), recMultiMerge(all0));

    int d = a/20;
    Vector<Queue<int>> all1(d);
    distribute(input, all1);
    TIME_OPERATION(input.size(), multiMerge(all1));
    TIME_OPERATION(input.size(), recMultiMerge(all1));
    EXPECT_EQUAL(multiMerge(all1), recMultiMerge(all1));

    int e = a/50;
    Vector<Queue<int>> all2(e);
    distribute(input, all2);
    TIME_OPERATION(input.size(), multiMerge(all2));
    TIME_OPERATION(input.size(), recMultiMerge(all2));
    EXPECT_EQUAL(multiMerge(all2), recMultiMerge(all2));


    int f = a/200;
    Vector<Queue<int>> all3(f);
    distribute(input, all3);
    TIME_OPERATION(input.size(), multiMerge(all3));
    TIME_OPERATION(input.size(), recMultiMerge(all3));
    EXPECT_EQUAL(multiMerge(all3), recMultiMerge(all3));


    int g = a/2000;
    Vector<Queue<int>> all4(g);
    distribute(input, all4);
    TIME_OPERATION(input.size(), multiMerge(all4));
    TIME_OPERATION(input.size(), recMultiMerge(all4));
    EXPECT_EQUAL(multiMerge(all4), recMultiMerge(all4));

}

STUDENT_TEST("Time muliti merge operation with the same k") {
    int b = 200;
    int a = b/200;
    Queue<int> input = createSequence(b);
    Vector<Queue<int>> all(a);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
    TIME_OPERATION(input.size(), recMultiMerge(all));
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));

    int c = 1000;
    a = c/200;
    Vector<Queue<int>> all1(a);
    Queue<int> input1 = createSequence(c);
    distribute(input1, all1);
    TIME_OPERATION(input1.size(), multiMerge(all1));
    TIME_OPERATION(input1.size(), recMultiMerge(all1));
    EXPECT_EQUAL(multiMerge(all1), recMultiMerge(all1));

    int d = 5000;
    a = d/200;
    Vector<Queue<int>> all2(a);
    Queue<int> input2 = createSequence(d);
    distribute(input2, all2);
    TIME_OPERATION(input2.size(), multiMerge(all2));
    TIME_OPERATION(input2.size(), recMultiMerge(all2));
    EXPECT_EQUAL(multiMerge(all2), recMultiMerge(all2));

    int f = 10000;
    a = f/200;
    Vector<Queue<int>> all3(a);
    Queue<int> input3 = createSequence(f);
    distribute(input3, all3);
    TIME_OPERATION(input3.size(), multiMerge(all3));
    TIME_OPERATION(input3.size(), recMultiMerge(all3));
    EXPECT_EQUAL(multiMerge(all3), recMultiMerge(all3));


    int g = 50000;
    a = g/200;
    Vector<Queue<int>> all4(a);
    Queue<int> input4 = createSequence(g);
    distribute(input4, all4);
    TIME_OPERATION(input4.size(), multiMerge(all4));
    TIME_OPERATION(input4.size(), recMultiMerge(all4));
    EXPECT_EQUAL(multiMerge(all4), recMultiMerge(all4));

}
