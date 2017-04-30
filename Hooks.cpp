#include "stdafx.h"

CHackManager Hacks;

VMTManager VMTPanel;
VMTManager VMTClient;
VMTManager VMTModelRender;
VMTManager VMTClientMode;
VMTManager VMTD3DDevice9;
VMTManager VMTGameEvent;

CPlayerList Playerlist;

bool warmup = false;

bool __fastcall Hooked_FireEventClientSide(void *ecx, void* edx, IGameEvent* pEvent) {
	if (!pEvent)
		return Hacks.oFireEventClientSide(ecx, pEvent);

	const char* szEventName = pEvent->GetName();

	if (!strcmp(szEventName, "round_freeze_end"))
		warmup = false;

	if (!strcmp(szEventName, "round_prestart"))
		warmup = true;






	return Hacks.oFireEventClientSide(ecx, pEvent);
}






void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	Hacks.oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
	{
		return;
	}


	/* DRAWING HERE */
	PT_Hacks.DrawPaintTraverseHacks();






	
	



	Color orange(255, 132, 0, 255);
	

	if (Settings.GetSetting(Tab_Misc, Misc_Build)) {
		Interfaces.pSurface->DrawString(Hacks.Font_Vermin_Vibes, 10, 30, Color::Purple(), 0, "" __DATE__);
	}
	if (Settings.GetSetting(Tab_Misc, Misc_Time)) {
		Interfaces.pSurface->DrawString(Hacks.Font_Vermin_Vibes, 10, 50, Color::Purple(), 0, "" __TIME__);
	}

	Color masturbation(0, 253, 1, 255);

	static float raduga;
	raduga += 0.00005f;
	if (raduga > 0.005f) raduga = 0.001f;

	if (Settings.GetSetting(Tab_Misc, Misc_Watermark)) {
		Interfaces.pSurface->DrawString(Hacks.Font_Tab, 10, 10, Color::FromHSB(raduga, 3.f, 30.f), 0, "|  REVENGER $ PROJECT ");
	}

	DrawMenu();

	//Interfaces.pSurface->DrawT2(100, 100, CColor(0, 255, 255, 255), Hacks.Font_Vermin_Vibes, "Tohomahhh!1!");




	{


		int crossindex = Settings.GetSetting(Tab_Misc, Misc_Cross_Index);


		int screenSizeX, screenCenterX;
		int screenSizeY, screenCenterY;
		Interfaces.pEngine->GetScreenSize(screenSizeX, screenSizeY);

		screenCenterX = screenSizeX / 2;
		screenCenterY = screenSizeY / 2;

		auto lineSize = 16;

			switch (crossindex)
			{
			case 2:

				Interfaces.pSurface->DrawSetColor(100, 100, 255, 255);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY - 5);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY - 5, screenCenterX + 5, screenCenterY - 5);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX + 5, screenCenterY);
				Interfaces.pSurface->DrawLine(screenCenterX + 5, screenCenterY, screenCenterX + 5, screenCenterY + 5);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY + 5);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY + 5, screenCenterX - 5, screenCenterY + 5);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX - 5, screenCenterY);
				Interfaces.pSurface->DrawLine(screenCenterX - 5, screenCenterY, screenCenterX - 5, screenCenterY - 5);
				break;
			case 3:
				Interfaces.pSurface->DrawSetColor(100, 100, 255, 255);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX - 5, screenCenterY - 5, 10, 10);
				break;
			case 4:
				Interfaces.pSurface->DrawSetColor(100, 100, 255, 255);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY - 30);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY - 30, screenCenterX + 30, screenCenterY - 30);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX + 30, screenCenterY);
				Interfaces.pSurface->DrawLine(screenCenterX + 30, screenCenterY, screenCenterX + 30, screenCenterY + 30);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY + 30);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY + 30, screenCenterX - 30, screenCenterY + 30);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX - 30, screenCenterY);
				Interfaces.pSurface->DrawLine(screenCenterX - 30, screenCenterY, screenCenterX - 30, screenCenterY - 30);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX, screenCenterY, 52, 52);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX, screenCenterY, 57, 57);

				break;

			case 5:

			{

				int fovvalue = Settings.GetSetting(Tab_LegitBot, Legit_Normal_FOV) * 8.5;

				int slowfovvalue = Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_FOV) * 8.5;

				int tapfovvalue = Settings.GetSetting(Tab_LegitBot, Legit_SA_FOV) * 8.5;

				Interfaces.pSurface->DrawSetColor(200, 200, 200, 255);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX - 5, screenCenterY - 5, fovvalue, fovvalue);

				Interfaces.pSurface->DrawSetColor(100, 100, 255, 255);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX - 5, screenCenterY - 5, slowfovvalue, slowfovvalue);

				Interfaces.pSurface->DrawSetColor(255, 0, 0, 255);
				Interfaces.pSurface->DrawOutlinedCircle(screenCenterX - 5, screenCenterY - 5, tapfovvalue, tapfovvalue);
				break;
			}

			case 6:
			{
				int size = Settings.GetSetting(Tab_Misc, Misc_CrossSize);

				Interfaces.pSurface->DrawSetColor(100, 100, 255, 255);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY - size);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX + size, screenCenterY);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX, screenCenterY + size);
				Interfaces.pSurface->DrawLine(screenCenterX, screenCenterY, screenCenterX - size, screenCenterY);
			}

			}


		}

	



}

bool infakelag = false;
bool fl = false;
int flTimer = -1;
bool lastfltick = -1;
int factor = Settings.GetSetting(Tab_Misc, Misc_FakelagAmmount) / 13;

void doFakeLag() {
	int fakeLagType = (int)Settings.GetSetting(Tab_Misc, Misc_Fakelagtype);
	if (fakeLagType > 0 && Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Aimbot)) {
		fl = true;
		auto Velocity = Hacks.LocalPlayer->GetVecVelocity().Length() * Interfaces.pGlobalVars->interval_per_tick;
		auto tmpLagTicks = Settings.GetSetting(Tab_Misc, Misc_FakelagAmmount) / 13;
		switch (fakeLagType) {
		case 1:
			Hacks.SendPacket = true;
			infakelag = false;
			break;
		case 2:
			if (flTimer > 13) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			}
			else {
				if (flTimer == 13)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 3: // I think this one is adaptive.
			do {
				factor = tmpLagTicks;
				if ((tmpLagTicks * Velocity) > 68.f)
					break;
				tmpLagTicks += 1;
				if (((tmpLagTicks + 1) * Velocity) > 68.f)
					break;
				tmpLagTicks += 2;
			} while (tmpLagTicks <= 12);
			if (flTimer > factor) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			}  else {
				if (flTimer == factor)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 4:
			if (flTimer > 13 || Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			} else {
				if (flTimer == 13)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 5:
			break;
		}
	}
}

bool bSendPacket = true;
void __declspec(naked) __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{

	__asm
	{
		MOV bSendPacket, BL
		PUSH EBP
			MOV EBP, ESP
			SUB ESP, 8
			PUSHAD
			PUSH active
			PUSH input_sample_frametime
			PUSH sequence_number
			CALL Hacks.oCreateMove
	}
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (Hacks.LocalPlayer)
	{
		Hacks.SendPacket = bSendPacket;

		doFakeLag();

		CM_Hacks.MovePacket(thisptr, _EAX, sequence_number, input_sample_frametime, active);

		bSendPacket = Hacks.SendPacket;
	}
	__asm
	{
		POPAD
		MOV BL, bSendPacket
			MOV ESP, EBP
			POP EBP
			RETN 0x0C
	}
}

int bullets = 1;

bool bullettime() {
	if (!Hacks.LocalWeapon)return false;
	float flServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

	bool BulletTime = true;

	if (flNextPrimaryAttack > flServerTime)
		BulletTime = false;

	return BulletTime;

}
void bilcount() {
	//bool bulletfired = true;
	static bool bulletcounter = 0;
	if (true) {
		bool bulletfired = bullettime();
		static bool firsttick = true;
		if (!bulletfired) {
			if (firsttick) {
				bullets++;
				firsttick = false;

			}
			bulletcounter++;
			if (bulletcounter > 20) {
				bulletcounter = 0;
				firsttick = true;
			}
		}
		else {
			firsttick = true;
			bulletcounter = 0;
		}
	}
}
bool switchf = false;
bool shouldresolve() {
	if (switchf) {
		switchf = false;
		return true;
	}
	else {
		switchf = true;
		return true;
	}
}


/*
Aimware Anti aims

Pitch:
Down = 90

Emotion = 88.9948

Fake down =  -90

Angel Down = 0

Angel up = 0
These values are realitivy to where they are facing except those where I say static



Yaw:
Backwards = 180
Fake backwards
1 = 180
2 = 0
Jitter
1 = 160
2 = 0
3 = -160
Jitter Sync
1 = 160
2 = 0
3 = 160
Sideways = 90
Fake sideways
1 = 90
2 = -90
Fake Forward
1 = 0
2 = 180
SlowSpinn / fast spin
CBF
Angel backwards = 180
Angel inverse
STATIC = 0
Angel Spin
= + 80
Angel Fake spin
1 = STATIC = 180
2 = +80 (per thing so really + 160)
Faken Angel
STATIC  = 180
*/
		
extern void CalcAngle(Vector src, Vector dst, Vector &angles);
Vector GetHitboxPOS(CPlayer* Player, int HitboxID);


void  __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{

	CBaseEntity* pLocal = Hacks.LocalPlayer;
	Vector aimPunch;
	Vector viewPunch;

	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		Playerlist.Update();

		static int aimPunchOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		static int viewPunchOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
		Vector *pPunchAngle = nullptr, *pViewPunchAngle = nullptr, vPunchAngle, vViewPunchAngle;

		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()) {
			if (pLocal) {

				if (curStage == FRAME_RENDER_START) {

					if (*(bool*)((DWORD)Interfaces.pInput + 0xA5))
						*(Vector*)((DWORD)pLocal + 0x31C8) = Hacks.LastAngles;

					if (Settings.GetBoolSetting(Tab_Visuals, Vis_Recoil) && Settings.GetBoolSetting(Tab_Visuals, Vis_Active)) {
						pPunchAngle = Hacks.LocalPlayer->GetPunchAnglePtr();
						pViewPunchAngle = Hacks.LocalPlayer->GetViewPunchAnglePtr();

						if (pPunchAngle && pViewPunchAngle) {
							vPunchAngle = *pPunchAngle;
							pPunchAngle->Init();
							vViewPunchAngle = *pViewPunchAngle;
							pViewPunchAngle->Init();
						}


					}
				}
			}
		}

		Hacks.oFrameStageNotify(curStage);


		if (pPunchAngle && pViewPunchAngle) {
			*pPunchAngle = vPunchAngle;
			//*pViewPunchAngle = vViewPunchAngle;
		}

		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()) {
			if (pLocal) {
				if (curStage == FRAME_RENDER_START) {
					//*(Vector*)((DWORD)pLocal + aimPunchOffset)  = aimPunch;
					//*(Vector*)((DWORD)pLocal + viewPunchOffset) = viewPunch;
				}
			}
		}

		if (Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Resolver))
		{
			Resolver.Resolver(curStage);
		}

		if (curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			// Update Playerlist

			if (true) {
				if (!Hacks.LocalPlayer)
					return;
				if (!Hacks.LocalWeapon)
					return;
				bilcount();
			}

			//
			// Do Resolver

		}
	}
}

void __stdcall Hooked_OverrideMouseInput(float *x, float* y)
{
	if (false) { // ur soo mean, u removed my meme
				 //	Hacks.oOverrideMouseInput(x, y);


		*(float*)x += 70;// for some reason its gotta be written with 
						 // *(float*) behind, i thought it was just *x = 0; but noh, its *(float*)x (im retarded)


	}
}

void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{

	if (!DMEHacks.Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
		Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	Interfaces.g_pModelRender->ForcedMaterialOverride(NULL, OverrideType_t::OVERRIDE_NORMAL);
}

void __fastcall Hooked_D3D()
{

}
void __fastcall Hooked_D3DReset()
{

}

LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//if (Menu.Opened)
	//	return true; // IF MENU ISNT OPEN, BLOCK IMPUT :)

	return CallWindowProc(Hacks.g_pOldWindowProc, hWnd, uMsg, wParam, lParam);
}
