/*
3233. Find the Count of Numbers Which Are Not Special
*/

// TC:O(sqrt(r-l) + lglg(sqrt(r))) SC:O(sqrt(r))
class Solution {
    vector<int> isPrime(int n){
        vector<int> q(n+1,0);
        q[1] = 1;
        for(int i = 2; i<=sqrt(n); i++){
            if(q[i] == 1) continue;
            int j = 2*i; 
            while(j<=n){
                q[j] = 1;
                j+=i;
            }
        }
        
        return q;
    }
public:
    int nonSpecialCount(int l, int r) {
        int count = 0; // 就是要是完全平方數才行
        vector<int> prime = isPrime(sqrt(r));
        int start = sqrt(l);
        if(start* start < l) start += 1;
        
        for(int num = start; num <= sqrt(r); num++){
            if(num == 1) continue;
            if(prime[num] == 0){
                count += 1;
            }
        }
        
        int res = r-l+1 - count;
        
        return res;
    }
};

/*
3602634
440140577

14364474
360213759
*/
