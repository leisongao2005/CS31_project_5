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

int getWord(istream& inf, char word[]);

int render(int lineLength, istream& inf, ostream& outf) {
    if (lineLength < 1) {
        return 2;
    }
    const int MAX = 10000;
    char line[MAX];
    for (;;)
    {
        int val = getWord(inf, line);
        if (val == 1) {
            break;
        }
        else {
            if (line[0] == '@' && line[1] =ç= 'P' && line[2] == '@' && line[3] == '\0') {
                outf << "paragraph written" << endl;
            }
            else {
                for (int i = 0; line[i] != '\0'; i ++) {
                    outf << line[i];
                }
            }
        }
    }
    return 0;
}

int getWord(istream& inf, char word[]) {
    char c;
    int i = 0;
    while (inf.get(c)) {
        if (!isspace(c)) {
            word[i] = c;
        }
        else {
            word[i] = '\0';
            return 0; // reached end of word
        }
        i ++;
    }
    return 1; // reached end of file
}

int main () {
    ofstream outfile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/ref.text");
    // outfile is a name of our choosing.
    if ( ! outfile )// Did the creation fail?
    {
    cerr << "Error: Cannot create results.txt!" << endl;
    }
    outfile << "This will be written to the file" << endl;
    outfile << "2 + 2 = " << 2+2 << endl;

    // input code
    ifstream infile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/results.text");    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
    cerr << "Error: Cannot open data.txt!" << endl;
    }
    
    const int MAX = 10000;
    char line[MAX];
    getWord(infile, line);
    cout << "Word: ";
    for (int i = 0; line[i] != '\0'; i ++) {
        cout << line[i];
    }
    getWord(infile, line);
    cout << '.' << endl << "Word: ";
    for (int i = 0; line[i] != '\0'; i ++) {
        cout << line[i];
    }
    cout << '.' << endl;
    
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
