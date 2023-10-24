/*
347. Top K Frequent Elements
*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(nums.size() == 0) return {};//base case

        unordered_map<int, int> key2freq;
        for(int i = 0; i< nums.size();i++){
            key2freq[nums[i]]++;
        }

        //轉變成求數組中k個最大的元素 似 215題 但這題要求的是前k個
        priority_queue<pair<int, int>, vector<pair<int,int>>, less<pair<int,int>> > pq;
        for(auto &[key, freq]:key2freq){
            pq.push({freq, key}); //pq.emplace(freq, key);更快 因為不需創建物件而是直接傳遞過去 要注意裡面的數據形態要跟pq要求的一致
        }

        vector<int> ans;

        while(k > 0){
            pair<int,int> x = pq.top(); pq.pop();
            ans.push_back(x.second);
            k--;
        }
        return ans;
    }
};

/*
解題思路：
此題給你一個k 代表我要一個數組中k種出現頻率最高的元素種類
如何知道頻率？ -> traverse一次數組去計算 -> 用一個哈希表存起來
在將結果按照頻率存到pq裡
只取出k個高的元素 放入ans

總體時間複雜度是 O(n lg k + k lg k)，其中 n 是 nums 數組的大小，k 是要找出的前 k 個頻率最高的元素的個數。 前者為插入所需時間 後者為取出k個元素所需時間
可以直接寫 o(nlgk)
空間複雜度是 O(n＋k)
*/
