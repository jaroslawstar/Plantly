/*
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"


#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

void buttons_engine(sf::RenderWindow& window, sf::Event event) {
	char url[70] = "https://github.com/jaroslawstar/Plantly/blob/master/README.md";
	std::string op = std::string("start ").append(url);
	
	switch (Click_Value){
	case 0:
		draw_menu(window, event, false);
		break;
	case 1:
		draw_menu(window, event, false);
		std::cout << "Click at 'Home' button SSSSS" << std::endl;
		//draw_plants(window);
		//draw_menu(window, event, false);
		break;
	case 2:
		//draw_main_screen(window);
		draw_menu(window, event, true);
		break;
	case 3:
		//draw_text(window, false);
		break;
	case 4:
		draw_text(window);
		break;
	case 5:
		system(op.c_str());
		Click_Value = 0;
		break;
	default:
		break;
	}
	



}


/*
void open_menu(sf::RenderWindow& window, sf::Event event,  int Click_Value) {
	if (Click_Value == 2)
		draw_menu(window);
	else if (Click_Value == 0) {
		draw_main_screen(window);
		draw_buttons(window, event, 0);
	}
	//else{
	//	draw_menu(window);
	//}


}




/*

void Add_Plant(sf::RenderWindow& window, int Click_Value, int ButtonRotation) {
	if (Click_Value == 3){
		draw_menu(window);
	}
	else {
		draw_main_screen(window);
	}
}



if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Sprawdzanie, czy kliknięto lewym przyciskiem

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Pobranie pozycji kursora w oknie
    if (event.type == sf::Event::MouseButtonReleased) {}
    // Sprawdzanie, czy kliknięcie miało miejsce w obszarze prostokąta
    if (HomeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 1) {
        std::cout << "Click at 'Home' button" << std::endl;
        Click_Value = 1;
        draw_plants(window);
        //return Click_Value; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (HomeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && event.type == sf::Event::MouseButtonReleased) {
        std::cout << "UnClick at 'Home' button" << std::endl;
        Click_Value = 0;
        //return Click_Value; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (MenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 2) {
        std::cout << "Click at 'Menu' button" << std::endl;
        Click_Value = 2;
        draw_menu(window, event, true);
        //return Click_Value = 2; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (MenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && event.type == sf::Event::MouseButtonReleased) {
        std::cout << "UnClick at 'Menu' button" << std::endl;
        Click_Value = 0;
        //return Click_Value = 2; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (APButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 3) {
        std::cout << "Click at 'Add Plant' button" << std::endl;
        APRotation = true;
        Click_Value = 3;
        //return Click_Value = 3; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (APButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 3 && event.type == sf::Event::MouseButtonReleased) {
        std::cout << "UnClick at 'Add Plant' button" << std::endl;
        APRotation = false;
        Click_Value = 0;
        //return Click_Value = 0; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (FeedButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 4) {
        std::cout << "Click at 'Feed' button" << std::endl;
        Click_Value = 4; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (FeedButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 4) {
        std::cout << "UnClick at 'Feed' button" << std::endl;
        Click_Value = 0;
        //return Click_Value = 4; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (QMButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 5) {
        std::cout << "Click at 'Question Mark' button" << std::endl;
        Click_Value = 5; // Zmiana wartosci zmiennej a po kliknięciu
    }
    else if (QMButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 5) {
        std::cout << "UnClick at 'Question Mark' button" << std::endl;
        Click_Value = 0;
        //return Click_Value = 5; // Zmiana wartosci zmiennej a po kliknięciu
    }
    //else
        //return Click_Value;
    //return Click_Value;
}







_____________________________________________________________________________________


 while (UserSighned == false && window.pollEvent(event)) {

               ///*
            //}
            window.clear();
            draw_main_screen(window);


            //while (UserSighned == true && window.pollEvent(event)) {//Main Window after login
                ///*

                window.clear();
                draw_buttons(window, APRotation);


                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    
                }
                //draw_signup_screen(window);

                //draw_logo(window);
                //open_menu(window, event, draw_buttons(window, event, APRotation));
                //draw_buttons(window, event, APRotation);
                //buttons_engine(window, event);
        window.display();

/*
* /


_____________________________________________________________________________________

*/



/*
                    switch (button) {
                    case ButtonClick::Home:

                        window.display();
                        break;
                    case ButtonClick::Menu:

                        window.display();
                        break;
                    case ButtonClick::AP:

                        window.display();
                        break;
                    case ButtonClick::Feed:

                        window.display();
                        break;
                    case ButtonClick::QM:

                        break;
                    default:
                        draw_main_screen(window);
                        draw_buttons(window, APRotation);
                        break;
                    }














                    draw_main_screen(window);
                        draw_plants(window, event, true);
                        draw_menu(window, false);
                        draw_AP_screen(window, false);
                        draw_text(window, false);

                        draw_main_screen(window);
                        draw_plants(window, event, false);
                        draw_menu(window, true);
                        draw_AP_screen(window, false);
                        draw_text(window, false);


                        draw_main_screen(window);
                        if (buttonClick == ButtonClick::AP) {
                            APRotation = false;
                            buttonClick = ButtonClick::undefined;
                        }
                        else {
                            APRotation = true;
                            buttonClick = ButtonClick::AP;
                        }




                         draw_main_screen(window);
                        if (buttonClick == ButtonClick::Feed) {
                            buttonClick = ButtonClick::undefined;
                        }
                        else {
                            buttonClick = ButtonClick::Feed;
                        }



                        draw_main_screen(window);
                        if (buttonClick == ButtonClick::QM) {
                            buttonClick = ButtonClick::undefined;
                        }
                        else {
                            buttonClick = ButtonClick::QM;
                        }
              
              
	std::string result(User.image.begin(), User.image.end());

	// Insert data
	std::string insertSQL = "INSERT INTO Users (Image) VALUES ('" + result + "');";
	if (sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		std::cerr << "Error inserting data for Plants: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data saved successfully!\n";
	}

	// Close database
	sqlite3_close(db);







        sprite.setScale(0.2f, 0.2f);
              
              
              
              
              
              
              
              

              
              
              
              
              
              
          





    std::string callPythonFunction() {
    // Initialize the Python interpreter
    std::cout << "Initializing Python interpreter..." << std::endl;
    if (!Py_IsInitialized()) {
        Py_Initialize();
    }

    std::cout << "Setting Python path..." << std::endl;
    PyRun_SimpleString("import sys; sys.path.append('.')");

    std::cout << "Importing Python module 'ai'..." << std::endl;
    PyObject* pName = PyUnicode_DecodeFSDefault("ai");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule) {
        std::cerr << "Failed to load Python module 'ai'." << std::endl;
        PyErr_Print();
        Py_FinalizeEx();
        throw std::runtime_error("Failed to load Python module 'ai'.");
    }

    std::cout << "Looking for function 'hello' in module 'ai'..." << std::endl;
    PyObject* pFunc = PyObject_GetAttrString(pModule, "hello");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        std::cerr << "Function 'hello' not found or not callable." << std::endl;
        Py_DECREF(pModule);
        Py_FinalizeEx();
        throw std::runtime_error("Function 'hello' not found in module 'ai'.");
    }

    std::cout << "Calling Python function 'hello'..." << std::endl;
    PyObject* pValue = PyObject_CallObject(pFunc, nullptr);
    if (!pValue) {
        std::cerr << "Call to Python function 'hello' failed." << std::endl;
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        Py_FinalizeEx();
        throw std::runtime_error("Python function call failed.");
    }

    std::cout << "Converting Python result to std::string..." << std::endl;
    const char* resultCStr = PyUnicode_AsUTF8(pValue);
    std::string result = resultCStr ? resultCStr : "";

    std::cout << "Cleaning up Python objects..." << std::endl;
    Py_DECREF(pValue);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    std::cout << "Finalizing Python interpreter..." << std::endl;
    if (Py_FinalizeEx() < 0) {
        std::cerr << "Error finalizing Python interpreter." << std::endl;
        throw std::runtime_error("Failed to finalize Python interpreter.");
    }

    return result;
}



//int result = -1; // Default result in case of error
    Py_Initialize();

    PyObject* pName, * pModule, * pFunc, * pArgs, * pValue;
    pName = PyUnicode_FromString((char*)"ai");
    pModule = PyImport_Import(pName);
    pArgs = PyTuple_Pack(2, PyLong_FromLong(a), PyLong_FromLong(b));
    pFunc = PyObject_GetAttrString(pModule, (char*)"add_numbers");
    pValue = PyObject_CallObject(pFunc, pArgs);
    auto result = PyLong_AsLong(pValue);
    std::cout << result << std::endl;
    Py_Finalize();
    return result;





    sum = add_numbers(5, 2)
print(sum)

hello()
*/

