class Solution{
    vector<int> Eratosthenes(int n){
        vector<int> q(n+1,0);
        for(int i = 2; i<=sqrt(n); i++){
            if(q[i] == 1) continue;
            int j = 2*i; 
            while(j<=n){
                q[j] = 1;
                j+=i;
            }
        }

        vector<int> prime;
        for(int i = 2; i<=n; i++){
            if(q[i] == 0) prime.push_back(i);
        }
    }
};
