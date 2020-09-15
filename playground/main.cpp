#include <QCoreApplication>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stack>
using namespace std;

int compareString(string a, string b) {
    if (a.length() != b.length()) {
        return -1;
    }
    for (int i = 0; i < a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) {
            return -1;
        }
    }
    return 1;
}

void towerOfHanoi() {
    stack<int> source;
    for (int i = 3; i > 0; i--) {
        source.push(i);
    }
    stack<int> aux;
    stack<int> destination;

    int j = source.top();
    destination.push(j);
    source.pop();

    j = source.top();
    aux.push(j);
    source.pop();

    j = destination.top();
    destination.pop();
    aux.push(j);

    j = source.top();
    destination.push(j);
    source.pop();

    j = aux.top();
    source.push(j);
    aux.pop();

    j = aux.top();
    aux.pop();
    destination.push(j);

    j = source.top();
    source.pop();
    destination.push(j);

    while (!destination.empty()) {
        cout << destination.top() << endl;
        destination.pop();
    }

}
string dna(string nucleotide) {
    string result = "";
    for (char c : nucleotide) {
        if (toupper(c) == 'A') {
            result += 'T';
        } else if (toupper(c) == 'T') {
            result += 'A';
        } else if (toupper(c) == 'G') {
            result += 'C';
        } else if (toupper(c) == 'C'){
            result += 'G';
        } else {
            string error = "invalid argument: ";
            throw new invalid_argument(error.append(nucleotide));
        }
    }
    return result;
}

string getLine(string prompt) {
    string name;
    cout << prompt;
    getline(cin, name);
    return name;
}


void consoleDemo() {
    string name = getLine("What's your name: ");
    string food = getLine("What is your favourite food: ");
    cout << "Hi " << name << endl;
    cout << "Would you like some " << food << " to eat?" << endl;
}

void square() {
    while (true) {
        string input = getLine("Please enter a number you would like to square (ENTER/RETURN to exit): ");
        if (input == "") {
            break;
        }
        try {
            int i = stoi(input);
            cout << "Square of " << input << " is " << i*i << endl;
        } catch(...) {
            cout << "invalid input." << endl;
        }
    }
}

void eliminateNegartivity(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] < 0) {
            vec[i] = -vec[i];
        }
    }
}

string add(string a, string b) {
    vector<int> va;
    vector<int> vb;
    int as = a.size();
    int bs = b.size();
    int maxsize = max(as, bs);
    for (int i = a.size(); i > 0; i--) {
        va.push_back(a[i - 1] - '0');
    }
    for (int i = as; i < maxsize; i++) {
        va.push_back(0);
    }
    for (int i = b.size(); i > 0; i--) {
        vb.push_back(b[i - 1] - '0');
    }
    for (int i = bs; i < maxsize; i++) {
        vb.push_back(0);
    }
    string result = "";
    int carry = 0;
    for (int i = 0; i < maxsize; i++) {
        int num = (va[i] + vb[i]) + carry;
        result = to_string(num % 10) + result;
        if (num > 9) {
            carry = 1;
        } else {
            carry = 0;
        }
    }
    if (carry != 0) {
        result = to_string(carry) + result;
    }
    return result;
}

int main()
{
//    cout << "Hello world" << endl;
//    cout << compareString("TV", "tv") << endl;
//    cout << compareString("TV", "tvA") << endl;

    //cout << "test: " << endl;
    // cout << dna("ABC") << endl;
    // cout << dna("atcg") << endl;
    // consoleDemo();

//    vector<int> vec = {-1, 0, 1};
//    eliminateNegartivity(vec);
//    for (int num : vec) {
//        cout << num << ", " << endl;
//    }

    // square();

//    string a = "1";
//    string b = "999";
//    cout << add(a, b) << endl;
//    return 0;

    towerOfHanoi();
}


