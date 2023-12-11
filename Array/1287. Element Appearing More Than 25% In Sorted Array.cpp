/*
1287. Element Appearing More Than 25% In Sorted Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return arr[0];
        int freq = n/4;
        int count = 1;
        for(int i = 1; i < n; i++){
            if(arr[i] == arr[i-1]) count++;
            else count = 1;
            
            if(count > freq) return arr[i];
        }

        return -1;
    }
};
