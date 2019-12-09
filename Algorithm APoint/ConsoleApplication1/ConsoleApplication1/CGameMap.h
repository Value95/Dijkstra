#pragma once
class CGameMap
{
	int **m_map; //맵의 배열을 저장
	bool **m_visitInfo; // 해당 맵을 방문했는지 검사하기 위한 배열
	int m_width;
	int m_height;


public:
	~CGameMap();
	CGameMap(int w, int h) : m_width(w), m_height(h) {
		m_map = new int *[h];
		m_visitInfo = new bool *[h];

		for (int i = 0; i < h; i++) {  // 0으로 모든 원소 초기화
			m_map[i] = new int[w];
			m_visitInfo[i] = new bool[w];
		}
		InitMap();
	}
	void InitMap();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	void setMapVal(int x, int y, int val) { m_map[y][x] = val; }
	int getMapVal(int x, int y) { return m_map[y][x]; }

	void setVisitInfo(int x, int y, bool val) { m_visitInfo[y][x] = val; }
	bool getVisitInfo(int x, int y) { return m_visitInfo[y][x]; }

	void Draw();


};

