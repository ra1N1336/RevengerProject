#pragma once
#include "stdafx.h"


typedef unsigned char uint8;
typedef unsigned char BYTE;
typedef unsigned char byte;

class KeyValues
{
public:
	char _pad[0x20];//csgo, for css its a diff size
};

inline void**& getvtable(void* inst, size_t offset = 0)
{

	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	if (!inst && !offset)
		return NULL;
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	if (!inst && offset == 0)
		return NULL;

	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];
typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;
typedef float					vec_t;

class VMatrix;


//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150
#define CURRENTCOMMANDOFFSET 0x16E8
#define CURRENTPLAYERCOMMANDOFFSET 0x1640
#define PREIDCTIONSEEDOFFSET 0x30
#define PREDICTIONPLAYEROFFSET 0x54
#define GLOBALSOFFSET 0x53
#define WEAPONDATA_MAXRANGEOFFSET 0x86C
#define WEAPONDATA_DAMAGEOFFSET 0x868
#define WEAPONDATA_RANGEMODIFIEROFFSET 0x870
#define WEAPONDATA_PENETRATIONPOWEROFFSET 0x864
#define INPUTOFFSET 0x5F
#define GETSPREADOFFSET 0xA20
#define GETCONEOFFSET 0x744
#define UPDATEACCURACYPENALTYOFFSET 0x748
#define WEAPONIDOFFSET 0x6D8
#define WEAPONDATAOFFSET 0x708
#define GETNAMEOFFSET 0x5CC
#define APPSYSTEMFACTORYOFFSET 0x3D
#define CLIENTFACTORYOFFSET 0x75
#define GLOWINDEXOFFSET 0x1DB8

//LIFESTATE
#define	LIFE_ALIVE				0 
#define	LIFE_DYING				1 
#define	LIFE_DEAD				2 
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

/* MOVE TYPES */
enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

#include "SDK_Others.h"

class ISurface;
class IPanel;
class HLCLient;
class CEntityList;
class CEngineClient;
class CInput;
class CGlowObjectManager;
class IVModelInfo;
class IVModelRender;
class CPrediction;
class CGameMovement;
class IMoveHelper;
class CGlobalVars;
class IEngineTrace;
class IPhysicsSurfaceProps;
class CDebugOverlay;
class IMaterialSystem;
class IGameEventManager2;
class IVRenderView;
class ICVar;



class CInterfaces
{
private:
	void* GetPointer(const char* Module, const char* InterfaceName)
	{
		void* Interface = NULL;
		char PossibleInterfaceName[1024];

		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");
		for (int i = 1; i < 100; i++)
		{
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				//#ifdef DEBUG
				cout << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				//#endif		

				break;
			}

			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				//#ifdef DEBUG
				cout << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				//#endif		
				break;
			}
		}

		return Interface;
	}
	void* GetInterfacePtr(const char* interfaceName, const char* ptrName, CreateInterface_t pInterface)
	{

		char szDebugString[2048];

		std::string sinterface = "";
		std::string interfaceVersion = "0";

		for (int i = 0; i <= 99; i++)
		{
			sinterface = interfaceName;
			sinterface += interfaceVersion;
			sinterface += std::to_string(i);

			void* funcPtr = pInterface(sinterface.c_str(), NULL);

			if ((DWORD)funcPtr != 0x0)
			{

				sprintf_s(szDebugString, "%s: 0x%x (%s%s%i)", ptrName, (DWORD)funcPtr, interfaceName, interfaceVersion.c_str(), i);
				//#ifdef DEBUG
				cout << iblue << ptrName << igreen << ": 0x" << funcPtr << "(" << iyellow << interfaceName << interfaceVersion << i << igreen << ")" << white << endl;
				//#endif		
				return funcPtr;
			}
			if (i >= 99 && interfaceVersion == "0")
			{
				interfaceVersion = "00";
				i = 0;
			}
			else if (i >= 99 && interfaceVersion == "00")
			{

				sprintf_s(szDebugString, "%s: 0x%x (error)", ptrName, (DWORD)funcPtr);
				cout << ired << ptrName << ": 0x" << funcPtr << " (ERROR)" << white << endl;
			}
		}
		return 0;
	}
public:
	inline void* CaptureInterface(const char* chHandle, const char* chInterfaceName)
	{
		volatile auto handlegotten = (GetModuleHandleA(chHandle) != nullptr);
		while (!GetModuleHandleA(chHandle)) Sleep(100);
		void* fnFinal = nullptr;
		auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
		auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(chHandle), "CreateInterface"));
		delete PossibleInterfaceName;
		return fnFinal;
	}
	void InitialiseSDK()
	{
		DWORD dwInitAddress = Utils.PatternSearch("engine.dll", (PBYTE)"\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\x53\x56\x57\xE8\x00\x00\x00\x00\x83\x3D\x00\x00\x00\x00\x00", "xxxxx????xxxx????xx?????", NULL, NULL);
		cout << igreen << "dwInitAddress: " << ired << "0x" << dwInitAddress << white << endl;

		DWORD p = Utils.PatternSearch("client.dll", (BYTE*)"\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xA8\x01\x75\x1A\x83\xC8\x01\xA3\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56", "xx????????xxxxxxxx????x????x????x????xxxx????x????x", NULL, NULL);

		if (p)
		{
			pClientMode = **(DWORD***)(p + 2);
			pClientMode = pClientMode;
		}

		cout << iblue << "pClientMode" << igreen << ": 0x" << pClientMode << white << endl;

		CreateInterfaceFn fnEngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
		CreateInterfaceFn AppSystemFactory = (CreateInterfaceFn)**(PDWORD*)(dwInitAddress + 0x3D);
		CreateInterfaceFn MaterialSystemFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("materialsystem.dll"), "CreateInterface");
		CreateInterfaceFn ClientFactory = (CreateInterfaceFn)**(PDWORD*)(dwInitAddress + 0x75);
		CreateInterfaceFn StdFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vstdlib.dll"), "CreateInterface");

		typedef CGlowObjectManager*(__thiscall* GetGlowObjectManager_t)(void);
		static GetGlowObjectManager_t GetGlowObjectManager = (GetGlowObjectManager_t)Utils.PatternSearch("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\xA8\x01\x75\x4E", "x????xxxx", NULL, NULL);
		g_pGlowObjectManager = GetGlowObjectManager();
		cout << iblue << "g_pGlowObjectManager:" << igreen << g_pGlowObjectManager << endl;

		pSurface = (ISurface*)GetInterfacePtr("VGUI_Surface", "g_pSurface", AppSystemFactory);
		pPanel = (IPanel*)GetInterfacePtr("VGUI_Panel", "g_pPanel", AppSystemFactory);
		pClient = (HLCLient*)GetInterfacePtr("VClient", "g_pClient", ClientFactory);
		pEngine = (CEngineClient*)GetInterfacePtr("VEngineClient", "g_pEngine", AppSystemFactory);
		pEntList = (CEntityList*)GetInterfacePtr("VClientEntityList", "g_pEntList", ClientFactory);
		g_pDebugOverlay = (CDebugOverlay*)GetInterfacePtr("VDebugOverlay", "g_pDebugOverlay", AppSystemFactory);
		pTrace = (IEngineTrace*)GetInterfacePtr("EngineTraceClient", "g_pEngineTraceClient", AppSystemFactory);
		g_pModelInfo = (IVModelInfo*)GetInterfacePtr("VModelInfoClient", "g_pModelInfo", AppSystemFactory);
		g_pModelRender = (IVModelRender*)GetInterfacePtr("VEngineModel", "g_ModelRender", AppSystemFactory);
		g_pPred = (CPrediction*)GetInterfacePtr("VClientPrediction", "g_pPred", ClientFactory);
		g_pGameMovement = (CGameMovement*)GetInterfacePtr("GameMovement", "g_pGameMovement", ClientFactory);
		pPhysProps = (IPhysicsSurfaceProps*)GetInterfacePtr("VPhysicsSurfaceProps", "g_pPhysprops", AppSystemFactory);
		pMaterialSystem = (IMaterialSystem*)GetInterfacePtr("VMaterialSystem", "pMaterialSystem", MaterialSystemFactory);
		g_pRenderView = (IVRenderView*)GetInterfacePtr("VEngineRenderView", "g_pRenderView", AppSystemFactory);
		pGlobalVars = *(CGlobalVars**)(((*(PDWORD*)pClient)[0]) + GLOBALSOFFSET);
		pGlobalVars = (CGlobalVars*)*(PDWORD)pGlobalVars;
		cout << iblue << "pGlobalVars " << igreen << ": 0x" << pGlobalVars << white << endl;
		pInput = *(CInput**)((*(DWORD**)pClient)[15] + 0x1);
		g_ICVars = (ICVar*)GetInterfacePtr("VEngineCvar", "g_pCVars", StdFactory);
		//g_GameEventMgr = (IGameEventManager2*)GetInterfacePtr("GAMEEVENTSMANAGER", "g_pGameEventsMgr", fnEngineFactory);
		g_GameEventMgr = (IGameEventManager2*)fnEngineFactory("GAMEEVENTSMANAGER002", NULL);



	}
private:
	bool InitialisedSuccessfuly = false;
public:
	ISurface* pSurface;
	DWORD* pClientMode;
	IPanel* pPanel;
	HLCLient* pClient;
	CEntityList* pEntList;
	CEngineClient* pEngine;
	CInput* pInput;
	CGlowObjectManager* g_pGlowObjectManager;
	IVModelInfo* g_pModelInfo;
	IVModelRender* g_pModelRender;
	CPrediction* g_pPred;
	CGameMovement* g_pGameMovement;
	IMoveHelper* g_pMoveHelper;
	CGlobalVars* pGlobalVars;
	IEngineTrace* pTrace;
	IGameEventManager2* pGameEventManager;
	IPhysicsSurfaceProps* pPhysProps;
	CDebugOverlay* g_pDebugOverlay;
	IMaterialSystem* pMaterialSystem;
	IVRenderView* g_pRenderView;
	ICVar* g_ICVars;
	IGameEventManager2* g_GameEventMgr;
};
extern CInterfaces Interfaces;

#include "Math.h"

#include "checksum_crc.h"
#include "dt_recv2.h"
#include "NetVars.h"


#include "ISurface.h"
#include "CClient.h"
#include "EngineClient.h"
#include "Entitys.h"
#include "EntList.h"
#include "DebugOverlay.h"
#include "CTrace.h"
#include "IVRenderView.h"
#include "CModelInfo.h"
#include "CInput.h"
#include "ICVars.h"
#include "CGlobleVars.h"
#include "CGameMovement.h"
#include "CPred.h"
#include "CGlow.h"

void UTIL_TracePos(Ray_t &ray, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);
void UTIL_TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);
void UTIL_ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr);
bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace);

/* FIRE BULLET DATA */
struct FireBulletData
{
	FireBulletData(const Vector &eye_pos)
		: src(eye_pos)
	{
	}
	Vector          src;
	trace_t         enter_trace;
	Vector          direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

/* HITGROUP DEFINITIONS */
#define		HITGROUP_GENERIC    0
#define		HITGROUP_HEAD       1
#define		HITGROUP_CHEST      2
#define		HITGROUP_STOMACH    3
#define		HITGROUP_LEFTARM    4    
#define		HITGROUP_RIGHTARM   5
#define		HITGROUP_LEFTLEG    6
#define		HITGROUP_RIGHTLEG   7
#define		HITGROUP_GEAR       10

typedef bool(*ShouldHitFunc_t)(IHandleEntity *pHandleEntity, int contentsMask);

enum class CSGOClassID
{
	CTestTraceline = 189,
	CTEWorldDecal = 190,
	CTESpriteSpray = 187,
	CTESprite = 186,
	CTESparks = 185,
	CTESmoke = 184,
	CTEShowLine = 182,
	CTEProjectedDecal = 179,
	CTEPlayerDecal = 178,
	CTEPhysicsProp = 175,
	CTEParticleSystem = 174,
	CTEMuzzleFlash = 173,
	CTELargeFunnel = 171,
	CTEKillPlayerAttachments = 170,
	CTEImpact = 169,
	CTEGlowSprite = 168,
	CTEShatterSurface = 181,
	CTEFootprintDecal = 165,
	CTEFizz = 164,
	CTEExplosion = 162,
	CTEEnergySplash = 161,
	CTEEffectDispatch = 160,
	CTEDynamicLight = 159,
	CTEDecal = 157,
	CTEClientProjectile = 156,
	CTEBubbleTrail = 155,
	CTEBubbles = 154,
	CTEBSPDecal = 153,
	CTEBreakModel = 152,
	CTEBloodStream = 151,
	CTEBloodSprite = 150,
	CTEBeamSpline = 149,
	CTEBeamRingPoint = 148,
	CTEBeamRing = 147,
	CTEBeamPoints = 146,
	CTEBeamLaser = 145,
	CTEBeamFollow = 144,
	CTEBeamEnts = 143,
	CTEBeamEntPoint = 142,
	CTEBaseBeam = 141,
	CTEArmorRicochet = 140,
	CTEMetalSparks = 172,
	CSteamJet = 135,
	CSmokeStack = 128,
	DustTrail = 238,
	CFireTrail = 62,
	SporeTrail = 244,
	SporeExplosion = 243,
	RocketTrail = 241,
	SmokeTrail = 242,
	CPropVehicleDriveable = 117,
	ParticleSmokeGrenade = 240,
	CParticleFire = 96,
	MovieExplosion = 239,
	CTEGaussExplosion = 167,
	CEnvQuadraticBeam = 55,
	CEmbers = 45,
	CEnvWind = 59,
	CPrecipitation = 111,
	CPrecipitationBlocker = 112,
	CBaseTempEntity = 18,
	NextBotCombatCharacter = 0,
	CBaseAttributableItem = 4,
	CEconEntity = 44,
	CWeaponXM1014 = 236,
	CWeaponTaser = 231,
	CSmokeGrenade = 126,
	CWeaponSG552 = 228,
	CWeaponSawedoff = 224,
	CWeaponNOVA = 220,
	CIncendiaryGrenade = 85,
	CMolotovGrenade = 93,
	CWeaponM3 = 212,
	CKnifeGG = 90,
	CKnife = 89,
	CHEGrenade = 82,
	CFlashbang = 64,
	CWeaponElite = 203,
	CDecoyGrenade = 40,
	CDEagle = 39,
	CWeaponUSP = 235,
	CWeaponM249 = 211,
	CWeaponUMP45 = 234,
	CWeaponTMP = 233,
	CWeaponTec9 = 232,
	CWeaponSSG08 = 230,
	CWeaponSG556 = 229,
	CWeaponSG550 = 227,
	CWeaponScout = 226,
	CWeaponSCAR20 = 225,
	CSCAR17 = 122,
	CWeaponP90 = 223,
	CWeaponP250 = 222,
	CWeaponP228 = 221,
	CWeaponNegev = 219,
	CWeaponMP9 = 218,
	CWeaponMP7 = 217,
	CWeaponMP5Navy = 216,
	CWeaponMag7 = 215,
	CWeaponMAC10 = 214,
	CWeaponM4A1 = 213,
	CWeaponHKP2000 = 210,
	CWeaponGlock = 209,
	CWeaponGalilAR = 208,
	CWeaponGalil = 207,
	CWeaponG3SG1 = 206,
	CWeaponFiveSeven = 205,
	CWeaponFamas = 204,
	CWeaponBizon = 199,
	CWeaponAWP = 198,
	CWeaponAug = 197,
	CAK47 = 1,
	CWeaponCSBaseGun = 201,
	CWeaponCSBase = 200,
	CC4 = 29,
	CBaseCSGrenade = 8,
	CSmokeGrenadeProjectile = 127,
	CMolotovProjectile = 94,
	CDecoyProjectile = 41,
	CFireCrackerBlast = 60,
	CInferno = 86,
	CChicken = 31,
	CFootstepControl = 66,
	CCSGameRulesProxy = 34,
	CWeaponCubemap = 0,
	CWeaponCycler = 202,
	CTEPlantBomb = 176,
	CTEFireBullets = 163,
	CTERadioIcon = 180,
	CPlantedC4 = 105,
	CCSTeam = 38,
	CCSPlayerResource = 36,
	CCSPlayer = 35,
	CCSRagdoll = 37,
	CTEPlayerAnimEvent = 177,
	CHostage = 83,
	CHostageCarriableProp = 84,
	CBaseCSGrenadeProjectile = 9,
	CHandleTest = 81,
	CTeamplayRoundBasedRulesProxy = 139,
	CSpriteTrail = 133,
	CSpriteOriented = 132,
	CSprite = 131,
	CRagdollPropAttached = 120,
	CRagdollProp = 119,
	CPredictedViewModel = 113,
	CPoseController = 109,
	CGameRulesProxy = 80,
	CInfoLadderDismount = 87,
	CFuncLadder = 72,
	CTEFoundryHelpers = 166,
	CEnvDetailController = 51,
	CWorld = 237,
	CWaterLODControl = 196,
	CWaterBullet = 195,
	CVoteController = 194,
	CVGuiScreen = 193,
	CPropJeep = 116,
	CPropVehicleChoreoGeneric = 0,
	CTriggerSoundOperator = 192,
	CBaseVPhysicsTrigger = 22,
	CTriggerPlayerMovement = 191,
	CBaseTrigger = 20,
	CTest_ProxyToggle_Networkable = 188,
	CTesla = 183,
	CBaseTeamObjectiveResource = 17,
	CTeam = 138,
	CSunlightShadowControl = 137,
	CSun = 136,
	CParticlePerformanceMonitor = 97,
	CSpotlightEnd = 130,
	CSpatialEntity = 129,
	CSlideshowDisplay = 125,
	CShadowControl = 124,
	CSceneEntity = 123,
	CRopeKeyframe = 121,
	CRagdollManager = 118,
	CPhysicsPropMultiplayer = 102,
	CPhysBoxMultiplayer = 100,
	CPropDoorRotating = 115,
	CBasePropDoor = 16,
	CDynamicProp = 43,
	CProp_Hallucination = 114,
	CPostProcessController = 110,
	CPointCommentaryNode = 108,
	CPointCamera = 107,
	CPlayerResource = 106,
	CPlasma = 105,
	CPhysMagnet = 103,
	CPhysicsProp = 101,
	CStatueProp = 134,
	CPhysBox = 99,
	CParticleSystem = 98,
	CMovieDisplay = 95,
	CMaterialModifyControl = 92,
	CLightGlow = 91,
	CInfoOverlayAccessor = 88,
	CFuncTrackTrain = 79,
	CFuncSmokeVolume = 78,
	CFuncRotating = 77,
	CFuncReflectiveGlass = 76,
	CFuncOccluder = 75,
	CFuncMoveLinear = 74,
	CFuncMonitor = 73,
	CFunc_LOD = 68,
	CTEDust = 158,
	CFunc_Dust = 67,
	CFuncConveyor = 71,
	CFuncBrush = 70,
	CBreakableSurface = 28,
	CFuncAreaPortalWindow = 69,
	CFish = 63,
	CFireSmoke = 61,
	CEnvTonemapController = 58,
	CEnvScreenEffect = 56,
	CEnvScreenOverlay = 57,
	CEnvProjectedTexture = 54,
	CEnvParticleScript = 53,
	CFogController = 65,
	CEnvDOFController = 52,
	CCascadeLight = 30,
	CEnvAmbientLight = 50,
	CEntityParticleTrail = 49,
	CEntityFreezing = 48,
	CEntityFlame = 47,
	CEntityDissolve = 46,
	CDynamicLight = 42,
	CColorCorrectionVolume = 33,
	CColorCorrection = 32,
	CBreakableProp = 27,
	CBeamSpotlight = 25,
	CBaseButton = 5,
	CBaseToggle = 19,
	CBasePlayer = 15,
	CBaseFlex = 12,
	CBaseEntity = 11,
	CBaseDoor = 10,
	CBaseCombatCharacter = 6,
	CBaseAnimatingOverlay = 3,
	CBoneFollower = 26,
	CBaseAnimating = 2,
	CAI_BaseNPC = 0,
	CBeam = 24,
	CBaseViewModel = 21,
	CBaseParticleEntity = 14,
	CBaseGrenade = 13,
	CBaseCombatWeapon = 7,
	CBaseWeaponWorldModel = 23
};