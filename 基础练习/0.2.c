#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 函数用于判断字符是否为字母或数字
int isAlphanumeric(char c) {
    return isalnum(c);
}

// 函数用于将字符转换为小写字母
char toLower(char c) {
    return tolower(c);
}

// 函数用于判断字符串是否为回文串
int isPalindrome(char *s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        // 跳过非字母和数字字符
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }

        // 将字符转换为小写字母进行比较
        if (toLower(s[left]) != toLower(s[right])) {
            return 0; // 不是回文串
        }

        left++;
        right--;
    }

    return 1;
}

int main() {
    char input[1000];
    char c;
    int i = 0;
    while((c=getchar()) != '?')
    	input[i++] = c;	

    if (isPalindrome(input)) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
