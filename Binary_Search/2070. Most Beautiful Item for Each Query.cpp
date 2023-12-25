/*
2070. Most Beautiful Item for Each Query
*/

// Offline Query + Sort TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {

        //紀錄index以構建答案
        vector<pair<int,int>> query;
        for(int i = 0; i < queries.size(); i++){
            query.push_back({queries[i],i});
        }

        sort(query.begin(), query.end());
        int k = 0;
        sort(items.begin(), items.end());
        int maxVal = 0;
        vector<int> res(queries.size());
        for(int i = 0; i < query.size(); i++){
            int price = query[i].first;
            int idx = query[i].second;
            while(k < items.size() && items[k][0] <= price){
                maxVal = max(maxVal, items[k][1]);
                k++;
            }

            res[idx] = maxVal;
        }

        return res;
    }
};

// Binary Search TC:O(nlgn + nlgn) SC:O(1)
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {

        sort(items.begin(), items.end()); // price low -> high
        int maxVal = 0;
        for(int i = 0; i < items.size(); i++){
            maxVal = max(maxVal, items[i][1]);
            items[i][1] = maxVal;
        }

        vector<int> res;
        for(int i = 0; i < queries.size(); i++){
            int prices = queries[i];
            int left = 0;
            int right = items.size()-1;
            
            while(left < right){
                int mid = left + (right - left+1)/2;
                if(items[mid][0] <= prices){
                    left = mid;
                }
                else right = mid - 1;
            }

            if(items[left][0] > prices) res.push_back(0);
            else res.push_back(items[left][1]);
        }


        return res;
    }
};

/*
價格在低於或者相等於query價格的狀況時 商品的美麗值 最高價值可以是多少
給了一堆query 返回每個問題的答案
兩個想法
1. Binary Search 
2. 善加利用query特性 offline query 對問題排序 從小到大 
這樣我的items也只需要遍歷一遍 遍歷過程紀錄當前最大值 

Binary search的話要先對給定數組做改造 將price排序並且rollingMax 不斷更新最大值assign給數組
*/
