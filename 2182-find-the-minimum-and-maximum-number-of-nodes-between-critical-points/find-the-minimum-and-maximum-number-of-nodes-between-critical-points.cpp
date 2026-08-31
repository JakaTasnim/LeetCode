/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        int first = -1;       // first critical point
        int prevCritical = -1; // previous critical point
        
        int minDist = INT_MAX;
        int maxDist = -1;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        int pos = 1;  // curr ki position
        
        while (curr->next != nullptr) {
            
            ListNode* next = curr->next;
            
            // Check whether curr is a critical point
            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);
            
            if (isCritical) {
                
                // First critical point
                if (first == -1) {
                    first = pos;
                }
                
                // At least two critical points
                if (prevCritical != -1) {
                    minDist = min(minDist, pos - prevCritical);
                }
                
                // Update maximum distance
                if (first != -1) {
                    maxDist = max(maxDist, pos - first);
                }
                
                prevCritical = pos;
            }
            
            prev = curr;
            curr = next;
            pos++;
        }
        
        // Fewer than two critical points
        if (minDist == INT_MAX) {
            return {-1, -1};
        }
        
        return {minDist, maxDist};
    }
};