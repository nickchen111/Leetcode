/*
1460. Make Two Arrays Equal by Reversing Subarrays
*/

// Set : TC:O(n) SC:O(n)
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& A) {
        return unordered_multiset<int>(A.begin(), A.end()) == unordered_multiset<int>(target.begin(),target.end());
    }
};

// Sort TC:O(nlgn) SC:O(1)
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        sort(target.begin(), target.end());
        sort(arr.begin(), arr.end());
        for(int i = 0; i < target.size(); i++){
            if(arr[i] != target[i]) return false;
        }

        return true;
    }
};
