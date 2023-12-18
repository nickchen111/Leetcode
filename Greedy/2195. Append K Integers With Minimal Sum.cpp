/*
2195. Append K Integers With Minimal Sum
*/

//最優解 TC:O(n + nlgn ) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long minimalKSum(vector<int>& nums, int k) {
        LL res = ((LL)(k+1) * (LL)k)/2;

        set<int> set(nums.begin(), nums.end());
        for(auto num : set){
            if(num <= k){
                res += (LL)(k+1);
                res -= num;
                k++;
            }
            else break;
        } 

        return res;
    }
};

//次佳解 k = 10^8 並且數組內空缺數字不超過10^2會TLE
class Solution {
    using LL = long long;
public:
    long long minimalKSum(vector<int>& nums, int k) {
        nums.insert(nums.begin(), 0);
        unordered_set<int> set(nums.begin(), nums.end());
        vector<LL> arr;
        for(auto p:set){
            arr.push_back(p);
        }

        sort(arr.begin(), arr.end());

        LL res = 0;
        int n = arr.size();
        for(int i = 1; i < n; i++){
            if(arr[i] - arr[i-1] > 1){
                if(arr[i] - arr[i-1]-1 <= k){
                    res += (LL)((arr[i]+1)*(arr[i])/2) - ((arr[i-1]+1)*(arr[i-1])/2) - (LL)(arr[i]); 
                    k -= (arr[i] - arr[i-1] - 1);
                } 
                else if(arr[i] - arr[i-1]-1 > k){
                    for(int t = 1; t <= k; t++){
                        res += arr[i-1] + t;
                    }
                    k = 0;
                    break;
                }
            }

            if(k == 0) break;
        }

        //我的寫法這裡會比較慢 如果數組內都是連續數字 k = 10^8 這樣就會TLE
        if(k > 0){
            for(int i = 1; i<=k; i++){
                res += (arr[n-1] + i);
            }
        }

        return res;
    }
};


/*
給你一組數組 要你加入k個跟nums都不重複的數字 
問最小總和會是多少
1.我會想到先紀錄最小是多少 順便用set紀錄裡面的數字 如果加的過程中遇到裡面數字 那就pass 繼續加一看看 但這樣時間複雜度就會很高 至少 10^8 = k
2.如何快速知道空缺數字有幾個並且總和 n+1 * n /2 公式 ->改成在遍歷過程確認空缺 並且用公式快速算出 但是如果數組內都是連續數字 k = 10^8 這樣就會TLE
3.換個想法 假設k為止的數字全部都是空缺 然後遍歷數組 一但有數字重複了 答案再去補K+1 並且把重複數字減去
0 [1 2 3] 4 -> 10 5*4/2 - (arr[i] +arr[i-1]) ; k - (arr[j] - arr[i]-1);
1 [2 3 4] 5 -> n+1*(n)/2 -> 6*5/2
*/
