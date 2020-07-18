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

/* Helper fundtion trims the word down to want we want to store
 * in our index. Removes any token that are not letter
 */
string cleanToken(string token) {
    int numAlpha = 0;
    for (char ch : token) {
        if(isalpha(ch)) {
            numAlpha++;
        }
    }
    if (numAlpha == 0) {
        return "";
    }
    char start = token[0];
    char end = token[token.length() - 1];
    if(ispunct(start)) {
        token = token.substr(1);
    }
    if (ispunct(end)) {
        token = token.erase(token.length()-1, 1);
    }
    return toLowerCase(token);
}

/* Reads from a file line by line and builds a map from an
 * URL to a Set<string> representing the unique words
 * that show up on the page
 */
Map<string, Set<string>> readDocs(string dbfile) {
    Map<string, Set<string>> docs;
    ifstream in;

    if (!openFile(in, dbfile))
        error("Cannot open file named " + dbfile);

    Vector<string> lines;
    readEntireFile(in, lines);

    for (int i = 0; i < lines.size(); i++) {
        if(i % 2 == 1) {
            Set<string> tokens;
            Vector<string> words = stringSplit(lines[i], " ");
            for (string s : words) {
                s = cleanToken(s);
                if (s.length() > 0) {
                    tokens.add(s);
                }
            }
            docs.add(lines[i - 1], tokens);
        }
    }
    return docs;
}

/* Builds invert data index that map from each word to a set
 * of URLs that contains that word
 */
Map<string, Set<string>> buildIndex(Map<string, Set<string>>& docs) {
    Map<string, Set<string>> index;
    for (string key : docs.keys()) {
        for (string s : docs.get(key)) {
            index[s].add(key);
        }
    }
    return index;
}

/* Give users the ability to query search and receive data back
 * The query string argument can either be a single search term
 * or a compound sequence of multiple terms
 */
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {
    Set<string> result;
    Vector<string> words = stringSplit(query, " ");
    for (string s : words){
        if (s[0] == '+') {
            s = cleanToken(s);
            Set<string> temp = index[s];
            result *= temp;
        } else if (s[0] == '-') {
            s = cleanToken(s);
            Set<string> temp = index[s];
            result -= temp;
        } else {
            Set<string> temp = index[s];
            result += temp;
        }
    }
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void searchEngine(string dbfile) {
    cout << "Stand by while building index" << endl;
    Map<string, Set<string>> data = readDocs(dbfile);
    Map<string, Set<string>> index = buildIndex(data);
    cout << "Indexed " << data.size() << " pages, containing " << index.size() << " unique terms" << endl;
    while (true) {
        string query = getLine("Enter query sentence (RETURN/ENTER to quit): ");
        if (query == "") {
            break;
        }
        Set<string> queryMatches = findQueryMatches(index, query);
        cout << "Found " << queryMatches.size() << " matching pages" << endl;
        cout << queryMatches << endl;
    }
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

STUDENT_TEST("cleanToken with punctuation in the middle") {
    EXPECT_EQUAL(cleanToken("as-is"), "as-is");
    EXPECT_EQUAL(cleanToken("h3ll0"), "h3ll0");
    EXPECT_EQUAL(cleanToken("wow!"), "wow");
}

STUDENT_TEST("readDocs from website.txt, contains 50 documents") {
    Map<string, Set<string>> docs = readDocs("res/website.txt");
    EXPECT_EQUAL(docs.size(), 50);
}
