#pragma once
#include <Windows.h>
#include <string>

#pragma region General Defines
inline int ScreenSize_X;
inline int ScreenSize_Y;
#pragma endregion

#pragma region Bots
#pragma region Gamble Bot Defines
//Weapon Defines
inline bool wep_Bawoo = false;
inline bool wep_Hawky = false;

inline int AmmoBox_Position;
//Random Defines
inline INPUT gb_ip;
inline bool bgstatus;
inline bool gb_FirstOpen = true;
inline bool gb_Start = false;
inline bool gb_Stop = false;
#pragma endregion
#pragma endregion
#pragma region Macros
#pragma region Heal Macro Defines
// Defines for getting the skills position on the Skill bar
inline int ShieldPos,
		   Form_ShieldPos;
inline int HealPos,
		   Form_HealPos;
// Defines for configuration
inline int hm_Delay;
inline bool UseHeal,
			UseFormHeal, 
			UseShield,
			UseFormShield;
inline int hm_FirstOpen = true;
// Main Defines for the code or something
static INPUT hm_h,
			 hm_fh,
			 hm_s,
			 hm_fs;
inline bool hm_Stop;
inline ImVec2 hm_CurrenMousePos;
#pragma endregion
#pragma endregion




