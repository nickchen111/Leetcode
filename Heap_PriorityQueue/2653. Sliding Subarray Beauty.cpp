/*
2653. Sliding Subarray Beauty
*/

// Slide Window  + Ordered_set TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();
        int j = 0;
        multiset<int> set1,set2;
        vector<int> res;
        for(int i = 0; i < n; i++){
            while(j < n && set1.size() + set2.size() < k){
                if(set1.size() < x){
                    set1.insert(nums[j]);
                }
                else {
                    if(*set1.rbegin() > nums[j]){
                        set2.insert(*set1.rbegin());
                        set1.erase(--set1.end());
                        set1.insert(nums[j]);
                    }
                    else set2.insert(nums[j]);
                }
                j++;
            }
            if(set1.size() + set2.size() == k){
                res.push_back(min(0, *set1.rbegin()));
            }
            if(j == n) break;
            auto iter = set2.find(nums[i]);
            if(iter != set2.end()){
                set2.erase(iter);
            }
            else {
                set1.erase(set1.find(nums[i]));
                if(!set2.empty()){
                    set1.insert(*set2.begin());
                    set2.erase(set2.begin());
                }
            }
        }

        return res;
    }
};


// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();

        vector<int> res;
        multiset<int> set1,set2; // set1 放小於x的元素 set2放大於等於
        for(int i = 0; i<n; i++){
            //先加入元素
            if(set1.size() < x){
                set1.insert(nums[i]);
            }
            else {
               int v = *set1.rbegin();
               if(v > nums[i]){
                   set1.erase(set1.find(v));
                   set1.insert(nums[i]);
                   set2.insert(v);
               }
               else set2.insert(nums[i]);
            }

            //看是否符合窗口大小
            if(i >= k-1){
                int v = *set1.rbegin();
                res.push_back(min(0,v));
            }
            //彈出元素
            if(i >= k-1){
                int v = nums[i-k+1];
                auto iter = set2.find(v);
                if(iter != set2.end()){
                    set2.erase(iter);
                }
                else {
                    set1.erase(set1.find(v));
                    if(!set2.empty()){
                        set1.insert(*set2.begin());
                        set2.erase(set2.begin());
                    } 
                }
               
            }
        }
       

        return res;
    }
};
// TC:O(n*k*lgk SC:O(k))-> TLE
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();

        vector<int> res;
        multiset<int> set;
        for(int i = 0; i<n; i++){
            if(i < n) set.insert(nums[i]);
            if(set.size() > k) set.erase(set.lower_bound(nums[i-k]));
            if(set.size() == k){
                auto iter = next(set.begin(),x-1);
                if(*iter >= 0) res.push_back(0);
                else res.push_back(*iter);
            }
        }
       

        return res;
    }
};
