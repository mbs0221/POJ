/*
*把M个车厢看做是一个队列
*把N条车道看成是N个队列
*于是对每一个车厢，按顺序测试每一个车道
*如果车道i为空，直接入车道i，并且出车厢队列，按在表中顺序记录进入的车道
*如果有一条车道i测试进入成功，就入i车道，出车厢队列，并按顺序记录进入的车道，并且跳出循环测试
*如果车厢尝试进入车道i失败，就换下一个车道i+1
*如果所有车道都失败，就跳出循环，最后输出失败的结果
*如果最终车厢队列为空也一样跳出循环测试
*最后，如果所有车厢都出了车厢队列，说明成功了，然后输出入车道的顺序
*并且从各车厢队列取最小的队首，输出其所在的车道号
*如果车厢队列不为空，有剩余，说明就失败了
*/
#define __EDG__ 1 // 由于所用VS2015出现问题，需要加上该宏才能顺利编译文件

#include <stdio.h>
#include <queue>
#include <stack>

using namespace std;

int nCarriages, nTracks;// 车厢数目，车道数目
int *Carriages;

queue<int> carriages;
queue<int> *tracks;

int POJ3452() {
	int i;// 循环变量
	int no, index;
	while (scanf_s("%d %d", &nCarriages, &nTracks)) {
		if (nCarriages == 0 && nTracks == 0)break;
		// 初始化nTrack条车道
		tracks = new queue<int>[nTracks];
		// 记录车厢进入线路顺序
		Carriages = new int[nCarriages];
		// 输入车厢序列
		for (i = 0; i < nCarriages; i++) {
			scanf_s("%d", &no);
			carriages.push(no);
		}
		i = 0;
		index = 0;
		// 每条车道都没有失败的情况下继续循环
		// 若全部车道测试失败或是全部车厢出队成功，就是跳出循环
		while (!carriages.empty() && i < nTracks) {
			for (i = 0; i < nTracks; i++) {
				// 只要车道不为空且车厢头小于车道尾就继续
				if (!tracks[i].empty() && carriages.front() < tracks[i].back()) {
					continue;
				}
				// 车道i为空或是车厢头大于车道尾，直接放进去
				tracks[i].push(carriages.front());// index车厢进入i车道					
				carriages.pop();// index车厢出队列
				Carriages[index++] = i + 1;// 按顺序记录车厢进入的车道
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
				int T = 0;// 队首最小车厢号所在车道
				for (i = 0; i < nTracks; i++) {
					if (!tracks[i].empty()) {
						if (tracks[i].front() < min) {
							min = tracks[i].front();
							T = i;
						}
					}
				}
				count++;
				tracks[T].pop();// 出队
				printf("%d", T + 1);
				if (count < index)printf(" ");// 格式化输出结果
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