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
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "Header.h"
#include "SQLite/sqlite3.h"
#include <fstream>
#include <array>

/*
#ifdef _WIN32
	#include <windows.h>
#else
	#include <cstdlib> // dla system()
#endif
*/
using namespace std;


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
		cout << "Failed to load profile picture!" << endl;
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
		cout << "Failed to load image!" << endl;
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

void draw_X(sf::RenderWindow& window, int x, int y) {
	sf::Texture XT;
	if (!XT.loadFromFile("Resources/images/AP.png"))
		cout << "Failed to load image!" << endl;

	sf::Sprite X;
	X.setTexture(XT);
	X.setScale(0.12f, 0.12f);
	X.setPosition(x, y);
	X.setRotation(45);
	window.draw(X);
	//window.display();
}
/*
void draw_logo(sf::RenderWindow& window) {
	// Ustawienia tekstu
	sf::Font logo_font;
	if (!logo_font.loadFromFile("Resources/Fonts/League_Script/LeagueScript-Regular.ttf")) {
		cout << "Failed to load font";
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
	

	sqlite3* db;
	sqlite3_stmt* stmt;

	// Otwarcie połączenia z bazą danych
	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Zapytanie SQL do pobrania danych
	const char* query = "SELECT ID, NAME, DAYS, FILEPATH FROM entries;";

	// Przygotowanie zapytania
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	std::cout << "Zawartosc bazy danych:" << std::endl;
	std::cout << "----------------------------------" << std::endl;

	// Wykonywanie zapytania i wyświetlanie wyników
	sf::Font Font;
	if (!Font.loadFromFile("Resources/Fonts/Instrument_Sans/static/InstrumentSans-SemiBold"))
		cout << "Failed to load font";

	sf::Texture PlantBlock;
	if (!PlantBlock.loadFromFile("Resources/images/PlantBackground.png")) {
		cout << "Failed to load plant block background!" << endl;
		return;
	}

	//zapt o wiersze
	int items = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		items++;
	}
	const int NUM_SPRITES = items; // Liczba spritów
	std::vector<sf::Sprite> plantSprites(NUM_SPRITES);
	std::vector<sf::Text> plantName(NUM_SPRITES);

	for (size_t i = 0; i < NUM_SPRITES; i++) {

		int id = sqlite3_column_int(stmt, 0);
		const unsigned char* name = sqlite3_column_text(stmt, 1);
		int days = sqlite3_column_int(stmt, 2);
		const unsigned char* filePath = sqlite3_column_text(stmt, 3);

		std::string names = name ? reinterpret_cast<const char*>(name) : "NULL";
		std::string filePaths = filePath ? reinterpret_cast<const char*>(filePath) : "NULL";

		std::cout << "ID: " << id << std::endl;
		std::cout << "Nazwa: " << (name ? reinterpret_cast<const char*>(name) : "NULL") << std::endl;
		std::cout << "Ilosc dni: " << days << std::endl;
		std::cout << "Plik: " << (filePath ? reinterpret_cast<const char*>(filePath) : "NULL") << std::endl;
		std::cout << "----------------------------------" << std::endl;

		sf::Texture PlantPictureT;
		if (!PlantPictureT.loadFromFile(filePaths)) {
			cout << "Failed to load plant block background!" << endl;
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



	}

	// Zwolnienie zasobów
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	
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
	window.display();
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

void draw_menu(sf::RenderWindow& window, sf::Event event, bool show) { //, int Click_Value_m
	sf::RectangleShape rectangle_white(sf::Vector2f(250.0f, 780.0f));
	rectangle_white.setFillColor(sf::Color(0xFFFFFFFF));
	rectangle_white.setPosition(120, 70);

	sf::RectangleShape rectangle_shadow(sf::Vector2f(250.0f, 780.0f));
	rectangle_shadow.setFillColor(sf::Color(0, 0, 0, 50));
	rectangle_shadow.setPosition(125, 75);

	// Ustawienia tekstu
	sf::Font text_font;
	if (!text_font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf")) {
		cout << "Failed to load font";
	}

	sf::Texture PFP;
	if (!PFP.loadFromFile("Resources/images/pfp.png")) {
		cout << "Failed to load profile picture!" << endl;
		return;
	}

	sf::Text name("Name \nSurname", text_font, 20);
	sf::Text Preferences("Preferences", text_font, 20);
	sf::Text AS("Account settings", text_font, 20);
	sf::Text RP("Restore purchases", text_font, 20);
	sf::Text LogoutB("Logout", text_font, 20);
	sf::Sprite PFPb;
	PFPb.setTexture(PFP);
	PFPb.setScale(0.15f, 0.15f);


	


	if (!show) {
		rectangle_white.setPosition(2000, 2000);
		rectangle_shadow.setPosition(2000, 2000);
		name.setPosition(2000, 2000); // Pozycja tekstu
		Preferences.setPosition(2000, 2000);
		AS.setPosition(2000, 2000);
		RP.setPosition(2000, 2000);
		PFPb.setPosition(2000, 2000);
	}
	else if (show) {
		name.setPosition(140, 100); // Pozycja tekstu
		Preferences.setPosition(140, 160);
		AS.setPosition(140, 190);
		RP.setPosition(140, 220);
		LogoutB.setPosition(140, 250);
		PFPb.setPosition(300, 100);

		name.setFillColor(sf::Color::Black);
		Preferences.setFillColor(sf::Color::Black);
		AS.setFillColor(sf::Color::Black);
		RP.setFillColor(sf::Color::Black);
		LogoutB.setFillColor(sf::Color::Black);

		sf::RectangleShape targetLogoutB(sf::Vector2f(49, 20));
		targetLogoutB.setPosition(140, 250);

		sf::RectangleShape targetMainBs(sf::Vector2f(51, 360));
		targetMainBs.setPosition(40, 40);

		bool MainBs = false;


		window.draw(rectangle_shadow);
		window.draw(rectangle_white);
		window.draw(name);
		window.draw(PFPb);
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
		cout << "Failed to load font";
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
	
	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf"))
		cout << "Failed to load font";
	
	sf::Text nameText("Name:", font, 20);
	sf::Text nameInput("", font, 20);
	sf::Text daysText("Days:", font, 20);
	sf::Text daysInput("", font, 20);
	sf::Text filePathText("File:", font, 20);
	sf::Text filePathInput("", font, 20);
	sf::Text saveText("Save", font, 20);
	
	
	if (!show) {
		nameText.setPosition(2000, 2000);
		nameInput.setPosition(2000, 2000);
		daysText.setPosition(2000, 2000);
		daysInput.setPosition(2000, 2000);
		filePathText.setPosition(2000, 2000);
		filePathInput.setPosition(2000, 2000);
		saveText.setPosition(2000, 2000);
	}
	else {
		window.clear(sf::Color::White);
		nameText.setPosition(100, 100);
		nameInput.setPosition(150, 100);
		daysText.setPosition(100, 200);
		daysInput.setPosition(150, 200);
		filePathText.setPosition(100, 300);
		filePathInput.setPosition(150, 300);
		saveText.setPosition(100, 450);

		nameText.setFillColor(sf::Color::Black);
		nameInput.setFillColor(sf::Color::Black);
		daysText.setFillColor(sf::Color::Black);
		daysInput.setFillColor(sf::Color::Black);
		filePathText.setFillColor(sf::Color::Black);
		filePathInput.setFillColor(sf::Color::Black);
		saveText.setFillColor(sf::Color::Black);

		sf::RectangleShape targetXB(sf::Vector2f(49, 49));
		targetXB.setPosition(849, 116);
		
		///window.draw(targetXB);
		window.draw(nameText);
		window.draw(nameInput);
		window.draw(daysText);
		window.draw(daysInput);
		window.draw(filePathText);
		window.draw(filePathInput);
		window.draw(saveText);

		draw_X(window, 870, 100);
		window.display();
		bool added_plant = false;
		std::string nameBuffer, daysBuffer, filePathBuffer;
		Plant entry;
		bool enteringFilePath = false;
		
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
				}

				if (event.type == sf::Event::TextEntered) {
					if (enteringFilePath) {
						handleTextInput(filePathInput, event, filePathBuffer);
					}
					else if (nameInput.getString().isEmpty() || nameInput.getString() == nameBuffer) {
						handleTextInput(nameInput, event, nameBuffer);
					}
					else {
						handleTextInput(daysInput, event, daysBuffer);
					}
					
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Tab) {
						enteringFilePath = !enteringFilePath;
						std::cout << "Tab pressed" << std::endl;
					}
					else if (event.key.code == sf::Keyboard::Enter) {
						std::cout << "Enter pressed" << std::endl;
						try {
							entry.name = nameBuffer;
							entry.days = std::stoi(daysBuffer);
							entry.filePath = filePathBuffer;
							entry.saveToDatabase("plants.db");
							std::cout << "Data saved!" << std::endl;
							added_plant = true;
						}
						catch (...) {
							std::cerr << "Invalid input!" << std::endl;
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
	int exit = sqlite3_open("plants.db", &db);

	if (exit) {
		std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Opened database successfully!" << std::endl;
	}
}



//--------------------------------------------------DB Files--------------------------------------------------
// 
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

// Helper function to handle text input

void handleTextInput(sf::Text& text, sf::Event& event, std::string& input) {
	if (event.text.unicode < 128) {
		if (event.text.unicode == '\b' && !input.empty()) { // Backspace
			input.pop_back();
		}
		else if (event.text.unicode != '\b') {
			input += static_cast<char>(event.text.unicode);
		}
		text.setString(input);
	}
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
		"Age TEXT, "
		"Email TEXT);";
	if (sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error creating table for Users: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	// Insert data
	std::string insertSQL = "INSERT INTO Users (Name, Age, Email) VALUES ('" +
		name + "', '" + age + "', '" + email + "');";
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

void Plant::saveToDatabase(const std::string& dbFile) {
	sqlite3* db;
	char* errorMessage = nullptr;

	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database for Plants: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	const char* createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS entries (
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                Name TEXT NOT NULL,
                Days INTEGER NOT NULL,
                Filepath TEXT NOT NULL
            );
        )";

	if (sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error creating table for Plants: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	std::string insertQuery = "INSERT INTO entries (NAME, DAYS, FILEPATH) VALUES ('" +
		name + "', " + std::to_string(days) + ", '" + filePath + "');";

	if (sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error inserting datafor Plants: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}

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