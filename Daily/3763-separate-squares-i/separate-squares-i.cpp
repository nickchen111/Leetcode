class Solution {
    double getAreaAbove(vector<vector<int>>& squares, double y) {
        double area = 0;
        for (const auto& square : squares) {
            double bottom = square[1];
            double top = bottom + square[2];
            double length = (double)square[2]; 
            
            if (y < top) {
                if (y > bottom) {
                    area += (top - y) * length;
                } else {
                    area += length * length; 
                }
            }
        }
        return area;
    }
public:
    double separateSquares(vector<vector<int>>& squares) {
        auto cmp = [&](const vector<int>&a, const vector<int>&b) {
            return a[1] < b[1];
        };
        sort(squares.begin(), squares.end(), cmp);
        double minY = 1e10, maxY = 0;
        double totalArea = 0.0;
        for (const auto& square : squares) {
            minY = min(minY, (double)square[1]);
            maxY = max(maxY, (double)(square[1] + square[2]));
            double side = (double)square[2];
            totalArea += side * side;
        }
        double left = minY, right = maxY, n = squares.size();
        
        double targetArea = totalArea / 2.0;
        for(int i = 0; i < 60; i++) {
            double mid = left + (right - left) / 2.0;
            double areaAbove = getAreaAbove(squares, mid);
            if (areaAbove > targetArea) {
                left = mid;
            } else {
                right = mid;
            }
        }
        // 因為 2e9 / 2^k <= 1e-5 -> k > 2e14, 2^60 ~= 1e18
        return left;
        
    }
};

/*
[[12,25,3],[3,14,2]]
*/