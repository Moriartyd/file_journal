#include "Menu.h"

using namespace std;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::show()
{
	if (fshow)
	{
		fshow = 0;
		std::cout << "====================================MENU====================================" << std::endl;
		std::cout << " 1. Create file" << std::endl
			<< " 2. Delete file" << std::endl
			<< " 3. Edit file" << std::endl
			<< " 4. Show MENU" << std::endl
			<< " 5. Show total" << std::endl
			<< " 0. Exit" << std::endl;
		std::cout << "============================================================================" << std::endl;
	}
}

void Menu::ops()
{
	int	op;

	std::cout << "Enter menu position: ";
	std::cin >> op;
	switch (op)
	{
		case 1:
			fman.create_file(read_fname());
			break;
		case 2:
			fman.del_file(read_fname());
			break;
		case 3:
			show_edit_menu();
			std::cout << "Enter edit-menu position: ";
			std::cin >> op;
			if (op)
				fman.edit_file(read_fname(), op);
			else
				fshow = 1;
			break;
		case 4:
			fshow = 1;
			break;
		case 5:
			fman.show_files();
			break;
		case 0:
			exit(1);
			break;
	}
}

void Menu::log_check()
{
	int		num;
	int		pos;
	string	buff;
	string	prev;
	string	fname;
	fstream	fs;
	fstream	bs;

	fman.reset_files();
	fs.open(LOG_FILE, ios_base::app);
	fs.close();
	bs.open("./Backup/log.txt", ios_base::app);
	bs.close();
	fs.open(LOG_FILE);
	if (!fs.is_open())
		log.show_error();
	num = 0;
	while (!fs.eof())
	{
		getline(fs, buff);
		num++;
	}
	fs.close();
	fs.open(LOG_FILE, ios_base::in);
	if (!fs.is_open())
		log.show_error();
	while (--num)
			getline(fs, buff);
	fs.close();
	log.check_log();
	pos = 0;
	if (buff != "" && buff[0] != '2')
	{
		for (int i = 0; i < buff.size(); i++)
		{
			if (buff[i] == ';')
				pos = i;
		}
		string newname;
		if (pos)
		{
			newname = buff.substr(pos + 1);
			fname = buff.substr(4, pos - 4);
		}
		else
			fname = buff.substr(4);
		switch (buff[1])
		{
		case '1':
			fman.sdel_file(fname);
			log.secreating(fname);
			cout << "The program was interrupted while creating a file '" << fname << "'" << endl;
			fman.create_file(fname);
			break;
		case '2':
			pos ? log.seediting(fname, newname) : log.seediting(fname);
			cout << "The program was interrupted while editing a file '" << fname << "'" << endl;
			pos ? fman.renamer(newname, fname) : void();
			fman.bcp_to_file(fname);
			break;
		case '3':
			log.serecovering(fname);
			cout << "The program was interrupted while recovering a file '" << fname << "'" << endl;
			fman.bcp_to_file(fname);
			break;
		case '4':
			log.seremoving(fname);
			fman.screate_file(fname);
			cout << "The program was interrupted while removing a file '" << fname << "'" << endl;
			fman.del_file(fname);
			break;
		}
	}
	fman.checker();
}

std::string Menu::read_fname()
{
	std::string fname;
	std::cout << "Enter filename: ";
	std::cin >> fname;
	return (fname);
}

void Menu::show_edit_menu()
{
	std::cout << "This is edit-menu:\n"
		<< "1. Add line at the end of file\n"
		<< "2. Rename file\n" 
		<< "3. Clear file\n"
		<< "0. Go to main menu" << std::endl;
}
