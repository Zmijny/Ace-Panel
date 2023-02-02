#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::fstream;
string filename = "Config.cfg";

int Old_ScreenSize[2], Old_AmmoBox_Pos;
bool Old_wepB, Old_wepH;

#pragma region LoadConfigs
//Load General stuff from config file
void LoadScreenSize(int& ScreenSize_X, int& ScreenSize_Y)
{
	string dummy;
	//Open Config file
	fstream Screen;
	Screen.open(filename);
	//Load General config stuff, can be found in config.cfg
	while (!Screen.eof())
	{
		Screen >> dummy;
		if (dummy == "Width:")
		{
			Screen >> dummy;
			ScreenSize_X = std::stoi(dummy);
			Old_ScreenSize[0] = std::stoi(dummy);

		}
		if (dummy == "Height:")
		{
			Screen >> dummy;
			ScreenSize_Y = std::stoi(dummy);
			Old_ScreenSize[1] = std::stoi(dummy);
			break;
		}
	}
	Screen.close();
}
//Load GrindBot configs
void gb_LoadConfig(int& AmmoBox_Position, bool& wep_Bawoo, bool& wep_Hawky)
{
	string dummy;
	fstream GrindBot;
	GrindBot.open(filename);
	while (!GrindBot.eof())
	{
		GrindBot >> dummy;
		//Check which weapon is picked, if any
		if (dummy == "Bawoo:")
		{
			GrindBot >> dummy;
			if (dummy == "1")
			{
				wep_Bawoo = true;
				Old_wepB = true;
			}			
		}
		if (dummy == "Hawky:")
		{
			GrindBot >> dummy;
			if (dummy == "1")
			{
				wep_Hawky = true;
				Old_wepH = true;
			}		
		}
		//Get The Ammo Box position on skill bar
		if (dummy == "AmmoBoxPosition:")
		{
			GrindBot >> dummy;
			AmmoBox_Position = std::stoi(dummy);
			Old_AmmoBox_Pos = std::stoi(dummy);
			break;
		}
	}
	GrindBot.close();
}
#pragma endregion
#pragma region Save New Configs
// Save new Values for Scren size
void SaveScreenSize(int ScreenSize_X, int ScreenSize_Y)
{
	if (Old_ScreenSize[1] != ScreenSize_Y || Old_ScreenSize[0] != ScreenSize_X)
	{
		std::vector<string> StoredLines;
		string CurrentLine;
		int line_number = 1;

		fstream read_file;
		read_file.open(filename);

		// Read each line of the file and store it as the next element of the vector,
		// the loop will stop when there are no more lines to read
		while (getline(read_file, CurrentLine))
			StoredLines.push_back(CurrentLine);

		read_file.close();

		//open the file in "writing mode"
		std::ofstream write_file;
		write_file.open(filename);

		// Loop through the vector elements to write each line back to the file 
		// EXCEPT the line we want to replace
		for (int i = 0; i < StoredLines.size(); i++)
		{
			if (i != line_number)
				write_file << StoredLines[i] << "\n";
			else
			{
				write_file << "Width: " << ScreenSize_X << "\n";
				write_file << "Height: " << ScreenSize_Y << "\n";
				Old_ScreenSize[1] = ScreenSize_Y; Old_ScreenSize[0] = ScreenSize_X;
				i++;
			}
		}
		write_file.close();
	}
}
// Save New GrindBot Values
void gb_SaveConfig(int AmmoBox_Position, bool wep_Bawoo, bool wep_Hawky)
{
	if (Old_AmmoBox_Pos != AmmoBox_Position || Old_wepB != wep_Bawoo || Old_wepH != wep_Hawky)
	{
		std::vector<string> StoredLines;
		string CurrentLine;
		fstream read_file;
		int line_number;
		
		read_file.open(filename);

		while (getline(read_file, CurrentLine))
			StoredLines.push_back(CurrentLine);

		read_file.close();

		std::ofstream write_file;
		write_file.open(filename);

		if (Old_wepB != wep_Bawoo || Old_wepH != wep_Hawky)
		{
			line_number = 5;
			for (int i = 0; i < StoredLines.size(); i++)
			{
				if (i != line_number)
					write_file << StoredLines[i] << "\n";
				else
				{
					write_file << "Bawoo: " << wep_Bawoo << "\n";
					write_file << "Hawky: " << wep_Hawky << "\n";
					Old_wepB = wep_Bawoo; Old_wepH = wep_Bawoo;
					i++;
				}
			}
		}
		else
		{
			line_number = 7;
			for (int i = 0; i < StoredLines.size(); i++)
			{
				if (i != line_number)
					write_file << StoredLines[i] << "\n";
				else
				{
					write_file << "AmmoBoxPosition: " << AmmoBox_Position << "\n";
					Old_AmmoBox_Pos = AmmoBox_Position;
				}
			}
		}
		write_file.close();
	}
}
#pragma endregion

