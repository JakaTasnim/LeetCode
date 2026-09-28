class Solution {
public:
    int maxDepth(string s) {
        int depth = 0;
        int answer = 0;

        for (char ch : s) {
            if (ch == '(') {
                depth++;
                answer = max(answer, depth);
            }
            else if (ch == ')') {
                depth--;
            }
        }

        return answer;
    }
};