#pragma once 

#include <string>
#include <iostream>


class Admin
{
public:

	std::string name;
	std::string state;


	bool Is_ClientConnectedToServer = false;

};
inline Admin g_Admin;