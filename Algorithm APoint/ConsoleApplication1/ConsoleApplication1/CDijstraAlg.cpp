#include "CDijstraAlg.h"
#include "CGameMap.h"
#include <iostream>>
using namespace std;

CDijstraAlg::~CDijstraAlg()
{
}

void CDijstraAlg::choose(point & choiceNode, int dx, int dy)
{
	int min = INT_MAX;
	int width = m_gameMap->getWidth();
	int height = m_gameMap->getHeight();

	int cx, cy;
	int H;
	list<point>::reverse_iterator curPos; // 반복자
										  // 방문한 노드와 연결된 방문하지 않은 노드들 중 가중치가 가장 작은 노드를 choice
	for (curPos = m_visitNode.rbegin(); curPos != m_visitNode.rend(); curPos++) { //curPos에 갔던 노드들을 넘기고 , curpos이 빌때까지반복
		for (int ty = -1; ty <= 1; ty++) {
			for (int tx = -1; tx <= 1; tx++) {
				cx = curPos->x + tx;
				cy = curPos->y + ty;
				if (cx < 0 || cx > width - 1 || cy < 0 || cy > height - 1 ||
					(tx == 0 && ty == 0))
					continue;

				H = Heuristic(cx, cy, dx, dy);
				if (m_gameMap->getMapVal(cx, cy) + H < min &&	//현재값 + 끝지점의 거리가 min보다 작고
					m_gameMap->getVisitInfo(cx, cy) == false) {							//왔던길 아니라면
					min = m_gameMap->getMapVal(cx, cy) + H; // 현재값을 min에넣어준다.
					choiceNode = { cx, cy };
				}
			}
		}
	}

}

bool CDijstraAlg::findPath(int sx, int sy, int dx, int dy)
{
	m_bFound = false;
	int width = m_gameMap->getWidth();	// 맵크기
	int height = m_gameMap->getHeight(); // 맵크기

	point **parent;					//각 노드의 parent 정보 저장
	parent = new point *[height];
	for (int i = 0; i < width; i++)
		parent[i] = new point[width];

	point choiceNode;				// V-S 의 노드 중 가중치가 가장 작은 노드
	choiceNode = { sx, sy };		// 시작 노드에서 시작
	m_gameMap->setMapVal(sx, sy, 0); // 시작노드의 가중치를 0으로
	parent[sy][sx] = choiceNode;	// 시작지점을넣어준다.

	for (int i = 0; i < width*height; i++) { // 맵크기만큼돈다
		choose(choiceNode, dx, dy); // 8방향중에 제일작은값을 가지고온다.
		m_gameMap->setVisitInfo(choiceNode.x, choiceNode.y, true); // 현재 위치를 갔다로 표시해준다.
		m_visitNode.push_back(choiceNode);	// 갔던 노드들을저장

		if (choiceNode.x == dx && choiceNode.y == dy) {		// 목적지 노드 방문시
			m_bFound = true;
			break;
		}
		// 8방향 간선 완화
		for (int ty = -1; ty <= 1; ty++) {
			for (int tx = -1; tx <= 1; tx++) {
				int nextX = choiceNode.x + tx; // 3방향을검사
				int nextY = choiceNode.y + ty; // 3방향으 검사
				int dist;
				if (nextX < 0 || nextX > width - 1 ||
					nextY < 0 || nextY > height - 1) // out of map range
					continue;
				// Edge relax
				if (m_gameMap->getVisitInfo(nextX, nextY) == false) { // 현재 조사할곳이 간곳이 아니라면
					dist = (tx == 0 || ty == 0) ? 10 : 14;

					if (m_gameMap->getMapVal(choiceNode.x, choiceNode.y) + dist <
						m_gameMap->getMapVal(nextX, nextY)) { // 현재 추가할가중치가 원래있던 가중치보다 작다면 현재 추가할 가중치를 넣어준다.
						int newVal = m_gameMap->getMapVal(choiceNode.x, choiceNode.y) + dist; // 추가할 가중치를 넣어주다.
						m_gameMap->setMapVal(nextX, nextY, newVal); // 위치에 값추가
						parent[nextY][nextX] = choiceNode; // 
					}
				}
			}
		}
	}

	if (m_bFound) { // ??
		point p;
		p = { dx, dy }; // 끝좌표를넣음
		m_path.push(p);
		while (p.x != sx || p.y != sy) { // 끝좌표가 나올때까지 돌린다.
			p = parent[p.y][p.x];
			m_path.push(p);
		}
		return true;
	}


	return false;
}

float CDijstraAlg::Heuristic(int sx, int sy, int dx, int dy)
{
	// 100을한이유는 숫자가 너무작아서 두점사이의거리가 소수점밖에 차이가 나지않아서 확실하게 거리를 벌리기위해서 100을곱했습니다.
	float H;
	int x = 100 * (sx - dx);
	int y = 100 * (sy - dy);
	H = sqrt((x * x) + (y * y));
	return H;
}

void CDijstraAlg::Draw()
{
	m_gameMap->Draw();
	if (m_bFound) {
		point curNode;
		do {
			curNode = m_path.top();
			cout << "(" << curNode.x << ", " << curNode.y << ")==>" << endl;
			m_path.pop();
		} while (!m_path.empty());
		cout << "Congratulation, You've found the shortest path !" << endl;
	}
}