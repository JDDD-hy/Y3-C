#include <stdio.h>
#include <string.h>
#include <time.h>
#define ARR_LEN 10000 // 确保足够大

// abcba --> ^#a#b#c#b#a#$
void preprocessString(char *input, char *processed) {
    int len = strlen(input);
    processed[0] = '^';
    int j = 1;
    for (int i = 0; i < len; i++) {
        processed[j++] = '#';
        processed[j++] = input[i];
    }
    processed[j++] = '#';
    processed[j++] = '$';
    processed[j] = '\0';
}

void findLongestPalindromicSubstring(char *input) {
    int len = strlen(input);
    char processed[2 * len + 3];
    preprocessString(input, processed);

    int n = strlen(processed);
    int P[n]; // 处理后每个元素的回文半径
    memset(P, 0, sizeof(P)); // 初始化结构体或数组，确保它们包含的值都是零

    int C = 0, R = 0; // C:回文中心 R: 最右边界
    for (int i = 1; i < n - 1; i++) {
        int mirr = 2 * C - i; // i关于回文中心的镜像位置
        if (i < R) {
            P[i] = (R - i < P[mirr]) ? R - i : P[mirr];
        }
        // 扩展中心
        while (processed[i + 1 + P[i]] == processed[i - 1 - P[i]]) {
            P[i]++;
        }
        // 更新中心和最右边界
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    // 找到最大回文长度
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    printf("Max length:%d\n", maxLen);

    // 打印最长回文串
    int start = (centerIndex - maxLen) / 2;
    char longestPalindrome[maxLen + 1];
    strncpy(longestPalindrome, input + start, maxLen);
    // 将字符串从start索引开始的字符复制到longestPalindrome中
    longestPalindrome[maxLen] = '\0';
    printf("The longest palindromic substring is: %s\n", longestPalindrome);
}

int main() {
    clock_t begin, end;
    double timeUsed;

    char input[ARR_LEN];
    scanf("%s", input);

    begin = clock();
    findLongestPalindromicSubstring(input);
    end = clock();

    timeUsed = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("程序运行时间: %f 秒\n", timeUsed);
    
    
    return 0;
}