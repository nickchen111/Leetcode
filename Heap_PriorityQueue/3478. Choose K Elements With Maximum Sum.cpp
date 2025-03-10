// TC:O(nlgn) SC:O(n)
class Solution {
    using ll = long long;
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        /*
        最多選k個 找到每個index上的其他比他還小的index 他們在nums2中選最多k個可以得到的最大總和
        看起來可以排序 然後保存一個index
        */
        int n = nums1.size();
        vector<int> idx(n, 0);
        iota(idx.begin(), idx.end(), 0);
        ranges::sort(idx, [&](int i, int j) {return nums1[i] < nums1[j];});
        ll sum = 0;
        vector<ll> ans(n);
        int cnt = 0, prevIdx = -1;
        priority_queue<ll, vector<ll>, greater<>> pq1;// 大到小 可用的數字
        priority_queue<ll, vector<ll>, less<>> pq2;
        for(int i = 0; i < n; i++) {
            int ansIdx = idx[i];
            if(prevIdx != -1 && nums1[ansIdx] != nums1[prevIdx]) {
                while(!pq2.empty()) {
                    int nxtNum = pq2.top();
                    pq2.pop();
                    if(!pq1.empty()) {
                        if(pq1.size() >= k && nxtNum > pq1.top()) {
                            sum -= pq1.top();
                            sum += nxtNum;
                            pq1.pop();
                            pq1.push(nxtNum);
                        }
                        else if(pq1.size() >= k){
                            continue;
                        }
                        else {
                            pq1.push(nxtNum);
                            sum += nxtNum;
                        }
                    }
                    else {
                        pq1.push(nxtNum);
                        sum += nxtNum;
                    }
                }
            }
            ans[ansIdx] = sum;
            pq2.push(nums2[ansIdx]);
            prevIdx = ansIdx;
        }
        return ans;
    }
};
