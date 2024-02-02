/*
2598. Smallest Missing Non-negative Integer After Operations
*/


//  TC:O(n) SC:O(n)
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int val) {
        unordered_map<int,int> map;
        int n = nums.size();
        for(int i = 0; i < n ; i++){
            if(nums[i] < 0){
                map[((nums[i]%val)+val)%val] += 1;
            }
            else map[nums[i]%val] += 1;
        }

        int target = 0;
        
        while(true){
            if(map.find(target%val) == map.end()){
                break;
            }
            else {
                map[target%val] -= 1;
                if(map[target%val]== 0) map.erase(target%val);
                target += 1;
            }
        }

        return target;
    }
};

/*
這題說你可以對數組內的數字做任意次的加減val數值
他要求這個數組內最小的非負整數可以有多大
首先透過觀察可以發現如果數字是負數那就要先將它轉成正數 ((nums[i]%val )+ val)%val
再來模擬了幾次後會發現 如果一個數字空缺的時候往往可以補上他的都是跟他有相同餘數的數字
如此一來就破題了 只要去紀錄這個數組各個餘數的數量 就可以從0開始模擬上去 是否還有當前數字%val的candidate可以取用
最後就可以求出最大的可能性
*/
