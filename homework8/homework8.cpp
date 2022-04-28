/*
1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero, 
если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения.

2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра. 
Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a.
Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0. 
В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.

3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, означающий задание переместиться на соседнюю позицию. 
Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand, 
если подана неверная команда (направление не находится в нужном диапазоне). 
Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения. 
Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех возникающих ошибках.
*/

#include <iostream>
#include <string>
//Task#1
class division
{
protected:
	std::string message;
public:
	division(std::string message = "") : message(message) {}
	const std::string& getMessage() const { return message; }
};

namespace exceptionForZero
{

	template <typename T>
	double div(T a, T b)
	{
		if (b == 0)
			throw division("Warning! Attempt to divide by zero!");

		return a / b;
	}

}

void Task1()
{
	try
	{
		double f, s;
		std::cout << "Enter first number" << std::endl;
		std::cin >> f;
		std::cout << "Enter second number" << std::endl;
		std::cin >> s;
		double result = exceptionForZero::div(f, s);
		std::cout << result << std::endl;
	}
	catch (const division& m)
	{
		std::cerr << m.getMessage() << std::endl;
	}
}

//Task#2
class Ex
{
public:
	double x;

	Ex(double x) : x(x) {};
};

class Bar
{
protected:
	double y;
public:
	Bar(double y = 0.0) : y(y) {}
	void set(double a)
	{
		if ((y + a) > 100) {
			throw Ex(a * y);
		}
		else {
			y = a;
		}

	}
};

void Task2()
{
	Bar a;
	int b;

	try
	{
		while (true)
		{
			std::cout << "Enter a number" << std::endl;
			std::cin >> b;
			if (b == 0) {
				break;
			}

			a.set(b);
		}
	}
	catch (const Ex& e)
	{
		std::cout << e.x << std::endl;
	}
}
//Task#3

class OffTheField
{
	int cur_pos_x;
	int cur_pos_y;
	int new_pos_x;
	int new_pos_y;
	std::string messageField;
public:
	OffTheField(int c_x, int c_y, int n_x, int n_y) :
		cur_pos_x(c_x), cur_pos_y(c_y), new_pos_x(n_x), new_pos_y(n_y), messageField("")
	{
		if (new_pos_x > 10 || new_pos_x < 1)
		{
			messageField += "Warning! Wrong x value! Robot left the field!\n";
			messageField += '[' + std::to_string(cur_pos_x) + ';' + std::to_string(cur_pos_y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
		if (new_pos_y > 10 || new_pos_y < 1)
		{
			messageField += "Warning! Wrong y value! Robot left the field!\n";
			messageField += '[' + std::to_string(cur_pos_x) + ';' + std::to_string(cur_pos_y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return messageField;
	}
};

class IllegalCommand
{
private:
	int cur_pos_x;
	int cur_pos_y;
	int new_pos_x;
	int new_pos_y;
	std::string messageCommand;
public:
	IllegalCommand(int c_x, int c_y, int n_x, int n_y) :
		cur_pos_x(c_x), cur_pos_y(c_y), new_pos_x(n_x), new_pos_y(n_y), messageCommand("")
	{
		if (abs(cur_pos_x - new_pos_x) > 1)
		{
			messageCommand += "Warning! X value exceeds the field!\n";
			messageCommand += '[' + std::to_string(cur_pos_x) + ';' + std::to_string(cur_pos_y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}

		if (abs(cur_pos_y - new_pos_y) > 1)
		{
			messageCommand += "Warning! Y value exceeds the field!\n";
			messageCommand += '[' + std::to_string(cur_pos_x) + ';' + std::to_string(cur_pos_y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}

		if (cur_pos_x == new_pos_x && cur_pos_y == new_pos_y)
		{
			messageCommand += "Warning! Wrong x and y values! Robot cannot be placed there!\n";
			messageCommand += '[' + std::to_string(cur_pos_x) + ';' + std::to_string(cur_pos_y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return messageCommand;
	}
};

class Robot
{
private:
	int pos_x;
	int pos_y;
public:
	Robot(int x = 5, int y = 5) : pos_x(x), pos_y(y)
	{
		std::cout << "Initial possition: [" << pos_x << ';' << pos_y << ']' << std::endl;
	}

	void move(int x, int y)
	{
		if (abs(pos_x - x) > 1 || abs(pos_y - y) > 1 || (pos_x == x && pos_y == y))
			throw IllegalCommand(pos_x, pos_y, x, y);
		if (x > 10 || x < 1 || y > 10 || y < 1)
			throw OffTheField(pos_x, pos_y, x, y);

		std::cout << "Move [" << pos_x << ';' << pos_y << "] => [" << x << ';' << y << ']' << std::endl;

		pos_x = x;
		pos_y = y;
	}
};

void Task3()
{
	int x = 0, y = 0;
	Robot r;

	while (true)
	{
		std::cin >> x >> y;

		if (x == 0 && y == 0)
			break;

		try
		{
			r.move(x, y);
		}
		catch (const IllegalCommand& e)
		{
			std::cerr << e.getInfo() << std::endl;
		}
		catch (const OffTheField& e)
		{
			std::cerr << e.getInfo() << std::endl;
		}
	}
}

int main()
{
	Task1();
	Task2();
	Task3();
}

