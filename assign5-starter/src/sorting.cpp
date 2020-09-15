#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Helper function for mergeSort: Split and rewire the link list into two even and odd list based on
 * the data of each node
 */

void split(ListNode*& front, ListNode*& even, ListNode*& odd) {
    if (front == nullptr) {return;}
    if (front->next == nullptr) {
        even = front;
        return;
    }
    even = front;
    ListNode *trackeven = even;
    odd = front->next;
    ListNode* trackodd = odd;

    while (trackeven != nullptr && trackodd != nullptr) {
        trackodd = trackeven->next;
        trackeven->next = trackeven->next->next;
        trackeven = trackeven->next;
        if (trackeven != nullptr) {
            trackodd->next = trackeven->next;
            trackodd = trackodd->next;
        }
    }
    trackodd = nullptr;
    trackeven = nullptr;
}

/* Helper function for merge Sort: Iteratively merge the two link lists into one and compare the values of their data */
void merge(ListNode*& front, ListNode*& even, ListNode*& odd) {
    ListNode* track;
    ListNode* trackeven = even;
    ListNode* trackodd = odd;
    if (even == nullptr && odd == nullptr) {return;}
    else if ((even != nullptr && odd != nullptr && even->data < odd->data) || (even != nullptr && odd == nullptr)) {
        front = trackeven;
        trackeven = trackeven->next;
    } else {
        front = trackodd;
        trackodd = trackodd->next;
    }

    track = front;

    while (trackodd != nullptr || trackeven != nullptr) {
        if((trackeven != nullptr && trackodd != nullptr && trackeven->data < trackodd->data) || (trackeven != nullptr && trackodd == nullptr)) {
            track->next = trackeven;
            track = track->next;
            trackeven = trackeven->next;
        } else {
            track->next = trackodd;
            track = track->next;
            trackodd = trackodd->next;
        }
    }
}

/* Divides the input list into two sublists, recursively sorts the two lists,
 * and applies a binary merge to join the two sorted lists into one combined whole
 */
void mergeSort(ListNode*& front) {
    if (front == nullptr || front->next == nullptr) {return;}
    ListNode* even = nullptr;
    ListNode* odd = nullptr;

    split(front, even, odd);
    mergeSort(even);
    mergeSort(odd);

    front = nullptr;
    merge(front, even, odd);
}

/* Helper function for quickSort: Divide the elements into three sublists: those elements that are strictly
 * less than the pivot, those that are equal to the pivot, and those that are strictly greater.
 */
void partition(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater, int pivot) {
    ListNode* track = front;
    ListNode* trackLess = less;
    ListNode* trackEqual = equal;
    ListNode* trackGreater = greater;
    while(track != nullptr) {
        if (track->data < pivot) {
            if (trackLess != nullptr) {
                trackLess->next = track;
                trackLess = trackLess->next;
            } else {
                less = track;
                trackLess = less;
            }
            track = track->next;
            trackLess->next = nullptr;
        } else if (track->data == pivot) {
            if (trackEqual != nullptr) {
                trackEqual->next = track;
                trackEqual = trackEqual->next;
            } else {
                equal = track;
                trackEqual = equal;
            }
            track = track->next;
            trackEqual->next = nullptr;
        } else {
            if (trackGreater != nullptr) {
                trackGreater->next = track;
                trackGreater = trackGreater->next;
            } else {
                greater = track;
                trackGreater = greater;
            }
            track = track->next;
            trackGreater->next = nullptr;
        }
    }
}

/* Helper function for quickSort: attaches the three sorted sublists in one combined list by
 * adding the missing links needed to concatenate them.
 */
void concatnate(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater) {
    if (less != nullptr) {
        front = less;
        ListNode* track = front;
        while (track->next != nullptr) {
            track = track->next;
        }
        track->next = equal;
        while (track->next != nullptr) {
            track = track->next;
        }
        track->next = greater;
    } else if (equal != nullptr) {
        front = equal;
        ListNode* track = front;
        while (track->next != nullptr) {
            track = track->next;
        }
        track->next = greater;
    } else if (greater != nullptr) {
        front = greater;
    } else {
        return;
    }


}
/* Divides the input list into sublists that are less than or greater than a chosen pivot.
 * After recursively sorting the sublists, they are joined in sequence.
 */
void quickSort(ListNode*& front) {
    if (front == nullptr) {return;}
    ListNode* less =  nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(front, less, equal, greater, front->data);
    quickSort(less);
    quickSort(greater);
    front = nullptr;
    concatnate(front, less, equal, greater);
}


/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 * As part of this process, you are also strongly recommedned to fill in
 * the function prototypes we have defined below.
 */

/*
 * We have provided this helper function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   while (front != nullptr) {
       cout << front->data;
       if (front->next != nullptr){
           cout << ", ";
       }
       front = front->next;
   }
   cout << "}" << endl;
}

/*
 * This helper function is provided a pointer to the front of the list
 * and is responsible for deallocating all of the memory being used
 * to store nodes in that list.
 */
void deallocateList(ListNode* front) {
    while (front != nullptr) {
        ListNode* next = front->next;
        delete front;
        front = next;
    }
}

/*
 * This helper function is provided a vector of integer values and
 * returns a pointer to the beginning of a linked list containing
 * those values in the specified order.
 */
ListNode* createList(Vector<int> values){
    if (values.isEmpty()) {return nullptr;}
    ListNode* front = new ListNode;
    front->data = values[0];
    front->next = nullptr;
    ListNode* cur = front;
    for (int i = 1; i < values.size(); i++) {
        ListNode* next = new ListNode;
        next->next = nullptr;
        next->data = values[i];
        cur->next = next;
        cur = next;
    }
    return front;
}

/*
 * This helper function is provided a vector of integer values
 * and a pointer to the beginning of a linked list. If these two structures
 * contain the same values in the same order, the function returns
 * true, otherwise it returns false.
 */
bool checkListVectorEquality(ListNode* front, Vector<int> v){
    if (v.isEmpty() && front == nullptr) {return true;}
    ListNode* track = front;
    for (int i = 0; i < v.size(); i++) {
        if (track == nullptr) {return false;}
        if (track->data != v[i]) {return false;}
        track = track->next;
    }
    if (track != nullptr) {return false;}
    return true;
}

STUDENT_TEST("Testing split function with small even number of values") {
    Vector<int> values = {1, 2, 3, 4};
    ListNode* list = createList(values);
    ListNode* even = nullptr;
    ListNode* odd = nullptr;
    split(list, even, odd);
    Vector<int> evenValues = {1, 3};
    Vector<int> oddValues = {2, 4};
    EXPECT(checkListVectorEquality(even, evenValues));
    EXPECT(checkListVectorEquality(odd, oddValues));
    deallocateList(even);
    deallocateList(odd);
}

STUDENT_TEST("Testing split function with small odd number of values") {
    Vector<int> values = {1, 2, 3, 4, 5};
    ListNode* list = createList(values);
    ListNode* even = nullptr;
    ListNode* odd = nullptr;
    split(list, even, odd);
    Vector<int> evenValues = {1, 3, 5};
    Vector<int> oddValues = {2, 4};
    EXPECT(checkListVectorEquality(even, evenValues));
    EXPECT(checkListVectorEquality(odd, oddValues));
    deallocateList(even);
    deallocateList(odd);}

STUDENT_TEST("Testing split function with no value") {
    Vector<int> values = {};
    ListNode* list = createList(values);
    ListNode* even = nullptr;
    ListNode* odd = nullptr;
    split(list, even, odd);
    Vector<int> evenValues = {};
    Vector<int> oddValues = {};
    EXPECT(checkListVectorEquality(even, evenValues));
    EXPECT(checkListVectorEquality(odd, oddValues));
    deallocateList(even);
    deallocateList(odd);}

STUDENT_TEST("Testing split function with 1 value") {
    Vector<int> values = {1};
    ListNode* list = createList(values);
    ListNode* even = nullptr;
    ListNode* odd = nullptr;
    split(list, even, odd);
    Vector<int> evenValues = {1};
    Vector<int> oddValues = {};
    EXPECT(checkListVectorEquality(even, evenValues));
    EXPECT(checkListVectorEquality(odd, oddValues));
    deallocateList(even);
    deallocateList(odd);
}

STUDENT_TEST("Testing merge function with small even number of values") {
    ListNode* even = createList({2, 4, 5, 6, 10});
    ListNode* odd = createList({1, 3, 7, 8, 9 });
    ListNode* list = nullptr;
    merge(list, even, odd);
    Vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT(checkListVectorEquality(list, expected));
    deallocateList(list);
}

STUDENT_TEST("Testing merge function with small odd number of values") {
    ListNode* even = createList({2, 4, 5, 6, 10});
    ListNode* odd = createList({1, 1, 3, 7, 8, 9});
    ListNode* list = nullptr;
    merge(list, even, odd);
    Vector<int> expected = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT(checkListVectorEquality(list, expected));
    deallocateList(list);
}

STUDENT_TEST("Testing merge function without any value") {
    ListNode* even = createList({});
    ListNode* odd = createList({});
    ListNode* list = nullptr;
    merge(list, even, odd);
    Vector<int> expected = {};
    EXPECT(checkListVectorEquality(list, expected));
    deallocateList(list);
}

STUDENT_TEST("Testing merge function with 1 value") {
    ListNode* even = createList({0});
    ListNode* odd = createList({});
    ListNode* list = nullptr;
    merge(list, even, odd);
    Vector<int> expected = {0};
    EXPECT(checkListVectorEquality(list, expected));
    deallocateList(list);
}

STUDENT_TEST("Testing merge function with 1 value") {
    ListNode* even = createList({});
    ListNode* odd = createList({0});
    ListNode* list = nullptr;
    merge(list, even, odd);
    Vector<int> expected = {0};
    EXPECT(checkListVectorEquality(list, expected));
    deallocateList(list);
}

STUDENT_TEST("This is a skeleton for what your overall student tests should look like."){
    /* Initialize the values and list for this test case. */
    Vector<int> values = {1, 2, 3, 4};
    ListNode* list = createList(values);

    /* Sort the linked list. */
    mergeSort(list);
    printList(list);

    /* Sort the vector. */
    values.sort();

    /* Check to make sure that the list is now in the correct order. */
    EXPECT(checkListVectorEquality(list, values));

    /* Avoid memory leaks by deallocating list. */
    deallocateList(list);
}

STUDENT_TEST("Test mergeSort with shuffle values"){
    /* Initialize the values and list for this test case. */
    Vector<int> values = {10, 9, 6, 7, 2, 3, 5, 1, 4, 8, 0};
    ListNode* list = createList(values);
    mergeSort(list);
    printList(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

STUDENT_TEST("Test mergeSort with no value"){
    /* Initialize the values and list for this test case. */
    Vector<int> values = {};
    ListNode* list = createList(values);
    mergeSort(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

STUDENT_TEST("Test mergeSort with large number of random values"){
    /* Initialize the values and list for this test case. */
    Vector<int> values;
    for (int i = 0; i < 2000; i++) {
        int r = randomInteger(-100, 60000);
        values.add(r);
    }
    ListNode* list = createList(values);
    mergeSort(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

STUDENT_TEST("Testing partition function with small number of values") {
    Vector<int> values = {3, 2, 1, 4};
    ListNode* list = createList(values);
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(list, less, equal, greater, values[0]);
    Vector<int> lessValues = {2, 1};
    Vector<int> equalValues = {3};
    Vector<int> greaterValues = {4};
    EXPECT(checkListVectorEquality(less, lessValues));
    EXPECT(checkListVectorEquality(equal, equalValues));
    EXPECT(checkListVectorEquality(greater, greaterValues));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Testing partition function with greater number of values") {
    Vector<int> values = {5,0, 1, 1, 2, 6, 3, 7, 8, 4, 9, 5, 10, 5, 5, 10};
    ListNode* list = createList(values);
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(list, less, equal, greater, values[0]);
    Vector<int> lessValues = {0, 1, 1, 2, 3, 4};
    Vector<int> equalValues = {5, 5, 5, 5};
    Vector<int> greaterValues = {6, 7, 8, 9, 10, 10};
    EXPECT(checkListVectorEquality(less, lessValues));
    EXPECT(checkListVectorEquality(equal, equalValues));
    EXPECT(checkListVectorEquality(greater, greaterValues));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Testing partition function with no value") {
    Vector<int> values = {};
    ListNode* list = createList(values);
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(list, less, equal, greater, 0);
    Vector<int> lessValues = {};
    Vector<int> equalValues = {};
    Vector<int> greaterValues = {};
    EXPECT(checkListVectorEquality(less, lessValues));
    EXPECT(checkListVectorEquality(equal, equalValues));
    EXPECT(checkListVectorEquality(greater, greaterValues));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Testing partition function with one value") {
    Vector<int> values = {5};
    ListNode* list = createList(values);
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(list, less, equal, greater, values[0]);
    Vector<int> lessValues = {};
    Vector<int> equalValues = {5};
    Vector<int> greaterValues = {};
    EXPECT(checkListVectorEquality(less, lessValues));
    EXPECT(checkListVectorEquality(equal, equalValues));
    EXPECT(checkListVectorEquality(greater, greaterValues));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Testing partition function with two value") {
    Vector<int> values = {5, 4};
    ListNode* list = createList(values);
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(list, less, equal, greater, values[0]);
    Vector<int> lessValues = {4};
    Vector<int> equalValues = {5};
    Vector<int> greaterValues = {};
    EXPECT(checkListVectorEquality(less, lessValues));
    EXPECT(checkListVectorEquality(equal, equalValues));
    EXPECT(checkListVectorEquality(greater, greaterValues));
    deallocateList(less);
    deallocateList(equal);
    deallocateList(greater);
}

STUDENT_TEST("Testing concatnate function with small amount of values") {
    ListNode* less = createList({1, 1, 2});
    ListNode* equal = createList({3, 3});
    ListNode* greater = createList({4, 5, 6});
    ListNode* front = nullptr;
    concatnate(front, less, equal, greater);
    Vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 6};
    EXPECT(checkListVectorEquality(front, expected));
    deallocateList(front);

}

STUDENT_TEST("Testing concatnate function with no value") {
    ListNode* less = createList({});
    ListNode* equal = createList({});
    ListNode* greater = createList({});
    ListNode* front = nullptr;
    concatnate(front, less, equal, greater);
    Vector<int> expected = {};
    EXPECT(checkListVectorEquality(front, expected));
    deallocateList(front);
}


STUDENT_TEST("Testing concatnate function with one value") {
    ListNode* less = createList({1});
    ListNode* equal = createList({});
    ListNode* greater = createList({});
    ListNode* front = nullptr;
    concatnate(front, less, equal, greater);
    Vector<int> expected = {1};
    EXPECT(checkListVectorEquality(front, expected));
    deallocateList(front);
}


STUDENT_TEST("Testing concatnate function with two value") {
    ListNode* less = createList({1});
    ListNode* equal = createList({4});
    ListNode* greater = createList({});
    ListNode* front = nullptr;
    concatnate(front, less, equal, greater);
    Vector<int> expected = {1, 4};
    EXPECT(checkListVectorEquality(front, expected));
    deallocateList(front);
}

PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(checkListVectorEquality(testList, {1, 2, 3}));
    EXPECT(!checkListVectorEquality(testList, {1, 2}));
    EXPECT(!checkListVectorEquality(testList, {1, 2, 3, 4}));
    EXPECT(!checkListVectorEquality(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

STUDENT_TEST("Testing quickSort on a small amount of values") {
    Vector<int> values = {10, 9, 6, 7, 2, 3, 5, 1, 4, 8, 0};
    ListNode* list = createList(values);
    quickSort(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

STUDENT_TEST("Test quickSort with no value"){
    /* Initialize the values and list for this test case. */
    Vector<int> values = {};
    ListNode* list = createList(values);
    quickSort(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

STUDENT_TEST("Test quickSort with large number of random values"){
    /* Initialize the values and list for this test case. */
    Vector<int> values;
    for (int i = 0; i < 2000; i++) {
        int r = randomInteger(-100, 60000);
        values.add(r);
    }
    ListNode* list = createList(values);
    quickSort(list);
    values.sort();
    EXPECT(checkListVectorEquality(list, values));
    deallocateList(list);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v;
        ListNode* list = nullptr;

        /* Insert the same random values into linked list and vector. */
        for (int i = 0; i < n; i++) {
            int val = randomInteger(-10000, 10000);
            v.add(val);
            list = new ListNode(val, list);
        }

        /* The vector values are currently in the reverse order than the
         * linked list values – let's fix that so we have a fair comparison. */
        v.reverse();

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to generate a comparison. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

