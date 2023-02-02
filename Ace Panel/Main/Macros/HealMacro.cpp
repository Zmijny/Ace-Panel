#include <iostream>
#include <windows.h>
#include <thread>
#include "../../ImGui/imgui.h"
#include "../Headers/Defines.h"
#define IM_PRIu64   "I64u"

// Main Loop of the program
void MainLoop()
{
	while (!hm_Stop)
	{
		if (UseHeal == true)
		{
			//hm_CurrenMousePos = ImGui::GetCursorPos();
			SetCursorPos((ScreenSize_X / 2), (ScreenSize_Y / 2));

			hm_h.ki.dwFlags = KEYEVENTF_SCANCODE;
			SendInput(1, &hm_h, sizeof(INPUT));
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			hm_h.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			SendInput(1, &hm_h, sizeof(INPUT));

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			
			//ImGui::SetCursorPos(hm_CurrenMousePos);
		}
		if (UseShield == true)
		{
			//hm_CurrenMousePos = ImGui::GetCursorPos();
			SetCursorPos((ScreenSize_X / 2), (ScreenSize_Y / 2));

			hm_s.ki.dwFlags = KEYEVENTF_SCANCODE;
			SendInput(1, &hm_s, sizeof(INPUT));
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			hm_s.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			SendInput(1, &hm_s, sizeof(INPUT));

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

			//ImGui::SetCursorPos(hm_CurrenMousePos);
		}
		if (UseFormHeal == true)
		{
			hm_fh.ki.dwFlags = KEYEVENTF_SCANCODE;
			SendInput(1, &hm_fh, sizeof(INPUT));
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			hm_fh.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			SendInput(1, &hm_fh, sizeof(INPUT));
		}
			
		if (UseFormShield == true)
		{
			hm_fs.ki.dwFlags = KEYEVENTF_SCANCODE;
			SendInput(1, &hm_fs, sizeof(INPUT));
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			hm_fs.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			SendInput(1, &hm_fs, sizeof(INPUT));
		}
			
		std::this_thread::sleep_for(std::chrono::milliseconds(1200 + hm_Delay));
	}
}
// Define of functions
void SetupInputs(INPUT& ip, int DefPosition);
void LoadScreenSize(int& ScreenSize_X, int& ScreenSize_Y);
void SaveScreenSize(int ScreenSize_X, int ScreenSize_Y);
// Generate ImGui stuff
void HealMacro()
{
	if (hm_FirstOpen)
	{
		LoadScreenSize(ScreenSize_X, ScreenSize_Y);
		hm_FirstOpen = false;
	}
	SaveScreenSize(ScreenSize_X, ScreenSize_Y);

	ImGui::SliderInt("Delay", &hm_Delay, 0, 1500, "%" IM_PRIu64 " ms");
	if (hm_Delay < 100)
		ImGui::Text("!!Warning, using the program with this delay\ncan result in you getting banned!!");
	
	ImGui::Checkbox("Use Heal", &UseHeal);
	if (UseHeal)
	{
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::SliderInt("Position", &HealPos, 0, 9);
		if (HealPos == Form_HealPos || HealPos == ShieldPos || HealPos == Form_ShieldPos)
		{
			if (HealPos >= 9)
				HealPos--;
			else //if (HealPos > 9)
				HealPos++;
		}
	}
	ImGui::Checkbox("Use FormHeal", &UseFormHeal);
	if (UseFormHeal)
	{
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::SliderInt("Position", &Form_HealPos, 0, 9);
		if (Form_HealPos == HealPos || Form_HealPos == ShieldPos || Form_HealPos == Form_ShieldPos)
		{
			if (Form_HealPos >= 9)
				Form_HealPos--;
			else //if (Form_HealPos > 9)
				Form_HealPos++;
		}
	}
	ImGui::Checkbox("Use Shield", &UseShield);
	if (UseShield)
	{
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::SliderInt("Position", &ShieldPos, 0, 9);
		if (ShieldPos == HealPos || ShieldPos == Form_HealPos || ShieldPos == Form_ShieldPos)
		{
			if (ShieldPos >= 9)
				ShieldPos--;
			else //if(ShieldPos > 9)
				ShieldPos++;
		}
	}
	ImGui::Checkbox("Use FormShield", &UseFormShield);
	if (UseFormShield)
	{
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::SliderInt("Position", &Form_ShieldPos, 0, 9);
		if (Form_ShieldPos == HealPos || Form_ShieldPos == ShieldPos || Form_ShieldPos == Form_HealPos)
		{
			if (Form_ShieldPos >= 9)
				Form_ShieldPos--;
			else //if (Form_ShieldPos > 9)
				Form_ShieldPos++;
		}
	}

	ImGui::Spacing();
	ImGui::InputInt("Screen Size X", &ScreenSize_X);
	ImGui::InputInt("Screen Size Y", &ScreenSize_Y);
	if (ImGui::Button("Start"))
	{
		hm_Stop = false;
		if (UseHeal == true)
			SetupInputs(hm_h, HealPos);
		if (UseFormHeal == true)
			SetupInputs(hm_fh, Form_HealPos);
		if (UseShield == true)
			SetupInputs(hm_s, ShieldPos);
		if (UseFormShield == true)
			SetupInputs(hm_fs, Form_ShieldPos);

		std::thread([]() { MainLoop(); }).detach();
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000)
		hm_Stop = true;
	if (hm_Stop)
		ImGui::Text("Macro Stopped");
}

// Function for setting up inputs
void SetupInputs(INPUT& ip, int DefPosition)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	switch (DefPosition)
	{
	case 0:
		ip.ki.wScan = 0x0B;
		break;
	case 1:
		ip.ki.wScan = 0x02;
		break;
	case 2:
		ip.ki.wScan = 0x03;
		break;
	case 3:
		ip.ki.wScan = 0x04;
		break;
	case 4:
		ip.ki.wScan = 0x05;
		break;
	case 5:
		ip.ki.wScan = 0x06;
		break;
	case 6:
		ip.ki.wScan = 0x07;
		break;
	case 7:
		ip.ki.wScan = 0x08;
		break;
	case 8:
		ip.ki.wScan = 0x09;
		break;
	case 9:
		ip.ki.wScan = 0x0A;
		break;
	}
}
