/*
128. Longest Consecutive Sequence
*/


//我最剛開始用hash mpa解法 TC:O(n) SC:O(n)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        map<int,int> map;
        int n = nums.size();
        if(n == 0) return 0;
        for(int i = 0; i<n; i++){
            if(map.count(nums[i]) > 0) continue;
            map[nums[i]]++;
        }

        int res = 1;
        int prev = INT_MIN/2;
        int cur = INT_MIN/2;
        int count = 1;
        for(auto p:map){
            prev = cur;
            cur = p.first;
            if(cur == prev+1){
                count++;
                res = max(res,count);
            }
            else{
                count = 1;
            }
        }

        return res;
    }
};

// Union_Find TC:O(n)數據差一點的話會變成nlgn SC(3*n)
class Solution {
    //union-find
    //因為此題不曉得會到多大 所以用public的 hash map來代替 
    unordered_map<int,int> parent;

    int findParent(int x){
        if(x !=parent[x]){
            parent[x] = findParent(parent[x]);
        }
        return parent[x];
    }
    void union_(int x, int y){
        int rootx = findParent(x);
        int rooty = findParent(y);
        if(rootx > rooty){
            parent[rooty] = rootx;
        }
        else if(rootx < rooty) parent[rootx] = rooty;
    }
    
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> nums2; //去重

        for(int i = 0; i<n; i++){
            int cur = nums[i];
            nums2.insert(nums[i]);
            if(parent.find(cur) == parent.end()){
                parent[cur] = cur;
            }
            if(parent.find(cur-1) != parent.end() && findParent(cur-1) != findParent(cur)){
                union_(cur,cur-1);
            }
            if(parent.find(cur+1) != parent.end() && findParent(cur+1) != findParent(cur)){
                union_(cur,cur+1);
            }
        }
        //狀態壓縮 空間壓縮 確保不會有 x->y->z<-w 這種, 扁平化管理
        for(int x:nums2){
            parent[x] = findParent(x);
        }

        unordered_map<int,int> count;
        //相同的parent++ 
        for(int x:nums2){
            count[parent[x]]++;
        }

        int res = 0;
        for(auto a:count){
            res = max(res,a.second);
        }

        return res;

    }
};

//最優解 set+greedy TC:O(n) SC:O(n)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set(nums.begin(), nums.end());//去重 跟方便之後查找
        int res = 0;
        for(auto x:set){
            if(set.find(x-1) != set.end()) continue;
            int count = 1;
            while(set.find(x+1) != set.end()){
                count++;
                x++;
            }
            res = max(res, count);
        }

        return res;
    }
};

/*
"1. 最爛解法 排序 nlgn
2. union find 
3. hash map 我最剛開始的解法
4. 類似貪心的解法 搜索元素 都找頭 然後藉由set底層邏輯是紅黑是或是哈西表 來快速查找下一個數 
union find:
考點:
1. 大小未知情況下直接寫出各自的union find函式
2. 用hash map替代 vector<int> 來充當parent 方便快速查找"
*/
