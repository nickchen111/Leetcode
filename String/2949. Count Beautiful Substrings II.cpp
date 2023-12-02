/*
2949. Count Beautiful Substrings II
*/

//TC: O(k * log(log(k)) + n) SC: O(k + n * m)
class Solution {
    vector<int> Eratosthenes(int n){
        vector<int> isPrime(n+1,0);
        for(int i = 2; i<=n; i++){
            if(isPrime[i] == 1) continue;
            int j = 2*i;

            while(j <= sqrt(n)){
                isPrime[j] = 1;
                j+=i;
            }
        }

        vector<int> res;
        for(int i = 2; i<=n; i++){
            if(isPrime[i] == 0){
                res.push_back(i);
            }
        }

        return res;
    }
    unordered_set<char> set = {'a','e','i','o','u'};
public:
    long long beautifulSubstrings(string s, int k) {
        //Hash matrix!?
        //需先求出i-j要跟誰取餘
        //他如果無法兩兩成對那就幫助他成對 反正對取餘不影響
        vector<int> prime = Eratosthenes(k);
        int m = 1;
        for(int p:prime){
            int count = 0;
            while(k%p == 0){
                count+=1;
                k/=p;
            }

            if(count != 0 && count % 2 == 0){
                m *= pow(p, count/2);
            }
            else if(count != 0 && count % 2 == 1){
                m *= pow(p, (count+1)/2);
            }
        }

        m *= 2;// sqrt(4*k) = 2 * sqrt(k)
        cout<<m<<endl;
        int n = s.size();
        s = "#" + s;
        unordered_map<int,unordered_map<int,int>> map;//V-C -> {idx對sqrt(4*k)餘數, 次數}
        map[0].insert({0,1});//將s多插入一個字的功用出現
       
        
        long long res = 0;
        int diff = 0;
        for(int i = 1; i<=n; i++){
            if(set.find(s[i]) != set.end()) diff++;
            else diff--;

            if(map.find(diff) != map.end() && map[diff].find(i%m) != map[diff].end()){
                res += map[diff][i%m];
            }
            map[diff][i%m]+=1;
        
        }
        return res;
    }
};


/*
此題限制
vowels == consonants.
(vowels * consonants) % k == 0

計算每次母音減子音數量 可以解決第一個條件
[1:j] ~ [1:i] 之間相減後母音子音的數量為
[(i-j)/2]^2 % k = 0;
(i-j)^2 % 4k = 0;
(i-j) % sqrt(4k) = 0;
-> i = j mod sqrt(4k) 

時間複雜度分析：
Eratosthenes 筛法的時間複雜度： 該部分的時間複雜度是 O(k * log(log(k)))，其中 k 是輸入的整數。
迭代字符串 s 的時間複雜度： 該部分的時間複雜度是 O(n)，其中 n 是字符串 s 的長度。
綜合來看，主要的時間複雜度是 Eratosthenes 筛法的部分，為 O(k * log(log(k)))。

空間複雜度分析：
Eratosthenes 筛法的空間複雜度： 該部分的空間複雜度是 O(k)。
map 的空間複雜度： 該部分的空間複雜度是 O(n * m)，其中 n 是字符串 s 的長度，m 是根據 Eratosthenes 筛法計算的 m 值。
綜合來看，主要的空間複雜度取決於 Eratosthenes 筛法的部分，為 O(k)。

總的來說，代碼的時間複雜度為 O(k * log(log(k)) + n)，空間複雜度為 O(k + n * m)。
*/
