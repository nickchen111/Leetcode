/*
659. Split Array into Consecutive Subsequences
*/


//TC:O(n) SC:O(M) M為nums中不同元素的數量
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,int> seq;//大腿
        unordered_map<int,int> count;
        
        for(auto x:nums){
            count[x]++;
        }

        for(auto x:nums){
            if(count[x] == 0) continue; //被一些數字組成戰隊搶走了 輪到他之後就也不用考慮了
            //可抱大腿的狀況
            if(seq[x-1] > 0){
                seq[x-1]--;
                seq[x]++;
                count[x]--;
            }

            else{
                //往後看也沒人可以連成三個
                if(count[x+1] == 0 || count[x+2] == 0) return false;
                //往後看有人可以連成三個組成戰隊
                seq[x+2]++;
                count[x]--;
                count[x+1]--;
                count[x+2]--;
            }
        }

        return true;
    }
};


/*
此題的思維非常巧妙 要用到貪心算法
xxxxxx 6 xxxxx
往前看往後看
站在6的角度上 要思考能否要抱前面人的大腿 且必須得是已經是長度超過3的大腿
能抱肯定抱 因為如果抱了 後面 ７ 8 也肯定可以抱大腿 站在當前角度上感覺起來是最優的狀態
如果沒有就看可否自己單幹 看後面是否有7 8 如果沒有直接返回false
*/
