/*
1980. Find Unique Binary String
*/

// 2025.02.20 TC:O(n * 2^n) SC:O(n^2)
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        unordered_set<string> numSet(nums.begin(), nums.end());
        int mask = (1 << n) - 1;
        int submask = mask;

        while (submask >= 0) { 
            string s = bitset<16>(submask).to_string().substr(16 - n);
            if (numSet.find(s) == numSet.end()) {
                return s;
            }
            int newmask = (submask - 1) & mask;
            if(submask == newmask) break;
            submask = newmask;
        }
        return "";
    }
};

class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        unordered_set<string> numSet(nums.begin(), nums.end());
        string ans;
        string s;
        auto backtrack = [&](auto &&backtrack,string& s) -> void {
            if(ans.size() > 0) return;
            if(s.size() == n && numSet.find(s) == numSet.end()) {
                ans = s;
                return;
            }
            if(s.size() == n) return;
            s += "0";
            backtrack(backtrack, s);
            s.pop_back();
            s += "1";
            backtrack(backtrack, s);
            s.pop_back();
        };
        backtrack(backtrack, s);
        return ans;
    }
};



//
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
