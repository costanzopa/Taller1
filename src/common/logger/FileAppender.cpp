/*
 * FileAppender.cpp
 *
 *  Created on: Sep 2, 2016
 *      Author: mario
 */

#include "FileAppender.h"

#include <fstream>
#include <iostream>

using namespace std;


namespace logger {

FileAppender::FileAppender(std::string& file) {
	this->file = file;
}

void FileAppender::append(std::string& message) {
	std::string file = this->file;
	FILE * pLog = fopen (file.c_str(),"a");
	fprintf(pLog,message.c_str());
	fprintf(pLog,"\n");
	fclose (pLog);
}

FileAppender::~FileAppender() {
}

} /* namespace logger */
