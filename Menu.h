#pragma once
#include "FileManager.h"

class Menu
{
public:
	Menu();
	~Menu();
	void		show();	//Показывает меню
	void		ops();	//Обрабатывает выбранные значения
	void		log_check();

private:
	bool		fshow = 1;
	bool		rf = 1;
	std::string	read_fname();
	void		show_edit_menu();
	FileManager	fman;
	Log			log;
};