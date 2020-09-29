#ifndef SEPTEMBER_CHALLENGE_SOLUTIONS_H
#define SEPTEMBER_CHALLENGE_SOLUTIONS_H

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    string largestTimeFromDigits(vector<int> &);//O(1)

    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t);//O(n*log(k))

    bool repeatedSubstringPattern(string s);//O(n)

    vector<int> partitionLabels(string S);//O(S.size())

    vector<int> getAllElements(TreeNode* root1, TreeNode* root2);

    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B);

    bool wordPattern(string pattern, string str);

    int sumRootToLeaf(TreeNode* root);

    int compareVersion(string version1, string version2);

    string getHint(string secret, string guess);

    int findMaximumXOR(vector<int>& nums);

    int lengthOfLastWord(string s);

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost);

    char findTheDifference(string s, string t);

    string largestNumber(vector<int>& nums);

    int findPoisonedDuration(vector<int>& timeSeries, int duration);

};


#endif //SEPTEMBER_CHALLENGE_SOLUTIONS_H
