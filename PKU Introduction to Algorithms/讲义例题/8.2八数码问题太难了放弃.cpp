//下面程序是1号字，所以看不见。请全选，拷贝粘贴到别处后再看#
//八数码问题POJ1077 ，双向广搜 POj 47MS HDU1043 2296MS
#include <iostream>
#include <bitset>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;
int nGoalStatus; //目标状态
bitset<362880> Flags[2]; //节点是否扩展的标记
const int MAXS = 400000;
char result[MAXS]; //结果
struct Node {
	int status; //状态
	int father; //父节点指针
	char move; //父节点到本节点的移动方式 u/d/r/l
	Node(int s, int f, char m) :status(s),
		father(f), move(m) { }
	Node() { }
};
Node myQueue[2][MAXS]; //两个方向的状态队列，状态总数362880
int qHead[2];
int qTail[2];
int matchingStatus; //双向碰到的那个状态
int matchingQ; // 队列matchingQ的队头元素是双向碰到的那个状态
char sz4Moves[] = "udrl";//四种动作
unsigned int factorial[21]; //存放0-20的阶乘。21的阶乘unsigned放不下了
unsigned int GetPermutationNumForInt(int* perInt, int len)
//perInt里放着整数 0 到 len-1 的一个排列，求它是第几个排列
//len不能超过21
{
	unsigned int num = 0;
	bool used[21];
	memset(used, 0, sizeof(bool) * len);
	for (int i = 0; i < len; ++i) {
		unsigned int n = 0;
		for (int j = 0; j < perInt[i]; ++j) {
			if (!used[j])
				++n;
		}
		num += n * factorial[len - i - 1];
		used[perInt[i]] = true;
	}
	return num;
}
template< class T>
unsigned int GetPermutationNum(T s1, T s2, int len)
//给定排列，求序号 。[s1,s1+len)里面放着第0号排列，[s2,s2+len)是要求序号的排列
//两者必须一样长 ，len不能超过21
//排列的每个元素都不一样。返回排列的编号
{
	int perInt[21]; //要转换成 [0,len-1] 的整数的排列
	for (int i = 0; i < len; ++i)
		for (int j = 0; j < len; ++j) {
			if (*(s2 + i) == *(s1 + j)) {
				perInt[i] = j;
				break;
			}
		}
	unsigned int num = GetPermutationNumForInt(perInt, len);
	return num;
}
template <class T>
void GenPermutationByNum(T s1, T s2, int len, unsigned int No)
//根据排列编号，生成排列 len不能超过21
{ //[s1,s1+len) 里面放着第0号 permutation,，排列的每个元素都不一样
	int perInt[21]; //要转换成 [0,len-1] 的整数的排列
	bool used[21];
	memset(used, 0, sizeof(bool) * len);
	for (int i = 0; i < len; ++i) {
		unsigned int tmp; int n = 0; int j;
		for (j = 0; j < len; ++j) {
			if (!used[j]) {
				if (factorial[len - i - 1] >= No + 1) break;
				else No -= factorial[len - i - 1];
			}
		}
		perInt[i] = j;
		used[j] = true;
	}
	for (int i = 0; i < len; ++i)
		*(s2 + i) = *(s1 + perInt[i]);
}
int StrStatusToIntStatus(const char* strStatus)
{
	return GetPermutationNum("012345678", strStatus, 9);
}
void IntStatusToStrStatus(int n, char* strStatus)
{
	GenPermutationByNum((char*)"012345678", strStatus, 9, n);
	strStatus[9] = 0;
}
int NewStatus(int nStatus, char cMove) {
	//求从nStatus经过 cMove 移动后得到的新状态。若移动不可行则返回-1
	char szTmp[20];
	int nZeroPos;
	IntStatusToStrStatus(nStatus, szTmp);
	for (int i = 0; i < 9; ++i)
		if (szTmp[i] == '0') {
			nZeroPos = i;
			break;
		} //返回空格的位置
	switch (cMove) {
	case 'u': if (nZeroPos - 3 < 0) return -1; //空格在第一行
			else {
		szTmp[nZeroPos] = szTmp[nZeroPos - 3];
		szTmp[nZeroPos - 3] = '0';
	}
			break;
	case 'd': if (nZeroPos + 3 > 8) return -1; //空格在第三行
			else {
		szTmp[nZeroPos] = szTmp[nZeroPos + 3];
		szTmp[nZeroPos + 3] = '0';
	}
			break;
	case 'l': if (nZeroPos % 3 == 0) return -1; //空格在第一列
			else {
		szTmp[nZeroPos] = szTmp[nZeroPos - 1];
		szTmp[nZeroPos - 1] = '0';
	}
			break;
	case 'r': if (nZeroPos % 3 == 2) return -1; //空格在第三列
			else {
		szTmp[nZeroPos] = szTmp[nZeroPos + 1];
		szTmp[nZeroPos + 1] = '0';
	}
			break;
	}
	return StrStatusToIntStatus(szTmp);
}
inline char ReverseMove(char c) {
	switch (c) {
	case 'u': return 'd';
	case 'l': return 'r';
	case 'r': return 'l';
	case 'd': return 'u';
	}
	return 0;
}
bool DBfs(int nStatus) {
	int nNewStatus;
	for (int i = 0; i < 2; ++i) {
		Flags[i].reset();
		qHead[i] = 0;
		qTail[i] = 1;
	}
	myQueue[0][0] = Node(nStatus, -1, 0);
	myQueue[1][0] = Node(nGoalStatus, -1, 0);
	Flags[0][nStatus] = 1;
	Flags[1][nGoalStatus] = 1;
	while (qHead[0] != qTail[0] && qHead[1] != qTail[1]) { //两个队列不都为空
		int qNo;
		if (qHead[0] == qTail[0])
			qNo = 1;
		else if (qHead[1] == qTail[1])
			qNo = 0;
		else {
			if (qTail[0] - qHead[0] < qTail[1] - qHead[1])
				qNo = 0;
			else
				qNo = 1;
		}
		int vqNo = 1 - qNo;
		nStatus = myQueue[qNo][qHead[qNo]].status;
		if (Flags[vqNo][nStatus] == 1) { // 出来的元素曾经在另一队列里面
			matchingStatus = nStatus;
			matchingQ = qNo;
			return true;
		}
		else {
			for (int i = 0; i < 4; i++) { //尝试4种移动
				nNewStatus = NewStatus(nStatus, sz4Moves[i]);
				if (nNewStatus == -1) continue; //不可移，试下一种
				if (Flags[qNo][nNewStatus])
					continue; //如果扩展标记已经存在，则不能入队
				Flags[qNo].set(nNewStatus, true); //设上已扩展标记
				//myQueue[qNo][qTail[qNo]].status = nNewStatus; //新节点入队列
				myQueue[qNo][qTail[qNo]] = Node(nNewStatus, qHead[qNo], sz4Moves[i]);
				qTail[qNo] ++;
			}
			qHead[qNo] ++;
		}
	}
	return false;
}
int main()
{
	factorial[0] = factorial[1] = 1;
	for (int i = 2; i < 21; ++i)
		factorial[i] = i * factorial[i - 1];
	char szLine[50]; char szLine2[20];
	while (cin.getline(szLine, 48)) {
		int i, j;
		for (i = 0, j = 0; szLine[i]; i++) {
			if (szLine[i] != ' ') {
				if (szLine[i] == 'x') szLine2[j++] = '0';
				else szLine2[j++] = szLine[i];
			}
		}
		szLine2[j] = 0;
		int sumGoal = 0;
		for (int i = 0; i < 8; ++i)
			sumGoal += i - 1;
		int sumOri = 0;
		for (int i = 0; i < 9; ++i) {
			if (szLine2[i] == '0')
				continue;
			for (int j = 0; j < i; ++j) {
				if (szLine2[j] < szLine2[i] && szLine2[j] != '0')
					sumOri++;
			}
		}
		if (sumOri % 2 != sumGoal % 2) {
			cout << "unsolvable" << endl;
			continue;
		}
		nGoalStatus = StrStatusToIntStatus("123456780");
		if (DBfs(StrStatusToIntStatus(szLine2))) {
			int nMoves = 0;
			int pos;
			if (matchingQ == 0)
				pos = qHead[0];
			else {
				for (int i = 0; i < qTail[0]; ++i)
					if (myQueue[0][i].status == matchingStatus) {
						pos = i;
						break;
					}
			}
			do {
				if (pos) {
					result[nMoves++] = myQueue[0][pos].move;
					pos = myQueue[0][pos].father;
				}
			} while (pos);
			reverse(result, result + nMoves);
			if (matchingQ == 0) {
				for (int i = 0; i < qTail[1]; ++i)
					if (myQueue[1][i].status == matchingStatus) {
						pos = i;
						break;
					}
			}
			else
				pos = qHead[1];
			do {
				if (pos) {
					result[nMoves++] = ReverseMove(myQueue[1][pos].move);
					pos = myQueue[1][pos].father;
				}
			} while (pos);
			for (int i = 0; i < nMoves; ++i)
				cout << result[i];
			cout << endl;
		}
		else cout << "unsolvable" << endl;
	}
	return 0;
}