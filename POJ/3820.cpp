/**
*
* 整个XML题目的思路就是有限状态机DFA
* 初始状态为0，根据不同的输入字符转到不同的状态
* 在识别标签的过程中，使用STL栈来记录不同<tag>的层次
* 凡是在指定状态没有合法输入的情况下，一律转到-1状态，即输入字符串为无效XML
* 最后扫描完整个字符串，然后进入下一轮字符串测试
* 在这还可以有优化空间，状态为-1的时候，就不需要再继续测试该字符串，直接跳出循环
* 但是提交的时候，并没有意识到这一点
*
**/

#define __EDG__ 1 // 由于所用VS2015出现问题，需要加上该宏才能顺利编译文件

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// XML
int POJ3820() {
	char state = 0;// 状态
	char c = '0';
	int bytes = 0;// 十六进制数字的位数
	string str, tmp;// str用于记录标签中的字母数字串，tmp用于记录每次输入的字符串
	stack<string> tags;// 记录标签的context
	while (getline(cin, tmp)) {
		for (int i = 0; i < tmp.length(); i++) {
			c = tmp.at(i);
			switch (state) {
			case 0:// Initial
				if (c == '<') {
					state = 1;
				}
				else if (c == '>' || c < 32 || c>127) {
					state = -1;
				}
				else if (c == '&') {
					state = 6;
				}
				break;
			case 1:
				if (c >= 'a'&&c <= 'z' || c >= '0'&&c <= '9') {
					state = 2;
					str.clear();
					str += c;
				}
				else if (c == '/') {
					state = 4;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 2:
				if (c >= 'a'&&c <= 'z' || c >= '0'&&c <= '9') {
					state = 2;
					str += c;
				}
				else if (c == '>') {
					state = 0;// <tag>
					tags.push(str);
				}
				else if (c == '/') {
					state = 3;
				}
				else {
					state = -1;// Invalid:
				}
				break;
			case 3:
				if (c == '>') {
					state = 0;// <tag/>
				}
				else {
					state = -1;// Invalid:
				}
				break;
			case 4:
				if (c >= 'a'&&c <= 'z' || c >= '0'&&c <= '9') {
					state = 5;
					str.clear();
					str += c;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 5:
				if (c >= 'a'&&c <= 'z' || c >= '0'&&c <= '9') {
					str += c;
				}
				else if (c == '>') {
					if (tags.empty()) {
						state = -1;
					}
					else {
						if (tags.top() == str) {
							state = 0;// </tag>
							tags.pop();
						}
						else {
							state = -1;// Invalid
						}
					}
				}
				else {
					state = -1;// Invalid;
				}
				break;
			case 6:
				if (c == 'l' || c == 'g') {
					state = 7;
				}
				else if (c == 'a') {
					state = 8;
				}
				else if (c == 'x') {
					state = 11;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 7:
				if (c == 't') {
					state = 10;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 8:
				if (c == 'm') {
					state = 9;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 9:
				if (c == 'p') {
					state = 10;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 10:// &lt; &gt; &amp;
				if (c == ';') {
					state = 0;
				}
				else {
					state = -1;
				}
				break;
			case 11:
				if (c >= '0'&&c <= '9' || c >= 'a'&&c <= 'f' || c >= 'A'&&c <= 'F') {
					state = 12;
					bytes = 0;
					bytes++;
				}
				else {
					state = -1;// Invalid
				}
				break;
			case 12:
				if (c >= '0'&&c <= '9' || c >= 'a'&&c <= 'f' || c >= 'A'&&c <= 'F') {
					bytes++;
				}
				else if ((c == ';') && (bytes % 2 == 0)) {
					state = 0;// &0xHEX;
				}
				else {
					state = -1;// Invalid
				}
				break;
			default:
				break;// Invalid
			}
		}
		// 一行结束，检查状态
		if (tags.empty() && state == 0) {
			// 最后回到初始状态
			// 所有无效的字符串，只要被置为无效状态，均不会回到初始状态
			// 直到换行，才会清除无效状态，进行下一行的判断
			printf("valid\n");
		}
		else {
			// <tag></tag>匹配失败
			while (!tags.empty())
				tags.pop();
			state = 0;
			printf("invalid\n");
		}
	}
	return 0;
}