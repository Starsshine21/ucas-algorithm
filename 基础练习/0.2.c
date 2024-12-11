#include <stdio.h>
#include <ctype.h>
#include <string.h>

// ���������ж��ַ��Ƿ�Ϊ��ĸ������
int isAlphanumeric(char c) {
    return isalnum(c);
}

// �������ڽ��ַ�ת��ΪСд��ĸ
char toLower(char c) {
    return tolower(c);
}

// ���������ж��ַ����Ƿ�Ϊ���Ĵ�
int isPalindrome(char *s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        // ��������ĸ�������ַ�
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }

        // ���ַ�ת��ΪСд��ĸ���бȽ�
        if (toLower(s[left]) != toLower(s[right])) {
            return 0; // ���ǻ��Ĵ�
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
