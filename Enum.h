#pragma once


// ====================== Scene ======================== // 
enum class SCENE_TYPE {
	TOOL,
	INTRO,
	CHARACTER,
	GAME,
	OUTTRO,
	TYPEEND_SCENE
};


// ====================== Object ======================== // 
enum class OBJECT_TYPE {

	// CStage
	S_LANDSCAPE,
	S_GROUND,

	// CMapCollider
	C_CAMERACOLLIDER,
	C_ENEMYCOLLIDER,
	C_GROUNDCOLLIDER,

	// CMoveobj
	// Projectile
	M_PLAYER_BULLET,
	M_PLAYER_GRENADE,
	M_ZOMBIE_LIQUID,
	M_REBEL_GRENADE,
	//Mobj
	M_PLAYER,
	M_ZOMBIE,
	M_MIDDLEBOSS,
	M_FINALBOSS,
	M_RABEL,
	M_PRISONER,

	// ITEM
	I_HEAVYMACHINRGUN,
	I_GRENADE,
	I_FOOD,


	TYPEEND_OBJECT

};

enum class ATTACKOBJ_WEAPON_TYPE
{
	
	// PLAYER, REBEL
	KNIFE,
	GRENADE,

	// PLAYER
	BASICGUN,
	HEAVYMACHIBEGUN,

	// ZOMBIE
	LIQUID,

	TYPEEND_MOVEOBJ_WEAPON

	

};


// ====================== Component ======================== // 
enum class COMPONENT_TYPE {
	TRANSFORM2D,
	COLLIDER2D,
	BOXCOLLIDER2D,
	LINECOLLIDER2D,
	ANIMATOR,
	RIGIDBODY2D,
	RAYCAST2D,
	TYPEEND_COMPONENT
};

enum class COLLISON_TYPE {
	AABB2D,
	LINE_BOX,
	TYPEEND_COLLISION
};

enum class COLLIDER_TYPE {
	BOX2D,
	LINE2D,
	TYPEEND_COLLIDER
};


// ====================== State ======================== // 

enum class OBJECT_STATE
{
	IDLE,
	WALK,
	ATTACK,
	DEAD,
	JUMP,
	TYPEEND_OBJECT_STATE
};

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK,
	DEAD,
	TYPEEND_PLAYER_STATE

};






// ====================== Key ======================== // 
enum class KEY_STATE {
	KEY_NONE,
	KEY_DOWN,
	KEY_HOLD,
	KEY_UP,
	TYPEEND_KEY
};

enum class KEY_TYPE {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SPACE,
	Z, // Jump
	X, // 공격
	S, // 수류탄
	P, // 동전
	L, // 개발자 모드
	ESC, // pause
	TYPEEND_KEY
};

// ====================== Event ======================== // 
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,

	TYPEEND_EVENT
};

// ====================== GDI ======================== // 
enum class BRUSH_TYPE
{
	HOLLOW,
	TYPEEND_BRUSH
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	TYPEEND_PEN
};
