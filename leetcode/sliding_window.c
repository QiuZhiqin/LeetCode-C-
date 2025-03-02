#include "stdlib.h"
#include "stdbool.h"

/* Solution for leetcode problem: https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/ */
int lengthOfLongestSubstring(char* s) {
    int longest_substring_len = 0, str_len = strlen(s);
    int left = 0, right = 0;
    int hash[128] = {0};
    char cur_char;

    while (right < str_len) {
        cur_char = s[right];
        if (hash[cur_char] != 0) {
            longest_substring_len = (right - left) > longest_substring_len ? (right - left) : longest_substring_len;
            hash[s[left]]--;
            left++;
        } else {
            hash[cur_char]++;
            right++;
        }
    }

    longest_substring_len = (right - left) > longest_substring_len ? (right - left) : longest_substring_len;
    return longest_substring_len;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/find-all-anagrams-in-a-string/description/ */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int *ret_array = NULL, array_size = 0;
    int left = 0, right = 0, str_len = strlen(s), target_len = strlen(p);
    int need[26] = {0};

    ret_array = (int*)malloc(sizeof(int) * str_len);
    if (ret_array == NULL) {
        printf("findAnagrams: malloc failed\n");
        return NULL;
    }
    memset(ret_array, 0, sizeof(int) * str_len);

    for (int i = 0; i < target_len; i++) {
        need[p[i] - 'a']++;
    }

    while (right < str_len) {
        need[s[right] - 'a']--; // s[right] concludes in the window.
        while (need[s[right] - 'a'] < 0) { // Too many charactor s[right] in the window, we must move the left pointer till the window is valid.
            need[s[left] - 'a']++;
            left++;
        }
        if (right - left + 1 == target_len) { // The sieze of the window is equal to the size of the target string, meaning we find a anagram.
            ret_array[array_size++] = left;
        }
        right++;
    }

    *returnSize = array_size;
    return ret_array;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/minimum-window-substring/description/ */
char* minWindow(char* s, char* t) {
    int str_len = strlen(s), target_len = strlen(t), min_len = str_len + 1, found = 0;
    int need[128] = {0}, window[128] = {0};
    int left = 0, right = 0, min_l;
    char *ret_str = NULL;

    for (int i = 0; i < target_len; i++) {
        need[t[i]]++;
    }

    ret_str = (char*)malloc(sizeof(char) * (str_len + 1));
    if (ret_str == NULL) {
        printf("minWindow: malloc failed\n");
        return NULL;
    }
    memset(ret_str, 0, sizeof(char) * (str_len + 1));

    while (right < str_len) {
        if (need[s[right]] > 0) {    // s[right] is in the target string.
            window[s[right]]++;
            if (window[s[right]] == need[s[right]]) {    // The number of s[right] in the window is equal to the number of s[right] in the target string.
                found += need[s[right]];
            }
        }

        while (found == target_len)  {    // All charactors in the target string can be found in the window, now we try to shrink the window.
            if (right - left + 1 < min_len) {
                min_l = left;
                min_len = right - left + 1;
            }
            if (need[s[left]] > 0) {
                window[s[left]]--;
                if (window[s[left]] < need[s[left]]) 
                    found -= need[s[left]];
            }
            left++;
        }

        right++;
    }

    if (min_len <= str_len) {
        strncpy(ret_str, s + min_l, min_len);
        ret_str[min_len] = '\0';
    }

    return ret_str;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/permutation-in-string/description/ */
bool checkInclusion(char* s1, char* s2) {
    int s1_len = strlen(s1), s2_len = strlen(s2);
    int need[26] = {0};
    int left = 0, right = 0;

    for (int i = 0; i < s1_len; i++) {
        need[s1[i] - 'a']++;
    }

    while (right < s2_len) {
        need[s2[right] - 'a']--;
        while (need[s2[right] - 'a'] < 0) {
            need[s2[left] - 'a']++;
            left++;
        }

        if (right - left + 1 == s1_len) {
            return true;
        }

        right++;
    }

    return false;
}