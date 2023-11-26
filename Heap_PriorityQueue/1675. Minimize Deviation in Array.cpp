/*
1675. Minimize Deviation in Array
*/


// TC:O(32n*lg32n) SC:O(N)
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        multiset<int> set;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            if(nums[i]%2 == 0){
                set.insert(nums[i]);
            }
            else set.insert(nums[i]*2);
        }
        
        int res = INT_MAX;
        while(1){
            res = min(res,*set.rbegin()-*set.begin());
            int m = *set.rbegin();
            set.erase(set.find(m));
            if(m%2==0){
                m/=2;
                set.insert(m);
            }
            else break;
        }

        return res;
    }
};

/*
此題給你兩個操作 如果你是偶數那就可以除2 是奇數那就可以乘二
任意兩個數字的差最小可以是多少
給我奇數最小值 他最高就可以從他出發*2的各種倍數 
給我偶數最大值 他最低就可以從他出發*2一次 之後就變成偶數
[1,2]
[2,1]
[3,6]
[4,2,1] 每個數字都有他的candidate 找到其中數字讓他range最小
就變成632題了 每次都把最大的拿出去 然後逐個判斷每個當作最大可以有的最小差值是多少 
奇數最大值肯定是他乘上2 偶數就自己本身
*/
