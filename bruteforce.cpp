#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <openssl/sha.h>
using namespace std;

#define MAXSIZE 256

int len;
unsigned char password[] = "tiago";
unsigned char pswdHash[MAXSIZE];
unsigned char hash[MAXSIZE];

struct Settings {
    int fixedSize;
    int maxSize;
    vector<int> alphabet;
    Settings() : maxSize(8) {}
};

string getInput(const string& msg);
Settings getOptions(void);
int strequals(const unsigned char* a, const char* b);
void bruteForce(Settings& settings, int idx);
void generatePasswords(Settings& opt);

int main() {
    SHA1(password, sizeof(password)-1, pswdHash);
    printf("%s\n", pswdHash);
    return 0;
    Settings opt = getOptions();
    generatePasswords(opt);
    return 0;
}

string getInput(const string& msg) {
    string input;
    do {
        cout << msg;
        cin >> input;
    } while (input != "y" and input != "n");    
    return input;
}

Settings getOptions() {
    Settings ret;
    if (getInput("Fixed size? [y/n]: ") == "n")
        ret.fixedSize = -1;
    if (ret.fixedSize != -1) {
        do {
            cout << "Size: ";
            cin >> ret.fixedSize;
        } while (ret.fixedSize < 0);
        ret.maxSize = ret.fixedSize;
    }
    if (getInput("Small letters? [y/n]: ") == "y")
        for (int ch = 'a'; ch <= 'z'; ch++)
            ret.alphabet.push_back(ch);
    if (getInput("Capital letters? [y/n]: ") == "y")
        for (int ch = 'A'; ch <= 'Z'; ch++)
            ret.alphabet.push_back(ch);
    if (getInput("Numbers? [y/n]: ") == "y")
        for (int ch = '0'; ch <= '9'; ch++)
            ret.alphabet.push_back(ch);
    return ret;
}

unsigned char partialString[MAXSIZE];

int strequals(const unsigned char* a, const char* b) {
    while (*a and *b) {
        if (*a != *b) return 0;
        a++, b++;
    }
    return !(*a) and !(*b); 
}

void generatePasswords(Settings& settings) {
    bruteForce(settings, 0);
    cout << "Password not found" << endl;
}

void bruteForce(Settings& settings, int idx) {
    if (idx == settings.fixedSize or idx == settings.maxSize) {
        partialString[idx] = 0;
        SHA1(partialString, idx, hash);
        if (strequals(hash, pswdHash)) {
            cout << "Password cracked: " << partialString << endl;
            exit(0);
        }
        return;
    } else if (settings.fixedSize == -1) {
        SHA1(partialString, idx, hash);
        if (strequals(hash, pswdHash)) {
            partialString[idx] = 0;
            cout << "Password cracked: " << partialString << endl;
            exit(0);
        }
    }
    for (int i = 0; i < (int)settings.alphabet.size(); i++) {
        partialString[idx] = settings.alphabet[i];
        // if (partialString[idx] == password[idx]) cout << password[idx] << endl;
        bruteForce(settings, idx+1);
    }
}

