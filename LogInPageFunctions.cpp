/*
Wazne parametry:
 Okno 1280x780
	sf::Vector2u windowSize = window.getSize(); //Pobor rozmiaru okna
 Czcionki:
	arial.ttf <Testing>
	Inria_Serif/InriaSerif-LightItalic.ttf <Text - glam>
	Instrument_Sans/static/InstrumentSans-SemiBold.ttf <Text - read>
	League_Script/LeagueScript-Regular.ttf <LOGO>

*/
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define NOMINMAX
#ifdef _WIN32
#include <windows.h>
#else
//#include <cstdlib> // dla system()
#endif
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "Header.h"
#include <SQLite/sqlite3.h>
#include <fstream>
#include "sqlitecloud/sqcloud.h"


void draw_clear_screen(sf::RenderWindow& window) {
	sf::Texture ClearScreen;
	if (!ClearScreen.loadFromFile("Resources/images/Clear_MainPage.png")) {
		std::cout << "Failed to load Clear screen!" << std::endl;
		return;
	}
	sf::Sprite ClearScreenP(ClearScreen);
	window.draw(ClearScreenP);
	window.display();

}

void draw_signup_screen(sf::RenderWindow& window, sf::Event event) {
	//window.clear();
	sf::Texture SignUPScreen;
	if (!SignUPScreen.loadFromFile("Resources/images/SignUp_MainPage.png")) {
		std::cout << "Failed to load Sign up screen!" << std::endl;
		return;
	}
	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf"))
		std::cout << "Failed to load font" << std::endl;

	sf::Sprite SignUPScreenP(SignUPScreen);
	window.draw(SignUPScreenP);
	sf::RectangleShape targetFieldName(sf::Vector2f(200, 17));
	sf::RectangleShape targetFieldEmail(sf::Vector2f(200, 17));
	sf::RectangleShape targetFieldPass1(sf::Vector2f(200, 17));
	sf::RectangleShape targetFieldPass2(sf::Vector2f(200, 17));
	sf::RectangleShape targetL(sf::Vector2f(105, 36));
	sf::RectangleShape targetN(sf::Vector2f(105, 36));
	targetFieldName.setPosition(578, 286);
	targetFieldEmail.setPosition(578, 327);
	targetFieldPass1.setPosition(578, 368);
	targetFieldPass2.setPosition(578, 409);
	targetL.setPosition(520, 212);
	targetN.setPosition(585, 467);

	//window.draw(targetFieldName);
	//window.draw(targetFieldEmail);
	//window.draw(targetFieldPass1);
	//window.draw(targetFieldPass2);

	std::string pass1Stars = "";
	std::string pass2Stars = "";
	std::string nameInput;
	std::string emailInput = "";
	std::string pass1Input;
	std::string pass2Input;
	sf::Text nameText(nameInput, font, 15);
	sf::Text emailText(emailInput, font, 15);
	sf::Text pass1Text(pass1Stars, font, 15);
	sf::Text pass2Text(pass2Stars, font, 15);
	nameText.setPosition(578, 286);
	emailText.setPosition(578, 327);
	pass1Text.setPosition(578, 368);
	pass2Text.setPosition(578, 409);
	nameText.setFillColor(sf::Color::Black);
	emailText.setFillColor(sf::Color::Black);
	pass1Text.setFillColor(sf::Color::Black);
	pass2Text.setFillColor(sf::Color::Black);
	window.display();


	bool userDataEntered = false;

	bool inNameField = false;
	bool inEmailField = false;
	bool inPass1Field = false;
	bool inPass2Field = false;
	
	while (!userDataEntered) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				ExecutePy_FinalizeEx();
				window.close();
				return;
			}
			//Close button service
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
				//----------Logged_OUT_Buttons----------
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				std::cout << "Mouse clicked at: ("
					<< mousePosition.x << ", "
					<< mousePosition.y << ")" << std::endl;
				if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					std::cout << "Click at 'SignUp' button" << std::endl;
					targetFieldName.setPosition(2000, 2000);
					targetFieldEmail.setPosition(2000, 2000);
					targetFieldPass1.setPosition(2000, 2000);
					targetFieldPass2.setPosition(2000, 2000);
					draw_login_screen(window, event);
					userDataEntered = true;
					break;

				}
				else if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inNameField == true) {
					std::cout << "Click at 'E-mail' field" << std::endl;
					inNameField = true;
					while (inNameField) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							nameText.setString(nameInput + "|");
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == 8 && !nameInput.empty()) { // Handle backspace
									nameInput.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									nameInput += static_cast<char>(event.text.unicode);
								}
								nameText.setString(nameInput + "|");
								std::cout << nameInput << std::endl;
								User.name = nameInput;
								//window.draw(emailText);
							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								nameText.setString(nameInput);
								if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = true;
									inPass1Field = false;
									inPass2Field = false;
									break;
								}else if (targetFieldPass1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = true;
									inPass2Field = false;
									break;
								} else if (targetFieldPass2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = true;
									break;
								}
								else if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'LogIn' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									userDataEntered = true;
									//draw_login_screen(window, event);
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									if (!check_user(nameInput, emailInput, pass1Input, pass2Input, "plantly.db")) {
										userDataEntered = false;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										pass1Text.setFillColor(sf::Color::Red);
										pass2Text.setFillColor(sf::Color::Red);
										userDataEntered = false;
										break;
									}
									userDataEntered = true;
									break;
								}
							}
							window.clear();
							window.draw(SignUPScreenP);
							window.draw(nameText);
							window.draw(emailText);
							window.draw(pass1Text);
							window.draw(pass2Text);
							window.display();
						}
					}
				}
				else if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inEmailField == true) {
					std::cout << "Click at 'E-mail' field" << std::endl;
					inEmailField = true;
					while (inEmailField) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							emailText.setString(emailInput + "|");
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == 8 && !emailInput.empty()) { // Handle backspace
									emailInput.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									emailInput += static_cast<char>(event.text.unicode);
								}
								emailText.setString(emailInput + "|");
								std::cout << emailInput << std::endl;
								User.email = emailInput;
								//window.draw(emailText);
							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								emailText.setString(emailInput);
								if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = true;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									break;
								} else if (targetFieldPass1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = true;
									inPass2Field = false;
									break;
								}
								else if (targetFieldPass2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = true;
									break;
								}
								else if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'LogIn' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									userDataEntered = true;
									//draw_login_screen(window, event);
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									if (!check_user(nameInput, emailInput, pass1Input, pass2Input, "plantly.db")) {
										userDataEntered = false;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										pass1Text.setFillColor(sf::Color::Red);
										pass2Text.setFillColor(sf::Color::Red);
										userDataEntered = false;
										break;
									}
									userDataEntered = true;
									break;
								}
								
							}
							window.clear();
							window.draw(SignUPScreenP);
							window.draw(nameText);
							window.draw(emailText);
							window.draw(pass1Text);
							window.draw(pass2Text);
							window.display();
						}
					}
				}
				else if (targetFieldPass1.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inPass1Field == true) {
					std::cout << "Click at 'Password1' field" << std::endl;
					inPass1Field = true;
					while (inPass1Field) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							pass1Text.setString(pass1Stars + "|");
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == 8 && !pass1Input.empty()) { // Handle backspace
									emailText.setFillColor(sf::Color::Black);
									pass1Text.setFillColor(sf::Color::Black);
									pass1Input.pop_back();
									pass1Stars.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									pass1Input += static_cast<char>(event.text.unicode);
									pass1Stars += "*";
								}
								pass1Text.setString(pass1Stars + "|");
								std::cout << pass1Input << std::endl;
								User.password = pass1Input;

							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								pass1Text.setString(pass1Stars);
								if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = true;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									break;
								}else if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = true;
									inPass1Field = false;
									inPass2Field = false;
									break;
								} else if (targetFieldPass2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = true;
									break;
								}
								else if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'LogIn' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									userDataEntered = true;
									//draw_login_screen(window, event);
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									if (!check_user(nameInput, emailInput, pass1Input, pass2Input, "plantly.db")) {
										userDataEntered = false;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										pass1Text.setFillColor(sf::Color::Red);
										pass2Text.setFillColor(sf::Color::Red);
										userDataEntered = false;
										break;
									}
									userDataEntered = true;
									break;
								}

							}
							window.clear();
							window.draw(SignUPScreenP);
							window.draw(nameText);
							window.draw(emailText);
							window.draw(pass1Text);
							window.draw(pass2Text);
							window.display();
						}
					}
				}
				else if (targetFieldPass2.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inPass2Field == true) {
					std::cout << "Click at 'Password2' field" << std::endl;
					inPass2Field = true;
					while (inPass2Field) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							pass2Text.setString(pass2Stars + "|");
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == 8 && !pass2Input.empty()) { // Handle backspace
									emailText.setFillColor(sf::Color::Black);
									pass2Text.setFillColor(sf::Color::Black);
									pass2Input.pop_back();
									pass2Stars.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									pass2Input += static_cast<char>(event.text.unicode);
									pass2Stars += "*";
								}
								pass2Text.setString(pass2Stars + "|");
								std::cout << pass2Input << std::endl;
								//User.password = pass2Input;

							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								pass2Text.setString(pass2Stars);
								if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = true;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									break;
								}
								else if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = true;
									inPass1Field = false;
									inPass2Field = false;
									break;
								}
								else if (targetFieldPass1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inNameField = false;
									inEmailField = false;
									inPass1Field = true;
									inPass2Field = false;
									break;
								}
								else if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'LogIn' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									userDataEntered = true;
									//draw_login_screen(window, event);
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inNameField = false;
									inEmailField = false;
									inPass1Field = false;
									inPass2Field = false;
									if (!check_user(nameInput, emailInput, User.password, pass2Input, "plantly.db")) {
										userDataEntered = false;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										pass1Text.setFillColor(sf::Color::Red);
										pass2Text.setFillColor(sf::Color::Red);
										userDataEntered = false;
										break;
									}
									userDataEntered = true;
									break;
								}
							}
							window.clear();
							window.draw(SignUPScreenP);
							window.draw(nameText);
							window.draw(emailText);
							window.draw(pass1Text);
							window.draw(pass2Text);
							window.display();
						}
					}
				}
			}
			if (userDataEntered == true)
				break;
		}
		//window.draw(emailText);
		//window.draw(passText);

	}
	draw_clear_screen(window);
	

	window.display();

}

void draw_login_screen(sf::RenderWindow& window, sf::Event event) {
	//window.clear();
	sf::Texture LogINScreen;
	if (!LogINScreen.loadFromFile("Resources/images/LogIn_MainPage.png")) {
		std::cout << "Failed to load Log in screen!" << std::endl;
		return;
	}
	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf"))
		std::cout << "Failed to load font" << std::endl;

	sf::Sprite LogINScreenP(LogINScreen);
	window.draw(LogINScreenP);

	sf::RectangleShape targetFieldEmail(sf::Vector2f(200, 17));
	sf::RectangleShape targetFieldPass(sf::Vector2f(200, 17));
	sf::RectangleShape targetS(sf::Vector2f(105, 36));
	sf::RectangleShape targetN(sf::Vector2f(105, 36));
	targetFieldEmail.setPosition(578, 286);
	targetFieldPass.setPosition(578, 327);
	targetS.setPosition(655, 212);
	targetN.setPosition(585, 467);

	//window.draw(targetFieldPass);
	std::string passStars = "";
	std::string emailInput = "";
	std::string passInput;
	sf::Text emailText(emailInput, font, 15);
	sf::Text passText(passStars, font, 15);
	emailText.setPosition(578, 286);
	passText.setPosition(578, 327);
	emailText.setFillColor(sf::Color::Black);
	passText.setFillColor(sf::Color::Black);
	window.display();

	//std::string

	bool userDataEntered = false;

	bool inPassField = false;
	bool inEmailField = false;
	
	while (!userDataEntered) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				ExecutePy_FinalizeEx();
				window.close();
				return;
			}
			//Close button service
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
				//----------Logged_OUT_Buttons----------
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				std::cout << "Mouse clicked at: ("
					<< mousePosition.x << ", "
					<< mousePosition.y << ")" << std::endl;
				if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					std::cout << "Click at 'SignUp' button" << std::endl;
					targetFieldEmail.setPosition(2000, 2000);
					targetFieldPass.setPosition(2000, 2000);
					draw_signup_screen(window, event);
					userDataEntered = true;
					break;

				}
				else if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inEmailField == true) {
					std::cout << "Click at 'E-mail' field" << std::endl;
					inEmailField = true;
					while (inEmailField) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							emailText.setString(emailInput + "|");
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == 8 && !emailInput.empty()) { // Handle backspace
									
									emailInput.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									emailInput += static_cast<char>(event.text.unicode);
								}
								emailText.setString(emailInput + "|");
								std::cout << emailInput << std::endl;
								User.email = emailInput;
								//window.draw(emailText);
							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								emailText.setString(emailInput);
								if (targetFieldPass.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inEmailField = false;
									inPassField = true;
									break;
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inPassField = false;
									inEmailField = false;
									if (check_user(emailInput, passInput, "plantly.db")) {
										std::cout << "Record is true!" << std::endl;
										check_user_in(emailInput, passInput, "plantly.db");
										userDataEntered = true;
										appState = AppState::LOGGED_IN;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										passText.setFillColor(sf::Color::Red);
										userDataEntered = false;
										//window.display();

									}
									break;
								}
								else if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'SignUp' button" << std::endl;
									inPassField = false;
									inEmailField = false;
									userDataEntered = true;
									//draw_signup_screen(window, event);
									break;
								}
							}
							window.clear();
							window.draw(LogINScreenP);
							window.draw(emailText);
							window.draw(passText);
							window.display();
						}
					}
				}
				else if (targetFieldPass.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inPassField == true) {
					std::cout << "Click at 'Password' field" << std::endl;
					
					inPassField = true;
					while (inPassField) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								ExecutePy_FinalizeEx();
								window.close();
								return;
							}
							passText.setString(passStars + "|");
							if (event.type == sf::Event::TextEntered)
							{
								
								if (event.text.unicode == 8 && !passInput.empty()) { // Handle backspace
									passInput.pop_back();
									passStars.pop_back();
								}
								else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
									passInput += static_cast<char>(event.text.unicode);
									passStars += "*";
								}
								passText.setString(passStars + "|");
								std::cout << passInput << std::endl;
								User.password = passInput;

							}
							if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
								std::cout << "Key pressed 'Enter'" << std::endl;
								sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
								passText.setString(passStars);
								if (targetFieldEmail.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									inPassField = false;
									inEmailField = false;
									break;
								}
								else if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'Next' button" << std::endl;
									inPassField = false;
									inEmailField = false;
									if (check_user(emailInput, passInput, "plantly.db")) {
										std::cout << "Record is true!" << std::endl;
										check_user_in(emailInput, passInput, "plantly.db");
										userDataEntered = true;
										appState = AppState::LOGGED_IN;
									}
									else {
										emailText.setFillColor(sf::Color::Red);
										passText.setFillColor(sf::Color::Red);
										userDataEntered = false;
										break;
									}
									break;
								}
								else if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
									std::cout << "Click at 'SignUp' button" << std::endl;
									inPassField = false;
									inEmailField = false;
									userDataEntered = true;
									//draw_signup_screen(window, event);
									break;

								}
							}
							window.clear();
							window.draw(LogINScreenP);
							window.draw(emailText);
							window.draw(passText);
							window.display();
						}
					}
				}
			}
			if (userDataEntered == true)
				break;
		}
		//window.draw(emailText);
		//window.draw(passText);
		
	}
	draw_clear_screen(window);
	
	//window.clear();
	//appState = AppState::LOGGED_IN;
	//window.draw(emailText);
	window.display();

}

//Check user for login
bool check_user(std::string email, std::string password, const std::string& dbFile) {
	if (email.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.-@") != std::string::npos) {
		std::cerr << "Error, email must contain only eligible characters\n";
		showErrorDialog("Email address typo", "Error, email must contain only\neligible characters");
		return false;
	}else if (email.find_first_of("@") == std::string::npos) {
		std::cerr << "Error, not an email\n";
		showErrorDialog("Email address typo", "Error, not an email");
		return false;
	}
	else if (password == "") {
		showErrorDialog("Passsword typo", "Error, password field is empty");
		return false;
	}

	sqlite3* db;
	sqlite3_stmt* stmt;
	bool exists = false;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		return false;
	}
	// Construct the SQL query
	std::string query = "SELECT 1 FROM Users WHERE Email = ? AND Password = ? LIMIT 1;";

	// Prepare the query
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}

	// Bind values to the query
	sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

	
	
	// Execute the query
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		exists = true;  // A record was found
	}

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return exists;
}

//Check user for signup
bool check_user(std::string name, std::string email, std::string password1, std::string password2, const std::string& dbFile) {
	if (email.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.-@") != std::string::npos) {
		std::cerr << "Error, email must contain only eligible characters\n";
		showErrorDialog("Email address typo", "Error, email must contain only\neligible characters");
		return false;
	}
	else if (email.find_first_of("@") == std::string::npos) {
		std::cerr << "Error, not an email\n";
		showErrorDialog("Email address typo", "Error, not an email");
		return false;
	}
	else if (password1 == "" || password2 == "") {
		showErrorDialog("Passsword typo", "Error, password field is empty");
		return false;
	}
	else if (password1 != password2) {
		showErrorDialog("Passsword typo", "Error, password doesn't match");
		return false;
	}

	User.saveToDatabase("plantly.db");
	showErrorDialog("SignUp", name + " successfully registered!");
	return true;
}//

void check_user_in(std::string email, std::string password, const std::string& dbFile) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	bool exists = false;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
	}
	// Construct the SQL query
	std::string query = "SELECT ID, Name, Email, Password, PStatus, Image FROM Users WHERE Email = ? AND Password = ? LIMIT 1;";

	// Prepare the query
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		sqlite3_close(db);
	}

	// Bind values to the query
	sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);



	// Execute the query
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		User.id = sqlite3_column_int(stmt, 0);
		User.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		User.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		User.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		User.pstatus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		const void* blobData = sqlite3_column_blob(stmt, 5);
		int blobSize = sqlite3_column_bytes(stmt, 5);
		if (blobData && blobSize > 0) {
			User.image.assign(reinterpret_cast<const uint8_t*>(blobData),
				reinterpret_cast<const uint8_t*>(blobData) + blobSize);
		}
		else {
			User.image.clear();
		}
	}

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	appState = AppState::LOGGED_IN;
}