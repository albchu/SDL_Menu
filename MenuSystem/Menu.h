#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Menu
{
public:
	Menu();
	void render();
	void add_option(string option);
private:
	vector<string> options;
	int selected_index;
};

#endif