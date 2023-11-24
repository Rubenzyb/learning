/*编写一个程序，从键盘输入一个字符串，分别统计其中的大写字母、小写字母以及数字的个数。
输入
输入字符串，只包括大写字母、小写字母以及数字，长度小于100。
输出
三个数字，分别为大写字母的个数，小写字母的个数，数字的个数，用空格分开。
样例输入 Copy
Areyouready14YesCaptain23
Vi8va7La6Vi5da14I3knowSaint2Peter
样例输出 Copy
3 18 4
6 19 8
提示
使用while(cin>> str){}批量处理数据；*/
#include <bits/stdc++.h>
using namespace std;

string str;

int main() {
    while(cin >> str) {
        int upper = 0;
        int lower = 0;
        int num = 0;
        for(int i = 0; i < str.size(); i++) {
            if(str[i] >= '0' && str[i] <= '9')
                num++;
            else
                if(str[i] >= 'a' && str[i] <= 'z')
                    lower++;
            else
                if(str[i] >= 'A' && str[i] <= 'Z')
                    upper++;
        }
        cout << upper << " " << lower << " " << num << endl;
    }
}