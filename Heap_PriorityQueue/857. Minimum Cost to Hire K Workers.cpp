/*
857. Minimum Cost to Hire K Workers
*/

// TC:O(nlgk + nlgn) SC:O(n)
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            arr.push_back({quality[i], wage[i]});
        }
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            return a.second*1.0/a.first < b.second*1.0/b.first;
        };

        sort(arr.begin(), arr.end(), cmp);
        
        double res = 1e20;
        int sum_quality;
        priority_queue<int> pq;
        for(int i = 0; i < n; i++){
            sum_quality += arr[i].first;
            pq.push(arr[i].first);
            if(pq.size() > k){
                sum_quality -= pq.top();
                pq.pop();
            }
            if(pq.size() == k){
                double unitWage = arr[i].second*1.0/arr[i].first;
                res = min(res, unitWage*sum_quality);
            }
        }

        return res;
        
    }
};

/*
選中的工人 需要付給他們至少是他們的最低工資
給每個工人的錢必須按照他們的quality比例
現在要選k個工人 問說最少需要付多少錢給工人
最省錢的肯定是品質高，工資較低的 -> wage/quality 越小越好
但他有可能工資超貴 只是剛好比例比較低，所以要去枚舉各種可能是最好的
枚舉過程就是工作量最小的k個人

arr[i-1].second*1.0 / arr[i-1].first == arr[i].second*1.0 / arr[i].first
arr[i-1].second*arr[i].first == arr[i].second * arr[i-1].first;
*/
