/*
2453. Destroy Sequential Targets
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) {
        int n = nums.size();
        unordered_map<int, vector<int>> map; // val -> 集合
        int maxNum = 0;
        for(int i = 0; i < n; i++){
            map[nums[i]%space].push_back(nums[i]);
            if(map[nums[i]%space].size() > maxNum){
                maxNum = map[nums[i]%space].size();
            }
        }

        int res = INT_MAX;
        for(auto &p : map){
            if(p.second.size() == maxNum){
                sort(p.second.begin(), p.second.end());
                res = min(res, p.second[0]);
            }
        }
        
        return res;
    }
};

/*
給一串數字 然後跟你說你可以給這串數字的任意一個數字feed in formula
nums[i] + c * space 任何數字在數組中的滿足這串公司都可以被刪除
c 只能是正數 or 0
問說最低可以feed的數字是多少並且刪除的量最大化
space的概念就會是不管給他任何數字 (他加出來的數字 % 完)都會跟(給的那個數字％space)一樣
所以概念就會是每個數字都去嘗試讓space % 放入map裏面 看裡面的哪個餘數數量最多 就去選這個餘數的最小值
*/
