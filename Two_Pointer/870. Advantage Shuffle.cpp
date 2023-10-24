/*
870. Advantage Shuffle
*/


// TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        sort(nums1.begin(),nums1.end());
        priority_queue<pair<int,int>> pq;//大頂堆
        for(int i = 0; i<nums2.size(); i++){
            pq.push({nums2[i],i});
        }

        int left = 0;
        int right = n-1;//雙指針去指向nums1自己的數字
        vector<int> res(n);
        while(!pq.empty()){
            int idx = pq.top().second;
            int val = pq.top().first;
            pq.pop();
            if(nums1[right] > val){
                res[idx] = nums1[right];
                right--;
            }
            else{
                res[idx] = nums1[left];
                left++;//養精蓄銳 先用最爛的去比
            }
        }

        return res;
    }
};

/*
有趣的題目 自己最強的數字打不贏就派最小的上去送 打得贏就碾壓
比較前要將兩個num都排序 不過nums2要另外用其他方式排 不能改原本順序
*/
