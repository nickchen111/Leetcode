/*
3229. Minimum Operations to Make Array Equal to Target
*/

// Stack : TC:O(n) SC:O(1)
class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        long long res = 0;
        int pre = 0, n = nums.size();
        for(int i = 0; i < n; i++){
            res += max(target[i] - nums[i] - pre, 0);
            pre = target[i] - nums[i];
        }

        return res + max(-pre, 0);
    }
};


/*

 0 -3 -4 -5 -4 -3 -2 
ebbs and flows
*/

// Diff : TC:O(n) SC:O(1)
class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        long long s = target[0] - nums[0];
        long long ans = abs(s);
        for (int i = 1; i < nums.size(); i++) {
            int k = (target[i] - target[i - 1]) - (nums[i] - nums[i - 1]);
            if (k > 0) {
                ans += s >= 0 ? k : max(k + s, 0LL);
            } else {
                ans -= s <= 0 ? k : min(k + s, 0LL);
            }
            s += k;
        }
        return ans;
    }
};

/*
"這題希望你將兩個數組變成一樣 並且可以在原數組區間加一減一 問說最少需要最多少次操作 可以達到
差分思想:
會想到說差分可以快速幫你對數組做加減，再來要聯想到 如果兩個數組要一樣的話 他們的差分過程也要相同，然後過稱中不一樣的地方就要去判斷說是否對之後有幫助
ex : 差分+ 後面要加上-，如果後面剛好是遞減趨勢，這個減法就會幫上忙，如果不是當下的負數的值就要加上當下遞增趨勢造成的負數 變得更負繼續走...
單調棧思想：
此題跟1526題類似，要想到說每次的變化都會是跟前面有關，就像一個海浪一樣，如果當下數字遞增不會去加上整段遞增狀況，因為前面可能已經遞增了一段所以要扣掉
並且ebbs and flows 遞增段的效果會在鐘型的前段反應，遞減段的則是在後段反應"
*/
