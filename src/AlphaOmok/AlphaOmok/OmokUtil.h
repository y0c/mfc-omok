#pragma once
#include <vector>
#include "Common.h"
using namespace std;

class OmokUtil
{
public:


	/*
		이어진 돌의 최대 개수를 리턴 
		승/ 패 여부체크시 사용 
		@param line
		@param c 
	*/
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
	
	/*
		이어진 돌의 그룹을 리턴 
		@param line 
		@param c
		@param index
		@return Group(startIndex, endIndex) 
	*/
	static Group getSamePieceGroup(vector<char> line, char c, int index) {

		Group indexGroup;

		indexGroup.startIndex = index;
		indexGroup.endIndex   = index;

		if (index - 1 > 0) {
			while (line[--index] == c);
			indexGroup.startIndex = ++index;
		}

		if (index + 1 < line.size() - 1) {
			while ( line[++index] == c);
			indexGroup.endIndex = --index;
		}
		return indexGroup;
	}

	/*
		현재 돌이 배치된라인에서 BLACK 혹은 WHITE 가 몇개 있는지 체크 
		돌이 이어진 여부는 체크하지 않는다. 
		금수 체크시 사용 
		@param line 
		@param c - character(BLACK or WHITE)
	*/
	static int getCharacterCount(vector<char> line, char c) {
		int cnt = 0;
		for (int i = 0; i < line.size() ; i++) {
			if (line[i] == c) {
				cnt++;
			}
		}
		return cnt;
	}

	/*
		라인 배열에서 현재돌의 위치 C를 BLACK OR WHITE 로 변경함 
		@param line
		@param c - character(BLACK or WHITE)
	*/
	static void replaceCurrent(vector<char> &line, char c) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == CURRENT){
				line.at(i) = c;
			}
		}
	}

	static vector<char> sliceLine(vector<char> line, int startIndex, int endIndex) {
		vector<char> result;
		for (int i = startIndex; i < endIndex; i++) {
			result.push_back(line[i]);
		}
		return result;
	}

	static int getCurrentIndexOf(vector<char> line) {
		for (int i = 0; i < line.size(); i++) 
			if (line[i] == CURRENT)
				return i;
		return -1;
	}
};

