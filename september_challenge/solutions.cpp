#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <string>

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
