/*
950. Reveal Cards In Increasing Order
*/


// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.rbegin(), deck.rend());
        deque<int> d;
        d.push_back(deck[0]);
        for (int i = 1; i < deck.size(); i++) {
            d.push_front(d.back());
            d.pop_back();
            d.push_front(deck[i]);
        }
        vector<int> res(d.begin(), d.end());
        return res;
    }
};

/*
遊戲王題 第一步先翻開第一張卡 然後將第二張卡放在底下 接著重複步驟直到所有卡都被翻開
返回你該如何佈置卡片順序 能呈現出遞增趨勢
奇數張牌一定無腦選從最小到最大

*/
