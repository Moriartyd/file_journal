#include "Log.h"

Log::Log()
{
}

Log::~Log()
{
}

void Log::show_error()
{
	cout << "Error: Can't open log file" << endl;
	exit(-1);
}

void Log::creating_error(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "21: " << fname << endl;
	bs << "21: " << fname << endl;
	cout << "LOG: Error: can't create file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::deleting_error(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "24: " << fname << endl;
	bs << "24: " << fname << endl;
	std::cout << "Log: Error: File '" << fname << "' does not exist!" << std::endl;
	fs.close();
	bs.close();
}

void Log::editing_error(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "22: " << fname << endl;
	bs << "22: " << fname << endl;
	std::cout << "Log: Error: File '" << fname << "' does not exist!" << std::endl;
	fs.close();
	bs.close();
}

void Log::creating(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "11: " << fname << endl;
	bs << "11: " << fname << endl;
	cout << "LOG: Start creating file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::secreating(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "11: " << fname << endl;
	bs << "11: " << fname << endl;
	fs.close();
	bs.close();
}

void Log::ecreating(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "21: " << fname << endl;
	bs << "21: " << fname << endl;
	cout << "LOG: File '" << fname << "' successfully created!" << endl;
	fs.close();
	bs.close();
}

void Log::editing(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "12: " << fname << endl;
	bs << "12: " << fname << endl;
	cout << "LOG: Start editing file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::seediting(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "22: " << fname << endl;
	bs << "22: " << fname << endl;
	fs.close();
	bs.close();
}

void Log::seediting(string fname, string newfname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "22: " << fname << ";" << newfname << endl;
	bs << "22: " << fname << ";" << newfname << endl;
	fs.close();
	bs.close();
}

void Log::editing(string fname, string newfname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "12: " << fname << ";" << newfname << endl;
	bs << "12: " << fname << ";" << newfname << endl;
	cout << "LOG: Start editing file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::eediting(string fname, string newfname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "22: " << fname << ";" << newfname << endl;
	bs << "22: " << fname << ";" << newfname << endl;
	cout << "LOG: File '" << newfname << "' saved!" << endl;
	fs.close();
	bs.close();
}

void Log::eediting(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "22: " << fname << endl;
	bs << "22: " << fname << endl;
	cout << "LOG: File '" << fname << "' saved!" << endl;
	fs.close();
	bs.close();
}

void Log::recover_log()
{
	std::ofstream	ofs;
	std::ifstream	ifs;
	std::string		tmp;
	int				a;

	ifs.open("./Backup/log.txt");
	ofs.open(LOG_FILE, std::ios_base::trunc);
	a = 0;
	while (ifs.is_open() && !ifs.eof())
	{
		getline(ifs, tmp);
		a++;
	}
	ifs.close();
	ifs.open("./Backup/log.txt");
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

void Log::check_log()
{
	std::ifstream	file;
	std::ifstream	bcp;
	std::string		fbuff;
	std::string		bbuff;

	file.open(LOG_FILE);
	bcp.open("./Backup/log.txt");
	while (!file.eof() && !bcp.eof())
	{
		std::getline(file, fbuff);
		std::getline(bcp, bbuff);
		if (fbuff != bbuff)
		{
			cout << "Log file is corrupted!" << endl;
			cout << "Start recovering Log file!" << endl;
			file.close();
			bcp.close();
			recover_log();
			cout << "Log file successfully recovered!" << endl;
		}
	}
	if ((file.is_open() && bcp.is_open()) && ((file.eof() && !bcp.eof()) || (!file.eof() && bcp.eof())))
	{
		cout << "Log file is corrupted!" << endl;
		cout << "Start recovering Log file!" << endl;
		file.close();
		bcp.close();
		recover_log();
		cout << "Log file successfully recovered!" << endl;
	}
	if (file.is_open())
		file.close();
	if (bcp.is_open())
		bcp.close();
}


void Log::recovering(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "13: " << fname << endl;
	bs << "13: " << fname << endl;
	cout << "LOG: Start recovering file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::serecovering(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "23: " << fname << endl;
	bs << "23: " << fname << endl;
	fs.close();
	bs.close();
}

void Log::erecovering(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "23: " << fname << endl;
	bs << "23: " << fname << endl;
	cout << "LOG: File '" << fname << "' successfully recovered!" << endl;
	fs.close();
	bs.close();
}

void Log::removing(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "14: " << fname << endl;
	bs << "14: " << fname << endl;
	cout << "LOG: Start removing file '" << fname << "'" << endl;
	fs.close();
	bs.close();
}

void Log::seremoving(string fname)
{
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "24: " << fname << endl;
	bs << "24: " << fname << endl;
	fs.close();
	bs.close();
}

void Log::eremoving(string fname)
{
	this_thread::sleep_for(chrono::seconds(3));
	fs.open(LOG_FILE, ios_base::app);
	bs.open("./Backup/log.txt", ios_base::app);
	if (!fs.is_open())
		show_error();
	fs << "24: " << fname << endl;
	bs << "24: " << fname << endl;
	cout << "LOG: File '" << fname << "' successfully removed!" << endl;
	fs.close();
	bs.close();
}
