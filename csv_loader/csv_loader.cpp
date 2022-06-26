/*
*
* Author: Lukas Ondrejka
* Date: 2022-06-17
*
* https://gist.github.com/lukasondrejka/9b0f12b3231126e70353de9578ecb275
*
*/


#include "csv_loader.h"


CSVLoader::CSVLoader(const std::string fileName, char separator) :
	fileName_(fileName),
	separator_(separator),
	file_(new std::fstream()),
	line_(std::vector<std::string>())
{
}


CSVLoader::CSVLoader(const std::string fileName) :
	CSVLoader(fileName, DEFAULT_SEPARATOR)
{
}


CSVLoader::~CSVLoader()
{
	this->fileName_ = "";
	this->separator_ = DEFAULT_SEPARATOR;
	this->close();

	delete this->file_;
	this->file_ = nullptr;
}


bool CSVLoader::isOpen()
{
	return file_->is_open();
}

void CSVLoader::open()
{
	if (this->isOpen() == false)
	{
		this->file_->open(fileName_, std::ios::in);
	}
}


void CSVLoader::close()
{
	if (this->isOpen() == true)
	{
		this->file_->close();
		this->line_.clear();
	}
}


bool CSVLoader::nextLine()
{
	if (this->isOpen() == false)
	{
		return false;
	}

	std::string s;

	if (std::getline(*this->file_, s))
	{
		std::stringstream line(s);

		this->line_.clear();

		while (std::getline(line, s, this->separator_))
		{
			this->line_.push_back(s);
		}

		return true;
	}
	else
	{
		this->close();

		return false;
	}
}

int CSVLoader::lineSize()
{
	return line_.size();
}


std::string CSVLoader::at(int index)
{
	return this->line_.at(index);
}


std::string CSVLoader::operator[](int index)
{
	return this->at(index);
}
