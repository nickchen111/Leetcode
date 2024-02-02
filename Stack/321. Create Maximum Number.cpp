/*
321. Create Maximum Number
*/

// TC:O(k*(m+n)) SC:O(k)
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {

        vector<int> res;
        for(int i = 0; i <= k; i++){
            // k*(m+n)
            if(i > nums1.size()) continue;
            if(k-i > nums2.size()) continue;
            vector<int> p1 = findMax(nums1,i);
            vector<int> p2 = findMax(nums2,k-i);
            vector<int> temp = merge(p1,p2);
            res = max(res,temp);
        }

        return res;
    }

    vector<int> findMax(vector<int>& nums, int k){
        vector<int> arr;
        int count = nums.size() - k;
        for(int i = 0; i < nums.size(); i++){
            while(arr.size() > 0 && count && arr.back() < nums[i]){
                arr.pop_back();
                count -= 1;
            }
            arr.push_back(nums[i]);
        }
        arr.resize(k);
        
        return arr;
    }
    vector<int> merge(vector<int>& nums1, vector<int>& nums2){
        

        int L = nums1.size() + nums2.size();
        vector<int> arr(L);
        for(int i = 0; i < L; i++){
            if(nums1 > nums2){
                arr[i] = nums1[0];
                nums1.erase(nums1.begin());
            }
            else {
                arr[i] = nums2[0];
                nums2.erase(nums2.begin());
            }
        }


        return arr;
    }
};


/*
402 follow up 也就是兩個數組選數字 只能選k個 不改變順序的狀況下能組多大
這題沒有比較好的做法 只能去逐個判斷如果第一個數組選k個那麼另外一個數組去補上的狀況 哪一種狀況能構造出較大的排序組合
考察了兩個知識點
1. 402的單調棧操作在需要刪掉nums.size()-k個的狀況下
2. 1754題的貪心 要從兩個數組構造最大數組時 遇到當下兩個數字相同狀況 直接去比較後面元素數組整體狀況
*/
