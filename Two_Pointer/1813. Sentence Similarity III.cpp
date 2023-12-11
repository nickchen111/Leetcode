/*
1813. Sentence Similarity III
*/

// Two Pointer TC:O(m + n + k) SC:O(m + n)
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> str1;
        vector<string> str2;
        for(int i = 0; i < sentence1.size(); i++){
            while(sentence1[i] == ' ') i++;
            int j = i;
            while(j < sentence1.size() && sentence1[j] != ' ') j++;
            string cur = sentence1.substr(i, j - i);
            str1.push_back(cur);
            i = j;
        }

        
        for(int i = 0; i < sentence2.size(); i++){
            while(sentence2[i] == ' ') i++;
            int j = i;
            while(j < sentence2.size() && sentence2[j] != ' ') j++;
            string cur = sentence2.substr(i, j - i);
            str2.push_back(cur);
            i = j;
        }

        int left1 = 0;
        int right1 = str1.size() - 1;
        int left2 = 0;
        int right2 = str2.size() - 1;
        if(str1.size() > str2.size()){
            while(left2 <= right2){
                if(str2[right2] == str1[right1]){
                    right1--;
                    right2--;
                }

                else if(str1[left1] == str2[left2]){
                    left1++;
                    left2++;
                }
                else return false;
            }
        }
        else {
            while(left1 <= right1){
                if(str2[right2] == str1[right1]){
                    right1--;
                    right2--;
                }

                else if(str1[left1] == str2[left2]){
                    left1++;
                    left2++;
                }
                else return false;
            }
        }

        return true;
    }
};

// Deque  TC:O(m + n + k) SC:O(m + n)
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        deque<string> str1;
        deque<string> str2;
        for(int i = 0; i < sentence1.size(); i++){
            while(sentence1[i] == ' ') i++;
            int j = i;
            while(j < sentence1.size() && sentence1[j] != ' ') j++;
            string cur = sentence1.substr(i, j - i);
            str1.push_back(cur);
            i = j;
        }

        
        for(int i = 0; i < sentence2.size(); i++){
            while(sentence2[i] == ' ') i++;
            int j = i;
            while(j < sentence2.size() && sentence2[j] != ' ') j++;
            string cur = sentence2.substr(i, j - i);
            str2.push_back(cur);
            i = j;
        }

        while(str1.size() && str2.size() && str1.front() == str2.front()){
            str1.pop_front();
            str2.pop_front();
        }
        while(str1.size() && str2.size() && str1.back() == str2.back()){
            str1.pop_back();
            str2.pop_back();
        }

        if(str2.size() == 0 || str1.size() == 0) return true;

        return false; 
        
    }
};

/*
此題問說 給你兩個字串 他們由很多字串組成 問是否只要在其中一個字串中插入一些字串就可以組成另一個字串？
此題我當下的想法即先將兩個字符串拆成兩個vector字串array 然後對兩個字串用指針互相比較 看最終較短的字串能不能走到left right交叉點
後來看解答區還可以用deque去解決這題 
*/
