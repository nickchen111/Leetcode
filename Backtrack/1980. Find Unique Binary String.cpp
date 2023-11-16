/*
1980. Find Unique Binary String
*/

// TC:O(2^n) S:O(2^n + n)
class Solution {
    string res = "";
    unordered_set<string> set;
public:
    string findDifferentBinaryString(vector<string>& nums) {
        //Backtrack
        int n = nums.size();
        vector<vector<int>> arr(n,vector<int>({0,1}));
        for(int i = 0; i<n; i++){
            set.insert(nums[i]);
        }
        string track = "";
        backtrack(nums,arr,0,track);
        return res;
    }

    void backtrack(vector<string>& nums,vector<vector<int>>& arr, int cur, string& track){
        int n = nums.size();
        if(track.size() == n && set.find(track) == set.end()){
            res = track;
            return;
        }

        if(res != "") return;
        if(track.size() == n) return;

        for(int i = cur; i<n; i++){
            for(int j = 0; j<2; j++){
                track+=to_string(arr[i][j]);
                backtrack(nums,arr,i+1,track);
                track.pop_back();
            }
        }
    }
};
