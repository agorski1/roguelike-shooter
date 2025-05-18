#include"Application.h"
#include <SFML/Graphics.hpp>
#include<iostream>
int main()
{
	try
	{
		Application application;
		application.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}