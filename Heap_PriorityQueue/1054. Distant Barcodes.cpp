/*
1054. Distant Barcodes
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using PII = pair<int, int>;
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        unordered_map<int,int> map; // val -> freq;
        for(int i = 0; i < n; i++){
            map[barcodes[i]] += 1;
        }

        priority_queue<PII, vector<PII>, less<PII>> pq;
        for(auto &[val, freq] : map){
            pq.push({freq,val});
        }

        vector<int> res;
        while(!pq.empty()){
            auto [freq,val] = pq.top();
            pq.pop();
            res.push_back(val);
            freq -= 1;
            if(!pq.empty()){
                auto [nextFreq, nextVal] = pq.top();
                pq.pop();
                res.push_back(nextVal);
                nextFreq -= 1;
                if(nextFreq > 0) pq.push({nextFreq, nextVal});
            }
            
            if(freq > 0) pq.push({freq, val});
        }

        return res;
    }
};

// 另一種寫法 general一點
class Solution {
    using PII = pair<int, int>;
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        unordered_map<int,int> map; // val -> freq;
        for(int i = 0; i < n; i++){
            map[barcodes[i]] += 1;
        }

        priority_queue<PII, vector<PII>, less<PII>> pq;
        for(auto &[val, freq] : map){
            pq.push({freq,val});
        }

        vector<int> res;
        while(!pq.empty()){
            if(pq.size() == 1 && pq.top().first > 1) return {};//失敗條件
            int len = pq.size();
            vector<PII> temp;
            for(int i = 0; i < min(2, len); i++){
                auto [freq, val] = pq.top();
                pq.pop();
                res.push_back(val);
                freq -= 1;
                if(freq > 0) temp.push_back({freq,val});
            }
            for(int i = 0; i < temp.size(); i++){
                pq.push({temp[i].first, temp[i].second});
            }
        }

        return res;
    }
};


/*
希望相鄰數字不重複並保證一定有此答案將排序順序返回
跟之前的要求你安排順序題目一樣明顯用PQ + Greedy
出現次數越多的越希望他提早用完
*/

