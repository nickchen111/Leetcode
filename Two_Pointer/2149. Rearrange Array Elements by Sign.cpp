/*
2149. Rearrange Array Elements by Sign
*/

//  TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> res;
        bool flag = 0;
        int left = 0, right = 0;
        while(left < n && right < n){
            if(flag == 0){
                while(left < n && nums[left] < 0){
                    left++;
                }
                if(left < n) res.push_back(nums[left]);
                left++;
                flag = 1;
            }
            else if(flag == 1){
                while(right < n && nums[right] > 0){
                    right++;
                }
                if(right < n) res.push_back(nums[right]);
                right++;
                flag = 0;
            }
        }

        while(right < n){
            if(nums[right] < 0)res.push_back(nums[right]);
            right++;
        }

       

        return res;
    }
};

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
