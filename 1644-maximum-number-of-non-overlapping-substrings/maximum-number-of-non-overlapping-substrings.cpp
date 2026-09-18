class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        for (int c = 0; c < 26; c++) {
            if (last[c] == -1) continue;

            int left = first[c];
            int right = last[c];
            bool valid = true;

            // right can grow while we scan.
            for (int i = left; i <= right; i++) {
                int current = s[i] - 'a';

                if (first[current] < left) {
                    valid = false;
                    break;
                }

                right = max(right, last[current]);
            }

            if (valid) {
                intervals.push_back({left, right});
            }
        }

        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) {
                 if (a.second != b.second) {
                     return a.second < b.second;
                 }
                 return a.first > b.first;
             });

        vector<string> answer;
        int previousEnd = -1;

        for (const auto& [left, right] : intervals) {
            if (left > previousEnd) {
                answer.push_back(s.substr(left, right - left + 1));
                previousEnd = right;
            }
        }

        return answer;
    }
};