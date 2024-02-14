/*
2149. Rearrange Array Elements by Sign
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> pos;
        vector<int> neg;
        for(int i = 0; i < n; i++){
            if(nums[i] > 0){
                pos.push_back(nums[i]);
            } 
            else neg.push_back(nums[i]);
        }
        vector<int> res;
        int left = 0, right = 0;
        while(left < pos.size() && right < neg.size()){
            if(left <= right){
                res.push_back(pos[left]);
                left++;
            }
            else {
                res.push_back(neg[right]);
                right++;
            }
        }

        while(left < pos.size()){
            res.push_back(pos[left]);
            left++;
        }
        while(right < neg.size()){
            res.push_back(neg[right]);
            right++;
        }

        return res;
    }
};

/*
將數組內的元素改成
1. 正負號正負號連續的相鄰過去
2. 從正號開始
3.不能改變每個正號 or 負號彼此原本的順序
*/
