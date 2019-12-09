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
	list<point>::reverse_iterator curPos; // �ݺ���
										  // �湮�� ���� ����� �湮���� ���� ���� �� ����ġ�� ���� ���� ��带 choice
	for (curPos = m_visitNode.rbegin(); curPos != m_visitNode.rend(); curPos++) { //curPos�� ���� ������ �ѱ�� , curpos�� ���������ݺ�
		for (int ty = -1; ty <= 1; ty++) {
			for (int tx = -1; tx <= 1; tx++) {
				cx = curPos->x + tx;
				cy = curPos->y + ty;
				if (cx < 0 || cx > width - 1 || cy < 0 || cy > height - 1 ||
					(tx == 0 && ty == 0))
					continue;

				H = Heuristic(cx, cy, dx, dy);
				if (m_gameMap->getMapVal(cx, cy) + H < min &&	//���簪 + �������� �Ÿ��� min���� �۰�
					m_gameMap->getVisitInfo(cx, cy) == false) {							//�Դ��� �ƴ϶��
					min = m_gameMap->getMapVal(cx, cy) + H; // ���簪�� min���־��ش�.
					choiceNode = { cx, cy };
				}
			}
		}
	}

}

bool CDijstraAlg::findPath(int sx, int sy, int dx, int dy)
{
	m_bFound = false;
	int width = m_gameMap->getWidth();	// ��ũ��
	int height = m_gameMap->getHeight(); // ��ũ��

	point **parent;					//�� ����� parent ���� ����
	parent = new point *[height];
	for (int i = 0; i < width; i++)
		parent[i] = new point[width];

	point choiceNode;				// V-S �� ��� �� ����ġ�� ���� ���� ���
	choiceNode = { sx, sy };		// ���� ��忡�� ����
	m_gameMap->setMapVal(sx, sy, 0); // ���۳���� ����ġ�� 0����
	parent[sy][sx] = choiceNode;	// �����������־��ش�.

	for (int i = 0; i < width*height; i++) { // ��ũ�⸸ŭ����
		choose(choiceNode, dx, dy); // 8�����߿� ������������ ������´�.
		m_gameMap->setVisitInfo(choiceNode.x, choiceNode.y, true); // ���� ��ġ�� ���ٷ� ǥ�����ش�.
		m_visitNode.push_back(choiceNode);	// ���� ����������

		if (choiceNode.x == dx && choiceNode.y == dy) {		// ������ ��� �湮��
			m_bFound = true;
			break;
		}
		// 8���� ���� ��ȭ
		for (int ty = -1; ty <= 1; ty++) {
			for (int tx = -1; tx <= 1; tx++) {
				int nextX = choiceNode.x + tx; // 3�������˻�
				int nextY = choiceNode.y + ty; // 3������ �˻�
				int dist;
				if (nextX < 0 || nextX > width - 1 ||
					nextY < 0 || nextY > height - 1) // out of map range
					continue;
				// Edge relax
				if (m_gameMap->getVisitInfo(nextX, nextY) == false) { // ���� �����Ұ��� ������ �ƴ϶��
					dist = (tx == 0 || ty == 0) ? 10 : 14;

					if (m_gameMap->getMapVal(choiceNode.x, choiceNode.y) + dist <
						m_gameMap->getMapVal(nextX, nextY)) { // ���� �߰��Ұ���ġ�� �����ִ� ����ġ���� �۴ٸ� ���� �߰��� ����ġ�� �־��ش�.
						int newVal = m_gameMap->getMapVal(choiceNode.x, choiceNode.y) + dist; // �߰��� ����ġ�� �־��ִ�.
						m_gameMap->setMapVal(nextX, nextY, newVal); // ��ġ�� ���߰�
						parent[nextY][nextX] = choiceNode; // 
					}
				}
			}
		}
	}

	if (m_bFound) { // ??
		point p;
		p = { dx, dy }; // ����ǥ������
		m_path.push(p);
		while (p.x != sx || p.y != sy) { // ����ǥ�� ���ö����� ������.
			p = parent[p.y][p.x];
			m_path.push(p);
		}
		return true;
	}


	return false;
}

float CDijstraAlg::Heuristic(int sx, int sy, int dx, int dy)
{
	// 100���������� ���ڰ� �ʹ��۾Ƽ� ���������ǰŸ��� �Ҽ����ۿ� ���̰� �����ʾƼ� Ȯ���ϰ� �Ÿ��� ���������ؼ� 100�����߽��ϴ�.
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