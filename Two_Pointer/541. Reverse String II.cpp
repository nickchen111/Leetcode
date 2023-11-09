/*
541. Reverse String II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for(int i =0; i<n; i+=2*k){
            int left = i;
            int right = min(n-1,left+k-1);
            while(left < right){
                swap(s[left],s[right]);
                left++;right--;
            }
        }
        
        return s;
    }
};
