#include "CGameMap.h"
#include<iostream>

using namespace std;

CGameMap::~CGameMap()
{
}

void CGameMap::InitMap()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x] = 1000;
			m_visitInfo[y][x] = false;

		}
	}

}

void CGameMap::Draw()
{
	cout << "==========================" << endl;
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			cout << m_map[y][x] << "\t";
		}
		cout << endl;
	}
}
