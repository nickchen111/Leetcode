/*
1405. Longest Happy String
*/

//
class Solution {
    using PII = pair<int,int>; 
public:
    string longestDiverseString(int a, int b, int c) {
        
        priority_queue<PII, vector<PII>, less<PII>> pq;

        if(a > 0) pq.push({a,0});
        if(b > 0) pq.push({b,1});
        if(c > 0) pq.push({c,2});

        string res = "";
        while(!pq.empty()){
            auto [freq, ch] = pq.top();
            pq.pop();
            int times = freq;
            for(int i = 0; i < min(times,2); i++){
                res += ch+'a';
                freq -= 1;
            }
            
            if(pq.empty()) break;
            auto [freq2, ch2] = pq.top();
            pq.pop();
            //如果第一個比第二大得多太多了 策略是只用一個
            if(freq > freq2){
                res += ch2+'a';
                freq2 -= 1;
                if(freq > 0) pq.push({freq, ch});
                if(freq2 > 0) pq.push({freq2, ch2});
            }
            else {
                int time2 = freq2;
                for(int i = 0; i < min(time2,2); i++){
                    res += ch2+'a';
                    freq2 -= 1;
                }
                if(freq > 0) pq.push({freq, ch});
                if(freq2 > 0) pq.push({freq2, ch2});
            }

        }

        return res;
    }
};


//  TC:O(nlgn) SC:O(n)
class Solution {
    using PII = pair<int,int>; 
public:
    string longestDiverseString(int a, int b, int c) {
        
        priority_queue<PII, vector<PII>, less<PII>> pq;

        if(a > 0) pq.push({a,0});
        if(b > 0) pq.push({b,1});
        if(c > 0) pq.push({c,2});

        string res = "";
        while(!pq.empty()){
            if(pq.size() == 1){
                auto [freq, ch] = pq.top();
                int times = freq;
                for(int i = 0; i < min(times,2); i++){
                    res += ch+'a';
                    freq -= 1;
                }
                break;
            }
            auto [freq, ch] = pq.top();
            pq.pop();
            auto [freq2, ch2] = pq.top();
            pq.pop();
            //如果第一個比第二大得多太多了 策略是只用一個
            int k = min(1 + freq-freq2, 2);
            for(int i = 0; i < k; i++){
                res += ch+'a';
            }
            res += ch2+'a';
            freq -= k;
            freq2 -= 1;

            if(freq > 0) pq.push({freq, ch});
            if(freq2 > 0) pq.push({freq2, ch2});
        }

        return res;
    }
};

/*
給你一堆限制
1.字串只能包含abc字母
2.字串不能有aaa, bbb, ccc
3. 字串最多只能有各自 x , y, z個 a b c 字母
問說最長可以組成的字串為何
這題也是一個要你排定行程的題目 想當然會想用最長的字串先開始排 然後用次長的去搭配他
結束條件是只剩某個字母或者都用完了
*/
