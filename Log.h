#pragma once
#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#define	LOG_FILE "log.txt"
#define	BACKUP_PATH "./Backup/"


using namespace std;

class Log
{
public:
	Log();
	~Log();
	void	show_error();
	void	creating_error(string fname);
	void	deleting_error(string fname);
	void	editing_error(string fname);
	void	creating(string fname); //1
	void	secreating(string fname);
	void	ecreating(string fname);
	void	editing(string fname); //2
	void	seediting(string fname);
	void	seediting(string fname, string newfname);
	void	editing(string fname, string newfname);
	void	eediting(string fname, string newfname);
	void	eediting(string fname);
	void	recover_log();
	void	check_log();
	void	recovering(string fname); //3
	void	serecovering(string fname);
	void	erecovering(string fname);
	void	removing(string fname); //4
	void	seremoving(string fname);
	void	eremoving(string fname);

private:
	fstream	fs;
	fstream	bs;
};

#endif // !LOG_H