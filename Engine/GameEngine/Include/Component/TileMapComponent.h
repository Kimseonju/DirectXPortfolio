#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/SpriteMesh.h"
#include "../Resource/TileMapCBuffer.h"
#include "Tile.h"

class CTileMapComponent :
	public CPrimitiveComponent
{
	friend class CGameObject;

protected:
	CTileMapComponent();
	CTileMapComponent(const CTileMapComponent& com);
	virtual ~CTileMapComponent();

protected:
	CSharedPtr<CSpriteMesh>     m_Mesh;
	Tile_Shape  m_Shape;
	int         m_CountX;
	int         m_CountY;
	Vector2     m_TileSize;
	Vector2     m_TileImageSize;
	Vector2		m_TileImageFrameSize;
	int			m_FrameMaxX;
	int			m_FrameMaxY;
	std::vector<CTile*>   m_vecTile;
	std::vector<TileInfo>	m_vecTileInfo;
	class CStructuredBuffer* m_WorldBuffer;
	CTileMapCBuffer* m_CBuffer;

public:
	void SetFrameMax(int x, int y);
	void SetTileDefaultFrame(int x, int y);
	void SetTileFrame(int TileIndex, int x, int y);

public:
	virtual class CMesh* GetMesh()  const;
	virtual void SetMesh(class CMesh* pMesh);
	virtual void SetMesh(const std::string& Name);
	virtual void SetMaterial(int SlotIndex, CMaterial* pMaterial);
	virtual void SetMaterial(int SlotIndex, const std::string& Name);
	virtual void AddMaterial(CMaterial* pMaterial);
	virtual void AddMaterial(const std::string& Name);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTileMapComponent* Clone();

private:
	void SetWorldInfo();

public:
	template <typename T>
	void CreateTile(Tile_Shape Shape, int CountX, int CountY,
		const Vector2& TileSize)
	{
		m_Shape = Shape;
		m_CountX = CountX;
		m_CountY = CountY;
		m_TileSize = TileSize;

		m_vecTile.resize(m_CountX * m_CountY);
		m_vecTileInfo.resize(m_CountX * m_CountY);

		for (int i = 0; i < m_CountY; ++i)
		{
			for (int j = 0; j < m_CountX; ++j)
			{
				T* Tile = new T;

				m_vecTile[i * m_CountX + j] = Tile;

				m_vecTileInfo[i * m_CountX + j].Color = Vector4(1.f, 1.f, 1.f, 1.f);
				m_vecTileInfo[i * m_CountX + j].Opacity = 1.f;
			}
		}

		switch (m_Shape)
		{
		case Tile_Shape::Rect:
		{
			Vector2 Pos;

			for (int i = 0; i < m_CountY; ++i)
			{
				Pos.x = 0.f;
				Pos.y = i * m_TileSize.y;
				for (int j = 0; j < m_CountX; ++j)
				{
					Pos.x = j * m_TileSize.x;

					int Index = i * m_CountX + j;

					m_vecTile[Index]->SetPos(Pos);
					m_vecTile[Index]->SetSize(m_TileSize);
					m_vecTile[Index]->SetShape(m_Shape);
					m_vecTile[Index]->SetIndex(j, i, Index);

					if (!m_vecTile[Index]->Init())
						return;
				}
			}
		}
		break;
		case Tile_Shape::Rhombus:
		{
			Vector2 Pos;

			for (int i = 0; i < m_CountY; ++i)
			{
				if (i % 2 == 0)
					Pos.x = 0.f;

				else
					Pos.x = m_TileSize.x * 0.5f;

				Pos.y = i * m_TileSize.y * 0.5f;

				for (int j = 0; j < m_CountX; ++j)
				{
					if (j > 0.f)
						Pos.x += m_TileSize.x;

					int Index = i * m_CountX + j;

					m_vecTile[Index]->SetPos(Pos);
					m_vecTile[Index]->SetSize(m_TileSize);
					m_vecTile[Index]->SetShape(m_Shape);
					m_vecTile[Index]->SetIndex(j, i, Index);

					if (!m_vecTile[Index]->Init())
						return;
				}
			}
		}
		break;
		}

		SetWorldInfo();
	}
};

