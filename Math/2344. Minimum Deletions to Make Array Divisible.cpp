/*
2344. Minimum Deletions to Make Array Divisible
*/

// Sort + GCD TC:O(nlgn + n + k) k為numsDivide的長度  SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        // Sort
        int prime = numsDivide[0];
        for(int i = 1; i < numsDivide.size(); i++){
            prime = gcd(numsDivide[i], prime);
        }

        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i = 0; i < nums.size(); i++){
            if(prime % nums[i] != 0) res++;
            else return res;
        }

        return -1;
    }
};


// PQ + Map + Set + GCD TC:O(~2*n + k + m) k為numsDivide的長度 m 為數字種類 SC:O(2*n + m)
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        unordered_map<int,int> map;
        int n = nums.size();
        for(int i = 0;  i < n; i++){
            map[nums[i]] += 1;
        }
        // find the prime
        int prime = numsDivide[0];
        for(int i = 1; i < numsDivide.size(); i++){
            prime = gcd(numsDivide[i], prime);
        }
        
        

        // sort number from nums and take it 
        priority_queue<int, vector<int>, greater<int>> pq;
        
        unordered_set<int> set(nums.begin(), nums.end());
        for(auto num : set){
            pq.push(num);
        }

        int res = 0;
        while(!pq.empty()){
            int curNum = pq.top();
            pq.pop();
            if(prime % curNum != 0) res += map[curNum];
            else return res;
        }

        return -1;

    }
};

/*
此題問說要刪除多少個數字才能讓數組內最小的元素能夠整除另一個數組所有的數字
另一個數組要的數字無非就是某些質數 或者他們的倍數
1. find the freq of all number and find the smallest number -> map
2. find the prime to divide numsDivide -> gcd
3. try the smallest number whether this number can divide all number from numsDivide -> pq + set delete duplicate
但其實可以直接sort如果不行就res++ 遇到可以的就停
*/
