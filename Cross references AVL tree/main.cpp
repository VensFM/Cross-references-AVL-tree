#include <iostream>
#include <fstream>
#include "AVLtree.h"

const std::string error_open = ", not open";
const std::string error_enter = ", enter failed";

int main()
{
	std::ifstream in;
	std::ofstream out;
	try
	{
		std::string inFileName;
		std::cout << "	<<Cross references>>\n Enter filename to read: ";
		std::cin >> inFileName;
		in.open(inFileName);
		if (!in)
		{
			throw "file " + inFileName + error_open;
		}
		system("cls");
		std::cout << "	<<Cross references>>\n\n";
		size_t n = 1;
		std::string buf;
		AVLtree dictionary;
		while (getline(in, buf))
		{
			std::cout.width(5);
			std::cout << n << ". " << buf << "\n";
			std::string word = "";
			bool flag = false;
			for (size_t i = 0; i <= buf.length(); ++i)
			{
				if ((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] == '\'' && flag))
				{
					word += buf[i];
					flag = true;
				}
				else if (word != "")
				{
					dictionary.insert(word, n);
					word = "";
					flag = false;
				}
			}
			++n;
		}
		std::cout << "\n";
		dictionary.getTable(std::cout);
		system("pause");
		int menu;
		while (true)
		{
			system("cls");
			std::cout << "	<<Cross references>>\n\n Choose action with dictionary:\n	1. Add word\n	2. Search word\n	3. Delete word\n	4. Print dictinary\n	5. Write dictionary to file\n	0. Exit\n ";
			std::cin >> menu;
			if (std::cin.peek() != '\n' || std::cin.fail() || menu < 0 || menu > 5)
			{
				throw "console" + error_enter;
			}
			if (menu == 0)
			{
				break;
			}
			if (menu == 1)
			{
				system("cls");
				std::cout << "	Add word:\n\n";
				std::string newWord;
				int page;
				std::cout << " Enter word: ";
				std::cin >> newWord;
				if (std::cin.peek() != '\n' || std::cin.fail())
				{
					throw "console" + error_enter;
				}
				std::cout << " Enter page: ";
				std::cin >> page;
				if (std::cin.peek() != '\n' || std::cin.fail() || page < 0)
				{
					throw "console" + error_enter;
				}
				if (dictionary.insert(newWord, page))
				{
					std::cout << " Word succecfully added\n";
				}
				else
				{
					std::cerr << " Word addition failed\n";
				}
				system("pause");
			}
			if (menu == 2)
			{
				system("cls");
				std::cout << "	Search word:\n\n";
				std::string newWord;
				std::cout << " Enter word: ";
				std::cin >> newWord;
				if (std::cin.peek() != '\n' || std::cin.fail())
				{
					throw "console" + error_enter;
				}
				if (dictionary.search(newWord))
				{
					std::cout << " Word succecfully found\n";
				}
				else
				{
					std::cerr << " Word not found\n";
				}
				system("pause");
			}
			if (menu == 3)
			{
				system("cls");
				std::cout << "	Delete word:\n\n";
				std::string newWord;
				std::cout << " Enter word: ";
				std::cin >> newWord;
				if (std::cin.peek() != '\n' || std::cin.fail())
				{
					throw "console" + error_enter;
				}
				if (dictionary.deleteKey(newWord))
				{
					std::cout << " Word succecfully deleted\n";
				}
				else
				{
					std::cerr << " Word not deleted\n";
				}
				system("pause");
			}
			if (menu == 4)
			{
				system("cls");
				std::cout << "	Dictionary:\n\n";
				dictionary.getTable(std::cout);
				system("pause");
				continue;
			}
			if (menu == 5)
			{
				system("cls");
				std::string outFileName = "";
				std::cout << "	Recording\n\n Enter a file name for the recording: ";
				std::cin >> outFileName;
				out.open(outFileName);
				if (!out)
				{
					throw "file " + outFileName + error_open;
				}
				dictionary.getTable(out);
				std::cout << " Dictionary successfully written\n";
				system("pause");
			}
		}

	}
	catch (const std::string& error)
	{
		std::cerr << " Error: " << error;
		exit(-1);
	}
	in.close();
	out.close();
	return 0;
}