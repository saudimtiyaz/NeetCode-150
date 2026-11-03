#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// intial trial implementation

bool isAnagram(string s, string t) {
    // checking if the sizes are same
    if (s.size() != t.size()) {
        cout << "size is not equal, false";
        return false;
    }

    // using 2 loop to iterate and remove the the common character
    for (int i = 0; i < s.size(); i++){
        int j = 0;
        while (t.size() != 0 && j < t.size()) {
            if (s[i] == t[j]) {
                t.erase(t.begin() + j);
                break;
            }
            j++;
        }
    }
    
    // checking if it returns 0 as we remove all common characters
    if (t.size() == 0){
        cout << "size is equal after loop, return true" << endl;
        return true;
    }
    else {
        cout << "size is not equal, false" << endl;
        return false;
    }
}


// using c style strings to do anagram check (STASHED)

/*
bool isAnagram(string s, string t) {
    // checking if the sizes are same
    if (s.size() != t.size()) {
        cout << "size is not equal, false";
        return false;
    }

    char cstring_s[s.size()], cstring_t[t.size()];
    for (int i = 0; i < s.size(); i++) {
        cstring_s[i] = s[i];
        cstring_t[i] = t[i];
    }

    int s_length = strlen(cstring_s);
    int t_length = strlen(cstring_t);

    sort(cstring_s, cstring_s + s_length);
    sort(cstring_t, cstring_t + t_length);


    if (strcmp(cstring_s, cstring_t) != 0){
        cout << "size is not equal, false" << endl;
        return false;
    }
    else {
        cout << "size is equal after loop, return true" << endl;
        return true;
    }
}
*/

//used O(n logn) sorting algorithm instead of c-style implementation

bool isAnagram(string s, string t) {
    // checking if the sizes are same
    if (s.size() != t.size()) {
        cout << "size is not equal, false";
        return false;
    }

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    for (int i = 0; i < s.size(); i++){
        if (s[i] == t[i]){
            continue;
        }
        return false;
    }
    return true;
}




int main(){
    string s = "racecar";
    string t = "carrace";

    cout << isAnagram(s, t) << endl;

    return 0;
}