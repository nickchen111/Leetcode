/*
1319. Number of Operations to Make Network Connected
*/

// 適用想連接的點也有可能跟其他點連接狀況 TC:O(n) SC:O(n)
class Solution {
    class UF{
        vector<int> parent;
    public:
        UF(int n){
            for(int i = 0; i < n; i++){
                parent.push_back(i);
            }
        }

        int find(int x){
            if( x != parent[x]){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void union_(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx < rooty){
                parent[rooty] = rootx;
            }
            else if(rootx > rooty){
                parent[rootx] = rooty;
            }
        }
    };
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        //看有幾個祖先 需要的線數就是祖先數-1
        UF uf(n);

        vector<int> cables(n);//計算每個點有多少條線 雙向都會被算入
        for(const auto& connect : connections){
            int node1 = connect[0];
            int node2 = connect[1];
            uf.union_(node1, node2);
            cables[connect[0]] +=1;
            cables[connect[1]] +=1;
        }

        unordered_map<int,int> count;//每個root 有多少個元素
        unordered_map<int,int> totalCable; //每個以此node為root的node有多少條線
        
        for(int i = 0; i < n; i++){
            int ancestor = uf.find(i);
            count[ancestor] += 1;
            totalCable[ancestor] += cables[i];
            
        }

        int redundant = 0;
        for(auto num : totalCable){
            int root = num.first;
            redundant += totalCable[root]/2 - (count[root]-1);
        }
        if(redundant >= totalCable.size() - 1) return totalCable.size()-1;
        else return -1;
    }
};

//只有一組大group其他都是單獨的點
class Solution {
    class UF{
        vector<int> parent;
    public:
        UF(int n){
            for(int i = 0; i < n; i++){
                parent.push_back(i);
            }
        }

        int find(int x){
            if( x != parent[x]){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void union_(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx < rooty){
                parent[rooty] = rootx;
            }
            else if(rootx > rooty){
                parent[rootx] = rooty;
            }
        }
    };
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int edge = connections.size();
        //看有幾個祖先 需要的線數就是祖先數-1
        UF uf(n);

        for(const auto& connect : connections){
            int node1 = connect[0];
            int node2 = connect[1];
            uf.union_(node1, node2);
        }

        unordered_map<int,int> count;
        int connectGroup;
        for(int i = 0; i < n; i++){
            int ancestor = uf.find(i);
            count[ancestor] += 1;
            if(count[ancestor] > 1) connectGroup = ancestor;
        }
        edge -= (count[connectGroup]-1);
        //map.size() 就是我的祖先數目
        if(edge < n - count[connectGroup]) return -1;
        else return count.size()-1;
    }
};

/*
此題給你一些已連線的node 並且總有幾台node是沒有被連上的 然後要查出目前連線到edge數是否可滿足連上那些未被連接的node
並且最少需牽多少線過去
所以我需要先知道總共的線數 -> 再去看哪些點跟哪些點是連節在一起的 用union-find 求出此祖先連了多少個人包含自己
*/

