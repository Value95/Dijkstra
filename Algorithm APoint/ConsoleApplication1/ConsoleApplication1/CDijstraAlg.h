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
	stack<point> m_path;		// 시작 노드에서 타겟 노드까지의 경로
	list<point> m_visitNode;	// 확장하면서 방문한 노드 저장
	bool m_bFound;
public:
	~CDijstraAlg();
	CDijstraAlg(CGameMap *map) : m_gameMap(map), m_bFound(false) {	}

	void choose(point &choiceNode, int dx, int dy); // Extract Min 영역 - 노드 받아오기
	bool findPath(int sx, int sy, int dx, int dy); // find a shortest path
	float Heuristic(int sx, int sy, int dx, int dy); // 최단거리 구하기
	void Draw();

};
