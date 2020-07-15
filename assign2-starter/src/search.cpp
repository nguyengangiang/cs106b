// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "testing/SimpleTest.h"
#include "map.h"
#include "set.h"
#include <string>
#include <iostream>
#include "filelib.h"
#include <fstream>
#include "simpio.h"
#include "strlib.h"
#include "search.h"
using namespace std;

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string cleanToken(string token) {
    /* TODO: Fill in the remainder of this function. */
    return "";
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
Map<string, Set<string>> readDocs(string dbfile) {
    Map<string, Set<string>> docs;
    /* TODO: Fill in the remainder of this function. */
    return docs;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
Map<string, Set<string>> buildIndex(Map<string, Set<string>>& docs) {
    Map<string, Set<string>> index;
    /* TODO: Fill in the remainder of this function. */
    return index;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {
    Set<string> result;
    /* TODO: Fill in the remainder of this function. */
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void searchEngine(string dbfile) {
    /* TODO: Fill in the remainder of this function. */
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on tokens with no punctuation") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
}

PROVIDED_TEST("cleanToken on tokens with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word tokens"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("readDocs from tiny.txt, contains 4 documents") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    EXPECT_EQUAL(docs.size(), 4);
}

PROVIDED_TEST("readDocs from tiny.txt, suess has 5 unique words and includes lowercase fish") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Set<string> seuss = docs["www.dr.seuss.net"];
    EXPECT_EQUAL(seuss.size(), 5);
    EXPECT(seuss.contains("fish"));
    EXPECT(!seuss.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 20 unique tokens overall") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    EXPECT_EQUAL(index.size(), 20);
    EXPECT(index.containsKey("fish"));
    EXPECT(!index.containsKey("@"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 3);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
