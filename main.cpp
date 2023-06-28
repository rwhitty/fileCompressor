#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main() {
    string filepath;
    cout << "Please type the absolute path of your file: ";
    cin >> filepath;
    ifstream file(filepath);
    if (!file.good()) {
        throw invalid_argument("Nonexistent filepath.");
    }
    string text_contents = "";
    string line;
    while (getline(file, line)) {
        text_contents += line;
    }
    cout << text_contents << "\n";
    return 0;
}
