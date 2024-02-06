/*
2808. Minimum Seconds to Equalize a Circular Array
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i < n; i++){
            nums.push_back(nums[i]);
        }

        n = nums.size();

        unordered_map<int, vector<int>> pos;
        for(int i = 0; i < n; i++){
            pos[nums[i]].push_back(i);
        }

        int res = INT_MAX;
        for(auto p : pos){
            p.second.insert(p.second.begin(), 0);
            p.second.push_back(n-1);
            int m = p.second.size();
            int res_tmp = 0;
            for(int i = 1; i < m; i++){
                res_tmp = max(res_tmp, (p.second[i] - p.second[i-1])/2);
            }

            res = min(res, res_tmp);
        }

        return res;
    }
};

/*
數組內的元素可以做自己跟自己換或者跟前一個換 可循環數組 或者跟下一個換
問說最少換幾次可以讓所有元素相同
[3 3 3 3 3 3 3 3 3] 4次
[1 2 3 3 4 5 6 7 8]
會希望頻率最高的數字可以一次影響多一點數字
頻率較多然後比較分散的最好 結論好難下手要怎麼找哪個影響的最快 那我就每個都試試看啦
[8,8,9,10,9] - > 0[2 4 7 9]9
[8,8,9,10,9 8 8 9 10 9] 0[0 1 5 6]9
2 x x x x x 8
*/
