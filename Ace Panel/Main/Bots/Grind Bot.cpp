#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <fstream>
#include <string>
#include "../../ImGui/imgui.h"
#include "../Headers/Defines.h"

//Config Loader function declaration
void gb_LoadConfig(int& AmmoBox_Position, bool& wep_Bawoo, bool& wep_Hawky);
void LoadScreenSize(int& ScreenSize_X, int& ScreenSize_Y);
//Save New Config values declarations
void SaveScreenSize(int ScreenSize_X, int ScreenSize_Y);
void gb_SaveConfig(int AmmoBox_Position, bool wep_Bawoo, bool wep_Hawky);
//Main loop
void Program()
{
	while (gb_Stop == false)
	{
		//550x bawoo 546x hawks
		gb_ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		gb_ip.ki.wScan = 0x1F;
		SendInput(1, &gb_ip, sizeof(INPUT));
		Sleep(8);
	}
}
//A function to use the Ammo Box
void AmmoBoxRefresh()
{
	//for some fucking reason always uses 2 ammunition boxes. To be fixed
	INPUT ab;
	ab.type = INPUT_KEYBOARD;

	switch (AmmoBox_Position)
	{
	case 0:
		ab.ki.wScan = 0x0B;
		break;
	case 1:
		ab.ki.wScan = 0x02;
		break;
	case 2:
		ab.ki.wScan = 0x03;
		break;
	case 3:
		ab.ki.wScan = 0x04;
		break;
	case 4:
		ab.ki.wScan = 0x05;
		break;
	case 5:
		ab.ki.wScan = 0x06;
		break;
	case 6:
		ab.ki.wScan = 0x07;
		break;
	case 7:
		ab.ki.wScan = 0x08;
		break;
	case 8:
		ab.ki.wScan = 0x09;
		break;
	case 9:
		ab.ki.wScan = 0x0A;
		break;
	}
	
	ab.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ab, sizeof(INPUT));
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	ab.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ab, sizeof(INPUT));

	bgstatus = false;
}
//uses a Ammo Box after a certain ammount of time
void AbTimer()
{
	while (!gb_Stop)
	{
		if (wep_Bawoo == true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(360000));
			bgstatus = true;
			if (bgstatus != false)
			{
				AmmoBoxRefresh();
			}
		}
		if (wep_Hawky == true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(210000));
			bgstatus = true;
			if (bgstatus != false)
			{
				AmmoBoxRefresh();
			}
		}
		
	}
}

void GrindBot()
{
	if (gb_FirstOpen)
	{
		gb_LoadConfig(AmmoBox_Position, wep_Bawoo, wep_Hawky);
		LoadScreenSize(ScreenSize_X, ScreenSize_Y);
		gb_FirstOpen = false;
	}
	SaveScreenSize(ScreenSize_X, ScreenSize_Y);
	gb_SaveConfig(AmmoBox_Position, wep_Bawoo, wep_Hawky);

	ImGui::Text("!You will have 5 seconds to focus to your game window!");

	ImGui::SliderInt("AmmoBox Slot", &AmmoBox_Position, 0, 9);

	if (ImGui::Checkbox("Bawoo", &wep_Bawoo))
		wep_Hawky = false;
	if (ImGui::Checkbox("Hawky", &wep_Hawky))
		wep_Bawoo = false;

	ImGui::Spacing();
	ImGui::InputInt("Screen Size X", &ScreenSize_X);
	ImGui::InputInt("Screen Size Y", &ScreenSize_Y);

	if (ImGui::Button("Start The GrindBot"))
	{
		//keyboard input
		gb_ip.type = INPUT_KEYBOARD;
		gb_ip.ki.wVk = VkKeyScanA('s');
		gb_ip.ki.dwFlags = KEYEVENTF_SCANCODE;

		//start counter
		Sleep(5500);

		//initialize the program
		SetCursorPos((ScreenSize_X / 2), (ScreenSize_Y / 2));
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		std::thread([]() { AbTimer(); }).detach();
		AmmoBoxRefresh();
		std::thread([]() { Program(); }).detach();
	}
	if (ImGui::Button("Stop"))
	{
		gb_Stop = true;
		gb_ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &gb_ip, sizeof(INPUT));
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		return;
	}
}

