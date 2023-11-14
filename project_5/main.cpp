//
//  main.cpp
//  project_5
//
//  Created by Leison Gao on 11/13/23.
//

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int getWord(int lineLength, int& pos, istream& inf, char word[], bool& doubleEnd);
int render(int lineLength, istream& inf, ostream& outf);
int writeFile(int lineLength, ostream& outf, char word[], int val, bool& startLine, bool addDouble, int& pos);

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
    for (;;)
    {
        int val = getWord(lineLength, pos, inf, word, doubleEnd);
        cerr << "Word: " << word << "| ending at pos: " << pos << endl;
        if (val == 1) {
            return 1; // out of words
        }
        else {
            writeFile(lineLength, outf, word, val, startLine, addDouble, pos);
        }
        addDouble = doubleEnd;
    }
    return 0;
}

int writeFile(int lineLength, ostream& outf, char word[], int val, bool& startLine, bool addDouble, int& pos) {
    // need to know ending of previous word to add whitespace before
    if (word[0] == '@' && word[1] == 'P' && word[2] == '@' && word[3] == '\0') {
//        cerr << "paragraph written" << endl;
        outf << '\n';
        pos = 0;
    }
    else if (val == 2 || val == 3) {
        // if word overflows line
//        cerr << endl << "Overflow Word: ";
        if (pos > lineLength) {
            outf << '\n';
            startLine = false;
            pos = 0;
        }
        for (int i = 0; word[i] != '\0'; i ++) {
            outf << word[i];
        }
        if (val == 2) {
            // maxline case, create newline
            outf << '\n'; // necessary endline
            startLine = true;
            pos = 0;
        } // necessary endline
//        cerr << endl; // just to visualize tokens
    }
    else {
        // checking for hyphen case
        if (word[0] == '\0') {
            return 0;
        }
        
        if (startLine) {
//            cerr << "First Word: ";
            startLine = false;
        }
        else {
//            cerr << "Word: ";
            // add whitespace after previous word
            if (addDouble) {
                outf << "**";
                pos += 2;
            }
            else {
                outf << "*";
                pos ++;
            }
//            cerr << "pos: " << pos;
        }
        // print word to line
        for (int i = 0; word[i] != '\0'; i ++) {
            outf << word[i];
        }
//        cerr << endl;
        
    }
    return 0;
}

int getWord(int lineLength, int& pos, istream& inf, char word[], bool& doubleEnd) {
    char c;
    int i = 0;
    char prevc = '\0';
    bool lineOverflow = false;
    int len = 0;
    while (inf.get(c)) {
        if (i >= lineLength - pos - 1){
            // word won't fit on rest of line, but not at max yet
            // keep on reading until max line lenght
//            if (!lineOverflow)
//                cerr << endl << endl << "overflowed line" << endl;
            lineOverflow = true;
        }
        if (i == lineLength - 1) {
            // word will fit max line
            word[i] = c;
            word[i + 1] = '\0';
            doubleEnd = false;
            if (lineOverflow) {
                // max line length and
                return 3;
            }
            else {
                // max line length
                return 2;
            }
        }
        
        if (!isspace(c)) {
            word[i] = c;
            len ++;
            // checking for word portions, need to deal with case of individual hyphen
            if (word[i] == '-') {
                word[i + 1] = '\0';
                doubleEnd = false;
                pos += len;
                if (lineOverflow) {
                    return 3;
                }
                return 0;
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
            if (lineOverflow) {
                return 3;
            }
            return 0; // reached end of word
        }
        i ++;
    }
    return 1; // reached end of file
}

int main () {
    ofstream outfile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/results.text");
    // outfile is a name of our choosing.
    if ( ! outfile )// Did the creation fail?
    {
    cerr << "Error: Cannot create results.txt!" << endl;
    }
//    outfile << "This will be written to the file" << endl;
//    outfile << "words, words, words, @P@ more words" << endl;
//    outfile << "2 + 2 = " << 2+2 << endl;

    // input code
    ifstream infile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/ref.text");    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
    cerr << "Error: Cannot open data.txt!" << endl;
    }
    
    int len = 30;
//    cout << "Input line length: ";
//    cin >> len;
    render(len, infile, outfile);
}
//int main() {
//    // output code
//    ofstream outfile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/results.text");
//    // outfile is a name of our choosing.
//    if ( ! outfile )// Did the creation fail?
//    {
//        cerr << "Error: Cannot create results.txt!" << endl;
//    }
//    outfile << "This will be written to the file" << endl;
//    outfile << "2 + 2 = " << 2+2 << endl;
//    return 0;
//    
//    // input code
//    ifstream infile("data.txt");    // infile is a name of our choosing
//    if ( ! infile )                // Did opening the file fail?
//    {
//        cerr << "Error: Cannot open data.txt!" << endl;
//    }
//    
//    // reading char
//    char c;
//    infile.get(c);
//    
//    // reading line by line
//    const int MAX = ....;
//    char line[MAX];
//    infile.getline(line, MAX);
//    
//    // reading entire file
//    while ( infile.getline(line, MAX) )
//    {
//        ... process line
//    }
//}

//int main()
//{
//    const int MAX_FILENAME_LENGTH = 100;
//    for (;;)
//    {
//        cout << "Enter input file name (or q to quit): ";
//        char filename[MAX_FILENAME_LENGTH];
//        cin.getline(filename, MAX_FILENAME_LENGTH);
//        if (strcmp(filename, "q") == 0)
//            break;
//        ifstream infile(filename);
//        if (!infile)
//        {
//            cerr << "Cannot open " << filename << "!" << endl;
//            continue;
//        }
//        cout << "Enter maximum line length: ";
//        int len;
//        cin >> len;
//        cin.ignore(10000, '\n');
//        int returnCode = render(len, infile, cout);
//        cout << "Return code is " << returnCode << endl;
//    }
//}
