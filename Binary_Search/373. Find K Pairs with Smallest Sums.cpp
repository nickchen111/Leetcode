/*
373. Find K Pairs with Smallest Sums
*/

// TC:O((lg(upper-lower)*(m+n)) SC:O(k) 
class Solution {
    int m,n;
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        m = nums1.size(); n = nums2.size();
        long lower = nums1[0] + nums2[0];
        long upper = nums1.back() + nums2.back();
        // 二分猜值
        while(lower < upper){
            long mid = lower + (upper - lower)/2;
            long count = checkLowerOrEqual(mid,nums1,nums2);
            if(count < k){
                lower = mid+1;
            }
            else upper = mid;//去壓上界到不能再壓為止就肯定可以求到答案
        }

        //兩種情況思考 一種是相加 < left or 相加  = left
        vector<vector<int>> res1;
        vector<vector<int>> res2;
        for(int i = 0; i<m; i++){
            int j = 0;
            while(j < n && nums1[i]+nums2[j] <= lower){
                if(nums1[i]+nums2[j] < lower){
                    res1.push_back({nums1[i],nums2[j]});
                }
                else res2.push_back({nums1[i],nums2[j]});
                j++;
            }
        }

        int t = min(res2.size(),k-res1.size());//因為有種case [1,2] [3] 跟你要三個 但只能輸出兩個 
        for(int i = 0; i<t; i++){
            res1.push_back(res2[i]);
        }
        return res1;
    }
    long checkLowerOrEqual(long mid, vector<int>& nums1, vector<int>& nums2){
        long res = 0;
        int j = n-1;
        //利用雙指針技巧 單調性增長 另一個就單調性下降 
        for(int i = 0; i<m; i++){
            while(j >= 0 && nums1[i]+nums2[j] > mid){
                j--;
            }
            res += (j+1);
        }

        return res;
    }
};
//PQ TC:O(klgk) SC:O(k)
class Solution {
    using AI3 = array<int,3>;
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(); int n = nums2.size();

        priority_queue<AI3, vector<AI3>, greater<AI3>> pq;
        pq.push({nums1[0]+nums2[0], 0, 0});
        set<pair<int,int>> set;//去重
        set.insert({0,0});
        vector<vector<int>> res;

        while(res.size() < k && !pq.empty()){
            auto [sum,i,j] = pq.top();
            pq.pop();
            res.push_back({nums1[i],nums2[j]});
            if(i+1 < m && set.find({i+1,j}) == set.end()){
                pq.push({nums1[i+1]+nums2[j],i+1,j});
                set.insert({i+1,j});
            }
            if(j+1 < n && set.find({i,j+1}) == set.end()){
                pq.push({nums1[i]+nums2[j+1],i,j+1});
                set.insert({i,j+1});
            }
        }

        return res;
    }
};

/*
此題跟378很像
去猜他的總和為某個數的時候會剛好讓他有第k小的情況 也就是有k個數包含他自己比他小
他的原型是外面套一個二分法裡面套一個單調性
*/
