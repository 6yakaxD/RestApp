#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <fstream>

#include "json.hpp"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <Windows.h>

class data
{
public:

	std::string GetAppdataPath()
	{
		char* appDataPath = nullptr;

		appDataPath = getenv("APPDATA");

		if (appDataPath == nullptr)
		{
			return "";
		}

		std::stringstream f;
		f << appDataPath;

		return f.str();
	}

	std::string slesh = "\\";
	std::string path_to_dir = data::GetAppdataPath() + slesh + "RestApp";
	std::string path_to_json = path_to_dir + slesh + "lastJoinData.json";

	


	bool CheckDir(std::string dir)
	{
		if (!std::filesystem::exists(dir))
		{
			return false;
		}
		return true;
	}
	bool CheckFile(const std::string& filename) {
		std::ifstream file(filename);
		return file.good();
	}

	bool CreateDir(const std::string& path)
	{
		int result = _mkdir(path.c_str());
		return (result == 0);
	}

	


	// ----------[ Json ]----------

	void readJson(std::string path, std::string* output_login, std::string* output_password)
	{
		// ������ ������ �� JSON �����

		std::ifstream file(path);
		nlohmann::json j;
		file >> j;
		file.close();


		// j.contains(key)  ->  �������� ��� � json ���� ���� ����

		/*std::cout << j["login"] << std::endl;
		std::cout << j["password"] << std::endl;
		std::cout << j["creation_date"] << std::endl;*/

		*output_login = j["login"];
		*output_password = j["password"];

	}

	void writeJson(std::string path, std::string login_value, std::string password_value)
	{
		nlohmann::json j;

		// ��������� ������ � JSON ������
		j["login"] = login_value;
		j["password"] = password_value;


		// ���������� JSON ������ � ����
		std::ofstream file(path);
		file << j.dump(4); // ���������� � ���� � ��������� ��� ���������������
		file.close();

	}




	// ----------[ Others ]----------
	std::vector<std::string> split(const std::string& str, char delimiter) {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);
		while (std::getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}
		return tokens;
	}

	void readAllJson()
	{
		// ������ ������ �� JSON �����
		std::ifstream file("input.json");
		nlohmann::json j;
		file >> j;
		file.close();

		// ��������� ���� �������� �� JSON �������
		for (auto& el : j.items()) {
			std::cout << "Key: " << el.key() << ", Value: " << el.value() << std::endl;
		}

		// ��������� �������� �� �����
		std::string keyToFind = "name";
		if (j.contains(keyToFind)) {
			std::cout << "Value of key '" << keyToFind << "': " << j[keyToFind] << std::endl;
		}
		else {
			std::cout << "Key '" << keyToFind << "' not found in the JSON object." << std::endl;
		}

	}

	bool Init()
	{
		if (!data::CheckDir(path_to_dir))
		{
			data::CreateDir(path_to_dir);
		}
		if (!data::CheckFile(path_to_json))
		{
			data::writeJson(path_to_json, "", "");
		}
		return true;
	}

};
inline data g_data;

