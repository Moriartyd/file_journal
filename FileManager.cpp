#include "FileManager.h"



FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::reset_files()
{
	std::ifstream	ifs;
	std::string		buff;
	int				i;

	ifs.open(RESET_FILE);
	while (ifs.is_open() && !ifs.eof())
	{
		std::getline(ifs, buff);
		cnt++;
	}
	cnt -= 1;
	if (cnt < 1)
	{
		cnt = 0;
		return;
	}
	ifs.close();
	files = new std::string[cnt];
	ifs.open(RESET_FILE);
	i = 0;
	while (i < cnt)
	{
		std::getline(ifs, files[i]);
		i++;
	}
	ifs.close();
}

void FileManager::checker()
{
	WIN32_FIND_DATA	FindFileData;
	HANDLE			hf;
	std::string		fname;
	int				op;
	int*			arr;

	arr = new int[cnt];
	for (int i = 0; i < cnt; i++)
		arr[i] = 0;
	hf = FindFirstFile(L"D:\\Labs\\ня\\Lab4\\Lab4\\Files\\*", &FindFileData);
	FindNextFile(hf, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hf, &FindFileData) != 0)
		{
			fname = WideStringToAnsi(FindFileData.cFileName);
			//std::cout << fname << std::endl;
			if (!is_exist(fname))
			{
				std::cout << "A new file '" << fname << "' has been appeared!\nAdd(1)/Remove(0): ";
				std::cin >> op;
				op == 1 ? create_new_file(fname) : del_new_file(fname);
			}
			else
			{
				for (int i = 0; i < cnt; i++)
				{
					if (files[i] == fname)
						arr[i] = 1;
				}
				check_file(fname);
			}
		}
		FindClose(hf);
	}
	for (int i = 0; i < cnt; i++)
	{
		if (!arr[i])
		{
			std::cout << "The file '" << files[i] << "' was deleted by a third-party program!\nRecover? (Y/n): ";
			std::string rec;
			std::cin >> rec;
			if (rec == "Y")
				bcp_to_file(files[i]);
			else
				delete_record(files[i]);
		}
	}
}

int FileManager::is_exist(std::string fname)
{
	for (int i = 0; i < cnt; i++)
		if (files[i] == fname)
			return (1);
	return (0);
}

void FileManager::screate_file(std::string fname)
{
	std::ofstream	ofs;
	std::ofstream	res;

	if (!cnt)
	{
		ofs.open(FILE_PATH + fname);
		if (ofs.is_open())
		{
			ofs.close();
			ofs.open(BACKUP_PATH + fname);
			ofs.close();
			files = new std::string[1];
			cnt = 1;
			files[0] = fname;
			res.open(RESET_FILE, std::ios_base::app);
			res << fname << std::endl;
			res.close();
		}
	}
	else
	{
		if (is_exist(fname))
		{
			return;
		}
		ofs.open(FILE_PATH + fname);
		if (ofs.is_open())
		{
			ofs.close();
			ofs.open(BACKUP_PATH + fname);
			ofs.close();
			res.open(RESET_FILE, std::ios_base::app);
			res << fname << std::endl;
			res.close();
			std::string* tmp;
			tmp = new std::string[cnt + 1];
			for (int i = 0; i < cnt; i++)
				tmp[i] = files[i];
			cnt++;
			tmp[cnt - 1] = fname;
			files = tmp;
		}
	}
}

void FileManager::create_file(std::string fname)
{
	std::ofstream	ofs;
	std::ofstream	res;

	log.creating(fname);
	if (!cnt)
	{
		ofs.open(FILE_PATH + fname);
		if (ofs.is_open())
		{
			ofs.close();
			ofs.open(BACKUP_PATH + fname);
			ofs.close();
			files = new std::string[1];
			cnt = 1;
			files[0] = fname;
			res.open(RESET_FILE, std::ios_base::app);
			res << fname << std::endl;
			res.close();
			log.ecreating(fname);
		}
		else
			log.creating_error(fname);
	}
	else
	{
		if (is_exist(fname))
		{
			log.creating_error(fname);
			return;
		}
		ofs.open(FILE_PATH + fname);
		if (ofs.is_open())
		{
			ofs.close();
			ofs.open(BACKUP_PATH + fname);
			ofs.close();
			res.open(RESET_FILE, std::ios_base::app);
			res << fname << std::endl;
			res.close();
			std::string* tmp;
			tmp = new std::string[cnt + 1];
			for (int i = 0; i < cnt; i++)
				tmp[i] = files[i];
			cnt++;
			tmp[cnt - 1] = fname;
			files = tmp;
			log.ecreating(fname);
		}
		else
			log.creating_error(fname);
	}
}

void FileManager::sdel_file(std::string fname)
{
	std::string		path;
	std::string		bpath;
	std::string* tmp;
	int				j;

	if (is_exist(fname))
	{
		path = FILE_PATH + fname;
		bpath = BACKUP_PATH + fname;
		if (!remove(path.c_str()) && !remove(bpath.c_str()))
		{
			tmp = new std::string[cnt - 1];
			j = 0;
			for (int i = 0; i < cnt; i++)
				if (files[i] != fname)
				{
					tmp[j] = files[i];
					j++;
				}
			cnt--;
			files = tmp;
			this->total_cpy();
		}
	}
}

void FileManager::del_file(std::string fname)
{
	std::string		path;
	std::string		bpath;
	std::string*	tmp;
	int				j;

	log.removing(fname);
	if (is_exist(fname))
	{
		path = FILE_PATH + fname;
		bpath = BACKUP_PATH + fname;
		if (!remove(path.c_str()) && !remove(bpath.c_str()))
		{
			tmp = new std::string[cnt - 1];
			j = 0;
			for (int i = 0; i < cnt; i++)
				if (files[i] != fname)
				{
					tmp[j] = files[i];
					j++;
				}
			cnt--;
			files = tmp;
			this->total_cpy();
		}
		log.eremoving(fname);
	}
	else
		log.deleting_error(fname);
}

void FileManager::total_cpy()
{
	std::ofstream	res;

	res.open(RESET_FILE, std::ios_base::trunc);
	for (int i = 0; i < cnt; i++)
		res << files[i] << std::endl;
	res.close();
}

void FileManager::edit_file(std::string fname, int op)
{
	std::ofstream	ofs;
	std::string		str;

	if (is_exist(fname) && op == 1)
	{
		log.editing(fname);
		ofs.open(FILE_PATH + fname, std::ios_base::app);
		std::cout << "Enter a line to add in file: ";
		getchar();
		std::getline(std::cin, str);
		ofs << str << std::endl;
		ofs.close();
		log.eediting(fname);
		file_to_bcp(fname);
	}
	else if (is_exist(fname) && op == 2)
	{
		std::string	path;
		std::string	bpath;
		std::string newpath;
		std::string newbpath;
		std::string new_fname;

		std::cout << "Enter a new filename of file '" << fname << "': ";
		std::cin >> new_fname;
		log.editing(fname, new_fname);
		if (is_exist(new_fname))
		{
			log.editing_error(fname);
			return;
		}
		path = FILE_PATH + fname;
		newpath = FILE_PATH + new_fname;
		bpath = BACKUP_PATH + fname;
		newbpath = BACKUP_PATH + new_fname;
		if (!rename(path.c_str(), newpath.c_str()) && !rename(bpath.c_str(), newbpath.c_str()))
		{
			for (int i = 0; i < cnt; i++)
				if (files[i] == fname)
				{
					files[i] = new_fname;
					break;
				}
			total_cpy();
			log.eediting(fname, new_fname);
		}
	}
	else if (is_exist(fname) && op == 3)
	{
		log.editing(fname);
		ofs.open(FILE_PATH + fname, std::ios_base::trunc);
		ofs.close();
		file_to_bcp(fname);
		log.eediting(fname);
	}
	else
		log.editing_error(fname);
}

void FileManager::show_files()
{
	std::cout << "Total: " << cnt << std::endl;
	for (int i = 0; i < cnt; i++)
		std::cout << i + 1 << ". " << files[i] << std::endl;
}

std::string _stdcall FileManager::WideStringToAnsi(std::wstring const& Str, UINT CodePage)
{
	DWORD const BuffSize = WideCharToMultiByte(CodePage, 0, Str.c_str(), -1, NULL, 0, NULL, NULL);
	if (!BuffSize) return NULL;
	std::vector<char> Buffer;
	Buffer.resize(BuffSize);
	if (!WideCharToMultiByte(CodePage, 0, Str.c_str(), -1, &Buffer[0], BuffSize, NULL, NULL)) return NULL;
	return (&Buffer[0]);
}

void FileManager::del_new_file(std::string fname)
{
	std::string		path;

	path = FILE_PATH + fname;
	if (!remove(path.c_str()))
	{
		std::cout << "File removed from your computer!" << std::endl;
	}
}

void FileManager::create_new_file(std::string fname)
{
	std::ofstream	res;

	res.open(RESET_FILE, std::ios_base::app);
	res << fname << std::endl;
	res.close();
	file_to_bcp(fname);
	std::string* tmp;
	tmp = new std::string[cnt + 1];
	for (int i = 0; i < cnt; i++)
		tmp[i] = files[i];
	cnt++;
	tmp[cnt - 1] = fname;
	files = tmp;
}

int FileManager::check_file(std::string fname)
{
	std::ifstream	file;
	std::ifstream	bcp;
	std::string		fbuff;
	std::string		bbuff;

	file.open(FILE_PATH + fname);
	bcp.open(BACKUP_PATH + fname);
	while (!file.eof() && !bcp.eof())
	{
		std::getline(file, fbuff);
		std::getline(bcp, bbuff);
		if (fbuff != bbuff)
		{
			std::cout << "The file '" << fname << "' was changed by a third-party program!\nRecover? (Y/n): ";
			std::cin >> fbuff;
			file.close();
			bcp.close();
			if (fbuff == "Y")
			{
				bcp_to_file(fname);
			}
			else if (fbuff == "n")
			{
				file_to_bcp(fname);
			}
			return 0;
		}
	}
	if ((file.eof() && !bcp.eof()) || (!file.eof() && bcp.eof()))
	{
		std::cout << "The file '" << fname << "' was changed by a third-party program!\nRecover? (Y/n): ";
		std::cin >> fbuff;
		file.close();
		bcp.close();
		if (fbuff == "Y")
		{
			bcp_to_file(fname);
		}
		else if (fbuff == "n")
		{
			file_to_bcp(fname);
		}
	}
	return 0;
}

void FileManager::file_to_bcp(std::string fname)
{
	std::ofstream	ofs;
	std::ifstream	ifs;
	std::string		fbuff;
	std::string		tmp;
	int				a;

	ifs.open(FILE_PATH + fname);
	ofs.open(BACKUP_PATH + fname, std::ios_base::trunc);
	a = 0;
	while (ifs.is_open() && !ifs.eof())
	{
		getline(ifs, tmp);
		a++;
	}
	ifs.close();
	ifs.open(FILE_PATH + fname);
	while (a)
	{
		getline(ifs, tmp);
		if (a == 1)
			ofs << tmp;
		else
			ofs << tmp << std::endl;
		a--;
	}
	ifs.close();
	ofs.close();
}

void FileManager::bcp_to_file(std::string fname)
{
	std::ofstream	ofs;
	std::ifstream	ifs;
	std::string		tmp;
	int				a;

	log.recovering(fname);
	ifs.open(BACKUP_PATH + fname);
	ofs.open(FILE_PATH + fname, std::ios_base::trunc);
	a = 0;
	while (ifs.is_open() && !ifs.eof())
	{
		getline(ifs, tmp);
		a++;
	}
	ifs.close();
	ifs.open(BACKUP_PATH + fname);
	while (a)
	{
		getline(ifs, tmp);
		if (a == 1)
			ofs << tmp;
		else
			ofs << tmp << std::endl;
		a--;
	}
	//std::cout << "File '" << fname << "' successfully recovered!" << std::endl;
	ifs.close();
	ofs.close();
	log.erecovering(fname);
}

void FileManager::renamer(std::string fname, std::string name)
{
	std::string path = FILE_PATH + fname;
	std::string newpath = FILE_PATH + name;
	std::string bpath = BACKUP_PATH + fname;
	std::string newbpath = BACKUP_PATH + name;
	if (!rename(path.c_str(), newpath.c_str()) && !rename(bpath.c_str(), newbpath.c_str()))
	{
		for (int i = 0; i < cnt; i++)
			if (files[i] == fname)
			{
				files[i] = name;
				break;
			}
		total_cpy();
	}
}

void FileManager::delete_record(std::string fname)
{
	std::string		path;
	std::string		bpath;
	std::string*	tmp;
	int				j;

	bpath = BACKUP_PATH + fname;
	if (!remove(bpath.c_str()))
	{
		tmp = new std::string[cnt - 1];
		j = 0;
		for (int i = 0; i < cnt; i++)
			if (files[i] != fname)
			{
				tmp[j] = files[i];
				j++;
			}
		cnt--;
		files = tmp;
		this->total_cpy();
	}
}
