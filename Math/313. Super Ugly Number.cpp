/*
313. Super Ugly Number
*/

//TC:O(nlgk) SC:O(n)
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        vector<int> p(k, 0);// k個指針 都先指向0
        vector<long long> res({1});
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        //{value,index} 此index為指向primes的index

        for(int i= 0; i<k; i++){
            pq.push({res[p[i]]*primes[i],i});
        }

        for(int t = 0; t < n-1; t++){
            long long cur = pq.top().first;
            res.push_back(cur);

            //處理重複的以及加入新的值
            while(!pq.empty() && cur == pq.top().first){
                int i = pq.top().second;
                pq.pop();

                p[i]++;
                pq.push({res[p[i]]*primes[i], i});
            }
        }

        return res.back();
    }
};

/*
264題的follow up 給你k個數 找可以是這k個數組成的第n個醜數
但因為你不知道k是多少 每次都要遍歷時間複雜度會太高 所以用PQ 以空間換時間
這裡的PQ跟第一種寫法的PQ不同 只會放入n個數
*/
