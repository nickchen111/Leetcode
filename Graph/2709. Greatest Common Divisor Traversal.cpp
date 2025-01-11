/*
2709. Greatest Common Divisor Traversal
*/

// TC:O(n*m* lglgn)) SC:O(n+n)
class Solution {
    int parent[2*100005];
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void union_(int x,int y){
        x = parent[x];
        y = parent[y];
        if(x < y){
            parent[x] = y;
        }
        else parent[y] = x;
    }
    vector<int> sieve(int x){
        vector<int> q(x+1,0);
        for(int i = 2; i <= sqrt(x); i++){
            if(q[i]) continue;
            int j = i*2;
            while(j <= x){
                q[j] = 1;
                j += i;
            }
        }

        vector<int> res;
        for(int i = 2; i <= x; i++){
            if(q[i] == 0) res.push_back(i);
        }
        return res;
    }
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> prime = sieve(maxVal);
       
        int m = prime.size();
        
        unordered_map<int,int> map;
        for(int i = 0; i < m; i++){
            map[prime[i]] = i;
        }

        for(int i = 0; i < n+m; i++){
            parent[i] = i;
        }

        for(int i = 0; i < n; i++){
            int cur = nums[i];
            for(int j = 0; j < m; j++){
                int p = prime[j];
                if(p > cur) break;

                if(p*p > cur){
                    if(find(i) != find(n+map[cur])){
                        union_(i, n + map[cur]);
                    }
                    break;
                }
                if(cur % p == 0){
                    if(find(i) != find(n+j)){
                        union_(i, n+j);
                    }
                    while(cur%p == 0){
                        cur /= p;
                    }
                }
            }
        }


        for(int i = 0; i < n; i++){
            if(find(i) != find(0)) return false;
        }
        
        return true;
        
    }
};

/*
可以遍歷在兩個數字之間 當他們的gcd > 1
問說是否可以透過某個數字index之間遊走 讓某個index走完所有數字
這題可以想到是union-find 連通相關題
但是如果用gcd(x,y) 聯通就太慢了 會是n^2 
有個技巧是直接連通 prime 
1e5 * sqrt(10^5) 大概300個數 又只找質因數 大概不到100個
有個小技巧 當 考察過程中 質因數^2已經大於這個數 這個數本身就是個質因數 考察過程中會一直拿質因數除以這個數
58 : 2-> 29 : 3,5,7 7^2 - 49 不用看了
*/
