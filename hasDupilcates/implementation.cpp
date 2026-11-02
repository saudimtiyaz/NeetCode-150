#include <iostream>
#include <vector>

using namespace std;


// novice implementation
bool hasDuplicate(vector<int>& nums){
    for (int i = 0; i < nums.size(); i++){
        for (int j = 1; j < nums.size(); j++){
            if ((nums[i] == nums[j]) && (i != j)){
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<int> nums1 = {1,2,3,1};
    cout << hasDuplicate(nums1) << endl;

    vector<int> nums2 = {1,2,3,4};
    cout << hasDuplicate(nums2) << endl;

    return 0;
}