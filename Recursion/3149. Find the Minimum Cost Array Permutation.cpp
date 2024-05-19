/*
3149. Find the Minimum Cost Array Permutation
*/

// TC:O(n^2 * 2^n) SC:O(15*2^n)
class Solution {
    vector<vector<int>> memo;
    vector<int> res;
    int n;
    vector<int> nums;
public:
    vector<int> findPermutation(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();
        memo.resize(1<<n, vector<int>(15,-1));
        print_res(1,0);

        return res;
    }

    void print_res(int state, int j){
        res.push_back(j);
        if(state == (1<<n)-1){
            return;
        }

        int ans = DFS(state,j);

        for(int k = 0; k < n; k++){
            if((state >> k)&1) continue;
            if(DFS((state | (1 << k)), k) + abs(j - nums[k]) == ans){
                print_res((state | (1 << k)), k);
                break;
            }
        }
    }

    int DFS(int state, int j){
        if(state == (1<<n)-1){
            return abs(j - nums[0]);
        }
        if(memo[state][j] != -1) return memo[state][j];
        int ans = INT_MAX;
        for(int k = 0; k < n; k++){
            if((state >> k)&1) continue;
            ans = min(ans, DFS((state | (1 << k)), k) + abs(j - nums[k]));
        }

        memo[state][j] = ans;

        return ans;
    }
};

/*
這題問說要按照他規則的公式去做 你可以全排列0->n-1的數字 
score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
會發現就是每一個元素上的index - 下一個元素上的value 的絕對值 這些加總 希望可以最小 那要如何排列 並且希望求出字典序最小的
一個很難想到的知識點是不論你怎麼排 你會發現012, 120, 201 都會有一樣的score 那這樣不如就讓0當第一個肯定最小
再來就是要如何排序後面的元素-> 排列型且跟相鄰有關DP 遞歸過程帶的是枚舉的狀態(狀態壓縮)以及上一個填什麼

*/
