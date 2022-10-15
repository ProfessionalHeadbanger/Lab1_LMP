//Дан текстовый файл input.txt, в котором хранятся целые числа.
//Создать список по принципу очереди. 
//Найти вторую подпоследовательность, состоящую из простых чисел. 
//Переставить эту подпоследовательность после первого элемента, кратного 4. 
//Полученную последовательность записать в текстовый файл output.txt. 
//Если искомой подпоследовательности нет, то помимо последовательности в файл записать соответствующее сообщение.

#include "My_List.h"
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool flag = true;
	while (flag)
	{
		LIST list;
		std::ifstream file_in("input.txt");
		if (file_in)
		{
			bool input = true;
			while (input)
			{
				char choice;
				std::cout << "Выберите, как будет создаваться список (1 - стек, 2 - очередь, 3 - упорядоченно): "; std::cin >> choice;
				switch (choice)
				{
				case '1':
					list.create_by_stack(file_in);
					input = false;
					break;
				case '2':
					list.create_by_queue(file_in);
					input = false;
					break;
				case '3':
					list.create_by_order(file_in);
					input = false;
					break;
				default:
					std::cout << "Неверный ввод" << std::endl;
					input = true;
					break;
				}
			}
		}

		file_in.close();

		char choice;
		bool label = true;
		while (label)
		{
			std::cout << "Желаете начать заново или выйти? 1 - заново, 2 - выйти ";
			std::cin >> choice;
			switch (choice)
			{
			default:
				std::cout << "Неверный ввод!" << std::endl;
				label = true;
				break;
			case '1':
				flag = true;
				label = false;
				break;
			case '2':
				flag = false;
				label = false;
				break;
			}
		}
	}
	std::cin.ignore();
	std::cin.get();
}