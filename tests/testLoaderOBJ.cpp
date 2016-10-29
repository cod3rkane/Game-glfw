#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    // Read file text mode
    // ifstream stall("../assets/Models/stall.obj");
    // Read file in binary mode
    ifstream stallBin("../assets/Models/stall.obj", ios::binary);

    const int Max = 80;
    char buff[Max];
    vector<string> tokens;
    string currLine;
    string delimiter = "/";
    size_t found;

    while (!stallBin.eof()) {
        stallBin.getline(buff, Max);
        currLine = buff;

        istringstream strToSplit(currLine);
        // split str in space
        for (string s; strToSplit >> s;) {
            tokens.push_back(s);
        }

        if (tokens[0] == "v") {
            cout << "its :v:" << endl;
            cout << tokens[1] << " : " << stof(tokens[1]) << endl;
        } else if (tokens[0] == "vt") {
            cout << "its :vt:" << endl;
        } else if (tokens[0] == "vn") {
            cout << "its :vn:" << endl;
        } else if (tokens[0] == "f") {
            cout << "its :f:" << endl;
            for (int i = 1; i < tokens.size(); i++) {
                cout << tokens[i] << endl;
                while (tokens[i].find(delimiter) != string::npos) {
                    found = tokens[i].find(delimiter);
                    tokens[i].replace(found, 1, " ");
                }

                cout << tokens[i] << endl;
            }
        }

        tokens.clear();
    }

    return 0;
}
