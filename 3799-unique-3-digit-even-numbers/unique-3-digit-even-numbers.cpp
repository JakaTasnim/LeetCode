#include <vector>
using namespace std;

class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int available[10] = {};

        for (int digit : digits) {
            available[digit]++;
        }

        int answer = 0;

        for (int num = 100; num <= 998; num += 2) {
            int needed[10] = {};

            needed[num / 100]++;        // Hundreds digit
            needed[(num / 10) % 10]++; // Tens digit
            needed[num % 10]++;        // Units digit

            bool possible = true;

            for (int digit = 0; digit <= 9; digit++) {
                if (needed[digit] > available[digit]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                answer++;
            }
        }

        return answer;
    }
};