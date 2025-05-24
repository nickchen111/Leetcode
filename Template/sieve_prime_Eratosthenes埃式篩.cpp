auto sieve = [](int n) -> vector<int> {
    vector<int> np(n+1);
    for(int i = 2; i*i <= n; i++){
        if(np[i] == 1) continue;
        int j = i*i; 
        while(j<=n){
            np[j] = 1;
            j+=i;
        }
    }

    vector<int> prime;
    for(int i = 2; i<=n; i++){
        if(np[i] == 0) prime.push_back(i);
    }
    return prime;
};
