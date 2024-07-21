/*
2251. Number of Flowers in Full Bloom
*/


// Diff : TC:O(mlgm + nlgn) SC:O(m+n)
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        map<int,int> map; // 時間 當時的差分結果
        
        for(auto flower : flowers){
            int start = flower[0], end = flower[1];
            map[start] += 1;
            map[end+1] -= 1;
        }

        int n = people.size();
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            arr.push_back({people[i], i});
        }
        sort(arr.begin(), arr.end());

        vector<int> res(n);
        auto iter = map.begin();
        int sum = 0;
        for(int i = 0; i < n; i++){
            while(iter != map.end() && iter->first <= arr[i].first){
                sum += iter->second;
                iter = next(iter);
            }
            res[arr[i].second] = sum;
        }

        return res;
    }
};

// Binary Search : TC:O((m+n)*lgn) SC:O(n)
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        int n = flowers.size();
        vector<int> starts(n), ends(n);
        for (int i = 0; i < n; i++) {
            starts[i] = flowers[i][0];
            ends[i] = flowers[i][1];
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        for (int &p: people)
            p = (upper_bound(starts.begin(), starts.end(), p) - starts.begin()) -
                (lower_bound(ends.begin(), ends.end(), p) - ends.begin());
        return people;
    }
};
