#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <fstream>
#include "shellapi.h"

#include "json.hpp"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define	C_SERVER			"C:\\Server"			// директория сервера
#define C_SERVER_USERS		"C:\\Server\\Users"		// директория пользователей (персонала)
#define C_SERVER_MENU		"C:\\Server\\Menu"		// директория меню блюд
#define C_SERVER_CLIENTS	"C:\\Server\\Clients"	// директория клиентов

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class Data
{
public:

	

	void createNewUser(std::string user_by_login_value, std::string password_value)
	{
		std::string slesh = "\\";
		std::string path = C_SERVER_USERS + slesh + user_by_login_value;
		CreateDir(path);

		std::time_t now = std::time(nullptr);
		std::tm* localTime = std::localtime(&now);

		std::ostringstream str_stream;
		str_stream << std::setfill('0')
			<< std::setw(4) << localTime->tm_year + 1900 << "-"
			<< std::setw(2) << localTime->tm_mon + 1 << "-"
			<< std::setw(2) << localTime->tm_mday << " | "
			<< std::setw(2) << localTime->tm_hour << ":"
			<< std::setw(2) << localTime->tm_min << ":"
			<< std::setw(2) << localTime->tm_sec;
		std::string time_ = str_stream.str();

		//writeJson(user_by_login_value, password_value, time_);

		std::cout << "New User [ " << user_by_login_value << " ] Created" << std::endl;
	}

	// ----------[ Directories ]----------
	
	void INIT()
	{

		if (!CheckDir(C_SERVER))
		{
			std::cout << "[Server CAUTION]: no Server Directory" << std::endl;
			CreateDir(C_SERVER);
			std::cout << "[Server]: Server Directory created" << std::endl;
		}
		if (!CheckDir(C_SERVER_USERS))
		{
			std::cout << "[Server CAUTION]: no Users Directory" << std::endl;
			CreateDir(C_SERVER_USERS);
			std::cout << "[Server]: Users Directory created" << std::endl;
		}
		if (!CheckDir(C_SERVER_MENU))
		{
			std::cout << "[Server CAUTION]: no Menu Directory" << std::endl;
			CreateDir(C_SERVER_MENU);
			std::cout << "[Server]: Menu Directory created" << std::endl;
		}
		if (!CheckDir(C_SERVER_CLIENTS))
		{
			std::cout << "[Server CAUTION]: no Clients Directory" << std::endl;
			CreateDir(C_SERVER_CLIENTS);
			std::cout << "[Server]: Clients Directory created" << std::endl;
		}

		// ВРЕМЕННО ПОтОМ УДАЛИТЬ ПО ХОРОШЕМУ
		if (!CheckFile("C:\\Server\\Users\\ramil\\Logs.json"))
		{
			createNewUser("ramil", "210605");
		}
	}

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

	void SendInformationNotification(const char* title, const char* message) {
		NOTIFYICONDATA nid = { sizeof(NOTIFYICONDATA) };    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);    nid.uCallbackMessage = WM_USER;
		lstrcpy(nid.szTip, "Информация");
		Shell_NotifyIcon(NIM_ADD, &nid);
		nid.uFlags = NIF_INFO;    lstrcpyn(nid.szInfo, message, sizeof(nid.szInfo));
		lstrcpyn(nid.szInfoTitle, title, sizeof(nid.szInfoTitle));    nid.dwInfoFlags = NIIF_INFO;
		Shell_NotifyIcon(NIM_MODIFY, &nid);
		Sleep(5000); // Ожидание 5 секунд
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	void COUT_CurrTime()
	{
		time_t currentTime = time(0);
		struct tm* localTime = localtime(&currentTime);
		std::cout << ", date -> " << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday << " | " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << std::endl;

	}



	void writeJson_BoostWay(std::string login_value, std::string password_value, std::string creation_date_value)
	{

		std::string path_of_new_user_json = "C:\\Server\\Users\\admin\\Logs.json";

		std::ifstream file(path_of_new_user_json);
		file.close();

		// Создаем новое дерево свойств
		boost::property_tree::ptree pt;

		// Добавляем данные в дерево свойств
		pt.put("login", login_value);
		pt.put("password", password_value);
		pt.put("creation_date", creation_date_value);

		// Записываем дерево свойств в JSON-файл
		boost::property_tree::write_json(path_of_new_user_json, pt);

		std::cout << "JSON файл успешно создан и данные записаны в него." << std::endl;
	}
	void readJson_BoostWay() {
		// C:\\Server\\Users\\user_login\\Logs.json


		std::ifstream file("C:\\Server\\Users\\ramil\\Logs.json");
		boost::property_tree::ptree pt;
		try
		{
			boost::property_tree::read_json(file, pt);
		}
		catch (const boost::property_tree::json_parser_error& e)
		{
			std::cout << "[Server]: Failed to parse JSON file: " << e.what() << std::endl;
		}

		std::string login = pt.get<std::string>("login");
		std::string password = pt.get<std::string>("password");
		std::string creation_date = pt.get<std::string>("creation_date");
		std::cout << "Login -> " << login << std::endl;
		std::cout << "Password -> " << password << std::endl;
		std::cout << "Creation date -> " << creation_date << std::endl;


		file.close();
	}
	void readAllJson()
	{
		// Чтение данных из JSON файла
		std::ifstream file("input.json");
		nlohmann::json j;
		file >> j;
		file.close();

		// Получение всех значений из JSON объекта
		for (auto& el : j.items()) {
			std::cout << "Key: " << el.key() << ", Value: " << el.value() << std::endl;
		}

		// Получение значения по ключу
		std::string keyToFind = "name";
		if (j.contains(keyToFind)) {
			std::cout << "Value of key '" << keyToFind << "': " << j[keyToFind] << std::endl;
		}
		else {
			std::cout << "Key '" << keyToFind << "' not found in the JSON object." << std::endl;
		}

	}


		//------------READ JSON------------
		/*std::string slesh = "\\";
		std::string path = C_SERVER_USERS + slesh + user_by_login_value + slesh + "Logs.json";
		std::ifstream file(path);
		nlohmann::json j;
		file >> j;
		file.close();
		// j.contains(key)  ->  проверка что в json есть этот ключ
		*output_login = j["login"];
		*output_password = j["password"];*/




		//------------WRITE JSON------------
		/*nlohmann::json j;
		j["login"] = user_by_login_value;
		j["password"] = password_value;
		j["creation_date"] = creation_date_value;
		std::string slesh = "\\";
		std::string path = C_SERVER_USERS + slesh + user_by_login_value + slesh + "Logs.json";
		std::ofstream file(path);
		file << j.dump(4);
		file.close();*/

};

inline Data g_data;




