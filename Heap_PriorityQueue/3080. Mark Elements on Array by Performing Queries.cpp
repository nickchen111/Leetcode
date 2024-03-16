/*
3080. Mark Elements on Array by Performing Queries
*/

// TC:O(nlgn + 2*n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        vector<LL> res(queries.size());
        
        LL sum = accumulate(nums.begin(), nums.end(), 0LL);
        
        unordered_set<int> index; // 尚未被選取的index
        
        std::multiset<pair<int,int>> set; // 從小到大
        for(int i = 0; i < nums.size(); i++){
            set.insert({nums[i],i});
            index.insert(i);
        }
        bool flag = 0;
        for(int i = 0; i < queries.size(); i++){
            int a = queries[i][0];
            int b = queries[i][1];
            if(index.find(a) != index.end()){
                sum -= nums[a];
                index.erase(a);
                set.erase(set.find({nums[a],a}));
            }
            
            if(set.size() >= b){
                for(int j = 0; j < b; j++){
                    sum -= set.begin()->first;
                    int e = set.begin()->second;
                    index.erase(e);
                    set.erase(set.begin());
                }
            }
            else {
                sum = 0;
                set.clear();
                flag = 1;
            }
            
            res[i] = sum;
            if(flag) break;
            
        }
        
        return res;
        
        
    }
};

/*
要按照牠的query順序mark index並且還要去選最小的幾個數字mark 然後問剩下的元素sum 為多少
set 去裝 尚未被填入的index 然後每一次被選到就去扣掉他的數字數值
用一個multiset容器自動排序 再用一個數組紀錄目前想刪除的index是否存在 存在的話set那邊也要相對應更改 在檢查最小值的時候反之亦然
*/
