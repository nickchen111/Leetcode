/*
1535. Find the Winner of an Array Game
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        int count = 0;
        int curMax = arr[0];
        for(int i = 1; i<n; i++){
            if(curMax > arr[i]){
                count += 1;
            }
            else{
                count = 1;
                curMax = arr[i];
            }
            
            if(count == k) return curMax;
        }

        return curMax;
    }
};
