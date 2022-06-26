/*
*
* Author: Lukas Ondrejka
* Date: 2022-06-17
*
* https://gist.github.com/lukasondrejka/9b0f12b3231126e70353de9578ecb275
*
*/


#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#pragma execution_character_set( "utf-8" )

#define DEFAULT_SEPARATOR ';'

/// <summary> CSVLoader – Simple C++ class for loading CSV files </summary>
class CSVLoader
{
public:

	/// <summary> Constructor </summary>
	/// <param name="fileName"> Name of CSV file </param>
	/// <param name="separator"> Separating character </param>
	CSVLoader(const std::string fileName, char separator);

	/// <summary> Constructor </summary>
	/// <param name="fileName"> Name of CSV file </param>
	CSVLoader(const std::string fileName);

	/// <summary> Destructor </summary>
	~CSVLoader();

	/// <summary> Is file open </summary>
	/// <returns> True if open, else false </returns>
	bool isOpen();

	/// <summary> Open CSV file </summary>
	void open();

	/// <summary> Close CSV file </summary>
	void close();

	/// <summary> Go to the next row </summary>
	/// <returns> True if passed, else false </returns>
	bool nextLine();

	/// <summary> Count of items in the current row </summary>
	/// <returns> Count of items </returns>
	int lineSize();

	/// <summary> Access to the item at the index in the current row </summary>
	/// <param name="index"> Index od item in the current row </param>
	/// <returns> Item </returns>
	std::string at(int index);

	/// <summary> Access to the item at the index in the current row </summary>
	/// <param name="index"> Index of item in the current row </param>
	/// <returns> Item </returns>
	std::string operator[](int index);

private:

	/// <summary> Name of CSV file </summary>
	std::string fileName_;

	/// <summary> Separating character </summary>
	char separator_;

	/// <summary> Stream to load the file </summary>
	std::fstream* file_;

	/// <summary> Items in the current row </summary>
	std::vector<std::string> line_;
};
