/*
1356. Sort Integers by The Number of 1 Bits
*/


// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        //每個都拿出來去算有幾個1 :)
        int n = arr.size();
        vector<int> res;

        auto comp = [] (pair<int,int>& a, pair<int,int>& b){
            if(a.first != b.first){
                return a.first > b.first;
            }
            else return a.second > b.second;
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq;//count:value

        for(int i = 0; i<n; i++){
            int count = 0;
            int cur = arr[i];
            while(cur != 0){
                cur = cur & (cur-1);
                count+=1;
            }
            pq.push({count,arr[i]});
        }

        while(!pq.empty()){
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;

    }
};
