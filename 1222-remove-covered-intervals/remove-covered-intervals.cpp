class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
            sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0])
                return a[1] > b[1];   // same start -> larger end first
            return a[0] < b[0];       // smaller start first
        });

        int count = 0;
        int maxEnd = 0;

        for (auto &in : intervals) {
            if (in[1] > maxEnd) {
                count++;
                maxEnd = in[1];
            }
        }

        return count;
    }
};