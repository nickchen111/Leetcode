/*
2013. Detect Squares
*/

// TC:O(1000) SC:O(1005*1005)
class DetectSquares {
    int counts[1005][1005];
public:
    DetectSquares() {
        for(int i = 0; i<=1000; i++){
            for(int j = 0; j<=1000; j++){
                counts[i][j] = 0;
            }
        }
    }
    
    void add(vector<int> point) {
        counts[point[0]][point[1]]+=1;
    }
    
    int count(vector<int> point) {
        int x = point[0]; int y = point[1];
        int res = 0;
        for(int i = 0; i<=1000; i++){
            int d = abs(x-i);
            if(d == 0) continue;
            int j;
            j = y+d;
            if(j >= 0 && j<=1000) res+=counts[i][j]*counts[x][j]*counts[i][y];
            j = y-d;
            if(j >= 0 && j<=1000) res+=counts[i][j]*counts[x][j]*counts[i][y];
        }

        return res;
    }
};

// hash map TC:O(1000) SC:O(1000*1000)
class DetectSquares {
    map<pair<int,int>, int> map;
public:
    DetectSquares() {

    }
    
    void add(vector<int> point) {
        map[{point[0],point[1]}]+=1;
    }
    
    int count(vector<int> point) {
        int x = point[0]; int y = point[1];
        int res = 0;
        for(auto m:map){
            auto cur = m.first;
            if(cur.first != x && cur.second != y && abs(cur.first-x) == abs(cur.second-y)){
                //找出三點的點數量
                int p1 = map[{cur.first,cur.second}];
                int p2 = map[{cur.first,y}];
                int p3 = map[{x,cur.second}];
                res+=p1*p2*p3;
            }
        }

        return res;
    }
};

/*
給你認一點 要找到能跟他組成正方形的所有可能 
因為題目有給定座標範圍到1000 所以只要O(1000)就可以遍歷出所有可能性
*/
