#include <iostream>
#include <algorithm>

using namespace std;

/*
Recommended Time & Space Complexity
You should aim for a solution with O(n) time and O(n) space, where n is the size of the input array.
*/


// time is O(n^2) and space is O(1).
vector<int> twoSum(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size(); j++) {
            if ((nums[i] + nums[j] == target) && (i !=j)) {
                vector<int> output(2);
                output[0] = i;
                output[1] = j;
                return output;
            }
        }
    }
    return {};
}


// two-pointer method (adapted from twoDifference question into twoSum)
vector<int> twoSum(vector<int>& nums, int target) {
    vector<pair<int, int>> arr;

    for (int k = 0; k < nums.size(); k++) {
        arr.push_back({nums[k], k});
    }

    sort(arr.begin(), arr.end());

    int i = 0, j = arr.size() - 1;

    while (i < j) {
        if (arr[i].first + arr[j].first == target) {
            return {min(arr[i].second, arr[j].second), 
                    max(arr[i].second, arr[j].second) 
            };
        }
        else if (arr[i].first + arr[j].first < target) {
            i++;
        }
        else {
            j--;
        }
    }

    return {};
}

// using hashmaps, instead of populating hashmap ahead, we do it when scanning,
// it can only be done, if we are guarnteed to have a pair of int that sum upto target.

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> output_map;

    for (int i = 0; i < nums.size(); i++) {
        int difference = target - nums[i];

        if (output_map.find(difference) != output_map.end()) {
            return {output_map[difference], i};
        }
        output_map[nums[i]] = i;
    }

    return {};
}



int main(){
    vector<int> nums1 = {3,4,5,6};
    vector<int> nums2 = {4,5,6};
    vector<int> output;

    output = twoSum(nums1, 7);
    cout << output[0] << endl;
    cout << output[1] << endl << endl;

    output = twoSum(nums2, 10);
    cout << output[0] << endl;
    cout << output[1] << endl;

    return 0;
}