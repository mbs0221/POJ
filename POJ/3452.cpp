/*
*��M�����ῴ����һ������
*��N������������N������
*���Ƕ�ÿһ�����ᣬ��˳�����ÿһ������
*�������iΪ�գ�ֱ���복��i�����ҳ�������У����ڱ���˳���¼����ĳ���
*�����һ������i���Խ���ɹ�������i��������������У�����˳���¼����ĳ�������������ѭ������
*������᳢�Խ��복��iʧ�ܣ��ͻ���һ������i+1
*������г�����ʧ�ܣ�������ѭ����������ʧ�ܵĽ��
*������ճ������Ϊ��Ҳһ������ѭ������
*���������г��ᶼ���˳�����У�˵���ɹ��ˣ�Ȼ������복����˳��
*���ҴӸ��������ȡ��С�Ķ��ף���������ڵĳ�����
*���������в�Ϊ�գ���ʣ�࣬˵����ʧ����
*/
#define __EDG__ 1 // ��������VS2015�������⣬��Ҫ���ϸú����˳�������ļ�

#include <stdio.h>
#include <queue>
#include <stack>

using namespace std;

int nCarriages, nTracks;// ������Ŀ��������Ŀ
int *Carriages;

queue<int> carriages;
queue<int> *tracks;

int POJ3452() {
	int i;// ѭ������
	int no, index;
	while (scanf_s("%d %d", &nCarriages, &nTracks)) {
		if (nCarriages == 0 && nTracks == 0)break;
		// ��ʼ��nTrack������
		tracks = new queue<int>[nTracks];
		// ��¼���������·˳��
		Carriages = new int[nCarriages];
		// ���복������
		for (i = 0; i < nCarriages; i++) {
			scanf_s("%d", &no);
			carriages.push(no);
		}
		i = 0;
		index = 0;
		// ÿ��������û��ʧ�ܵ�����¼���ѭ��
		// ��ȫ����������ʧ�ܻ���ȫ��������ӳɹ�����������ѭ��
		while (!carriages.empty() && i < nTracks) {
			for (i = 0; i < nTracks; i++) {
				// ֻҪ������Ϊ���ҳ���ͷС�ڳ���β�ͼ���
				if (!tracks[i].empty() && carriages.front() < tracks[i].back()) {
					continue;
				}
				// ����iΪ�ջ��ǳ���ͷ���ڳ���β��ֱ�ӷŽ�ȥ
				tracks[i].push(carriages.front());// index�������i����					
				carriages.pop();// index���������
				Carriages[index++] = i + 1;// ��˳���¼�������ĳ���
				break;
			}
		}
		if (carriages.empty()) {	
			for (i = 0; i < index - 1; i++) {
				printf("%d ", Carriages[i]);
			}
			printf("%d\n", Carriages[i]);
			int count = 0;
			while (count < index) {
				int min = INT_MAX;
				int T = 0;// ������С��������ڳ���
				for (i = 0; i < nTracks; i++) {
					if (!tracks[i].empty()) {
						if (tracks[i].front() < min) {
							min = tracks[i].front();
							T = i;
						}
					}
				}
				count++;
				tracks[T].pop();// ����
				printf("%d", T + 1);
				if (count < index)printf(" ");// ��ʽ��������
			}
			printf("\n");
		}
		else {
			while(!carriages.empty())
				carriages.pop();
			printf("Transportation failed\n");	
		}
	}
	return 0;
}