/* 
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;

/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int points(string str) {
    if (str.length() <= 3) {
        return 0;
    } else {
        return str.length() - 3;
    }
}

Set<GridLocation> discoverPossibleMoves(GridLocation cur, Grid<char> &board) {
    Set<GridLocation> neighbors;
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <=1; c++) {
            GridLocation neighbor = {cur.row + r, cur.col + c};
            if (board.inBounds(neighbor)) {
                neighbors.add(neighbor);
            }
        }
    }
    neighbors.remove(cur);
    return neighbors;
}

void findWord(Grid<char>& board, Lexicon& lex, string soFar, GridLocation cur, Set<string>& words, Set<GridLocation> visited) {
    Set<GridLocation> neighbors = discoverPossibleMoves(cur, board);
    Set<GridLocation> neighbored = neighbors;
    visited.add(cur);
    for (GridLocation path : neighbors) {
        string s = soFar + charToString(board[path]);
        if (!lex.containsPrefix(s)) {
            neighbored.remove(path);
        }
    }
    if (!neighbored.isEmpty()) {
        for (GridLocation path : neighbored) {
            if (!visited.contains(path) && isalpha(board[path])) {
                string s = soFar + charToString(board[path]);
                if (lex.contains(s)) {
                        words.add(s);
                }
                findWord(board, lex, s, path, words, visited);
            }
        }
    }
}
/* 
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int scoreBoard(Grid<char>& board, Lexicon& lex) {
    int total = 0;
    Set<string> wordFound{};
    Set<GridLocation>visited{};
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            GridLocation cur = {r, c};
            string s = charToString(board[cur]);
            findWord(board, lex, s, cur, wordFound, visited);
        }
    }
    for (string word : wordFound) {
        total += points(word);
    }
    return total;
}


/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 0);

}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'A','_','_','_'},
                        {'_','R','_','_'}};
    //EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 1);

}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 12);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 8);

}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    // EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
    TIME_OPERATION(scoreBoard(board, sharedLexicon()), 234);
}
