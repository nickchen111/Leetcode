/*
1647. Minimum Deletions to Make Character Frequencies Unique
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minDeletions(string s) {
        int n = s.size();
        //freq low->high
        //空擋頻率紀錄
        unordered_map<char,int> ch2freq; // ch -> freq
        for(int i = 0; i < n; i++){
            ch2freq[s[i]]++;
        }

        int res = 0;
        unordered_set<int> set;//收集 已經做過的頻率
        for(auto p:ch2freq){
            int freq = p.second;
            while(freq > 0 && set.find(freq) != set.end()){
                freq--;
                res++;
            }
            set.insert(freq);
        }

        return res;
    }
};

/*
此題希望所有元素的頻率皆不一樣 如果有一樣的就可以不斷刪除元素直到頻率不同
1. 頻率超高的一樣 但後面頻率低的皆滿 ex : 10 10 9 8 7 6 5 4 3 2 1 只能刪掉變0 十次操作
2.頻率超高的一樣 但後面有空擋 剪到某一方變空擋
3.頻率高的有三個一樣 空擋只有一個 兩個減 並且一方可以接上空擋 一方只能到0
4. 中間頻率有人相同 最高頻率也有相同 要先剪哪個？ 5 3 3  1  共享了一個空擋 5-2+3 = 6, 3-2+5 = 6

此題卡住的地方在於 要怎麼去找每個空擋頻率 其實換個角度想 每一個頻率出來直接找空白的頻率表 如果有重複直接往下降繼續找
反正就算之後有頻率相同的被遍歷到 那他就當作是上一次找到位置的頻率繼續往下找的概念
*/
