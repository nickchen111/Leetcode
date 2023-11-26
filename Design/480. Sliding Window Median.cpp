/*
480. Sliding Window Median
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<double> set; 
        vector<double> res;
        for (int i=0; i<k; i++)        
            set.insert(nums[i]);
        
        auto iter= next(set.begin(),(k+1)/2-1);
       
        //先將前k個的中位數加入答案中
        if(k%2 == 0){
            res.push_back((*iter*1.0/2.0 )+ (*next(iter,1)*1.0/2.0));
        }
        else {
            res.push_back(*iter);
        }

        for(int i = k; i<nums.size(); i++){
        
            set.insert(nums[i]);
            //加入之後中位數該如何移動 奇數變偶數
            if(k%2==1){
                if(nums[i] < *iter){
                    iter = prev(iter,1);
                }

                if(nums[i-k] < *iter){
                    iter = next(iter,1);
                }
                else if(nums[i-k] > *iter){
                    ;
                }
                else {
                    iter = next(iter,1);
                }
            }
            //偶數變奇數
            else {
                if(nums[i] >= *iter){
                    iter = next(iter,1);
                }
                
                if(nums[i-k] < *iter){
                    ;
                }
                else if(nums[i-k] > *iter){
                    iter = prev(iter,1);
                }
                else{
                    if(iter != set.begin() && *iter == *prev(iter,1)){
                        ;//可以刪掉 且肯定是刪掉左邊的先
                    }
                    //刪掉是他本身
                    else {
                        iter = prev(iter,1);
                    }
                }
            }
            set.erase(set.lower_bound(nums[i-k]));

            if(k%2 == 0){
                res.push_back((*iter*1.0/2.0)+ (*next(iter,1)*1.0/2.0));
            }
            else {
                res.push_back(*iter);
            }
        }


        return res;
    }
};

/*
[x x x]
*/
