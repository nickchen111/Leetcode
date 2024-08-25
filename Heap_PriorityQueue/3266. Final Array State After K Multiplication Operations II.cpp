/*
3266. Final Array State After K Multiplication Operations II
*/


// C++20 寫法 TC:O(nlgM) M為齊頭式增長時取出的次數，每一個數字最多被取出31次所以是lg31n SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    long long pow(long long x, long long n) {
        if (n == 0) {
            return 1;
        }
        LL y = pow(x, n / 2) % M;
        if(n%2){
          return (y*y%M)*x%M;
        }
        else return y*y%M;
    }
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        int n = nums.size();
        if (multiplier == 1) { // 数组不变
            return nums;
        }
        
        
        vector<pair<LL, int>> h;
        for(int i = 0; i < n; i++){
            h.emplace_back(nums[i], i);
        }
        
        int maxVal = ranges::max(nums);
        ranges::make_heap(h, greater<>());
        for(; k && h[0].first < maxVal; k--){
            ranges::pop_heap(h, greater<>()); // 將最小的那項數值放到陣列最後面來
            h.back().first *= multiplier; 
            ranges::push_heap(h, greater<>()); // 將最後面那項元素重新加入堆中
        }
        
        for (int i = 0; i < n; i++) {
            ranges::pop_heap(h, greater<>());
            auto [x, j] = h.back();
            h.pop_back();
            nums[j] = x % M * pow(multiplier, k / n + (i < k % n)) % M;
        }
        return nums;
    }
};

// TC:O(nlgM) M為齊頭式增長時取出的次數，每一個數字最多被取出31次所以是lg31n SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    long long pow(long long x, long long n) {
        if (n == 0) {
            return 1;
        }
        LL y = pow(x, n / 2) % M;
        if(n%2){
          return (y*y%M)*x%M;
        }
        else return y*y%M;
    }
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        int n = nums.size();
        if (multiplier == 1) { // 数组不变
            return nums;
        }
        
        priority_queue<pair<LL,int>, vector<pair<LL,int>>, greater<pair<LL,int>>> pq;
        vector<int> res(n);
        LL maxVal = *max_element(nums.begin(), nums.end());
        for(int i = 0; i < n; i++){
            pq.push({nums[i], i});
        }
        
        while(true){
            if(pq.top().first == maxVal){
                k -= 1;
                LL cur = pq.top().first;
                cur *= (LL) multiplier;
                int idx = pq.top().second;
                pq.pop();
                pq.push({cur,idx});
                break;
            }
            LL cur = pq.top().first;
            int idx = pq.top().second;
            pq.pop();
            cur *= (LL) multiplier;
            pq.push({cur,idx});
            
            k -= 1;
            if(k == 0){
                while(!pq.empty()){
                    res[pq.top().second] = pq.top().first;
                    pq.pop();
                }
                
                return res;
            }
        }
     
       
        if(k == 0){
            while(!pq.empty()){
                res[pq.top().second] = pq.top().first % M;
                pq.pop();
            }
            return res;
        }
        
        
        LL mod = k % n;
        LL times = k / n;
        
        for(int i = 0; i < n; i++){
            LL cur = pq.top().first;
            int idx = pq.top().second;
            pq.pop();
            if(i < mod){
                cur = cur%M * pow(multiplier, times+1) % M;
                res[idx] = cur;
            }
            else {
                cur = cur%M * pow(multiplier, times) % M;
                res[idx] = cur;
            }
        }
      
        return res;
        
    }
};

/*
1e9 要取出某個數組最小數字k次 一個一個換都會超時
數組1e4 所以遍歷數組過程可以是nlgn

先齊頭式增長到差不多，在一次性的去分配剩餘的k給整個數組的數字
齊頭式增長過程 就是無腦拿出來判斷直到剩下最後一個原本較大的元素
*/
