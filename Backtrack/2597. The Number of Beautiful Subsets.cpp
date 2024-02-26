/*
2597. The Number of Beautiful Subsets
*/

// 狀態壓縮 Backtrack TC:O(2^n) SC:O(2^n)
class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        return DFS(nums,k, 0, 0)-1;// 因為包含了空集
    }
    int DFS(vector<int>& nums, int k, int cur, int state){
        if(cur == nums.size()) return 1;

        bool flag = 1;
        for(int i = 0; i < cur; i++){
            
            if(((state>>i)&1) && abs(nums[i] - nums[cur]) == k){
                //用這個方法就不用排序 直接用狀態來判斷
                flag = 0;
                break;
            }
        }
        int take = DFS(nums, k , cur+1, state + (1<<cur));
        int notake = DFS(nums, k, cur+1, state);
        if(flag == 0) return notake;
        else return take + notake;
    }
};

// Backtrack+Hash Map TC:O(2^n) SC:O(2^n)
class Solution {
    int k,n;
    int res = 0;
    unordered_map<int,int> map;
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        //每次取的時候直接查找有沒有小於我k的元素 沒有就取
        n = nums.size();
        this->k = k;
        sort(nums.begin(),nums.end());
        backtrack(nums,0);

        return res-1;// 因為包含了空集
    }
    
    void backtrack(vector<int>& nums, int cur){
        res+=1;
        
        if(cur == n){
            return;
        }
        
        for(int i = cur; i<n; i++){
            if(map[nums[i]-k]) continue;
            map[nums[i]]++;
            backtrack(nums,i+1);
            map[nums[i]]--;

        }
     // 2 3 4 5 9 10   
    }
};



//DP TC:O(n) SC:O(n)
class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        // DP
        int n = nums.size();
        unordered_map<int,int> count;
        //先去重
        for(int i = 0; i<n; i++){
            count[nums[i]]++;
        }
        unordered_map<int, vector<pair<int,int>>> map; // remainder-> val, freq
        for(const auto& [val,freq]: count){
            map[val%k].push_back({val,freq});
        }

        int res = 1;
        for(auto &[r,arr]:map){
            sort(arr.begin(),arr.end());
            int take = 0, notake = 1;//at first we couldn't take any number->0 / we can take nothing->1
            for(int i = 0; i < arr.size(); i++){
                int take_tmp = take, notake_tmp = notake;
                if(i > 0 && abs(arr[i].first - arr[i-1].first) == k){
                    take = notake_tmp * (pow(2, arr[i].second)-1);
                    notake = (take_tmp + notake_tmp)*1;
                }
                else {
                    take = (take_tmp + notake_tmp) * (pow(2, arr[i].second)-1);
                    notake = (take_tmp + notake_tmp)*1;
                }
            }
            res *= (take+notake);
        }

        return res-1;
    }
};


// Multiset + Backtrack TC:O(2^n) SC:O(2^n)
class Solution {
    int res = 0;
    bool visited[25];
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        multiset<int> set;
        for(int i = 0; i < n; i++){
            set.insert(nums[i]);
            visited[i] = 1;
            backtrack(nums, k, i+1, set);
            set.erase(set.find(nums[i]));
            visited[i] = 0;
        }
        
        return res;
    }
    void backtrack(vector<int>& nums, int k, int cur, multiset<int>& set){
        res += 1;
        if(cur == nums.size()) return;
        for(int i = cur; i < nums.size(); i++){
            if(visited[i]) continue;
            if(set.find(nums[i]-k) != set.end()) continue;
            set.insert(nums[i]);
            visited[i] = 1;
            backtrack(nums, k, i+1, set);
            set.erase(set.find(nums[i]));
            visited[i] = 0;
        }
    }
};
/*
對k取模
nums%k  = 0 1 2 3 .... k-1
[0] [1] [2] [3]彼此互相獨立 可互取 所以全部相乘會是取的可能性
重複元素另外計算數量
take[i] =the number of combinations s.t if we take the ith element
notake[i] =the number of combinations s.t if we don't take the ith element
if(abs(nums[i]-nums[i-1]) == k){
    take[i] = notake[i-1]*(2^t-1);//減一檢調都不取的空集合
    notake[i] = (take[i-1]+notake[i-1])*1;
}
else{
    take[i] = (notake[i-1]+take[i-1])*(2^t-1);
    notake[i] = (take[i-1]+notake[i-1])*1;
}
return take[m-1]+notake[m-1];
*/
