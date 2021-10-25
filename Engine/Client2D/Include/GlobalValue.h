#pragma once
#include <math.h>
#include <random>
class CPlayer;
class CBasicMouse;
class CGlobalValue
{
public:
	static CPlayer* MainPlayer;
    static CBasicMouse* MainMouse;
    static int GetRandom(int Random);


    static float Lerp2DMax(float _Start, float _End, float _Ratio);

    static float Lerp2D(float _Start, float _End, float _Ratio);
};

enum class Object_Dir
{
    Left,
    Right,
    End
};

enum class RoomCreate_Dir
{
    Left,
    Right,
    Up,
    Down,
    End
};

enum class Room_Dir
{
    Left,
    Right,
    Up,
    Down,
    End
};
enum class Effect_Dir
{
    Left,
    Right,
    Up,
    Down
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