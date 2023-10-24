/*
990. Satisfiability of Equality Equations
*/


class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UF uf(26);// 26個字母

        for(string eq:equations){
            if(eq[1] == '='){
                char x =eq[0];
                char y =eq[3];
                uf.union_(x - 'a', y - 'a');
            }
        }

        for(string eq:equations){
            if(eq[1] == '!'){
                char x =eq[0];
                char y =eq[3];
                if(uf.isconnect(x - 'a', y - 'a')){
                    return false;
                }
            }
        }

        return true;

    }
    class UF {
public:
    vector<int> parent; // 紀錄若干棵樹
    int count;//紀錄連通分量
    UF(int n){
        this -> count = n;
        for(int i = 0; i <26; i++){
            parent.push_back(i);//0~25
        }
    }

    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);//一路找到root
        }
        return parent[x];
    }

    void union_(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX!=rootY) {
            parent[rootX] = rootY;
        }
        if (rootX == rootY) return;
        count--;
    }

    bool isconnect(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        return rootX == rootY;
    }
    //count此題不需要
    int getcount(){
        return count;
    }

};
};


/*
union find 經典題
需先自己搭建uf function
tc: o(n) sc:o(1)
解题核心思想是，将 equations 中的算式根据 == 和 != 分成两部分，先处理 == 算式，使得他们通过相等关系各自勾结成门派（连通分量）；然后处理 != 算式，检查不等关系是否破坏了相等关系的连通性。
*/
