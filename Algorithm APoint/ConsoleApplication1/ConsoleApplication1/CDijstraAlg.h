#pragma once
#include <stack>
#include <list>
using namespace std;
#include <iostream>
#include <cmath>


class CGameMap;

struct point {
	int x;
	int y;
};

class CDijstraAlg
{
	CGameMap *m_gameMap;
	stack<point> m_path;		// ���� ��忡�� Ÿ�� �������� ���
	list<point> m_visitNode;	// Ȯ���ϸ鼭 �湮�� ��� ����
	bool m_bFound;
public:
	~CDijstraAlg();
	CDijstraAlg(CGameMap *map) : m_gameMap(map), m_bFound(false) {	}

	void choose(point &choiceNode, int dx, int dy); // Extract Min ���� - ��� �޾ƿ���
	bool findPath(int sx, int sy, int dx, int dy); // find a shortest path
	float Heuristic(int sx, int sy, int dx, int dy); // �ִܰŸ� ���ϱ�
	void Draw();

};
