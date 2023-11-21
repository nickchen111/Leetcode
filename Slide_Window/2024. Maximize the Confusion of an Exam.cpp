/*
2024. Maximize the Confusion of an Exam
*/

// TC:O(2*n) SC:O(1)
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        //與1004類似 試試看兩個都各做一次
        int n = answerKey.size();
        int j = 0;
        int res = 0; 
        int count = 0;
        for(int i = 0; i<n; i++){
            while(j < n && (answerKey[j] == 'T' || count <=k)){
                if(answerKey[j] == 'T'){
                    res = max(res, j-i+1);
                }
                else{
                    if(count == k){
                        break;
                    }
                    else if(count < k){
                        count++;
                        res = max(res, j-i+1);
                    }
                }
                j++;
            }
            if(answerKey[i] == 'F') count-=1;
        }

        count = 0;
        j = 0;
        for(int i = 0; i<n; i++){
            while(j < n && (answerKey[j] == 'F' || count <=k)){
                if(answerKey[j] == 'F'){
                    res = max(res, j-i+1);
                }
                else{
                    if(count == k){
                        break;
                    }
                    else if(count < k){
                        count++;
                        res = max(res, j-i+1);
                    }
                }
                j++;
            }
            if(answerKey[i] == 'T') count-=1;
        }

        return res;
    }
};
