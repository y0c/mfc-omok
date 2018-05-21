#pragma once
#include <vector>
#include "Common.h"
using namespace std;
typedef struct Group{
	int startIndex;
	int endIndex;
} Group;
class OmokUtil
{
public:


	static int getMaxContinueCharacterCount(vector<char> line, char c) {
		int charCount = 0;
		int startIndex = -1;
		int maxCnt = 0;
		vector<int> cntHistory;

		for (int i = 0; i < line.size(); i++) {
			
			if (startIndex != -1) {
				if (line[i] == c ) {
					maxCnt++;
				}
				else {
					startIndex = -1;
					cntHistory.push_back(maxCnt);
					maxCnt = 0;
				}
			}
			else {
				if (line[i] == c) {
					startIndex = i;
					maxCnt++;
				}
			}
		}
		int max = 0;
		if (cntHistory.size() > 0) {
			max = cntHistory[0];
			for (int cnt : cntHistory) {
				if (cnt > max) {
					max = cnt;
				}
			}
		}
		
		printf("\n max : %d\n", max);
		return max;
	}
	static Group getSamePieceGroup(vector<char> line, char c, int index) {

	}
	static int getCharacterCount(vector<char> line, char c) {

	}

	static void replaceCurrent(vector<char> &line, char c) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == CURRENT){
				line.at(i) = c;
			}
		}
	}
};

