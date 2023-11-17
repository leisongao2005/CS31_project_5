//
//  main.cpp
//  project_5
//
//  Created by Leison Gao on 11/13/23.
//

#include <iostream>
#include <fstream>
#include <cctype>
// extra test code
    #include <sstream>
    #include <streambuf>
    #include <cstring>
    #include <cassert>

using namespace std;

int getWord(int lineLength, int& pos, istream& inf, char word[], bool& doubleEnd, int& length);
int render(int lineLength, istream& inf, ostream& outf);
int writeFile(ostream& outf, char word[], int val, bool& startLine, bool addDouble, int& pos, int len, bool& hyp);

int render(int lineLength, istream& inf, ostream& outf) {
    if (lineLength < 1) {
        return 2;
    }
    const int MAX = 10000;
    char word[MAX];
    bool doubleEnd = false;
    bool addDouble = false;
    bool startLine = true;
    int pos = 0;
    int len;
    bool hyp = false;
    bool overflow = false;
    for (;;)
    {
        len = 0;
        doubleEnd = false;
        int val = getWord(lineLength, pos, inf, word, doubleEnd, len);
        
//        cerr << "Word: " << word << "| next pos: " << pos << "| val : " << val << addDouble << endl;
        if (val == 1) {
//            cerr << "out of words" << endl;
            writeFile(outf, word, val, startLine, addDouble, pos, len, hyp);
            outf << '\n';
            if (overflow == true)
                return 1;
            return 0; // out of words
        }
        else if (val == 2) {
            overflow = true;
            writeFile(outf, word, val, startLine, addDouble, pos, len, hyp);
        }
        else if (val == 4) {
            writeFile(outf, word, val, startLine, addDouble, pos, len, hyp);
            hyp = true;
        }
        else {
            writeFile(outf, word, val, startLine, addDouble, pos, len, hyp);
        }
        
        addDouble = doubleEnd;
    }
    return 0;
}

int writeFile(ostream& outf, char word[], int val, bool& startLine, bool addDouble, int& pos, int len, bool& hyp) {
    // need to know ending of previous word to add whitespace before
    bool hypp = false;
    if (hyp) {
        hypp = true;
        hyp = false;
    }
    if (word[0] == '@' && word[1] == 'P' && word[2] == '@' && word[3] == '\0') {
        outf << '\n' << '\n';
        pos = 0;
        startLine = true;
    }
    else if (val == 2 || val == 3) {
        // if word overflows line
        if (!startLine) {
            outf << '\n';
        }
        for (int i = 0; word[i] != '\0'; i ++) {
            outf << word[i];
        }
        startLine = false;
        pos = len; // need to change position to new word length
        if (val == 2) {
            // maxline case, create newline
            outf << '\n'; // necessary endline
            startLine = true;
        }
    }
    else {
        // checking for hyphen case
        if (word[0] == '\0') {
            return 0;
        }
        
        if (startLine) {
            startLine = false;
        }
        else {
            // add whitespace after previous word
            if (addDouble) {
                outf << ' ' << ' ';
                pos += 2;
            }
            else if (!hypp){
                outf << ' ';
                pos ++;
            }
            else {
                hyp = false;
            }
        }
        // print word to line
        for (int i = 0; word[i] != '\0'; i ++) {
            outf << word[i];
        }
    }
    return 0;
}

int getWord(int lineLength, int& pos, istream& inf, char word[], bool& doubleEnd, int& length) {
    char c;
    int i = 0;
    char prevc = '\0';
    bool lineOverflow = false;
    int len = 0;
    int offset = 0;
    if (doubleEnd) {
        offset = 2;
    }
    else {
        offset = 1;
    }
    while (inf.get(c)) {
        if (i > lineLength - pos - offset){
            // word won't fit on rest of line, but not at max yet
            // keep on reading until max line lenght
            lineOverflow = true;
        }
        if (i == lineLength - 1) {
            // word will fit max line
            word[i] = c;
            word[i + 1] = '\0';
            doubleEnd = false;
            return 2;
        }
        
        if (!isspace(c)) {
            word[i] = c;
            len ++;
            // checking for word portions, need to deal with case of individual hyphen
            if (word[i] == '-') {
                word[i + 1] = '\0';
                doubleEnd = false;
                pos += len;
                length = len;
                if (lineOverflow) {
                    return 3;
                }
                return 4;
            }
            prevc = c;
        }
        else {
            word[i] = '\0';
            if (prevc == '.' || prevc == '?' || prevc == '!' || prevc == ':') {
                doubleEnd = true;
            }
            else {
                doubleEnd = false;
            }
            pos += len;
            length = len;
            if (lineOverflow) {
                return 3;
            }
            return 0; // reached end of word
        }
        i ++;
    }
    word[i] = '\0';
    return 1; // reached end of file
}
//
//int main () {
//    ofstream outfile("/Users/leisongao/Desktop/cs31/project_5/textFiles/results.text");
////    ofstream outfile("results.text");     // g31 code
//    if ( ! outfile )// Did the creation fail?
//    {
//    cerr << "Error: Cannot create results.txt!" << endl;
//    }
//
//    // input code
//    ifstream infile("/Users/leisongao/Desktop/cs31/project_5/textFiles/ref.text");
////    ifstream infile("ref.text");    // g31 code
//    if ( ! infile )                // Did opening the file fail?
//    {
//    cerr << "Error: Cannot open data.txt!" << endl;
//    }
//    
////    outfile << "Testing it\n";
//    
//    int len = 6;
//    render(len, infile, outfile);
//}

void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput) {
        cerr << "WRONG RESULT FOR: " << input << endl;
        for (int i = 0; i < oss.str().size(); i++) {
            if (oss.str()[i] != expectedOutput[i]) {
                cerr << "ERROR AT POSITION: " << i << "EXPECTED: " << expectedOutput[i] << " INSTEAD OF " << oss.str()[i] << endl;
            }
        }
    }
}

int main()
{
    testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
    testRender(8, "  This is a test  \n", "This is\na test\n", 0);
    testRender(6, "Testing it\n", "Testin\ng it\n", 1);
    testRender(-5, "irrelevant", "irrelevant", 2);
    cerr << "Tests complete" << endl;
}
