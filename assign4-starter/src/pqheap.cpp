#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
PQHeap::PQHeap() {
    numItems = 0;
    allocatedCapacity = INITIAL_CAPACITY;
    elements = new DataPoint[allocatedCapacity];
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
PQHeap::~PQHeap() {
    delete[] elements;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void PQHeap::enqueue(DataPoint elem) {
    if (numItems == allocatedCapacity) {
        expand();
    }
    elements[numItems] = elem;
    numItems++;
    bubbleUp(getParentIndex(numItems - 1), numItems - 1);
}

void PQHeap::bubbleUp(int parentIndex, int curIndex) {
    DataPoint temp = elements[parentIndex];
    if (elements[parentIndex].priority > elements[curIndex].priority) {
        elements[parentIndex] = elements[curIndex];
        elements[curIndex] = temp;
        curIndex = parentIndex;
        bubbleUp(getParentIndex(curIndex), curIndex);
    } else {
        return;
    }
}

void PQHeap::expand() {
    // 1. ask for new space for a new array
    DataPoint* newElements = new DataPoint[allocatedCapacity * 2];

    // 2. copy the values over
    for (int i = 0; i < numItems; i++) {
        newElements[i] = elements[i];
    }

    // 3. delete old array
    delete[] elements;

    // 4. point elements to new array
    elements = newElements;

    // 5. Update capacity
    allocatedCapacity *= 2;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
DataPoint PQHeap::peek() const {
    if (isEmpty()) {
        error("Cannot peek empty queue");
    }
    return elements[0];
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
DataPoint PQHeap::dequeue() {
    if (isEmpty()) {
        error("Cannot dequeue empty queue");
    }
    DataPoint root = elements[0];
    elements[0] = elements[numItems - 1];
    int curIndex = 0;
    bubbleDown(getLeftChildIndex(curIndex), getRightChildIndex(curIndex), curIndex);
    numItems--;
    return root;
}

void PQHeap::bubbleDown(int leftChildIndex, int rightChildIndex, int curIndex) {
    DataPoint temp;
    int newCurIndex;
    if (leftChildIndex != -1 && rightChildIndex != -1 && elements[leftChildIndex].priority <  elements[curIndex].priority && elements[rightChildIndex].priority <  elements[curIndex].priority) {
        newCurIndex = elements[leftChildIndex].priority < elements[rightChildIndex].priority ? leftChildIndex : rightChildIndex;
        temp = elements[newCurIndex];
    } else if (leftChildIndex != -1 && elements[leftChildIndex].priority <  elements[curIndex].priority) {
        temp = elements[leftChildIndex];
        newCurIndex = leftChildIndex;
    } else if (rightChildIndex != - 1 && elements[rightChildIndex].priority <  elements[curIndex].priority) {
        temp = elements[rightChildIndex];
        newCurIndex = rightChildIndex;
    } else {
        return;
    }
    elements[newCurIndex] = elements[curIndex];
    elements[curIndex] = temp;
    bubbleDown(getLeftChildIndex(newCurIndex), getRightChildIndex(newCurIndex), newCurIndex);

}
/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
bool PQHeap::isEmpty() const {
    return (numItems == 0);
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
int PQHeap::size() const {
    return numItems;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void PQHeap::clear() {
    numItems = 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void PQHeap::printDebugInfo() {
    for (int i = 0; i < size(); i++) {
        cout << "[" << i << "] = " << elements[i] << endl;
    }}

/*
 * We strongly recommend implementing this helper function, which
 * should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 */
void PQHeap::validateInternalState(){
    /* TODO: Fill in this function. */
}

/* 
 * We strongly recommend implementing this helper function, which 
 * should calculate the index of the parent of the element with the
 * provided index.
 */
int PQHeap::getParentIndex(int curIndex){
    int parentIndex = (curIndex - 1) / 2;
    if (parentIndex < 0) {
        return -1; // error token
    }
    return parentIndex;

}

/* 
 * We strongly recommend implementing this helper function, which 
 * should calculate the index of the left child of the element with the
 * provided index.
 */
int PQHeap::getLeftChildIndex(int curIndex){
    int leftChild =  2 * curIndex + 1;
    if (leftChild >= numItems) {
        return -1; // error token
    }
    return leftChild;
}

/* 
 * We strongly recommend implementing this helper function, which 
 * should calculate the index of the right child of the element with the
 * provided index.
 */
int PQHeap::getRightChildIndex(int curIndex){
    int rightChild =  2 * curIndex + 2;
    if (rightChild >= numItems) {
        return -1; // error token
    }
    return rightChild;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */
STUDENT_TEST("Test Enqueue function") {
    PQHeap pq;
    pq.enqueue({"a", 5});
    pq.enqueue({"b", 10});
    pq.enqueue({"c", 8});
    pq.enqueue({"d", 12});
    pq.enqueue({"3", 11});
    pq.enqueue({"g", 13});
    pq.enqueue({"f", 14});
    pq.enqueue({"h", 22});
    pq.enqueue({"i", 43});
    pq.enqueue({"j", 9});
    pq.printDebugInfo();
}



/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Newly-created heap is empty.") {
    PQHeap pq;

    EXPECT(pq.isEmpty());
    EXPECT(pq.size() == 0);
}

PROVIDED_TEST("Provided Test: Enqueue / dequeue single element (two cycles)") {
    PQHeap pq;
    DataPoint point = { "Programming Abstractions", 106 };
    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.peek(), point);
    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.peek(), point);
    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Test clear operation works with single element."){
    PQHeap pq;
    DataPoint point = { "Programming Abstractions", 106 };

    pq.enqueue(point);
    pq.clear();
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Dequeue / peek on empty priority queue throws error") {
    PQHeap pq;

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

PROVIDED_TEST("Provided Test: Dequeue / peek on recently-cleared priority queue throws error") {
    PQHeap pq;
    DataPoint point = { "Programming Abstractions", 106 };

    pq.enqueue(point);
    pq.clear();
    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

PROVIDED_TEST("Provided Test: Enqueue elements in sorted order.") {
    PQHeap pq;
    for (int i = 0; i < 25; i++) {
        pq.enqueue({ "elem" + integerToString(i), i });
    }

    EXPECT_EQUAL(pq.size(), 25);
    for (int i = 0; i < 25; i++) {
        DataPoint removed = pq.dequeue();
        DataPoint expected = {
            "elem" + integerToString(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Enqueue elements in reverse-sorted order.") {
    PQHeap pq;
    for (int i = 25; i >= 0; i--) {
        pq.enqueue({ "elem" + integerToString(i), i });
    }

    EXPECT_EQUAL(pq.size(), 26);
    for (int i = 0; i <= 25; i++) {
        DataPoint removed = pq.dequeue();
        DataPoint expected = {
            "elem" + integerToString(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Insert ascending and descending sequences.") {
    PQHeap pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + integerToString(i), 2 * i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + integerToString(i), 2 * i + 1 });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 40; i++) {
        DataPoint removed = pq.dequeue();
        EXPECT_EQUAL(removed.priority, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Insert random sequence of elements.") {
    Vector<DataPoint> sequence = {
        { "A", 0 },
        { "D", 3 },
        { "F", 5 },
        { "G", 6 },
        { "C", 2 },
        { "H", 7 },
        { "I", 8 },
        { "B", 1 },
        { "E", 4 },
        { "J", 9 },
    };

    PQHeap pq;
    for (DataPoint elem: sequence) {
        pq.enqueue(elem);
    }

    EXPECT_EQUAL(pq.size(), sequence.size());

    for (int i = 0; i < 10; i++) {
        DataPoint removed = pq.dequeue();
        DataPoint expected = {
            charToString('A' + i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}


PROVIDED_TEST("Provided Test: Insert duplicate elements.") {
    PQHeap pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + integerToString(i), i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + integerToString(i), i });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 20; i++) {
        DataPoint one = pq.dequeue();
        DataPoint two = pq.dequeue();

        EXPECT_EQUAL(one.priority, i);
        EXPECT_EQUAL(two.priority, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

PROVIDED_TEST("Provided Test: Handles data points with empty string name.") {
    PQHeap pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 10);
}

PROVIDED_TEST("Test enqueue/dequeue of longer random sequence") {
    PQHeap pq;

    for (int i = 0; i < 100; i++) {
        int randomValue = randomInteger(0, 100);
        DataPoint pt = {"elem" + integerToString(randomValue), randomValue};
        pq.enqueue(pt);
    }
    EXPECT_EQUAL(pq.size(), 100);
    DataPoint last = {"", -1};
    for (int i = 0; i < 100; i++) {
        DataPoint cur = pq.dequeue();
        EXPECT(cur.priority >= 0 && cur.priority <= 100 && cur.priority >= last.priority);
        last = cur;
    }
    EXPECT_EQUAL(pq.size(), 0);
}


PROVIDED_TEST("Provided Test: Handles data points with negative weights.") {
    PQHeap pq;
    for (int i = -10; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 20);
    for (int i = -10; i < 10; i++) {
        DataPoint removed = pq.dequeue();
        EXPECT_EQUAL(removed.priority, i);
    }
}

PROVIDED_TEST("Provided Test: Interleave enqueues and dequeues.") {
    PQHeap pq;
    int n = 100;
    for (int i = n / 2; i < n; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = n / 2; i < n; i++) {
        EXPECT_EQUAL(pq.dequeue().priority, i);
    }
    EXPECT_EQUAL(pq.size(), 0);

    for (int i = 0; i < n / 2; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = 0; i < n / 2; i++) {
        EXPECT_EQUAL(pq.dequeue().priority, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
}

static void fillAndEmpty(int n) {
    PQHeap pq;
    DataPoint max = {"max", 106106106};
    DataPoint min = {"min", -106106106};

    pq.enqueue(min);
    pq.enqueue(max);
    for (int i = 0; i < n; i++) {
        int randomPriority = randomInteger(-10000, 10000);
        pq.enqueue({ "", randomPriority });
    }
    EXPECT_EQUAL(pq.size(), n + 2);

    EXPECT_EQUAL(pq.dequeue(), min);
    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
    EXPECT_EQUAL(pq.dequeue(), max);
    EXPECT_EQUAL(pq.size(), 0);
}

PROVIDED_TEST("Provided Test: Stress Test. Time the amount of time it takes to cycle many elements in and out. Should take at most about 5-10 seconds.") {
    TIME_OPERATION(20000, fillAndEmpty(20000));
}
