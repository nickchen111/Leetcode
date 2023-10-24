/*
264. Ugly Number II
*/


// BFS+PQ  TC:O(3n*lg3n) SC:O(3n)
class Solution {
public:
    int nthUglyNumber(int n) {
        
        priority_queue<long long, vector<long long>, greater<long long>> pq;//小頂堆
        pq.push(1);

        //需要計算到第n個 index n-1的那項就是
        for(int i = 0; i<n; i++){
            long long cur = pq.top();
            pq.pop();
            if(i == n-1) return cur;
            //有可能有重複的狀況
            while(!pq.empty() && cur == pq.top()){
                pq.pop();
            }
            pq.push(cur*2);
            pq.push(cur*3);
            pq.push(cur*5);
        }
        return -1;
    }
};

//three pointer + dp & greedy concept TC:O(n) SC:O(n)
class Solution {
public:
    int nthUglyNumber(int n) {
        int i = 0, j = 0, k = 0;
        vector<int> res({1});

        for(int t = 0; t<n-1; t++){
            int cur = min(res[i]*2, min(res[j]*3,res[k]*5));
            res.push_back(cur);

            if(cur == res[i]*2) i++;
            if(cur == res[j]*3) j++;
            if(cur == res[k]*5) k++;
        }

        return res.back();
    }
};

/*
此題可以有兩種解法 
1. BFS+priority queue
[1]
[2,3,5]
[3,5,4,6,10] -> [3,4,5,6,10]
[4,5,6,10,6,9,15] -> [4,5,6,6,9,10,15]會有重複的狀況
2.類似動態規劃又類似貪心 也類似雙鍊錶的概念去創建三指針

*/
