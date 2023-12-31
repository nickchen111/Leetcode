/*
2856. Minimum Array Length After Pair Removals
*/

// Boyer Moore TC:O(n) SC:O(n)
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            map[nums[i]] += 1;
        }

        int count = 0;
        for(auto &p : map){
            if(p.second > n/2) count = p.second;
        }

       if(count == 0) return n%2;
       else return count - (n-count);
        
    }
};


// Heap
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            map[nums[i]] += 1;
        }

        priority_queue<int, vector<int>, less<int>> pq;
        for(auto &p : map){
            pq.push(p.second);
        }

        while(pq.size() >= 2){
            int freq1 = pq.top();
            pq.pop();
            int freq2 = pq.top();
            pq.pop();
            freq1 --; freq2 --;
            if(freq1 > 0) pq.push(freq1);
            if(freq2 > 0) pq.push(freq2);
        }

        if(pq.empty()) return 0;
        else return pq.top(); 
        
    }
};

/*
一個數組已經由小到大排序 可以任意挑兩個滿足條件元素where i < j, such that nums[i] < nums[j].
移除這兩個元素 問說最少可以剩下多少元素
會希望盡量將相同的元素跟其他元素相消
並且重複元素較小的一定要找較大的去消 
其實這題就是boyer Moore majority element

[1 3 4 4 4] 
[1,3,3,3,4]
*/
