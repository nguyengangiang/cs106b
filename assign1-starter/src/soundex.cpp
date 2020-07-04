// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include <fstream>
#include <cctype>
#include <string>
#include "simpio.h"

using namespace std;

/* This function takes a string s and returns a version of
 * the string that has all non-letter characters removed
 * from it.
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/* This function takes in a char and return
 * a digt that correspond to it according to the
 * table below
    Digit	represents the letters
    0	A E I O U H W Y
    1	B F P V
    2	C G J K Q S X Z
    3	D T
    4	L
    5	M N
    6	R
 */

char encodeLetterAsDigit(char c) {
    c = toUpperCase(c);
    if (c == 'R') {
        return '6';
    } else if (c == 'M' || c == 'N') {
        return '5';
    } else if (c == 'L') {
        return '4';
    } else if (c == 'D' || c == 'T') {
        return '3';
    } else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' || c == 'X' || c == 'S' || c == 'Z') {
            return '2';
    } else if (c == 'B' || c == 'F' || c == 'P' || c == 'V') {
        return '1';
    } else {
        return '0';
    }
}

/* This function takes in a string and  return a string that
 * has been coalescde adjacent duplicate digits from code
 */
string removeAdjecentRepeatedDigit(string s) {
    string result = "";
    result += s[0];
    for (int i = 1; i < s.length(); i++) {
        if (!(s[i] == s[i-1])) {
            result += s[i];
        }
    }
    return result;
}

/* This function takes in a string. iterate through it and remove
 * any 0 character
 */
string removeZeros(string s) {
    for (int i = 0; i < s.length(); i++) {
        if(s[i] == '0') {
            s = s.erase(i, 1);
        }
    }
    return s;
}

/* This function takes in a string that has a length < 4 and
 * return a new string with the exact length of 4 by adding
 * character '0' to the end of it
 */
string padding(string s) {
    int add = 4 - s.length();
    for (int i = 0; i < add; i++) {
        s.append("0");
    }
    return s;
}

/* This function takes in a string with a length greater than 4
 * and return a tring that only includes first 4 character of the
 * original string
 */
string truncate(string s) {
    return s.substr(0, 4);
}

/* This function takes in a surname as a string and return the soundex code
 * for that surname. The initial letter is the first letter of the surname,
 * and the three digits are drawn from the sounds within the surname
 */
string soundex(string s) {
    string result = "";
    s = removeNonLetters(s);
    result += toUpperCase(s[0]);
    for (int i = 1; i < s.length(); i++) {
        char c = encodeLetterAsDigit(s[i]);
        result += c;
    }
    result = removeAdjecentRepeatedDigit(result);
    result = removeZeros(result);
    if (result.length() < 4) {
        return padding(result);
    } else if (result.length() > 4) {
        return truncate(result);
    }
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name 
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    while (true) {
        string surname = getLine("Enter a surname (RETURN to quit) ");
        if (surname == "") {
            break;
        }
        string target = soundex(surname);
        cout << "Soundex code is " << target << endl;
        Vector<string> matched;
        for (int i = 0; i < databaseNames.size(); i++) {
            if (soundex(databaseNames[i]) == target) {
                matched.add(databaseNames[i]);
            }
        }
        matched.sort();
        cout << "Match from database: " << matched << endl;
   }
   cout << "All done." << endl;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Master"), "M236");
    EXPECT_EQUAL(soundex("Jue"), "J000");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("Student test removing puntuation, digits, and spaces") {
    EXPECT_EQUAL(removeNonLetters("Nguy3n Ng@n G1@ng"), "NguynNgnGng");
    EXPECT_EQUAL(removeNonLetters("     he  ll o "), "hello");
}
