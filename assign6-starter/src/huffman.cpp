#include "bits.h"
#include "treenode.h"
#include "huffman.h"
#include "map.h"
#include "vector.h"
#include "priorityqueue.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
using namespace std;

/**
 * Given a Queue<Bit> containing the compressed message bits and the encoding tree
 * used to encode those bits, decode the bits back to the original message text.
 *
 * You can assume that tree is a well-formed non-empty encoding tree and
 * bits queue contains a valid sequence of encoded bits.
 */
string decodeText(EncodingTreeNode* tree, Queue<Bit>& messageBits) {
    EncodingTreeNode* track = tree;
    string result = "";
    while(!messageBits.isEmpty()) {
        Bit bit = messageBits.dequeue();
        if (track == nullptr) {
            track = tree;
        }
        if (bit == 0) {
            track = track->zero;
        } else {
            track = track->one;
        }
        if (track->one == nullptr && track->zero == nullptr) {
            result += track->ch;
            track = tree;
        }
    }
    return result;
}

/**
 * Reconstruct encoding tree from flattened form Queue<Bit> and Queue<char>.
 *
 * You can assume that the input Queues are well-formed and represent
 * a valid encoding tree.
 */
EncodingTreeNode* unflattenTree(Queue<Bit>& treeBits, Queue<char>& treeLeaves) {
    EncodingTreeNode* root = nullptr;
    if (!treeBits.isEmpty()) {
        if (treeBits.dequeue() == 1) {
            root = new EncodingTreeNode(nullptr, nullptr);
            root->zero = unflattenTree(treeBits, treeLeaves);
            root->one = unflattenTree(treeBits, treeLeaves);
        } else {
            root = new EncodingTreeNode(treeLeaves.dequeue());
        }
    }
    return root;
}

/**
 * Decompress the given EncodedData and return the original text.
 *
 * You can assume the input data is well-formed and was created by a correct
 * implementation of compress.
 *
 * Your implementation may change the data parameter however you like. There
 * are no requirements about what it should look like after this function
 * returns.
 */
string decompress(EncodedData& data) {
    Queue<Bit> treeBits = data.treeBits;
    Queue<char> treeLeaves = data.treeLeaves;
    Queue<Bit> messageBits = data.messageBits;
    EncodingTreeNode* root = unflattenTree(treeBits, treeLeaves);
    string result = decodeText(root, messageBits);
    deallocateTree(root);
    return result;
}

/**
 * Constructs an optimal Huffman coding tree for the given text, using
 * the algorithm described in lecture.
 *
 * Reports an error if the input text does not contain at least
 * two distinct characters.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* buildHuffmanTree(string text) {
    Map<char, int> frequency;
    PriorityQueue<EncodingTreeNode*> forest;
    for (char ch : text) {
        if (frequency.containsKey(ch)) {
            frequency.put(ch, frequency.get(ch) + 1);
        } else {
            frequency.put(ch, 1);
        }
    }
    if (frequency.size() <= 1) {error("Input text does not contain at least two distinct characters");}
    for (char ch : frequency) {
        EncodingTreeNode* c = new EncodingTreeNode(ch);
        forest.enqueue(c, frequency.get(ch));
    }
    while (forest.size() > 1) {
        int firstPriority = forest.peekPriority();
        EncodingTreeNode* first = forest.dequeue();
        int secondtPriority = forest.peekPriority();
        EncodingTreeNode* second = forest.dequeue();
        EncodingTreeNode* combine = new EncodingTreeNode(first, second);
        forest.enqueue(combine, firstPriority + secondtPriority);
    }
    return forest.dequeue();
}

/**
 * Given a string and an encoding tree, encode the text using the tree
 * and return a Queue<Bit> of the encoded bit sequence.
 *
 * You can assume tree is a valid non-empty encoding tree and contains an
 * encoding for every character in the text.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
Queue<Bit> encodeText(EncodingTreeNode* tree, string text) {
    Queue<Bit> result;
    Map<char, Queue<Bit>> table;
    createTable(tree, table, result);
    for (char ch : text) {
        Queue<Bit> bits = table.get(ch);
        while (!bits.isEmpty()) {
            result.enqueue(bits.dequeue());
        }
    }
    return result;

}

void createTable(EncodingTreeNode* tree, Map<char, Queue<Bit>>& table, Queue<Bit> soFar) {
    if (tree->one == nullptr && tree->zero == nullptr) {
        table.add(tree->ch, soFar);
    } else {
        Queue<Bit> zero = soFar;
        zero.enqueue(0);
        createTable(tree->zero, table, zero);
        Queue<Bit> one = soFar;
        one.enqueue(1);
        createTable(tree->one, table, one);
    }
}

/**
 * Flatten the given tree into a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment writeup.
 *
 * You can assume the input Queues are empty on entry to this function.
 *
 * You can assume tree is a valid well-formed encoding tree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
void flattenTree(EncodingTreeNode* tree, Queue<Bit>& treeBits, Queue<char>& treeLeaves) {
    if (tree->one == nullptr && tree->zero == nullptr) {
        treeLeaves.enqueue(tree->ch);
        treeBits.enqueue(0);
    } else {
        treeBits.enqueue(1);
        flattenTree(tree->zero, treeBits, treeLeaves);
        flattenTree(tree->one, treeBits, treeLeaves);
    }
}

/**
 * Compress the input text using Huffman coding, producing as output
 * an EncodedData containing the encoded message and encoding tree used.
 *
 * Reports an error if the message text does not contain at least
 * two distinct characters.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodedData compress(string messageText) {
    EncodingTreeNode* tree = buildHuffmanTree(messageText);
    Queue<Bit> treeBits;
    Queue<char> treeLeaves;
    Queue<Bit> messageBits = encodeText(tree, messageText);
    flattenTree(tree, treeBits, treeLeaves);
    EncodedData data = EncodedData{treeBits, treeLeaves, messageBits};
    deallocateTree(tree);
    return data;
}

/* * * * * * Testing Helper Functions Below This Point * * * * * */

EncodingTreeNode* createExampleTree() {
    /* Example encoding tree used in multiple test cases:
     *                *
     *              /   \
     *             T     *
     *                  / \
     *                 *   E
     *                / \
     *               R   S
     */
    /* TODO: Implement this helper function needed for testing. */
    EncodingTreeNode* t = new EncodingTreeNode('T');
    EncodingTreeNode* r = new EncodingTreeNode('R');
    EncodingTreeNode* s = new EncodingTreeNode('S');
    EncodingTreeNode* e = new EncodingTreeNode('E');
    EncodingTreeNode* third = new EncodingTreeNode(r, s);
    EncodingTreeNode* second = new EncodingTreeNode(third, e);
    EncodingTreeNode* root = new EncodingTreeNode(t, second);
    return root;
}

void deallocateTree(EncodingTreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deallocateTree(root->one);
    deallocateTree(root->zero);
    delete root;
}

bool areEqual(EncodingTreeNode* a, EncodingTreeNode* b) {
    EncodingTreeNode* trackA = a;
    EncodingTreeNode* trackB = b;
    if (trackA != nullptr && trackB != nullptr && trackA->ch == trackB->ch){
        areEqual(trackA->zero, trackB->zero);
        areEqual(trackA->one, trackB->one);
        return true;
    } else if (trackA == nullptr && trackB == nullptr){
        return true;
    } else {
        return false;
    }
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Write your own student tests. */
STUDENT_TEST("Testing deallocateTree function") {
    EncodingTreeNode* head = createExampleTree();
    deallocateTree(head);
}

STUDENT_TEST("Testing areEqual function") {
    EncodingTreeNode* a = createExampleTree();
    EncodingTreeNode* b = createExampleTree();
    EXPECT(areEqual(a, b));
    EXPECT(areEqual(a->one, b->one));
    EXPECT(areEqual(a->zero, b->zero));
    EXPECT(!areEqual(a->one, b->zero));
    EXPECT(!areEqual(a->zero, b->one));
    EXPECT(!areEqual(a->zero, b));
    EXPECT(areEqual(a->one->one, b->one->one));
    deallocateTree(a);
    deallocateTree(b);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("decodeText, small example encoding tree") {
    EncodingTreeNode* tree = createExampleTree(); // see diagram above

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(decodeText(tree, messageBits), "E");

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(decodeText(tree, messageBits), "SET");

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1}; // STREETS
    EXPECT_EQUAL(decodeText(tree, messageBits), "STREETS");

    deallocateTree(tree);
}

PROVIDED_TEST("unflattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  treeBits   = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeLeaves = { 'T', 'R', 'S', 'E' };
    EncodingTreeNode* tree = unflattenTree(treeBits, treeLeaves);

    EXPECT(areEqual(tree, reference));

    deallocateTree(tree);
    deallocateTree(reference);
}

PROVIDED_TEST("decompress, small example input") {
    EncodedData data = {
        { 1, 0, 1, 1, 0, 0, 0 }, // treeBits
        { 'T', 'R', 'S', 'E' },  // treeLeaves
        { 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 } // messageBits
    };

    EXPECT_EQUAL(decompress(data), "TRESS");
}

PROVIDED_TEST("buildHuffmanTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    EncodingTreeNode* tree = buildHuffmanTree("STREETTEST");
    EXPECT(areEqual(tree, reference));

    deallocateTree(reference);
    deallocateTree(tree);
}

PROVIDED_TEST("encodeText, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(encodeText(reference, "E"), messageBits);

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(encodeText(reference, "SET"), messageBits);

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1 }; // STREETS
    EXPECT_EQUAL(encodeText(reference, "STREETS"), messageBits);

    deallocateTree(reference);
}

PROVIDED_TEST("flattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  expectedBits   = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'T', 'R', 'S', 'E' };

    Queue<Bit>  treeBits;
    Queue<char> treeLeaves;
    flattenTree(reference, treeBits, treeLeaves);

    EXPECT_EQUAL(treeBits,   expectedBits);
    EXPECT_EQUAL(treeLeaves, expectedLeaves);

    deallocateTree(reference);
}

PROVIDED_TEST("compress, small example input") {
    EncodedData data = compress("STREETTEST");
    Queue<Bit>  treeBits    = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeChars   = { 'T', 'R', 'S', 'E' };
    Queue<Bit>  messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };

    EXPECT_EQUAL(data.treeBits, treeBits);
    EXPECT_EQUAL(data.treeLeaves, treeChars);
    EXPECT_EQUAL(data.messageBits, messageBits);
}

PROVIDED_TEST("Test end-to-end compress -> decompress") {
    Vector<string> inputs = {
        "HAPPY HIP HOP",
        "The job requires extra pluck and zeal from every young wage earner.",
        ":-) :-D XD <(^_^)>",
    };

    for (string input: inputs) {
        EncodedData data = compress(input);
        string output = decompress(data);

        EXPECT_EQUAL(output.size(), input.size());

        /* Don't clobber the output with a huge string if there's a mismatch. */
        EXPECT(input == output);
    }
}
