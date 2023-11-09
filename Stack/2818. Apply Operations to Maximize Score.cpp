/*
2818. Apply Operations to Maximize Score
*/

// TC:O(n+nlglgn+lgn) SC:O(n)
using LL = long long;
LL M = 1e9+7;
class Solution {
public:
    vector<int> Eratosthenes(int n){
         //先來做埃氏篩
        vector<int> q(n+1,0);//改成count計數
        for(int i = 2; i<=n; i++){
            if(q[i] >= 1) continue;
            q[i] = 1; //第一次遇到他自己會是自己的質因數
            int j = 2*i; 
            while(j<=n){
                q[j] += 1;
                j+=i;
            }
        }

        return q; 
    }
    long long QuickPow(int x, int n){
        if(n == 0) return 1;
        long long res = QuickPow(x,n/2)%M;
        if(n%2) return (res*res%M)*x%M;
        else return (res*res)%M;

    }

    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int MAX = *max_element(nums.begin(), nums.end());
        //需返回1~MAX每個元素各自有多少個質因數 這也是埃氏篩可以做到的 只要將刪除元素改成count計數
        vector<int> s1 = Eratosthenes(MAX);
        vector<int> score(n);
        for(int i = 0; i<n; i++){
            score[i] = s1[nums[i]];//nums[i]是數值 s[nums[i]即為他有多少個質因子
        }

        //開始去列prevLarger nextLarger
        vector<int> prevLarger(n,-1);
        vector<int> nextLarger(n,n);
        stack<int> s;
        for(int i = n-1; i>=0; i--){
            while(!s.empty() && score[s.top()] <= score[i]){
                s.pop();
            }
            if(!s.empty()) nextLarger[i] = s.top();
            s.push(i);
        }
        while(!s.empty()) s.pop();
        for(int i=0; i<n; i++){
            while(!s.empty() && score[s.top()] < score[i]){
                s.pop();
            }
            if(!s.empty()) prevLarger[i] = s.top();
            s.push(i);
        }

        vector<pair<LL,LL>> temp;
        for(int i = 0; i<n; i++){
            LL t = (i-prevLarger[i])*(nextLarger[i]-i);
            temp.push_back({nums[i],t});
        }

        sort(temp.rbegin(),temp.rend());
        LL res = 1;
        for(auto [num,t]:temp){
            if((LL)k >= t){
                res = res * QuickPow(num,t)%M;
                k-=t;
            }
            else {
                res = res* QuickPow(num,k)%M;
                k = 0;
            }
            if(k == 0) break;
        }

        return res;

    }
};

/*
本題是個縫合怪 縫合了很多知識點考察
1. count subarray by element
2. precompute prime score
3. prev greater element/ next grater element
4. Ouick pow
*/
