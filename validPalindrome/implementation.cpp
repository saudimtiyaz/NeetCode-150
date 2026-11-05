#include <iostream>
#include <string>

using namespace std;

/*
Valid Palindrome
Given a string s, return true if it is a palindrome, otherwise return false.

A palindrome is a string that reads the same forward and backward. It is also case-insensitive and ignores all non-alphanumeric characters.

Note: Alphanumeric characters consist of letters (A-Z, a-z) and numbers (0-9).
*/

/*
bool isPalindrome(string s) {
    int i = 0, j = s.length();
    while ( i <= j ){
        if (s[i] == ' ') {
            i++;
        } else if (s[j] == ' ') {
            j--;
        }
        
        if (s[i] != s[j] and i != j) {
            return false;
        } else {
            i++;
            j--;
        }
    }
    return true;
}
*/

/*
bool isPalindrome(string s) {
    string new_string;
    int index = 0;
    for (int i = 0; i < s.length(); i++){
        if (s[i] != ' ') {
            new_string[index] = s[i];
            index++;
        }
    }       
    
    cout << new_string << endl;

    int i = 0, j = new_string.length();
    while (i <= j) {
        if (new_string[i] != new_string[j]) {
            return false;
        }
        i++; j--;
    }
    return true;
}
*/

// using hint1:
/*
bool isPalindrome(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (isupper(s[i])) {
            s[i] = tolower(s[i]);
        }

        if (!islower(s[i])) {
            s[i] = ' ';
        }
    }

    string new_string;

    for (int i = s.length() - 1; i >= 0; i--){
        new_string.push_back(s[i]);
    }

    for (int i = 0; i < s.length(); i++){
        if (s[i] != new_string[i]) {
            return false;
        }
    }

    return true;
}
*/

bool isPalindrome(string s) {
    int i = 0;
    int j = s.length() - 1;

    while (i < j) {
        if (!isalnum(s[i])) {
            i++;
            continue;
        }

        if (!isalnum(s[j])) {
            j--;
            continue;
        }

        if (tolower(s[i]) != tolower(s[j])) {
            return false;
        }

        i++;
        j--;
    }

    return true;
}



int main() {
    string s1 = "Was it a car or a cat I saw?";
    cout << isPalindrome(s1) << endl;

    string s2 = "tab a cat";
    cout << isPalindrome(s2) << endl;

    return 0;
}