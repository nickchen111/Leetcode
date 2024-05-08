/*
506. Relative Ranks
*/

// TC:O(nlgn) SC:O(1)
class Solution {
    using PII = pair<int,int>;
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> res(n);
        int count = 0;
        priority_queue<PII, vector<PII>, less<>> pq;
        for(int i = 0; i < n; i++){
            pq.push({score[i],i});
        }

        while(!pq.empty()){
            int idx = pq.top().second;
            pq.pop();
            count ++;
            if(count == 1) res[idx] = "Gold Medal";
            else if(count == 2) res[idx] = "Silver Medal";
            else if(count == 3) res[idx] = "Bronze Medal";
            else res[idx] = to_string(count);
        }

        return res;

    }
};
