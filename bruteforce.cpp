#include <iostream>
#include <vector>
using namespace std;

const string password = "tiago";

struct Settings {
    int fixedSize;
    int maxSize;
    vector<int> alphabet;
    Settings() : maxSize(8) {}
};

Settings getOptions(void);
void generatePasswords(Settings& opt);
void bruteForce(Settings& settings, int idx, string& partialString);

int main() {
    Settings opt = getOptions();
    generatePasswords(opt);
    return 0;
}

Settings getOptions() {
    Settings ret;
    string input;
    do {
        cout << "Fixed size? [y/n]: ";
        cin >> input;
    } while (input != "y" and input != "n");
    if (input == "n")
        ret.fixedSize = -1;
    if (ret.fixedSize != -1) {
        do {
            cout << "Size: ";
            cin >> ret.fixedSize;
        } while (ret.fixedSize < 0);
        ret.maxSize = ret.fixedSize;
    }
    do {
        cout << "Small letters? [y/n]: ";
        cin >> input;
    } while (input != "y" and input != "n");
    if (input == "y") {
        for (int ch = 'a'; ch <= 'z'; ch++)
            ret.alphabet.push_back(ch);
    }
    do {
        cout << "Capital letters? [y/n]: ";
        cin >> input;
    } while (input != "y" and input != "n");
    if (input == "y") {
        for (int ch = 'A'; ch <= 'Z'; ch++)
            ret.alphabet.push_back(ch);
    }
    do {
        cout << "Numbers? [y/n]: ";
        cin >> input;
    } while (input != "y" and input != "n");
    if (input == "y") {
        for (int ch = '0'; ch <= '9'; ch++)
            ret.alphabet.push_back(ch);
    }
    return ret;
}

void bruteForce(Settings& settings, int idx, string& partialString) {
    if (idx == settings.fixedSize or idx == settings.maxSize) {
        if (partialString == password) {
            cout << "Password cracked: " << partialString << endl;
            exit(0);
        }
        return;
    } else if (settings.fixedSize == -1) {
        if (partialString == password) {
            cout << "Password cracked: " << partialString << endl;
            exit(0);
        }
    }
    for (int i = 0; i < (int)settings.alphabet.size(); i++) {
        partialString.push_back(settings.alphabet[i]);
        bruteForce(settings, idx+1, partialString);
        partialString.pop_back();
    }
}

void generatePasswords(Settings& settings) {
    string partialString = "";
    bruteForce(settings, 0, partialString);
}
