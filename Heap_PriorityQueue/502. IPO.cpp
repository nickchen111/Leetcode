/*
502. IPO
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int,int>> arr;
        for(int i = 0; i < profits.size(); i++){
            arr.push_back({capital[i],profits[i]});
        }

        sort(arr.begin(), arr.end());
        int sum = w;
        priority_queue<int, vector<int>, less<int>> pq;
        int idx = 0;
        for(int i = 0; i < arr.size(); i++){
            if(sum >= arr[i].first){
                idx = i+1;
                pq.push(arr[i].second);
            }
        }
        int count = 0;
        while(count < k && !pq.empty()){
            sum += pq.top();
            pq.pop();
            count += 1;
            while(idx < arr.size() && arr[idx].first <= sum){
                pq.push(arr[idx].second);
                idx++;
            }
        }

        return sum;
    }
};

/*
只能選k項 盡量選profits大的越好 但是只能選當下w大於capital[i]的商品 要如何最大化利益
因為選了之後capital只會增加不會扣分 所以就用一個heap 去判斷當下可以有的最好選擇就好
*/
