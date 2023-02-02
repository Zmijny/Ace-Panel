#pragma once
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <thread>
#include <chrono>
#include <future>

void GrindBot();
void HealMacro();
#pragma region Defines for Activating/Closing the windows
bool Active = true;//Main Window
//Bots
bool gb_Active = false;//Grind
bool gab_Active = false;//Gamble Bot
bool fb_Active = false;//Fix
bool tb_Active = false;//token
bool cb_Active = false;//chat
bool eb_Active = false;//enchant
// Macros
bool hm_Active = false;// Heal

// Functions
bool FPS_Boost = false;

#pragma endregion

void AppManifest()
{
    // Main function  
    ImGui::SetNextWindowPos({ 0,200 });
    ImGui::SetNextWindowSize(ImVec2(400, 800));
    if (ImGui::Begin("Ace Panel", &Active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
    {
        ImGui::Checkbox("Enable fps boost", &FPS_Boost);

        // Bots
        if (ImGui::CollapsingHeader("Bots"))
        {
            if (ImGui::Button("Grind Bot", { 385,0 })) { gb_Active = true; }
            if (ImGui::Button("Gamble Bot", { 385,0 })) { gab_Active = true; }
            if (ImGui::Button("Fix Bot", { 385,0 })) { fb_Active = true; }
            if (ImGui::Button("Token Bot", { 385,0 })) { tb_Active = true; }
            if (ImGui::Button("Chat Bot", { 385,0 })) { cb_Active = true; }
            if (ImGui::Button("Enchant Bot", { 385,0 })) { eb_Active = true; }
        }
        // Macros
        if (ImGui::CollapsingHeader("Macros"))
        {
            if (ImGui::Button("Heal Macro", { 385,0 })) { hm_Active = true; }
        }
        // Mods
        if (ImGui::CollapsingHeader("Mods"))
        {
            ImGui::Text("Kits");
        }
    }if (!Active) { ::PostQuitMessage(0); }ImGui::End();

#pragma region Bot Menu
    //Grind Bot
    if (gb_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 215));
        if (ImGui::Begin("GrindBot", &gb_Active, ImGuiWindowFlags_NoResize))
        {
            GrindBot();
        }ImGui::End();
    }

    //Gamble Bot
    if (gab_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        if (ImGui::Begin("GambleBot", &gab_Active, ImGuiWindowFlags_NoResize))
        {

        }ImGui::End();
    }

    //Fix Bot
    if (fb_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        if (ImGui::Begin("FixBot", &fb_Active, ImGuiWindowFlags_NoResize))
        {

        }ImGui::End();
    }

    //Token Bot
    if (tb_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        if (ImGui::Begin("TokenBot", &tb_Active, ImGuiWindowFlags_NoResize))
        {

        }ImGui::End();
    }

    //Chat Bot
    if (cb_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        if (ImGui::Begin("ChatBot", &cb_Active, ImGuiWindowFlags_NoResize))
        {

        }ImGui::End();
    }

    //Enchant Bot
    if (eb_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 200));
        if (ImGui::Begin("EnchantBot", &eb_Active, ImGuiWindowFlags_NoResize))
        {

        }ImGui::End();
    }
#pragma endregion
#pragma region Macros
    //Heal Macro
    if (hm_Active)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 400));
        if (ImGui::Begin("HealMacro", &hm_Active, ImGuiWindowFlags_NoResize))
        {
            HealMacro();
        }ImGui::End();
    }
#pragma endregion

}