/*
528. Random Pick with Weight
*/

//TC:O(lgn) SC:O(n)
class Solution {
    vector<int> p;
public:
    Solution(vector<int>& w) {
        int sum = -1;
        for(auto ww:w){
            sum+=ww;
            p.push_back(sum);
        }
    }
    
    int pickIndex() {
        int r = rand()%(p.back()+1);//p.back() 是index 要再加一才是總共權重樹
        auto iter = lower_bound(p.begin(),p.end(),r);

        return iter-p.begin();
    }
};
/*
此題想求帶權重的隨機分佈機率
用累積概率分佈
ex:
index 0 1 2 3 4 5 6
w     1 2 5 6 3 5 2
cumu: 1 3 8 14 17 22 24 
    [0] [1,2] [3,4,5,6,7] [8,9,10,11,12,13] [14,15,16] [17,18,19,20,21] [22,23]
每個權重掌管類似這樣的區間 隨機選一個數去找大於等於他的那項去對應index即是答案 
*/
