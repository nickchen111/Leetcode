/*
995. Minimum Number of K Consecutive Bit Flips
*/

// Diff TC:O(n) SC:O(n)
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> diff(n+1);
        int res = 0;
        int flips = 0;
        for(int i = 0; i < n; i++){
            flips += diff[i];
            //代表不用翻 他可以變成1
            if(nums[i] + flips%2 == 1) continue;
            if(i + k - 1 >= n) return -1;
            flips += 1;
            diff[i+k] -= 1;
            res += 1;
        }

        return res;
    }
};


//暴力解 TC:O(nk) SC:O(1)
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] != 1){
                if(i+k-1 >= n) return -1;
                for(int j = i; j < i + k; j++){
                    nums[j] = !nums[j];
                }
                res += 1;
            }
        }

        return res;
    }
};

/*
一次可以翻k個元素 讓1<->0互換 問最少要翻幾次讓數組內都是 1 如果無法達成返回-1
這題觀察一下會發現就是個貪心思想 如果當前沒有0都是1那我就不翻 一但發現一個0我就要翻
暴力解的話可以直接O(nk)每個都翻一下然後往後走
比較聰明的辦法是設定差分 代表這些區間內的數字我會翻幾次 一旦翻的次數讓他不是0那他後面的一串也必須跟著翻
*/
