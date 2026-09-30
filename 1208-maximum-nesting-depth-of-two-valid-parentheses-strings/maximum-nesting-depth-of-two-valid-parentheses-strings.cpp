class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> answer;
        int depth = 0;

        for (char ch : seq) {
            if (ch == '(') {
                depth++;
                answer.push_back((depth - 1) % 2);
            } else {
                answer.push_back((depth - 1) % 2);
                depth--;
            }
        }

        return answer;
    }
};