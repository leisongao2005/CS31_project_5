//
//  main.cpp
//  project_5
//
//  Created by Leison Gao on 11/13/23.
//

#include <iostream>
#include <fstream>

using namespace std;


int main() {
    // output code
    ofstream outfile("/Users/leisongao/desktop/cs31/Projects/project_5/textFiles/results.text");
    // outfile is a name of our choosing.
    if ( ! outfile )// Did the creation fail?
    {
        cerr << "Error: Cannot create results.txt!" << endl;
    }
    outfile << "This will be written to the file" << endl;
    outfile << "2 + 2 = " << 2+2 << endl;
    return 0;
    
    // input code
    ifstream infile("data.txt");    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
    }
    
    // reading char
    char c;
    infile.get(c);
    
    // reading line by line
    const int MAX = ....;
    char line[MAX];
    infile.getline(line, MAX);
    
    // reading entire file
    while ( infile.getline(line, MAX) )
    {
        ... process line
    }
}
