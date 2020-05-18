#pragma once
#include "Log.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <locale>
#include <vector>

#define FILE_PATH "./Files/"
#define	RESET_FILE "filenames.txt"

class FileManager
{
public:
	FileManager();
	~FileManager();
	void	reset_files();					//Берет данные о созданных файлах из  RESET_FILE
	void	checker();
	int		is_exist(std::string fname);	//Проверка на существование файла с именем fname
	void	screate_file(std::string fname); //Создание файла Silence
	void	create_file(std::string fname); //Создание файла
	void	sdel_file(std::string fname);	//Удаление файла Silence
	void	del_file(std::string fname);	//Удаление файла
	void	total_cpy();					//Копирует данные о созданных файлах из программы в RESET_FILE
	void	edit_file(std::string fname, int op);	//Изменение файла
	void	show_files();					//Показывает количество и имя созданных файлов
	void	bcp_to_file(std::string fname);
	void	renamer(std::string fname, std::string name);
private:
	std::string _stdcall WideStringToAnsi(std::wstring const& Str, UINT CodePage = CP_ACP);
	void	del_new_file(std::string fname);	//Удаление файла
	void	create_new_file(std::string fname); //Создание файла
	int		check_file(std::string fname);		//Проверка файла на целостность
	void	file_to_bcp(std::string fname);
	void	delete_record(std::string fname);
	std::string*	files;
	int		cnt = 0;
	Log		log;
};

