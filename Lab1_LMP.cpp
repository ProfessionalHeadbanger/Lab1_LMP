//Дан текстовый файл input.txt, в котором хранятся целые числа.
//Создать список по принципу очереди. 
//Найти вторую подпоследовательность, состоящую из простых чисел. 
//Переставить эту подпоследовательность после первого элемента, кратного 4. 
//Полученную последовательность записать в текстовый файл output.txt. 
//Если искомой подпоследовательности нет, то помимо последовательности в файл записать соответствующее сообщение.

#include "My_List.h"
#include <Windows.h>

bool task(LIST& list)
{
	auto is_simple = [](int first, int second)
	{
		bool prime = true;
		if ((first == 0 || first == 1) && (second == 0 || second == 1))
		{
			prime = false;
		}
		else
		{
			for (int i = 2; i <= first / 2; ++i)
			{
				if (first % i == 0)
				{
					prime = false;
					break;
				}
			}
			for (int i = 2; i <= second / 2; ++i)
			{
				if (second % i == 0)
				{
					prime = false;
					break;
				}
			}
		}
		return prime;
	};

	bool check = false;
	ptrNODE beg = nullptr, end = nullptr, head = list.get_head();
	ptrNODE p = head;
	ptrNODE p1 = head;
	ptrNODE kr4 = nullptr;
	int counter = 0;
	while (p1->next)
	{
		if (*p1->next->info % 4 == 0 && kr4 == nullptr)
		{
			kr4 = p1->next;
		}
		p1 = p1->next;
	}
	while (p->next && p->next->next)
	{
		if (is_simple(*p->next->info, *p->next->next->info) && (p == head || !is_simple(*p->info, *p->next->info)))
		{
			beg = p;
			end = nullptr;
		}
		else
		{
			if (is_simple(*p->info, *p->next->info) && !is_simple(*p->next->info, *p->next->next->info))
			{
				end = p->next;
				counter++;
			}
		}
		p = p->next;
		if (counter == 2)
		{
			break;
		}
	}
	if (beg && !end)
	{
		end = p->next;
	}
	if (beg)
	{
		if (end != kr4)
		{
			ptrNODE tmp = beg->next;
			beg->next = end->next;
			end->next = kr4->next;
			kr4->next = tmp;
			list.set_tail(end);
		}
		check = true;
	}
	return check;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool flag = true;
	while (flag)
	{
		LIST list;
		std::ifstream file_in("input.txt");
		std::ofstream file_out("output.txt");
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
			if (task(list))
			{
				list.print(file_out, "Преобразованная последовательность: \n");
			}
			else
			{
				list.print(file_out);
			}
		}

		file_in.close();
		file_out.close();

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
