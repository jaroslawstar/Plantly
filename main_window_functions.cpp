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
#include <shobjidl.h> // For IFileOpenDialog
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "Header.h"
#include "SQLite/sqlite3.h"
#include <fstream>
#include <array>
#include "sqlitecloud/sqcloud.h"
#include "sqlitecloud/lz4.h"




void draw_main_screen(sf::RenderWindow& window) {
	/* // Tworzenie prostok?ta
	sf::RectangleShape rectangle_main(sf::Vector2f(1160.0f, 780.0f)); // Rozmiar prostokata na cale okno
	rectangle_main.setFillColor(sf::Color(0xF7F7F7FF));
	rectangle_main.setPosition(120, 0);
	window.draw(rectangle_main);
	sf::RectangleShape rectangle_white(sf::Vector2f(1160.0f, 70.0f));
	rectangle_white.setFillColor(sf::Color::White);
	rectangle_white.setPosition(120, 0);
	window.draw(rectangle_white);

	//return Click_Value;
	*/
	sf::Texture MainScreen;
 	if (!MainScreen.loadFromFile("Resources/images/Plantly_Main_Screen.png")) {
		std::cout << "Failed to load profile picture!" << std::endl;
		return;
	}
	sf::Sprite MainScreenP;
	MainScreenP.setTexture(MainScreen);
	MainScreenP.setPosition(0, 0);
	window.draw(MainScreenP);
	window.display();
}
/*
void draw_buttons(sf::RenderWindow& window) {

	//int Click_Value = 0;

	//sf::RectangleShape rectangle_green(sf::Vector2f(120.0f, 780.0f));
	//rectangle_green.setFillColor(sf::Color(0xC4F7B7FF)); // Kolor prostokata (Cornflower Blue)

	sf::Texture Home;
	sf::Texture Menu;
	sf::Texture AP;
	sf::Texture Feed;
	sf::Texture QM;
	if (!Home.loadFromFile("Resources/images/Home.png") || !Menu.loadFromFile("Resources/images/Menu.png") || !AP.loadFromFile("Resources/images/AP.png") || !Feed.loadFromFile("Resources/images/Feed.png") || !QM.loadFromFile("Resources/images/QM.png")) {
		std::cout << "Failed to load image!" << endl;
	}

	sf::Sprite HomeButton;
	HomeButton.setTexture(Home);
	HomeButton.setPosition(40.0f, 40.0f);
	HomeButton.setScale(0.1f, 0.1f);

	sf::Sprite MenuButton;
	MenuButton.setTexture(Menu);
	MenuButton.setPosition(45.0f, 115.0f);
	MenuButton.setScale(0.08f, 0.08f);

	sf::Sprite APButton;
	APButton.setTexture(AP);
	APButton.setScale(0.12f, 0.12f);
	APButton.setPosition(35.0f, 200.0f);
	APButton.setRotation(0);

	sf::Sprite FeedButton;
	FeedButton.setTexture(Feed);
	FeedButton.setPosition(45.0f, 300.0f);
	FeedButton.setScale(0.08f, 0.08f);

	sf::Sprite QMButton;
	QMButton.setTexture(QM);
	QMButton.setPosition(50.0f, 400.0f);
	QMButton.setScale(0.05f, 0.05f);

	//window.draw(rectangle_green);
	window.draw(HomeButton);
	window.draw(MenuButton);
	window.draw(APButton);
	window.draw(FeedButton);
	window.draw(QMButton);
	//window.display();
}
*/

void draw_AP_Screen(sf::RenderWindow& window) {
	sf::Texture XT;
	if (!XT.loadFromFile("Resources/images/AP_Screen.png"))
		std::cout << "Failed to load image!" << std::endl;

	sf::Sprite X;
	X.setTexture(XT);
	X.setPosition(0, 0);
	//X.setRotation(45);
	window.draw(X);
	//window.display();
}

/*
void draw_logo(sf::RenderWindow& window) {
	// Ustawienia tekstu
	sf::Font logo_font;
	if (!logo_font.loadFromFile("Resources/Fonts/League_Script/LeagueScript-Regular.ttf")) {
		std::cout << "Failed to load font";
	}
	sf::Text logo;
	logo.setFont(logo_font);
	logo.setString("PLANTLY");
	logo.setCharacterSize(50);
	logo.setFillColor(sf::Color::Black);
	logo.setPosition(640, 0); // Pozycja tekstu
	window.draw(logo);
	//window.display();
}
*/



void draw_plants(sf::RenderWindow& window, sf::Event event, bool show, const std::string& dbFile) {
	usersPlants->fetch_plants_from_db("plantly.db");
	sf::Texture AddFirstPlant;
	sf::Texture WaterToday;
	sf::Texture PlantFrame;
	sf::Texture PlantInfoBlock;
	sf::Texture PlantImageMask;

	sf::Sprite AFPS;
	sf::Sprite WaterTodayS;
	  
	sf::RectangleShape TargetObject(sf::Vector2f(170, 250));
	TargetObject.setFillColor(sf::Color(0, 0, 0, 50));
	std::vector<sf::RectangleShape> TargetsObjects;

	sf::Sprite PlantFrames;
	std::vector<sf::Sprite> PlantFrameS;
	sf::Sprite PlantInfoBlocks;
	std::vector<sf::Sprite> PlantInfoBlockS;


	for (size_t i = 0; i < plants_number(); i++){
		TargetsObjects.push_back(TargetObject);
	}
	for (size_t i = 0; i < plants_number(); i++) {
		PlantFrameS.push_back(PlantFrames);
	}
	for (size_t i = 0; i < plants_number(); i++) {
		PlantInfoBlockS.push_back(PlantInfoBlocks);
	}

	sf::RectangleShape targetMainBs(sf::Vector2f(51, 360));
	targetMainBs.setPosition(40, 40);
	targetMainBs.setFillColor(sf::Color(0, 0, 0, 50));

	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf"))
		std::cout << "Failed to load font";

	if (!show){
		AFPS.setPosition(2000, 2000);
		WaterTodayS.setPosition(2000, 2000);
		for (size_t i = 0; i <= PlantInfoBlockS.size(); i++)
			PlantInfoBlockS[i].setPosition(2000, 2000);
		
		for (size_t i = 0; i <= PlantFrameS.size(); i++)
			PlantFrameS[i].setPosition(2000, 2000);


	}
	else if (show) {
		if (plants_number() == 0) {
			if (!AddFirstPlant.loadFromFile("Resources/images/PlantsList/AddFirstPlant.png")) {
				std::cout << "Failed to load plant block background!" << std::endl;
				return;
			}
			AFPS.setTexture(AddFirstPlant);
			AFPS.setPosition(223, 126);
			window.draw(AFPS);
			window.display();
			bool inHomeScreen = true;

			while (inHomeScreen) {
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						window.close();
					//Close button service
					if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
						//----------Logged_OUT_Buttons----------
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						std::cout << "Mouse clicked at: ("
							<< mousePosition.x << ", "
							<< mousePosition.y << ")" << std::endl;
						if (targetMainBs.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
							std::cout << "Click at 'X' button" << std::endl;
							inHomeScreen = false;
						}
					}

					if (inHomeScreen == false)
						break;
				}



			}
			window.display();
		}
		else {
			if (!WaterToday.loadFromFile("Resources/images/PlantsList/WaterToday.png")) {
				std::cout << "Failed to load plant block background!" << std::endl;
				return;
			}
			WaterTodayS.setTexture(WaterToday);
			WaterTodayS.setPosition(1111, 140);
			window.draw(WaterTodayS);
			//window.display();

			if (!PlantFrame.loadFromFile("Resources/images/PlantsList/PlantFrame.png")) {
				std::cout << "Failed to load plant block background!" << std::endl;
				return;
			}

			if (!PlantInfoBlock.loadFromFile("Resources/images/PlantsList/PlantInfoBlock.png")) {
				std::cout << "Failed to load plant block background!" << std::endl;
				return;
			}

			if (!PlantImageMask.loadFromFile("Resources/images/PlantsList/ImageMask.png")) {
				std::cout << "Failed to load plant block background!" << std::endl;
				return;
			}
			//
			//PlantFrameS[0].setTexture(PlantFrame);

			//
			//PlantInfoBlockS[0].setTexture(PlantInfoBlock);


			// Building Targets:
			if (plants_number() <= 5) {
				for (size_t i = 0; i < plants_number(); i++) {
					TargetsObjects[i].setPosition(145 + (i * 195), 140);
					TargetsObjects[i].setFillColor(sf::Color(0, 0, 0, 50));
					window.draw(TargetsObjects[i]);
				}
				std::cout << "Targets built\n" << std::endl;
			}
			else if (plants_number() > 5) {
				int showeditems = 0;
				for (size_t j = 0; j < 2; j++) {
					for (size_t i = 0; i < 5; i++) {
						std::cout << "I value: " << i << std::endl;
						int ti = i + (j * 5);
						std::cout << "Ti value: " << ti << std::endl;
						TargetsObjects[ti].setPosition(145 + (i * 195), 140 + (j * 320));
						TargetsObjects[ti].setFillColor(sf::Color(0, 0, 0, 50));
						window.draw(TargetsObjects[ti]);
						showeditems++;
						if (showeditems == plants_number()) {
							i = 5;
						}
					}
				}
			}
			//
			window.display();

			// Building Objects:
			if (plants_number() <= 5) {
				for (size_t i = 0; i < plants_number(); i++) {
					usersPlants[i].showObject(window, PlantFrame, PlantImageMask, PlantFrameS[i], 145 + (i * 195), 140, font);
					window.draw(PlantFrameS[i]);
				}
			}
			else if (plants_number() > 5) {
				int showeditems = 0;
				for (size_t j = 0; j < 2; j++) {
					for (size_t i = 0; i < 5; i++) {
						std::cout << "I value: " << i << std::endl;
						int ti = i + (j * 5);
						std::cout << "Ti value: " << ti << std::endl;
						TargetsObjects[ti].setPosition(145 + (i * 195), 140 + (j * 320));
						TargetsObjects[ti].setFillColor(sf::Color(0, 0, 0, 50));
						window.draw(TargetsObjects[ti]);
						showeditems++;
						if (showeditems == plants_number()) {
							i = 5;
						}
					}
				}
			}

			window.display();
			

			bool inHomeScreen = true;

			while (inHomeScreen) {
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						window.close();
					//Close button service
					if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
						//----------Logged_OUT_Buttons----------
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						std::cout << "Mouse clicked at: ("
							<< mousePosition.x << ", "
							<< mousePosition.y << ")" << std::endl;
						if (targetMainBs.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
							std::cout << "Click at 'X' button" << std::endl;
							inHomeScreen = false;
						}
						/*
						else if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inNameField == true) {
							std::cout << "Click at 'Plant name' field" << std::endl;
							inNameField = true;
							while (inNameField) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed)
										window.close();
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
										entry.name = nameInput;
										//window.draw(emailText);
									}
									if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
										std::cout << "Key pressed 'Enter'" << std::endl;
										sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
										nameText.setString(nameInput);
										if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = true;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = true;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = true;
											inImageField = false;
											break;
										}
										else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = true;
											break;
										}
										else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'X' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											added_plant = true;
											break;
										}
										else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'Save' button" << std::endl;
											std::cout << "entry.name: " << entry.name << std::endl;
											std::cout << "entry.days: " << entry.days << std::endl;
											std::cout << "entry.loca: " << entry.location << std::endl;
											std::cout << "entry.type: " << entry.type << std::endl;


											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											if ((entry.name != "") || (entry.days != NULL) || (entry.type != "") || (entry.location != "")) {
												entry.saveToDatabase("plantly.db");
												added_plant = true;
												break;
											}
											else {
												showErrorDialog("Error adding Plant", "All fields must be filled out");
												break;
											}
										}
									}
									window.clear();
									window.clear(sf::Color::White);
									/*
									window.draw(nameUI);
									window.draw(daysUI);
									window.draw(typeUI);
									window.draw(locaUI);
									window.draw(imageUI);
									window.draw(saveUI);
									* /
									window.draw(plantP);
									draw_AP_Screen(window);

									window.draw(nameText);
									window.draw(daysText);
									window.draw(typeText);
									window.draw(locaText);
									/*
									window.draw(targetFieldName);
									window.draw(targetFieldDays);
									window.draw(targetFieldType);
									window.draw(targetFieldLoca);
									window.draw(targetFieldImage);
									window.draw(targetSave);
									window.draw(targetXB);
									* /

									window.display();
								}
							}
						}
						else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inDaysField == true) {
							std::cout << "Click at 'Watering days' field" << std::endl;
							inDaysField = true;
							while (inDaysField) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed)
										window.close();
									daysText.setString(daysInput + "|");
									if (event.type == sf::Event::TextEntered)
									{
										if (event.text.unicode == 8 && !daysInput.empty()) { // Handle backspace
											daysInput.pop_back();
										}
										else if (event.text.unicode >= 48 && event.text.unicode < 57) { // Handle printable characters
											daysInput += static_cast<char>(event.text.unicode);
										}
										else {
											std::cerr << "Error, this field receives only digits\n";
											showErrorDialog("Days typo", "Error, this field receives only digits");
											daysInput = "";
										}
										daysText.setString(daysInput + "|");
										std::cout << daysInput << std::endl;
										entry.days = stoi(daysInput);
										//window.draw(emailText);
									}
									if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
										std::cout << "Key pressed 'Enter'" << std::endl;
										sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
										daysText.setString(daysInput);
										if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = true;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = true;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = true;
											inImageField = false;
											break;
										}
										else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = true;
											break;
										}
										else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'X' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											added_plant = true;
											break;
										}
										else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'Save' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
												entry.saveToDatabase("plantly.db");
												added_plant = true;
												break;
											}
											else {
												showErrorDialog("Error adding Plant", "All fields must be filled out");
												break;
											}
										}

									}
									window.clear();
									window.clear(sf::Color::White);
									/*
									window.draw(nameUI);
									window.draw(daysUI);
									window.draw(typeUI);
									window.draw(locaUI);
									window.draw(imageUI);
									window.draw(saveUI);
									* /
									window.draw(plantP);
									draw_AP_Screen(window);

									window.draw(nameText);
									window.draw(daysText);
									window.draw(typeText);
									window.draw(locaText);

									/*
									window.draw(targetFieldName);
									window.draw(targetFieldDays);
									window.draw(targetFieldType);
									window.draw(targetFieldLoca);
									window.draw(targetFieldImage);
									window.draw(targetSave);
									window.draw(targetXB);
									* /
									window.display();
								}
							}
						}
						else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inTypeField == true) {
							std::cout << "Click at 'Plant type' field" << std::endl;
							inTypeField = true;
							while (inTypeField) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed)
										window.close();
									typeText.setString(typeInput + "|");
									if (event.type == sf::Event::TextEntered)
									{
										if (event.text.unicode == 8 && !typeInput.empty()) { // Handle backspace
											typeText.setFillColor(sf::Color::Black);
											typeInput.pop_back();
										}
										else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
											typeInput += static_cast<char>(event.text.unicode);
										}
										typeText.setString(typeInput + "|");
										std::cout << typeInput << std::endl;
										entry.type = typeInput;

									}
									if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
										std::cout << "Key pressed 'Enter'" << std::endl;
										sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
										typeText.setString(typeInput);
										if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = true;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = true;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = true;
											inImageField = false;
											break;
										}
										else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = true;
											break;
										}
										else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'X' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											added_plant = true;
											break;
										}
										else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'Save' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
												entry.saveToDatabase("plantly.db");
												added_plant = true;
												break;
											}
											else {
												showErrorDialog("Error adding Plant", "All fields must be filled out");
												break;
											}
										}

									}
									window.clear();
									window.clear(sf::Color::White);
									window.draw(plantP);
									draw_AP_Screen(window);
									/*
									window.draw(nameUI);
									window.draw(daysUI);
									window.draw(typeUI);
									window.draw(locaUI);
									window.draw(imageUI);
									window.draw(saveUI);
									* /

									window.draw(nameText);
									window.draw(daysText);
									window.draw(typeText);
									window.draw(locaText);

									/*
									window.draw(targetFieldName);
									window.draw(targetFieldDays);
									window.draw(targetFieldType);
									window.draw(targetFieldLoca);
									window.draw(targetFieldImage);
									window.draw(targetSave);
									window.draw(targetXB);
									* /
									window.display();
								}
							}
						}
						else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inLocaField == true) {
							std::cout << "Click at 'Location' field" << std::endl;
							inLocaField = true;
							while (inLocaField) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed)
										window.close();
									locaText.setString(locaInput + "|");
									if (event.type == sf::Event::TextEntered)
									{
										if (event.text.unicode == 8 && !locaInput.empty()) { // Handle backspace
											locaText.setFillColor(sf::Color::Black);
											locaInput.pop_back();
										}
										else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
											locaInput += static_cast<char>(event.text.unicode);
										}
										locaText.setString(locaInput + "|");
										std::cout << locaInput << std::endl;
										entry.location = locaInput;

									}
									if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
										std::cout << "Key pressed 'Enter'" << std::endl;
										sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
										locaText.setString(locaInput);
										if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = true;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = true;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = true;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = true;
											break;
										}
										else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'X' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											added_plant = true;
											break;
										}
										else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'Save' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
												entry.saveToDatabase("plantly.db");
												added_plant = true;
												break;
											}
											else {
												showErrorDialog("Error adding Plant", "All fields must be filled out");
												break;
											}
										}

									}
									window.clear();
									window.clear(sf::Color::White);
									window.draw(plantP);
									draw_AP_Screen(window);
									/*
									window.draw(nameUI);
									window.draw(daysUI);
									window.draw(typeUI);
									window.draw(locaUI);
									window.draw(imageUI);
									window.draw(saveUI);
									* /

									window.draw(nameText);
									window.draw(daysText);
									window.draw(typeText);
									window.draw(locaText);

									/*
									window.draw(targetFieldName);
									window.draw(targetFieldDays);
									window.draw(targetFieldType);
									window.draw(targetFieldLoca);
									window.draw(targetFieldImage);
									window.draw(targetSave);
									window.draw(targetXB);
									* /
									window.display();
								}
							}
						}
						else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inImageField == true) {
							std::cout << "Click at 'Choose image' field" << std::endl;

							//entry.set_image("Plantly.db"); //Save image to DataBase
							entry.image = GetFileBlobDialog();

							window.clear(sf::Color::White);
							plantT.loadFromMemory(entry.image.data(), entry.image.size());
							plantP.setTexture(plantT, true);
							CenterBlobImage(window, entry.image, plantT, plantP);

							window.draw(plantP);
							draw_AP_Screen(window);

							window.draw(nameText);
							window.draw(daysText);
							window.draw(typeText);
							window.draw(locaText);
							/*
							window.draw(targetFieldName);
							window.draw(targetFieldDays);
							window.draw(targetFieldType);
							window.draw(targetFieldLoca);
							window.draw(targetFieldImage);
							window.draw(targetSave);
							window.draw(targetXB);
							* /

							window.display();


							inImageField = false;

							/*
							while (inImageField) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed)
										window.close();
									auto blob = GetFileBlobDialog();


									sf::Texture PFP;
									if (!PFP.loadFromMemory(blob.data(), blob.size())) {
										std::cout << "Failed to load profile picture from binary data!" << std::endl;
										PFP.loadFromFile("Resources/images/pfp.png");
									}

									if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
										std::cout << "Key pressed 'Enter'" << std::endl;
										sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
										if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = true;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = true;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = true;
											inLocaField = false;
											inImageField = false;
											break;
										}
										else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = true;
											inImageField = false;
											break;
										}
										else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
											std::cout << "Click at 'Next' button" << std::endl;
											inNameField = false;
											inDaysField = false;
											inTypeField = false;
											inLocaField = false;
											inImageField = false;
											///*
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
											// * /
											added_plant = true;
											break;
										}
									}
									window.clear();
									window.clear(sf::Color::White);
									draw_AP_Screen(window);
									window.draw(nameUI);
									window.draw(daysUI);
									window.draw(typeUI);
									window.draw(locaUI);
									window.draw(imageUI);
									window.draw(saveUI);

									window.draw(nameText);
									window.draw(daysText);
									window.draw(typeText);
									window.draw(locaText);

									window.draw(targetFieldName);
									window.draw(targetFieldDays);
									window.draw(targetFieldType);
									window.draw(targetFieldLoca);
									window.draw(targetFieldImage);
									window.draw(targetSave);
									window.display();

								}* /
								//}
						}
						else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
							//usersPlants[plants_number()] = entry;
							std::cout << "Click at 'Save' button" << std::endl;
							inNameField = false;
							inDaysField = false;
							inTypeField = false;
							inLocaField = false;
							inImageField = false;
							if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
								entry.saveToDatabase("plantly.db");
								added_plant = true;
								break;
							}
							else {
								showErrorDialog("Error adding Plant", "All fields must be filled out");
								break;
							}
						}*/
					}

					if (inHomeScreen == false)
						break;
				}



			}
			window.display();
		}
	}
	

	std::cout << "Plants owner: " << User.name << std::endl;
	std::cout << "----------------------------------" << std::endl;

	// Wykonywanie zapytania i wyświetlanie wyników
	//sf::Font Font;
	//if (!Font.loadFromFile("Resources/Fonts/Instrument_Sans/static/InstrumentSans-SemiBold"))
	//	std::cout << "Failed to load font\n";

	for (size_t i = 0; i < plants_number(); i++) {

		int id = usersPlants[i].id;
		int userid = usersPlants[i].userid;
		int days = usersPlants[i].days;
		std::string name = usersPlants[i].name;
		std::string location = usersPlants[i].location;
		std::string type = usersPlants[i].type;
		std::vector<uint8_t> image = usersPlants[i].image;



		std::cout << "Plant ID: " << id << std::endl;
		std::cout << "Owner's ID: " << userid << std::endl;

		std::cout << "Plant name: " << name << std::endl;
		std::cout << "Watering frequency days: " << days << std::endl;
		std::cout << "Type: " << type << std::endl;
		std::cout << "Location: " << location << std::endl;

		std::cout << "Image: " << image.size() << std::endl;
		std::cout << "----------------------------------" << std::endl;


		
	}

	

		/*
		sf::Texture PlantPictureT;
		if (!PlantPictureT.loadFromFile(location)) {
			std::cout << "Failed to load plant block background!" << std::endl;
			return;
		}
		sf::Sprite PlantPicture;
		PlantPicture.setTexture(PlantPictureT);
		PlantPicture.setPosition((210 + i * 100), 160);
		plantSprites[i].setTexture(PlantBlock);
		plantSprites[i].setPosition((200 + i * 100), 160);
		plantName[i].setFont(Font);
		plantName[i].setCharacterSize(30);
		plantName[i].setString(names);
		plantName[i].setFillColor(sf::Color::Black);
		plantName[i].setPosition((210 + i * 100), 518);

		//("PlantBackground", Font, 20);


		*/


	// Zwolnienie zasobów
	//sqlite3_finalize(stmt);
	//sqlite3_close(db);

	
	/*
	
	if (show == true) {
		window.draw(PlantBlockP);
		draw_AP_screen(window, event, true);
		window.display();
	}
	else if (show == false) {
		PlantBlockP.setPosition(2000, 2000);
	}






	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		std::cout << "Mouse clicked at: ("
			<< mousePosition.x << ", "
			<< mousePosition.y << ")" << std::endl;
		// Check if click is in targetL
		if (PlantBlockP.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
			std::cout << "Click at 'Add Plant Block' button" << std::endl;
			ButtonClick::AP;
		}
	}*/
	//window.display();
}
/*
void buttonsEngine(sf::RenderWindow& window, sf::RectangleShape targetHB, sf::RectangleShape targetMB, sf::RectangleShape targetAPB, sf::RectangleShape targetFB, sf::RectangleShape targetQMB) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	std::cout << "Mouse clicked at: ("
		<< mousePosition.x << ", "
		<< mousePosition.y << ")" << std::endl;
	// Check if click is in targetL
	if (targetHB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
		std::cout << "Click at 'Home' button" << std::endl;
		APRotation = false;
		
		if (buttonClick == ButtonClick::Home) {
			buttonClick = ButtonClick::undefined;
		}
		else {
			buttonClick = ButtonClick::Home;
		}
		
		//return ButtonClick::Home;
	}
	else if (targetMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
		std::cout << "Click at 'Menu' button" << std::endl;
		APRotation = false;
		
		if (buttonClick == ButtonClick::Menu) {
			buttonClick = ButtonClick::undefined;
		}
		else {
			buttonClick = ButtonClick::Menu;
		}
		
		//return ButtonClick::Menu;
	}
	else if (targetAPB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
		std::cout << "Click at 'Add Plant' button" << std::endl;
		
		if (buttonClick == ButtonClick::AP) {
			APRotation = false;
			buttonClick = ButtonClick::undefined;
		}
		else {
			APRotation = true;
			buttonClick = ButtonClick::AP;
		}
		
		//return ButtonClick::AP;
	}
	else if (targetFB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
		std::cout << "Click at 'Feed' button" << std::endl;
		APRotation = false;
		
		if (buttonClick == ButtonClick::Feed) {
			buttonClick = ButtonClick::undefined;
		}
		else {
			buttonClick = ButtonClick::Feed;
		}
		
		//return ButtonClick::Feed;
	}
	else if (targetQMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
		std::cout << "Click at 'Question Mark' button" << std::endl;
		APRotation = false;
		
		if (buttonClick == ButtonClick::QM) {
			buttonClick = ButtonClick::undefined;
		}
		else {
			buttonClick = ButtonClick::QM;
		}
		
		//return ButtonClick::QM;
	}
}
*/

void draw_menu(sf::RenderWindow& window, sf::Event event, bool show) {
	sf::RectangleShape rectangle_white(sf::Vector2f(250.0f, 780.0f));
	rectangle_white.setFillColor(sf::Color(0xFFFFFFFF));
	rectangle_white.setPosition(120, 70);

	sf::RectangleShape rectangle_shadow(sf::Vector2f(250.0f, 780.0f));
	rectangle_shadow.setFillColor(sf::Color(0, 0, 0, 50));
	rectangle_shadow.setPosition(125, 75);
	
	// Ustawienia tekstu
	sf::Font text_font;
	if (!text_font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf")) {
		std::cout << "Failed to load font";
	}

	sf::Texture PFP;
	if (!PFP.loadFromMemory(User.image.data(), User.image.size())) {
		std::cout << "Failed to load profile picture from binary data!" << std::endl;
		PFP.loadFromFile("Resources/images/pfp.png");
	}
	//if (!PFP.loadFromMemory(User.image.data(), User.image.size()) || !PFP.loadFromFile("Resources/images/pfp.png")) {
	//	std::cout << "Failed to load profile picture!" << std::endl;
	//}

	sf::Text name(User.name +"\n" + generate_username(User.email), text_font, 20);
	sf::Text Preferences("Preferences", text_font, 20);
	sf::Text AS("Account settings", text_font, 20);
	sf::Text RP("Restore purchases", text_font, 20);
	sf::Text LogoutB("Logout", text_font, 20);
	std::cout << "Texture size x: " << PFP.getSize().x << std::endl;
	std::cout << "Texture size x: " << PFP.getSize().y << std::endl;
	sf::Sprite PFPp;
	PFPp.setTexture(PFP);

	// Desired width and height for the sprite
	float desiredWidth = 48.0f; // in pixels
	float desiredHeight = 48.0f; // in pixels

	// Get the original size of the texture
	sf::Vector2u originalSize = PFP.getSize();
	float originalWidth = static_cast<float>(originalSize.x);
	float originalHeight = static_cast<float>(originalSize.y);

	// Calculate scale factors
	float scaleX = desiredWidth / originalWidth;
	float scaleY = desiredHeight / originalHeight;
	PFPp.setScale(scaleX, scaleY);
	//PFPp.setScale(0.15f, 0.15f);



	
	
	if (!show) {
		rectangle_white.setPosition(2000, 2000);
		rectangle_shadow.setPosition(2000, 2000);
		name.setPosition(2000, 2000); // Pozycja tekstu
		Preferences.setPosition(2000, 2000);
		AS.setPosition(2000, 2000);
		RP.setPosition(2000, 2000);
		PFPp.setPosition(2000, 2000);
	}
	else if (show) {
		name.setPosition(140, 100); // Pozycja tekstu
		Preferences.setPosition(140, 160);
		AS.setPosition(140, 190);
		RP.setPosition(140, 220);
		LogoutB.setPosition(140, 250);
		PFPp.setPosition(300, 100);

		name.setFillColor(sf::Color::Black);
		Preferences.setFillColor(sf::Color::Black);
		AS.setFillColor(sf::Color::Black);
		RP.setFillColor(sf::Color::Black);
		LogoutB.setFillColor(sf::Color::Black);

		sf::RectangleShape targetPFP(sf::Vector2f(43, 43));
		targetPFP.setPosition(300, 100);

		sf::RectangleShape targetASB(sf::Vector2f(150, 20));
		targetASB.setPosition(140, 190);

		sf::RectangleShape targetLogoutB(sf::Vector2f(49, 20));
		targetLogoutB.setPosition(140, 250);

		sf::RectangleShape targetMainBs(sf::Vector2f(51, 360));
		targetMainBs.setPosition(40, 40);

		
		//targetASB.setFillColor(sf::Color(0, 0, 0, 50));

		bool MainBs = false;


		window.draw(rectangle_shadow);
		window.draw(rectangle_white);
		window.draw(name);
		//window.draw(targetPFP);
		//window.draw(targetASB);
		window.draw(PFPp);
		window.draw(Preferences);
		window.draw(AS);
		window.draw(RP);
		window.draw(LogoutB);
		window.display();

		while (!MainBs) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				//Close button service
				if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
					//----------Logged_OUT_Buttons----------
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					std::cout << "Mouse clicked at: ("
						<< mousePosition.x << ", "
						<< mousePosition.y << ")" << std::endl;
					if (targetMainBs.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						std::cout << "Click at 'X' button" << std::endl;
						MainBs = true;
					}
					if (targetPFP.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						std::cout << "Click at 'Profile Picture' button" << std::endl;
						//if () {
						//
						//}
						User.image = GetFileBlobDialog();
						User.set_image("Plantly.db");
						PFP.loadFromMemory(User.image.data(), User.image.size());
						PFPp.setTexture(PFP);
						window.draw(rectangle_shadow);
						window.draw(rectangle_white);
						window.draw(name);
						//window.draw(targetPFP);
						window.draw(PFPp);
						window.draw(Preferences);
						window.draw(AS);
						window.draw(RP);
						window.draw(LogoutB);
						window.display();
					}
					if (targetASB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						//std::string result(User.image.begin(), User.image.end());
						std::cout << "Logged in User info from DataBase:\nID: " << User.id <<
							"\nName: " << User.name << "\nEmail: " << User.email << "\nPassword: " 
							<< User.password << "\nStatus:" << User.pstatus << std::endl;
							//<< User.password << "\nStatus:" << User.pstatus << "\nImage:" << result << std::endl;
					}
					if (targetLogoutB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						std::cout << "Click at 'Logout' button" << std::endl;
						appState = AppState::LOGGED_OUT;
						MainBs = true;
					}	
				}
			}
		}
		window.display();
		//draw_menu(window, event, true);
	}
	
}

void draw_text(sf::RenderWindow& window, bool show) { //, bool show
	// Ustawienia tekstu
	sf::Font text_font;
	if (!text_font.loadFromFile("Resources/Fonts/Instrument_Sans/static/InstrumentSans-SemiBold.ttf")) {
		std::cout << "Failed to load font";
	}
	sf::Text text;
	text.setFont(text_font);
	text.setString("The app Plantly is developed by\nJarosław Szekuła for the subject of Projekt C++ on Uniwersytet Wrocławski.\nThis is NOT the final look or the final platform.\nThis look was only created to present the idea and show what it is about.\n\nThe app is going to be developed for Windowsand MacOS, using programming language C++,\nwith small design changes (to make it usable on horizontal screens).\n\nIt is NO estimated date for final developed version for smartphones, yet.");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(200, 160);
	if (show == true) {
		window.draw(text);	
	}
	else if (show == false) {
		text.setPosition(2000, 2000);
	}
	window.display();
}

void draw_AP_screen(sf::RenderWindow& window, sf::Event event, bool show) {

	//Call for function to get array used spaces aka plants number
	int PlantsNumber = plants_number();
	std::wcout << "Plants number after function calling:" << PlantsNumber << std::endl;
	if (PlantsNumber >= 10) {
		showErrorDialog("Error adding new plant", "You reached maximum size of available\nplants, please consider buying\nPlantlyCare+ to get more spaces");
		show = false;
	}


	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf"))
		std::cout << "Failed to load font\n";

	//Description text
	/*
	sf::Text nameUI("Name:", font, 20);
	sf::Text daysUI("Days:", font, 20);
	sf::Text typeUI("Type:", font, 20);
	sf::Text locaUI("Loca:", font, 20);
	sf::Text imageUI("Image:", font, 20);
	sf::Text saveUI("Save", font, 20);
	*/



	std::string nameInput = "";
	std::string daysInput = "";
	std::string typeInput = "";
	std::string locaInput = "";
	sf::Text nameText(nameInput, font, 15);
	sf::Text daysText(daysInput, font, 15);
	sf::Text typeText(typeInput, font, 15);
	sf::Text locaText(locaInput, font, 15);

	//window.draw(targetFieldPass);
	window.display();


	if (!show) {
		/*
		nameUI.setPosition(2000, 2000);
		daysUI.setPosition(2000, 2000);
		typeUI.setPosition(2000, 2000);
		locaUI.setPosition(2000, 2000);
		imageUI.setPosition(2000, 2000);
		saveUI.setPosition(2000, 2000);
		*/
		nameText.setPosition(2000, 2000);
		daysText.setPosition(2000, 2000);
		typeText.setPosition(2000, 2000);
		locaText.setPosition(2000, 2000);
	}
	else {
		window.clear(sf::Color::White);
		/*
		nameUI.setPosition(100, 100);
		daysUI.setPosition(150, 100);
		typeUI.setPosition(585, 467);
		locaUI.setPosition(585, 467);
		imageUI.setPosition(100, 200);
		saveUI.setPosition(585, 467);
		*/
		nameText.setPosition(500, 463);
		daysText.setPosition(500, 523);
		typeText.setPosition(500, 583);
		locaText.setPosition(500, 643);


		/*
		nameUI.setFillColor(sf::Color::Black);
		daysUI.setFillColor(sf::Color::Black);
		typeUI.setFillColor(sf::Color::Black);
		locaUI.setFillColor(sf::Color::Black);
		imageUI.setFillColor(sf::Color::Black);
		saveUI.setFillColor(sf::Color::Black);
		*/
		nameText.setFillColor(sf::Color::Black);
		daysText.setFillColor(sf::Color::Black);
		typeText.setFillColor(sf::Color::Black);
		locaText.setFillColor(sf::Color::Black);



		sf::RectangleShape targetXB(sf::Vector2f(60, 60));
		targetXB.setPosition(560, 700);

		//Buttons and fields 
		sf::RectangleShape targetFieldName(sf::Vector2f(300, 25));
		sf::RectangleShape targetFieldDays(sf::Vector2f(300, 25));
		sf::RectangleShape targetFieldType(sf::Vector2f(300, 25));
		sf::RectangleShape targetFieldLoca(sf::Vector2f(300, 25));
		sf::RectangleShape targetFieldImage(sf::Vector2f(1280, 435));
		sf::RectangleShape targetSave(sf::Vector2f(60, 60)); // posibility of getting rid cause sf::Text is enough to get global bounds
		targetFieldName.setPosition(490, 460);
		targetFieldDays.setPosition(490, 520);
		targetFieldType.setPosition(490, 580);
		targetFieldLoca.setPosition(490, 640);
		targetFieldImage.setPosition(0, 0);
		targetSave.setPosition(680, 700); //sameee

		targetFieldName.setFillColor(sf::Color(0, 0, 0, 50));
		targetFieldDays.setFillColor(sf::Color(0, 0, 0, 50));
		targetFieldType.setFillColor(sf::Color(0, 0, 0, 50));
		targetFieldLoca.setFillColor(sf::Color(0, 0, 0, 50));
		targetFieldImage.setFillColor(sf::Color(0, 0, 0, 50));
		targetSave.setFillColor(sf::Color(0, 0, 0, 50));
		targetXB.setFillColor(sf::Color(0, 0, 0, 50));

		//Text and targets
		/*
		window.draw(nameUI);
		window.draw(daysUI);
		window.draw(typeUI);
		window.draw(locaUI);
		window.draw(imageUI);
		window.draw(saveUI);
		*/

		Plant entry;
		bool added_plant = false;
		bool enteringFilePath = false;
		bool inNameField = false;
		bool inDaysField = false;
		bool inTypeField = false;
		bool inLocaField = false;
		bool inImageField = false;

		window.clear(sf::Color::White);

		sf::Texture plantT;
		if (!plantT.loadFromMemory(entry.image.data(), entry.image.size())) {
			std::cout << "Failed to load plant picture from binary data!" << std::endl;
			plantT.loadFromFile("Resources/images/Image_text.png");
		}

		std::cout << "Texture size x: " << plantT.getSize().x << std::endl;
		std::cout << "Texture size x: " << plantT.getSize().y << std::endl;
		sf::Sprite plantP;
		plantP.setTexture(plantT);
		plantP.setPosition(507, 200);
		//CenterBlobImage(window, entry.image, plantT, plantP);
		window.draw(plantP);
		



		draw_AP_Screen(window);

		window.draw(nameText);
		window.draw(daysText);
		window.draw(typeText);
		window.draw(locaText);
		/*
		window.draw(targetFieldName);
		window.draw(targetFieldDays);
		window.draw(targetFieldType);
		window.draw(targetFieldLoca);
		window.draw(targetFieldImage);
		window.draw(targetSave);
		window.draw(targetXB);
		*/


		window.display();





		while (!added_plant) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				//Close button service
				if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
					//----------Logged_OUT_Buttons----------
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					std::cout << "Mouse clicked at: ("
						<< mousePosition.x << ", "
						<< mousePosition.y << ")" << std::endl;
					if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						std::cout << "Click at 'X' button" << std::endl;
						added_plant = true;
					}
					else if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inNameField == true) {
						std::cout << "Click at 'Plant name' field" << std::endl;
						inNameField = true;
						while (inNameField) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed)
									window.close();
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
									entry.name = nameInput;
									//window.draw(emailText);
								}
								if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
									std::cout << "Key pressed 'Enter'" << std::endl;
									sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
									nameText.setString(nameInput);
									if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = true;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = true;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = true;
										inImageField = false;
										break;
									}
									else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = true;
										break;
									}
									else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'X' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										added_plant = true;
										break;
									}
									else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'Save' button" << std::endl;
										std::cout << "entry.name: " << entry.name << std::endl;
										std::cout << "entry.days: " << entry.days << std::endl;
										std::cout << "entry.loca: " << entry.location << std::endl;
										std::cout << "entry.type: " << entry.type << std::endl;


										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										if ((entry.name != "") || (entry.days != NULL) || (entry.type != "") || (entry.location != "")) {
											entry.saveToDatabase("plantly.db");
											added_plant = true;
											break;
										}
										else {
											showErrorDialog("Error adding Plant", "All fields must be filled out");
											break;
										}
									}
								}
								window.clear();
								window.clear(sf::Color::White);
								/*
								window.draw(nameUI);
								window.draw(daysUI);
								window.draw(typeUI);
								window.draw(locaUI);
								window.draw(imageUI);
								window.draw(saveUI);
								*/
								window.draw(plantP);
								draw_AP_Screen(window);

								window.draw(nameText);
								window.draw(daysText);
								window.draw(typeText);
								window.draw(locaText);
								/*
								window.draw(targetFieldName);
								window.draw(targetFieldDays);
								window.draw(targetFieldType);
								window.draw(targetFieldLoca);
								window.draw(targetFieldImage);
								window.draw(targetSave);
								window.draw(targetXB);
								*/

								window.display();
							}
						}
					}
					else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inDaysField == true) {
						std::cout << "Click at 'Watering days' field" << std::endl;
						inDaysField = true;
						while (inDaysField) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed)
									window.close();
								daysText.setString(daysInput + "|");
								if (event.type == sf::Event::TextEntered)
								{
									if (event.text.unicode == 8 && !daysInput.empty()) { // Handle backspace
										daysInput.pop_back();
									}
									else if (event.text.unicode >= 48 && event.text.unicode < 57) { // Handle printable characters
										daysInput += static_cast<char>(event.text.unicode);
									}
									else {
										std::cerr << "Error, this field receives only digits\n";
										showErrorDialog("Days typo", "Error, this field receives only digits");
										daysInput = "";
									}
									daysText.setString(daysInput + "|");
									std::cout << daysInput << std::endl;
									entry.days = stoi(daysInput);
									//window.draw(emailText);
								}
								if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
									std::cout << "Key pressed 'Enter'" << std::endl;
									sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
									daysText.setString(daysInput);
									if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = true;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = true;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = true;
										inImageField = false;
										break;
									}
									else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = true;
										break;
									}
									else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'X' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										added_plant = true;
										break;
									}
									else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'Save' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
											entry.saveToDatabase("plantly.db");
											added_plant = true;
											break;
										}
										else {
											showErrorDialog("Error adding Plant", "All fields must be filled out");
											break;
										}
									}

								}
								window.clear();
								window.clear(sf::Color::White);
								/*
								window.draw(nameUI);
								window.draw(daysUI);
								window.draw(typeUI);
								window.draw(locaUI);
								window.draw(imageUI);
								window.draw(saveUI);
								*/
								window.draw(plantP);
								draw_AP_Screen(window);

								window.draw(nameText);
								window.draw(daysText);
								window.draw(typeText);
								window.draw(locaText);

								/*
								window.draw(targetFieldName);
								window.draw(targetFieldDays);
								window.draw(targetFieldType);
								window.draw(targetFieldLoca);
								window.draw(targetFieldImage);
								window.draw(targetSave);
								window.draw(targetXB);
								*/
								window.display();
							}
						}
					}
					else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inTypeField == true) {
						std::cout << "Click at 'Plant type' field" << std::endl;
						inTypeField = true;
						while (inTypeField) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed)
									window.close();
								typeText.setString(typeInput + "|");
								if (event.type == sf::Event::TextEntered)
								{
									if (event.text.unicode == 8 && !typeInput.empty()) { // Handle backspace
										typeText.setFillColor(sf::Color::Black);
										typeInput.pop_back();
									}
									else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
										typeInput += static_cast<char>(event.text.unicode);
									}
									typeText.setString(typeInput + "|");
									std::cout << typeInput << std::endl;
									entry.type = typeInput;

								}
								if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
									std::cout << "Key pressed 'Enter'" << std::endl;
									sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
									typeText.setString(typeInput);
									if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = true;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = true;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = true;
										inImageField = false;
										break;
									}
									else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = true;
										break;
									}
									else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'X' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										added_plant = true;
										break;
									}
									else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'Save' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
											entry.saveToDatabase("plantly.db");
											added_plant = true;
											break;
										}
										else {
											showErrorDialog("Error adding Plant", "All fields must be filled out");
											break;
										}
									}

								}
								window.clear();
								window.clear(sf::Color::White);
								window.draw(plantP);
								draw_AP_Screen(window);
								/*
								window.draw(nameUI);
								window.draw(daysUI);
								window.draw(typeUI);
								window.draw(locaUI);
								window.draw(imageUI);
								window.draw(saveUI);
								*/

								window.draw(nameText);
								window.draw(daysText);
								window.draw(typeText);
								window.draw(locaText);

								/*
								window.draw(targetFieldName);
								window.draw(targetFieldDays);
								window.draw(targetFieldType);
								window.draw(targetFieldLoca);
								window.draw(targetFieldImage);
								window.draw(targetSave);
								window.draw(targetXB);
								*/
								window.display();
							}
						}
					}
					else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inLocaField == true) {
						std::cout << "Click at 'Location' field" << std::endl;
						inLocaField = true;
						while (inLocaField) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed)
									window.close();
								locaText.setString(locaInput + "|");
								if (event.type == sf::Event::TextEntered)
								{
									if (event.text.unicode == 8 && !locaInput.empty()) { // Handle backspace
										locaText.setFillColor(sf::Color::Black);
										locaInput.pop_back();
									}
									else if (event.text.unicode >= 32 && event.text.unicode < 128) { // Handle printable characters
										locaInput += static_cast<char>(event.text.unicode);
									}
									locaText.setString(locaInput + "|");
									std::cout << locaInput << std::endl;
									entry.location = locaInput;

								}
								if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
									std::cout << "Key pressed 'Enter'" << std::endl;
									sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
									locaText.setString(locaInput);
									if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = true;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = true;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = true;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = true;
										break;
									}
									else if (targetXB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'X' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										added_plant = true;
										break;
									}
									else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'Save' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
											entry.saveToDatabase("plantly.db");
											added_plant = true;
											break;
										}
										else {
											showErrorDialog("Error adding Plant", "All fields must be filled out");
											break;
										}
									}

								}
								window.clear();
								window.clear(sf::Color::White);
								window.draw(plantP);
								draw_AP_Screen(window);
								/*
								window.draw(nameUI);
								window.draw(daysUI);
								window.draw(typeUI);
								window.draw(locaUI);
								window.draw(imageUI);
								window.draw(saveUI);
								*/

								window.draw(nameText);
								window.draw(daysText);
								window.draw(typeText);
								window.draw(locaText);

								/*
								window.draw(targetFieldName);
								window.draw(targetFieldDays);
								window.draw(targetFieldType);
								window.draw(targetFieldLoca);
								window.draw(targetFieldImage);
								window.draw(targetSave);
								window.draw(targetXB);
								*/
								window.display();
							}
						}
					}
					else if (targetFieldImage.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || inImageField == true) {
						std::cout << "Click at 'Choose image' field" << std::endl;
						
						//entry.set_image("Plantly.db"); //Save image to DataBase
						entry.image = GetFileBlobDialog();
		 
						window.clear(sf::Color::White);
						plantT.loadFromMemory(entry.image.data(), entry.image.size());
						plantP.setTexture(plantT, true);
						CenterBlobImage(window, entry.image, plantT, plantP);

						window.draw(plantP);
						draw_AP_Screen(window);

						window.draw(nameText);
						window.draw(daysText);
						window.draw(typeText);
						window.draw(locaText);
						/*
						window.draw(targetFieldName);
						window.draw(targetFieldDays);
						window.draw(targetFieldType);
						window.draw(targetFieldLoca);
						window.draw(targetFieldImage);
						window.draw(targetSave);
						window.draw(targetXB);
						*/

						window.display();

		
						inImageField = false;
						
						/*
						while (inImageField) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed)
									window.close();
								auto blob = GetFileBlobDialog();


								sf::Texture PFP;
								if (!PFP.loadFromMemory(blob.data(), blob.size())) {
									std::cout << "Failed to load profile picture from binary data!" << std::endl;
									PFP.loadFromFile("Resources/images/pfp.png");
								}

								if (event.key.code == sf::Keyboard::Enter || ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))) {
									std::cout << "Key pressed 'Enter'" << std::endl;
									sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
									if (targetFieldName.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = true;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldDays.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = true;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldType.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = true;
										inLocaField = false;
										inImageField = false;
										break;
									}
									else if (targetFieldLoca.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = true;
										inImageField = false;
										break;
									}
									else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
										std::cout << "Click at 'Next' button" << std::endl;
										inNameField = false;
										inDaysField = false;
										inTypeField = false;
										inLocaField = false;
										inImageField = false;
										///*
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
										// * /
										added_plant = true;
										break;
									}
								}
								window.clear();
								window.clear(sf::Color::White);
								draw_AP_Screen(window);
								window.draw(nameUI);
								window.draw(daysUI);
								window.draw(typeUI);
								window.draw(locaUI);
								window.draw(imageUI);
								window.draw(saveUI);

								window.draw(nameText);
								window.draw(daysText);
								window.draw(typeText);
								window.draw(locaText);

								window.draw(targetFieldName);
								window.draw(targetFieldDays);
								window.draw(targetFieldType);
								window.draw(targetFieldLoca);
								window.draw(targetFieldImage);
								window.draw(targetSave);
								window.display();

							}*/
							//}
					}
					else if (targetSave.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						//usersPlants[plants_number()] = entry;
						std::cout << "Click at 'Save' button" << std::endl;
						inNameField = false;
						inDaysField = false;
						inTypeField = false;
						inLocaField = false;
						inImageField = false;
						if ((entry.name != "") && (entry.days != NULL) && (entry.type != "") && (entry.location != "")) {
							entry.saveToDatabase("plantly.db");
							added_plant = true;
							break;
						}
						else {
							showErrorDialog("Error adding Plant", "All fields must be filled out");
							break;
						}
					}
				}

				if (added_plant == true)
					break;
			}
		}
		window.display();
	}
}

//loged in user class
//Function to data base for Plants
void open_plants_db() {
	sqlite3* db;
	int exit = sqlite3_open("plantly.db", &db);

	if (exit) {
		std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Opened database successfully!" << std::endl;
	}
}



//--------------------------------------------------db--------------------------------------------------

// Function to read a file and return its content as a byte vector
std::vector<unsigned char> readFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filePath);
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<unsigned char> buffer(size);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
		throw std::runtime_error("Error reading file: " + filePath);
	}

	return buffer;
}

// Function to write binary data to a file (if needed)
void saveBlobToFile(const std::vector<unsigned char>& blobData, const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile) {
		std::cerr << "Error: Could not write blob to file: " << fileName << std::endl;
		return;
	}

	outFile.write(reinterpret_cast<const char*>(blobData.data()), blobData.size());
	outFile.close();
	std::cout << "Picture saved to file: " << fileName << std::endl;
}

void UserData::saveToDatabase(const std::string& dbFile) {
	sqlite3* db;
	char* errorMessage = nullptr;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db)) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Create table if it doesn't exist
	std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Users ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Name TEXT, "
		"Email TEXT,"
		"Password TEXT,"
		"PStatus BOOLEAN,"
		"Image BLOP);";
	if (sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error creating table for Users: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	// Insert data
	std::string insertSQL = "INSERT INTO Users (Name, Email, Password, PStatus) VALUES ('" +
		name + "', '" + email + "', '" + password + "', '" + pstatus + "');";
	if (sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error inserting data for Plants: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data saved successfully!\n";
	}

	// Close database
	sqlite3_close(db);
}

void UserData::set_image(const std::string& dbFile) {
	sqlite3* db;
	char* errorMessage = nullptr;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db)) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	std::string updateSQL = "UPDATE Users SET Image = ? WHERE ID = ?;";
	sqlite3_stmt* stmt;

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(db, updateSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Bind the BLOB data
	if (sqlite3_bind_blob(stmt, 1, image.data(), image.size(), SQLITE_STATIC) != SQLITE_OK) {
		std::cerr << "Failed to bind BLOB: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	// Bind the user ID
	if (sqlite3_bind_int(stmt, 2, id) != SQLITE_OK) {
		std::cerr << "Failed to bind ID: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}

	// Execute the statement
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "User image updated successfully!" << std::endl;
	}

	// Clean up
	sqlite3_finalize(stmt);
}

void Plant::showObject(sf::RenderWindow& Window, sf::Texture frameTexture, sf::Texture maskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font Font) {


	sf::Texture PlantImageT;
	if (!PlantImageT.loadFromMemory(image.data(), image.size())) {
		std::cout << "Failed to load plant image into texture\n" << std::endl;
		return;
	}
	
	Sprite.setTexture(PlantImageT);

	// Apply the mask to the sprite
	sf::RenderTexture renderTexture;
	renderTexture.create(PlantImageT.getSize().x, PlantImageT.getSize().y);
	sf::Sprite textureSprite(PlantImageT);
	sf::Sprite maskSprite(maskTexture);

	renderTexture.clear(sf::Color::Transparent);
	renderTexture.draw(textureSprite); // Draw the original texture
	renderTexture.draw(maskSprite, sf::BlendMultiply); // Blend with the mask
	renderTexture.display();

	// Use the rendered texture as the sprite's texture
	sf::Texture finalTexture = renderTexture.getTexture();
	Sprite.setTexture(finalTexture);

	Sprite.setPosition(posX, posY);


	sf::Text Name(name, Font, 15);
	auto center = Name.getGlobalBounds().getSize() / 2.f;
	Name.setPosition((posX + 9 + (85 - center.x)), (posY + (217 - center.y)));

}

void Plant::saveToDatabase(const std::string& dbFile) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* errorMessage = nullptr;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		return;
	}

	const char* createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS Plants (
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                UserID INTEGER NOT NULL,
                Days INTEGER NOT NULL,
                Datetime DATETIME NOT NULL,
                Name TEXT NOT NULL,
                Type TEXT NOT NULL,
                Location TEXT NOT NULL,
                Image BLOP
            );
        )";

	if (sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error creating table for Plants: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	//std::string insertQuery = "INSERT INTO entries (UserID, Days, Name, Type, Location, Image) VALUES ('" +
	//	name + "', " + std::to_string(days) + ", '" + filePath + "');";

	std::string insertQuery = "INSERT INTO Plants (UserID, Days, Name, Type, Location, Image) VALUES (?, ?, ?, ?, ?, ?);";


	if (sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	// Bind values to the query
	sqlite3_bind_int(stmt, 1, User.id);
	sqlite3_bind_int(stmt, 2, days);
	sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, type.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, location.c_str(), -1, SQLITE_STATIC);

	// Bind the BLOB data
	if (sqlite3_bind_blob(stmt, 6, image.data(), image.size(), SQLITE_STATIC) != SQLITE_OK) {
		std::cerr << "Failed to bind BLOB: " << sqlite3_errmsg(db) << std::endl;
		
		return;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
	}

	// Clean up resources
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return;
}

void Plant::insertCurrentDateTime(const std::string& dbFile) {
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	char* errorMessage = nullptr;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Construct the SQL query
	std::string insertQuery = "UPDATE Plants SET Datetime = DATETIME('now') WHERE id = ?;";

	// Prepare the SQL statement
	if (sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}
	//Binding
	sqlite3_bind_int(stmt, 1, id);

	// Execute the SQL statement
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Inserted current DATETIME successfully." << std::endl;
	}

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
//____________________________________________
void Plant::fetch_plants_from_db(const std::string& dbFile) {
	for (size_t i = 0; i < plantsnum; i++){
		usersPlants[i].populate(NULL, NULL, NULL, "", "", "", { static_cast<uint8_t>(NULL) });
	}

	sqlite3* db;
	sqlite3_stmt* stmt;
	bool exists = false;

	// Open SQLite database
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
	}
	// Construct the SQL query
	std::string query = "SELECT id, userid, days, name, type, location, image FROM Plants WHERE userid = ? LIMIT 10;";

	// Prepare the query
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
		showErrorDialog("Database error", sqlite3_errmsg(db));
		sqlite3_close(db);
	}

	// Bind values to the query
	sqlite3_bind_int(stmt, 1, User.id);

	int i = 0;
	// Execute the query and fetch the results
	while (sqlite3_step(stmt) == SQLITE_ROW && i < plantsnum) {
		int id = sqlite3_column_int(stmt, 0);
		int userid = sqlite3_column_int(stmt, 1);
		int days = sqlite3_column_int(stmt, 2);
		std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		std::string location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		// Fetch BLOB data
		const void* blobData = sqlite3_column_blob(stmt, 6);
		int blobSize = sqlite3_column_bytes(stmt, 6);
		std::vector<uint8_t> image;
		if (blobData && blobSize > 0) {
			image.assign(static_cast<const uint8_t*>(blobData), static_cast<const uint8_t*>(blobData) + blobSize);
		}

		// Populate the array with the object
		usersPlants[i].populate(id, userid, days, name, type, location, image);
		++i;
	}
	/*
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
	*/

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

// Helper function to join strings (for constructing SQL query)
std::string join(const std::vector<std::string>& elements, const std::string& delimiter) {
	std::string result;
	for (size_t i = 0; i < elements.size(); ++i) {
		result += elements[i];
		if (i < elements.size() - 1) {
			result += delimiter;
		}
	}
	return result;
}

std::string generate_username(std::string email) {
	std::string result = "@";
	std::string output = "";
	email.length();
	for (int i = 0; i < email.find("@"); i++) {
		output += email[i];
	}

	return result += output;

}

void showErrorDialog(const std::string& title, const std::string& message) {
	sf::RenderWindow window(sf::VideoMode(400, 200), title);
	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Instrument_Sans/static/InstrumentSans-SemiBold.ttf")) {
		return;  // Error loading font
	}

	sf::Text text(message, font, 20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(20, 80);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.draw(text);
		window.display();
	}
}



// Function to display a file dialog and return the file content as a binary blob
const size_t MAX_FILE_SIZE = 2 * 1024 * 1024; // 2 MB
std::vector<uint8_t> GetFileBlobDialog() {
	// Initialize COM library
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) {
		std::cerr << "Failed to initialize COM library." << std::endl;
		return {};
	}

	IFileOpenDialog* pFileOpen = nullptr;

	// Create the FileOpenDialog object
	hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
	if (FAILED(hr)) {
		std::cerr << "Failed to create file dialog instance." << std::endl;
		CoUninitialize();
		return {};
	}

	// Set file type filters (images only)
	const COMDLG_FILTERSPEC fileTypes[] = {
		{L"Image Files", L"*.jpg;*.jpeg;*.png;*.bmp;*.gif"}, // Friendly name and filter
		{L"JPEG Files", L"*.jpg;*.jpeg"},
		{L"PNG Files", L"*.png"},
		{L"BMP Files", L"*.bmp"},
		{L"GIF Files", L"*.gif"}
	};
	pFileOpen->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes); // Apply the filter
	pFileOpen->SetFileTypeIndex(1); // Default to the first filter
	pFileOpen->SetDefaultExtension(L"jpg"); // Default file extension

	// Show the file open dialog
	hr = pFileOpen->Show(nullptr);
	if (SUCCEEDED(hr)) {
		// Get the file name from the dialog
		IShellItem* pItem = nullptr;
		hr = pFileOpen->GetResult(&pItem);
		if (SUCCEEDED(hr)) {
			PWSTR pszFilePath = nullptr;
			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
			if (SUCCEEDED(hr)) {
				// Convert the wide string to a standard string
				std::wstring widePath(pszFilePath);
				std::string filePath(widePath.begin(), widePath.end());

				// Check the file size before reading
				std::ifstream file(filePath, std::ios::binary | std::ios::ate); // Open in binary mode and seek to the end
				if (!file) {
					std::cerr << "Error opening file." << std::endl;
					CoTaskMemFree(pszFilePath);
					pItem->Release();
					pFileOpen->Release();
					CoUninitialize();
					return {};
				}

				// Get the file size
				std::streamsize fileSize = file.tellg();
				if (fileSize > MAX_FILE_SIZE) {
					std::cerr << "File size exceeds the 2 MB limit. File size: " << fileSize / 1024 << " kilobytes." << std::endl;
					showErrorDialog("File size error", "File size exceeds the 2 MB limit.\nFile size: " + std::to_string(fileSize/1024) + " kilobytes.");
					file.close();
					CoTaskMemFree(pszFilePath);
					pItem->Release();
					pFileOpen->Release();
					CoUninitialize();
					return {};
				}

				// Read the file into a binary blob
				file.seekg(0, std::ios::beg); // Move back to the start of the file
				std::vector<uint8_t> blob(fileSize);
				file.read(reinterpret_cast<char*>(blob.data()), fileSize);

				// Clean up
				file.close();
				CoTaskMemFree(pszFilePath);
				pItem->Release();
				pFileOpen->Release();
				CoUninitialize();

				return blob;
			}
			pItem->Release();
		}
	}

	// Clean up
	if (pFileOpen) {
		pFileOpen->Release();
	}
	CoUninitialize();
	return {};
}


int plants_number() {
	//std::cout << "\nThe length of the given Array is: " << usersPlants.size();
	//int al = sizeof(usersPlants) / sizeof(Plant);
	
	int ans = 0;
	for (int i = 0; i < plantsnum; i++){
		if (usersPlants[i].id != NULL){
			ans++;
			std::cout << "Ans: " << ans << std::endl;
		}
		else {
			i = plantsnum;
		}
	}
	std::cout << "Final ans: " << ans << std::endl;
	return ans;
}

// Func to change picture's position
void CenterBlobImage(sf::RenderWindow& window, const std::vector<uint8_t>& image, sf::Texture& texture, sf::Sprite& sprite) {
	if (!texture.loadFromMemory(image.data(), image.size())) {
		std::cerr << "Nie można utworzyć tekstury!\n";
		return;
	}
	float scale = 0.2f;
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);

	// Obliczanie pozycji centralnej
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2u textureSize = texture.getSize();
	float x = (windowSize.x - (textureSize.x * scale)) / 2.0f;
	float y = (windowSize.y - (textureSize.y * scale)) / 2.0f;
	sprite.setPosition(x, y - 125);
	// Odrysowanie obrazu w oknie
	window.draw(sprite);
}

/*
bool init_sqcloud() {
	// setup config
	const char* conninfo = "sqlitecloud://cqrhaexnhz.sqlite.cloud:8860/plantly?apikey=Z1eHgB57uXYKCxgTOdUfl8EIudaYh6YauGTcEjBugMc";

	SQCloudConnection * conn = SQCloudConnectWithString(conninfo, NULL);
	if (SQCloudIsError(conn)) {
		std::cerr << "ERROR connecting: %s (%d)\n" << SQCloudErrorMsg(conn) << SQCloudErrorCode(conn) << std::endl;
		return false;
	}
	else {
		std::cout << "Connection to host OK...\n\n" << std::endl;
		return true;
	}


}
*/