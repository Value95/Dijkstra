#include "CGameMap.h"
#include "CDijstraAlg.h"

void main()
{
	CGameMap gameMap(10, 10);
	CDijstraAlg shortPath(&gameMap);

	shortPath.Draw();

	//bool bFound = shortPath.findPath(0, 0, 4, 9);
	//shortPath.Draw();

}