#include "Navigation2D.h"

CNavigation2D::CNavigation2D() :
	m_InfoManager(nullptr)
{
}

CNavigation2D::~CNavigation2D()
{
}

bool CNavigation2D::FindPath(const Vector3& Start, const Vector3& Goal,
	std::vector<Vector3>& vecPath)
{
	if (!m_NavData)
		return false;

	// ���� Ÿ�ϰ� ����Ÿ���� �ε����� ���´�.
	int	GoalIndex = m_NavData->GetTileIndex(Goal);

	if (GoalIndex == -1)
		return false;

	int	StartIndex = m_NavData->GetTileIndex(Start);

	if (StartIndex == -1)
		return false;

	vecPath.clear();

	NavInfo* StartInfo = &m_InfoManager->vecNavInfo[StartIndex];
	NavInfo* GoalInfo = &m_InfoManager->vecNavInfo[GoalIndex];

	if (StartInfo == GoalInfo)
	{
		vecPath.push_back(Goal);
		return true;
	}

	m_InfoManager->UseCount = 0;
	m_InfoManager->OpenCount = 0;

	m_InfoManager->vecOpen[m_InfoManager->OpenCount] = StartInfo;
	++m_InfoManager->OpenCount;

	m_InfoManager->vecUse[m_InfoManager->UseCount] = StartInfo;
	++m_InfoManager->UseCount;
	m_InfoManager->vecUse[m_InfoManager->UseCount] = GoalInfo;
	++m_InfoManager->UseCount;

	NavInfo* Node = nullptr;

	while (m_InfoManager->OpenCount > 0)
	{
		--m_InfoManager->OpenCount;
		Node = m_InfoManager->vecOpen[m_InfoManager->OpenCount];

		// ����������� ������ش�.
		Node->Type = Nav_Insert_Type::Close;

		// �ֺ� 8���� ��带 ���´�.
		// �Ʒ� �Լ��� ���� ã���� ��� ��θ� ������ְ� true�� ��ȯ�Ѵ�.
		if (FindNode(StartInfo, GoalInfo, Goal, vecPath))
			break;

		// ���� ���� ã�ƾ� �Ѵٸ� ������Ͽ� �� �ִ� ������ �������ֵ��� �Ѵ�.
		std::sort(m_InfoManager->vecOpen.begin(),
			m_InfoManager->vecOpen.begin() + m_InfoManager->OpenCount,
			CNavigation2D::SortOpenList);
	}

	// ��ã�Ⱑ �����ٸ� ����ߴ� ������ �ʱ�ȭ �����ش�.
	for (int i = 0; i < m_InfoManager->UseCount; ++i)
	{
		m_InfoManager->vecUse[i]->Clear();
	}

	return true;
}

bool CNavigation2D::FindNode(NavInfo* Node, NavInfo* GoalNode,
	const Vector3& Goal, std::vector<Vector3>& vecPath)
{
	// 8������ �̿���带 ���ϱ� ���� x�� y�� �ε����� ���Ѵ�.
	int	IndexX = Node->IndexX;
	int	IndexY = Node->IndexY;

	// Ÿ�� 1���� ũ�⸦ ���Ѵ�.
	const Vector2& TileSize = Node->Tile->GetSize();

	NavInfo* Neighbor[ND_End] = {};

	// ���� Ÿ���� ��翡 ���� 8���� ��带 �����ִ� ����� �޶�����.
	// �׷��Ƿ� Ÿ���� ��翡 ���� 8������ ��带 �����ִ� switch����
	// �ۼ��Ѵ�.
	switch (m_NavData->GetTileShape())
	{
	case Tile_Shape::Rect:
		Neighbor[ND_Top] = m_InfoManager->GetNavInfo(IndexX, IndexY + 1);
		Neighbor[ND_RightTop] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY + 1);
		Neighbor[ND_Right] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY);
		Neighbor[ND_RightBottom] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY - 1);
		Neighbor[ND_Bottom] = m_InfoManager->GetNavInfo(IndexX, IndexY - 1);
		Neighbor[ND_LeftBottom] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY - 1);
		Neighbor[ND_Left] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY);
		Neighbor[ND_LeftTop] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY + 1);
		break;
	case Tile_Shape::Rhombus:
		if (IndexY % 2 == 0)
		{
			Neighbor[ND_RightTop] = m_InfoManager->GetNavInfo(IndexX, IndexY + 1);
			Neighbor[ND_RightBottom] = m_InfoManager->GetNavInfo(IndexX, IndexY - 1);
			Neighbor[ND_LeftBottom] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY - 1);
			Neighbor[ND_LeftTop] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY + 1);
		}

		else
		{
			Neighbor[ND_RightTop] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY + 1);
			Neighbor[ND_RightBottom] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY - 1);
			Neighbor[ND_LeftBottom] = m_InfoManager->GetNavInfo(IndexX, IndexY - 1);
			Neighbor[ND_LeftTop] = m_InfoManager->GetNavInfo(IndexX, IndexY + 1);
		}

		Neighbor[ND_Top] = m_InfoManager->GetNavInfo(IndexX, IndexY + 2);
		Neighbor[ND_Bottom] = m_InfoManager->GetNavInfo(IndexX, IndexY - 2);
		Neighbor[ND_Left] = m_InfoManager->GetNavInfo(IndexX - 1, IndexY);
		Neighbor[ND_Right] = m_InfoManager->GetNavInfo(IndexX + 1, IndexY);
		break;
	}

	// �̿��� ����ŭ �ݺ��Ѵ�.
	for (int i = 0; i < ND_End; ++i)
	{
		if (!Neighbor[i])
			continue;

		// �̿���尡 �� �� ���� ���̶�� üũ�� �����Ѵ�.
		if (Neighbor[i]->Tile->GetTileType() == Tile_Type::Wall)
			continue;

		// �̿���尡 ������Ͽ� �� ����� �����Ѵ�.
		if (Neighbor[i]->Type == Nav_Insert_Type::Close)
			continue;

		Neighbor_Dir	Dir1 = ND_End, Dir2 = ND_End;

		if (m_NavData->GetTileShape() == Tile_Shape::Rect)
		{
			switch (i)
			{
			case ND_RightTop:
				Dir1 = ND_Top;
				Dir2 = ND_Right;
				break;
			case ND_RightBottom:
				Dir1 = ND_Bottom;
				Dir2 = ND_Right;
				break;
			case ND_LeftTop:
				Dir1 = ND_Top;
				Dir2 = ND_Left;
				break;
			case ND_LeftBottom:
				Dir1 = ND_Bottom;
				Dir2 = ND_Left;
				break;
			}
		}

		else
		{
			switch (i)
			{
			case ND_Top:
				Dir1 = ND_RightTop;
				Dir2 = ND_LeftTop;
				break;
			case ND_Bottom:
				Dir1 = ND_RightBottom;
				Dir2 = ND_LeftBottom;
				break;
			case ND_Left:
				Dir1 = ND_LeftTop;
				Dir2 = ND_LeftBottom;
				break;
			case ND_Right:
				Dir1 = ND_RightBottom;
				Dir2 = ND_RightTop;
				break;
			}
		}

		if (Dir1 != ND_End || Dir2 != ND_End)
		{
			if (Neighbor[Dir1] && Neighbor[Dir2])
			{
				if (Neighbor[Dir1]->Tile->GetTileType() == Tile_Type::Wall &&
					Neighbor[Dir2]->Tile->GetTileType() == Tile_Type::Wall)
					continue;
			}

			else if (Neighbor[Dir1])
			{
				if (Neighbor[Dir1]->Tile->GetTileType() == Tile_Type::Wall)
					continue;
			}

			else if (Neighbor[Dir2])
			{
				if (Neighbor[Dir2]->Tile->GetTileType() == Tile_Type::Wall)
					continue;
			}
		}

		// �����ߴ��� �Ǵ��ϰ� �ƴ϶�� ��������� �������ش�.
	}

	return false;
}

bool CNavigation2D::SortOpenList(NavInfo* Src, NavInfo* Dest)
{
	return Src->Total > Dest->Total;
}
