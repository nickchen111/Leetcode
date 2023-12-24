/*
2974. Minimum Number Game
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        vector<int> arr;
        int n = nums.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n; i++){
            pq.push(nums[i]);
        }
        
        while(!pq.empty()){
            vector<int> temp;
            for(int i = 0; i < 2; i++){
                int minVal = pq.top();
                pq.pop();
                temp.push_back(minVal);
            }
            for(int i = 1; i >= 0; i--){
                arr.push_back(temp[i]);   
            }
        }
        
        return arr;
    }
};

/*
此題說Alice Bob輪流拿最小的數字 並且改變順序由包伯先放數字在另一個數組
輸出數組為何  

*/
