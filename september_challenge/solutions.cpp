#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <string>
#include <stack>

using namespace std;

#include "solutions.h"


string Solution::largestTimeFromDigits(vector<int> &A) {
    int time_max[4] = {2, 3, 5, 9};
    if (find(A.begin(), A.end(), 2) == A.end() || count_if(A.begin(), A.end(), [](int i) { return i > 5; }) > 1) {
        time_max[0] = 1;
        time_max[1] = 9;
    }

    int time[4] = {-1, -1, -1, -1};

    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < 4; j++) {
            if (A[i] == -1)
                break;

            if (A[i] <= time_max[j] && A[i] > time[j]) {
                swap(A[i], time[j]);
            }
        }

    for (int i = 0; i < 4; i++)
        if (time[i] == -1)
            return "";

    return to_string(time[0]) + to_string(time[1]) + ':' + to_string(time[2]) + to_string(time[3]);

}

bool Solution::containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
    multiset<int> k_set;

    if (nums.size() < 2 || k == 0)
        return false;
    if (k >= nums.size())
        k = nums.size() - 1;

    for (int i = 0; i <= k; i++)
        k_set.insert(nums[i]);


    for (auto i = k_set.begin(); i != prev(k_set.end()); ++i)
        if (abs((long) *i - (long) *(next(i))) <= (long) t)
            return true;

    for (int i = k + 1; i < nums.size(); i++) {
        k_set.erase(nums[i - k - 1]);

        auto pointer = k_set.insert(nums[i]);
        if (pointer != k_set.begin() && abs((long) *pointer - (long) *(prev(pointer))) <= (long) t)
            return true;

        if (pointer != prev(k_set.end()) && abs((long) *pointer - (long) *(next(pointer))) <= (long) t)
            return true;
    }
    return false;

}

vector<int> zFunction(const string &str) {
    int len = str.length();
    int left = 0, right = 0;
    vector<int> zf(len);
    zf[0] = 0;

    for (int i = 1; i < len; i++) {
        zf[i] = 0;
        zf[i] = max(0, min(right - i, zf[i - left]));

        while (i + zf[i] < len && str[zf[i]] == str[i + zf[i]])
            zf[i]++;

        if (i + zf[i] > right) {
            left = i;
            right = i + zf[i];
        }
    }
    return zf;
}

bool Solution::repeatedSubstringPattern(string s) {
    vector<int> zf = zFunction(s);

    int len = s.length();

    for (int i = 1; i <= len / 2; i++)
        if (zf[i] + i == len && len % i == 0)
            return true;

    return false;
}
vector<int> Solution::partitionLabels(string S) {
    const int MAX = 'z'-'a';
    int last_app[MAX + 1];

    for (int i = 0; i < S.length(); i++)
        last_app[S[i] - 'a'] = i;

    vector<int> answ;
    int counter = 0;
    int border = 0;
    for (int i = 0; i < S.length(); i++){
        if (i == last_app[S[i] - 'a'] && border == i){
            answ.push_back(counter + 1);
            counter = 0;
            border = i + 1;
        }else{
            counter++;
            border = max(border, last_app[S[i] - 'a']);
        }
    }
    return answ;
}

TreeNode* getNext(stack<pair<bool, TreeNode*>>& st){
    if (st.empty())
        return nullptr;

    auto next = st.top();
    st.pop();
    if (!next.first)
        return next.second;

    if (next.second->right != nullptr)
        st.push(make_pair(true, next.second->right));

    st.push(make_pair(false, next.second));

    if (next.second->left != nullptr)
        st.push(make_pair(true, next.second->left));

    return getNext(st);
}

vector<int> Solution::getAllElements(TreeNode *root1, TreeNode *root2) {
        stack<pair<bool, TreeNode *>> stack1;
        stack<pair<bool, TreeNode *>> stack2;

        vector<int> answ;
        if (root1 != nullptr)
            stack1.emplace(make_pair(true, root1));
        if (root2 != nullptr)
            stack2.emplace(make_pair(true, root2));

        TreeNode *next1 = getNext(stack1);
        TreeNode *next2 = getNext(stack2);
        while (true) {

            if (next1 == nullptr && next2 == nullptr)
                return answ;

            if (next1 == nullptr) {
                answ.push_back(next2->val);
                next2 = getNext(stack2);
            } else if (next2 == nullptr || next2->val > next1->val) {
                answ.push_back(next1->val);
                next1 = getNext(stack1);
            } else {
                answ.push_back(next2->val);
                next2 = getNext(stack2);
            }
        }
}

int Solution::largestOverlap(vector<vector<int> > &A, vector<vector<int> > &B) {
    int size = A.size();
    int answ = 0;

    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++){//slide
            int counterLT = 0, counterRT = 0, counterLB = 0, counterRB = 0;
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++){
                    if (A[i][j] == 1 && B[(i+x)%size][(j + y)%size] == 1){
                        if (i+x < size && j+y < size)
                            counterLT++;
                        else if (i + x < size && j + y >= size)
                            counterRT++;
                        else if (i + x >= size && j + y < size)
                            counterLB++;
                        else
                            counterRB++;
                    }
                }

            answ = max(max(counterLT, counterRT), max(counterLB, max(counterRB, answ)));
        }

    return answ;
}

vector<string> parseWord(const string& str){
    string curr;
    vector<string> answ;

    for (int i = 0; i < str.length(); i++)
        if (str[i]==' '){
            answ.push_back(curr);
            curr = "";
        }
        else
            curr+=str[i];

    answ.push_back(curr);

    return answ;

}

bool Solution::wordPattern(string pattern, string str) {
    const int MAX = 'z' - 'a' + 1;
    string mas[MAX];

    for (int i = 0; i < MAX; i++)
        mas[i] = "";

    vector<string> words = parseWord(str);

    if (words.size() != pattern.length())
        return false;

    for (int i = 0; i < pattern.size(); i++){
        char c = pattern[i];
        if (mas[c - 'a'] == "")
            mas[c - 'a'] = words[i];
        else
        if (mas[c - 'a'] != words[i])
            return false;
    }

    for (int i = 0; i < MAX; i++)
        for (int j = i + 1; j < MAX; j++)
            if (mas[i] != "" && mas[i] == mas[j])
                return false;
    return true;
}

int requrAddValue(TreeNode* node, int * mas, int place){
    mas[place] = node->val;
    int val = 0;

    if (node->left == nullptr && node->right == nullptr){

        for (int i = 0; i <= place; i++)
            val = (val<<1) | mas[i];
        return val;
    }

    if (node->left != nullptr)
        val += requrAddValue(node->left, mas, place + 1);
    if (node->right != nullptr)
        val += requrAddValue(node->right, mas, place + 1);

    return val;

}

int Solution::sumRootToLeaf(TreeNode *root) {
    const int MAX = 1001;
    int mas[MAX];
    return requrAddValue(root, mas ,0);
}

int getNextValue(const string &str, int& place){
    if (place >= str.length())
        return -1;

    int answ = 0;
    while (place < str.length() && str[place] != '.'){
        answ *= 10;
        answ += (str[place] - '0');
        place++;
    }
    place++;

    return answ;
}

int Solution::compareVersion(string version1, string version2) {
    int place1 = 0, place2 = 0;
    while (true){
        int val1 = getNextValue(version1, place1);
        int val2 = getNextValue(version2, place2);
        if (val1 == -1 && val2 == -1)
            return 0;
        if (val1 == -1 && val2 == 0 || val2 == -1 && val1 == 0)
            continue;
        if (val1 != val2)
            return (val1 > val2 ? 1 : -1);
    }
    return 0;
}

string Solution::getHint(string secret, string guess) {
    const int MAX = '9' - '0';
    int cows_mas[MAX + 1];
    for (int i = 0; i < MAX + 1; i++)
        cows_mas[i] = 0;

    int bulls = 0;
    for (int i =0 ; i< secret.size(); i++)
        if (secret[i] == guess[i])
            bulls++;
        else
            cows_mas['9' - secret[i]]++;

    int cows = 0;
    for (int i = 0; i < guess.size(); i++)
        if (secret[i] != guess[i] && cows_mas['9' - guess[i]] != 0){
            cows_mas['9' - guess[i]]--;
            cows++;
        }

    return  to_string(bulls) + "A"  + to_string(cows) + "B";
}

