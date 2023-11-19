/*
1681. Minimum Incompatibility
*/

// Backtrack 不會超時的寫法
class Solution {
    int res = INT_MAX;
    int k,n;
    vector<bool> visited;
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        this->k = k;
        n = nums.size();
        this-> n = n;
        sort(nums.begin(),nums.end()); //去重
        visited.resize(n);
        //如果某個元素出現了k+1次注定無解
        unordered_map<int,int> map;
        for(auto num:nums){
            map[num]+=1;
            if(map[num] >= k+1) return -1;
        }

        visited[0] = 1;
        backtrack(nums,0,0,1,nums[0],nums[0]);
        return res;
    }
    void backtrack(vector<int>& nums, int cur, int sum, int countNum, int low, int high){

        if(countNum == n/k){
            int j = 0;
            while(j<n && visited[j] == 1) j++;
            if(j == n){
                res = min(res,sum+high-low);
                return;
            }
            else {
                visited[j] = 1;
                backtrack(nums,j,sum+high-low,1,nums[j],nums[j]);
                //未必成功
                visited[j] = 0;
            }
        }
        else{
            for(int i = cur+1; i<nums.size(); i++){
                if(visited[i] == 1) continue;
                if(nums[cur] == nums[i]) continue;
                if(i > cur+1 && visited[i-1] == 0 && nums[i] == nums[i-1]) continue;
                visited[i] = 1;
                backtrack(nums,i,sum,countNum+1,low, nums[i]);
                visited[i] = 0;
            }
        }
    }
};
//會超時的寫法
class Solution {
    int res = INT_MAX;
    int k,n;
    unordered_set<int> set;
    vector<bool> visited;
    int target;
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        this->k = k;
        n = nums.size();
        this-> n = n;
        target = n/k;
        sort(nums.begin(),nums.end()); //去重
        visited.resize(n);
        //如果某個元素出現了k+1次注定無解
        unordered_map<int,int> map;
        for(auto num:nums){
            map[num]+=1;
            if(map[num] >= k+1) return -1;
        }

        
        backtrack(nums,0,0,0,INT_MAX,INT_MIN,0);
        return res;
    }
    void backtrack(vector<int>& nums, int cur, int sum, int countNum, int low, int high,int count){

        if(countNum == target){
            sum+=high-low;
            count+=1;
            set.clear();
            if(count == k){
                res = min(res,sum);
                return;
            }
            else {
                backtrack(nums,0,sum,0,INT_MAX,INT_MIN,count);
            }
        }
        else{
            for(int i = cur; i<nums.size(); i++){
                if(visited[i] == 1) continue;
                if(i && visited[i-1] == 0 && nums[i] == nums[i-1]) continue;
                if(set.find(nums[i]) != set.end()) continue;
                set.insert(nums[i]);
                visited[i] = 1;
                backtrack(nums,i+1,sum,countNum+1,min(low,nums[i]), max(high,nums[i]),count);
                visited[i] = 0;
                set.erase(nums[i]);
            }
        }
    }
};

/*
此題算是698題的follow up 分成k組 但是每一組不能有重複的數字
計算每組最大最小值的差之加總
1. Backtrack
一般backtrack不能用之前的邏輯寫 要稍微換個想法變成 我先挑好一個元素 以選擇 然後從他出發繼續選 
用這種想法可以避免要用一個hash set 去紀錄我選的元素是否包含重複 hash set查找 雖然平均時間為O(1) 但是仍有哈希碰撞可能
最壞時間為O(n)
2.狀態壓縮
轉成二進制 就變成01背包問題 
1代表選 0代表沒選 2^16次方 去選都會是1的支路
m = C(n,n/k) - # of subsets containing duplicates number
state[]
pick k state from state[] s.t union of that equal 1.1.1..1.....11111
find the minimum sum of incompatibility if all k states

dp[i][dpstate] = the minimum sum of incompatibility when pick element form dpstate by considering the first i element

for(int i = 0; i<m; i++){//可選擇的物品 pick from state
    for(int dpstate = 0; dpstate<(1<<n); dpstate++){
    ......
    }
}
*/
