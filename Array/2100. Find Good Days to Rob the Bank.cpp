/*
2100. Find Good Days to Rob the Bank
*/


// Prefix + Suffix Three Pass TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        if(n <= time*2) return {};
        // x x x x
        vector<int> suf(n,0);
        vector<int> presum(n,0);

        for(int i = 1; i < n; i++){
            if(security[i] <= security[i-1]){
                presum[i] = presum[i-1] + 1;
            }
        }

        for(int i = n-2; i >= 0; i--){
            if(security[i] <= security[i+1]){
                suf[i] = suf[i+1] + 1;
            }
        }

        vector<int> res;
        for(int i = time; i < n - time; i++){
            if(presum[i] >= time && suf[i] >= time){
                res.push_back(i);
            }
        }

        return res;
    }
};

/*
要搶銀行的前提
1. 要搶那天前後至少要保留 time day
2. 保全數量在第time天 before i th day 要是非遞增的
3. 保全數量在第time天 after i th day 要是非遞減的
類似一個凹型曲線的日子能搶銀行
想維護一段從某點往前往後長度time 他是呈現凹型分佈 or 前高後瓶 前平後高 
security[i - time] >= security[i - time + 1] >= ... >= security[i] <= ... <= security[i + time - 1] <= security[i + time].
既然這樣我就會想知道以我這點以前一格他有多少個單調遞減長度 以我這點往後一格有多長單調遞增長度
suf + pre 
*/
