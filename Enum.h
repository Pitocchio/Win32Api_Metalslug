#pragma once


// ====================== Scene ======================== // 
enum class SCENE_TYPE {
	ANITOOL1,
	ANITOOL2,
	MAPTOOL,
	INTRO,
	CHARACTER,
	GAME,
	OUTTRO,
	TYPEEND_SCENE
};


// ====================== Object ======================== // 
enum class OBJECT_TYPE {


	NONE,

	// Map Obj
	ML_LINE,
	MC_CAMERA_FOLLOWPLAYERY,
	MC_CAMERA_ROCK,
	MC_PLAYER_LEFTMOVEROCK,
	MC_ENEMY_SPAWNER,

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
	ANIMATOR2D,
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
	NONE,
	DOWN,
	HOLD,
	UP,
	TYPEEND_KEY
};

enum class KEY_TYPE {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SPACE,
	ESC,
	ENTER,

	Q,
	W,
	E,
	R,
	T,
	Y,
	A,
	S,
	D,
	F,
	Z,
	X,
	C,
	V,
	U,
	I,
	O,
	P,
	TYPEEND_KEY
};


// ====================== Mouse ======================== // 
enum class MOUSE_STATE {
	NONE,
	DOWN,
	HOLD,
	UP,
	TYPEEND_KEY
};

enum class MOUSE_TYPE {
	LBTN,
	MBTN,
	RBTN,
	TYPEEND_MOUSE
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
	NONE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	ORANGE,
	PURPLE,
	TYPEEND_PEN
};






// Map
//
//enum class MAPOBJ_TYPE
//{
//	NONE,
//	LINE,
//	COL_CAMERA_FOLLOWPLAYERY,
//	COL_CAMERA_ROCK,
//	COL_PLAYER_LEFTMOVEROCK,
//	COL_ENEMY_SPAWNER,
//	TYPEEND_EVENT
//};
//


/*
Collider CameraFollowPlayerY

Collider PlayerLeftMoveLock

Collider CameraRock

Collider MonsterSpawn
*/


