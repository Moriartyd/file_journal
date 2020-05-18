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
	void	reset_files();					//����� ������ � ��������� ������ ��  RESET_FILE
	void	checker();
	int		is_exist(std::string fname);	//�������� �� ������������� ����� � ������ fname
	void	screate_file(std::string fname); //�������� ����� Silence
	void	create_file(std::string fname); //�������� �����
	void	sdel_file(std::string fname);	//�������� ����� Silence
	void	del_file(std::string fname);	//�������� �����
	void	total_cpy();					//�������� ������ � ��������� ������ �� ��������� � RESET_FILE
	void	edit_file(std::string fname, int op);	//��������� �����
	void	show_files();					//���������� ���������� � ��� ��������� ������
	void	bcp_to_file(std::string fname);
	void	renamer(std::string fname, std::string name);
private:
	std::string _stdcall WideStringToAnsi(std::wstring const& Str, UINT CodePage = CP_ACP);
	void	del_new_file(std::string fname);	//�������� �����
	void	create_new_file(std::string fname); //�������� �����
	int		check_file(std::string fname);		//�������� ����� �� �����������
	void	file_to_bcp(std::string fname);
	void	delete_record(std::string fname);
	std::string*	files;
	int		cnt = 0;
	Log		log;
};

