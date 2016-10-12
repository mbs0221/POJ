/**
*
* ����XML��Ŀ��˼·��������״̬��DFA
* ��ʼ״̬Ϊ0�����ݲ�ͬ�������ַ�ת����ͬ��״̬
* ��ʶ���ǩ�Ĺ����У�ʹ��STLջ����¼��ͬ<tag>�Ĳ��
* ������ָ��״̬û�кϷ����������£�һ��ת��-1״̬���������ַ���Ϊ��ЧXML
* ���ɨ���������ַ�����Ȼ�������һ���ַ�������
* ���⻹�������Ż��ռ䣬״̬Ϊ-1��ʱ�򣬾Ͳ���Ҫ�ټ������Ը��ַ�����ֱ������ѭ��
* �����ύ��ʱ�򣬲�û����ʶ����һ��
*
**/

#define __EDG__ 1 // ��������VS2015�������⣬��Ҫ���ϸú����˳�������ļ�

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// XML
int POJ3820() {
	char state = 0;// ״̬
	char c = '0';
	int bytes = 0;// ʮ���������ֵ�λ��
	string str, tmp;// str���ڼ�¼��ǩ�е���ĸ���ִ���tmp���ڼ�¼ÿ��������ַ���
	stack<string> tags;// ��¼��ǩ��context
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
		// һ�н��������״̬
		if (tags.empty() && state == 0) {
			// ���ص���ʼ״̬
			// ������Ч���ַ�����ֻҪ����Ϊ��Ч״̬��������ص���ʼ״̬
			// ֱ�����У��Ż������Ч״̬��������һ�е��ж�
			printf("valid\n");
		}
		else {
			// <tag></tag>ƥ��ʧ��
			while (!tags.empty())
				tags.pop();
			state = 0;
			printf("invalid\n");
		}
	}
	return 0;
}