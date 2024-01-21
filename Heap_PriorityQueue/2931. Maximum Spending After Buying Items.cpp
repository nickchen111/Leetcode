/*
2931. Maximum Spending After Buying Items
*/

// TC:O(m*n*lgmn) SC:O(m)
class Solution {
    using LL = long long;
public:
    long long maxSpending(vector<vector<int>>& values) {
        int n = values.size();
        int m = values[0].size();
        vector<int> idx(n,m-1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // price, pos
        for(int i = 0; i < values.size(); i++){
            pq.push({values[i][m-1], i});
        }

        LL days = 1;
        LL res = 0;
        while(!pq.empty()){
            auto [price, pos] = pq.top();
            pq.pop();
            res += days*(LL)price;
            days += 1;
            idx[pos] -= 1;
            if(idx[pos] >= 0) pq.push({values[pos][idx[pos]], pos});
        }

        return res;


    }
};

/*
從最小的value開始購買 之後將他的下一項加入隊列 就可以逐天購買後得到可以花的最多錢
很套路的題目 每個小數組已經按照非遞增排好序 問你只能從每個數組的右邊開始拿 每過一天可以拿一個 得到的price會是當天天數乘上拿到的東西price
套路在要用另一個數組紀錄index拿取狀況 PQ裡面放當前的price以及拿的是哪一個小數組
*/
