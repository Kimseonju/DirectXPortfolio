#pragma once
#include <math.h>
#include <GameEngine.h>
class CPlayer;
class CBasicMouse;
class CGlobalValue
{
public:
	static CPlayer* MainPlayer;
    static CBasicMouse* MainMouse;

    static float Lerp2DMax(float _Start, float _End, float _Ratio);

    static float Lerp2D(float _Start, float _End, float _Ratio);
};

enum class Object_Dir
{
    Left,
    Right,
    Up,
    Down,
    End
};

enum class Weapon_Type
{
    Melee,
    Range
};
enum class ITEM_TYPE
{
    Weapon_One_Hand,
    Weapon_Two_Hand,
    Acc,
    End
};

enum class ITEM_RANK
{
    Normal,
    High,
    Rare,
    Legend,
    End
};

enum class Mouse_State
{
    World,
    UI,
    End
};
enum class InventoryButton_State
{
    Normal,
    Item,
    NotItem, //아이템장착불가
    End
};

enum class InventoryButton_Slot
{
    Weapon,
    Acc,
    All, 
    End
};

enum class Select_Weapon
{
    Left,
    Right
};

enum class Enemy_State
{
    Idle,
    Move,
    Attack,
    Skill,
    End
};

enum class Belial_Pattern
{
    Sword,
    Laser,
    Bullet,
    End
};

enum Stage_Dir
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    END
};
enum class Stage_State
{
    Idle,
    Spawn,
    Clear,
    End
};
enum class StageType
{
    None,
    Base,
    Start,
    End,
    Shop,
    Restaurant
};


struct StageInfo
{
    //방문했는지
    bool visit;

    //스테이지타입
    //우선순위별
    //-1 없음 0 일반 1 시작방 2 끝방 3 상점 4 식당
    StageType StageType;

    //벽 왼쪽부터 시계방향으로 (왼,위,오,아)
    bool Wall[4];
};
struct StageObjectSpawnInfo
{
    Vector3 Pos;
    Vector3 Rot;
    Vector3 Scale;
    Vector3 Pivot;
    Client_Class_Type ClassType;
    Client_Object_Type ObjectType;
    Client_Enemy_Type EnemyType;
    Door_Dir DoorDir;
    bool			  CreateEnemyEffect;
    int				  CreateEnemyOrder ;
    //몇번 사용했는지
};
struct StageObjectsInfo
{
    std::string Name;
    std::vector<StageObjectSpawnInfo> StageSpawn;
    class CGameObject* TileMap;
    class CGameObject* TileMapObject;
    class CTileMapComponent* TileMapComponent;
    class CTileMapComponent* TileObjectMapComponent;
    int UseCount;
};
enum class WallDir
{
    Left,
    Up,
    Right,
    Down
};

enum UI_ZOrder
{
    BossUI,
    PlayerUI,
    InventoryUI,
    MapUI
};