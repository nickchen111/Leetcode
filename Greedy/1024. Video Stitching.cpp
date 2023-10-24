/*
1024. Video Stitching
*/

//TC:O(nlgn) SC:O(n)
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b){
        if(a[0] == b[0])
            return a[1] > b[1];
        else return a[0] < b[0];
    }
public:
    int videoStitching(vector<vector<int>>& clips, int time) {

        sort(clips.begin(), clips.end(), cmp);
        if(clips[0][0] != 0) return -1;
        int right = clips[0][1];
        int index = 0;
        int count = 1;
        if(clips[0][1] >= time) return count;// 如果第一個片段直接涵蓋全部

        while(index < clips.size()){
            int fareach = right;
            while(index < clips.size() && clips[index][0] <= right){
                fareach = max(fareach, clips[index][1]);
                index++;
            }
            if(fareach == right) return -1; //代表跟他重疊的片段都沒辦法讓他變長 連不到下一段中間有空白

            count++;
            if(fareach >= time) return count;
            right = fareach;
        }

        return -1;//代表所有片短都沒辦法抵達time的長度


    }
};

/*
此題就是明顯的貪心策略 要找最少的片段湊滿整個影片
先找出符合區間開頭的片段 如果沒有的話就可以直接return -1代表不可能填滿所有區間
然後根據跟你選取的第一個片段有重疊的片段(如果很多個都有起始點那就選最長的那個) 找結束點最後面的那項
並且不斷比較往後接 一直到片段有涵蓋到結尾即可返回片段數
*/
