/*
3133. Minimum Array End
*/

// 2024.11.09
class Solution {
    using LL = long long;
public:
    long long minEnd(int n, int x) {
        int count = n - 1;
        // 轉成bit
        vector<LL> bit;
        while(count){
            bit.push_back(count&1);
            count >>= 1;
        }

        int cnt = 0;
        LL res = x;
        for(int i = 0; i < bit.size(); i++) {
            while((res >> cnt) & 1) cnt ++;
            res |= (bit[i] << cnt);
            cnt ++;
        }


        return res;
    }
};


// TC:O(n) SC:O(n) n = 32
class Solution {
    using LL = long long;
public:
    long long minEnd(int n, int x) {
        LL diff = n-1;
        vector<int> arr;
        while(diff != 0){
            int cur = diff%2;
            arr.push_back(cur);
            diff /= 2;
        }
        
        vector<int> bit;
        while(x != 0){
            int cur = x%2;
            bit.push_back(cur);
            x /= 2;
        }
        
        int j = 0;
        for(int i = 0; i < bit.size(); i++){
           if (bit[i]==1) continue;
            if(j < arr.size()){
                bit[i] = arr[j];
                j++;
            }
        }
        
        while(j < arr.size()){
            bit.push_back(arr[j]);
            j++;
        }
        
        LL res = 0;
        for(int i = bit.size()-1; i >= 0; i--){
            res = res*2 + bit[i];
        }
        
        return res;
    }
};

/*
給你一個AND所有元素後的數字x 以及他的數組長度n
問你最大的那個元素最小值會是多少
1. 因爲AND 讓我很容易想到 要從最小的元素肯定是x 中去對應他的bit 為 0 元素 每個0都有兩種可能
2. 要去找nexxt n-1個元素
把要新增上去的元素數量轉換成bit， 然後去填上最小元素bit狀態時的0的位置 如果不夠直接push_back往後加即可
*/
