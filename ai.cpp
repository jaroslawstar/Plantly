#include <Python.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include "api_key.h"

std::string callPythonFunctionHello() {
    if (!Py_IsInitialized()) {
        Py_Initialize();
    }

    PyObject* pName, * pModule, * pFunc, * pArgs, * pValue;
    pName = PyUnicode_FromString((char*)"ai");
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule, (char*)"hello");
    pArgs = PyTuple_Pack(1, PyUnicode_FromString(ReturnMyApiKeyString1().c_str()));

    pValue = PyObject_CallObject(pFunc, nullptr);
    auto result = PyUnicode_AsUTF8(pValue);
    std::cout << result << std::endl;
    //Py_Finalize();
    return result;
}

int callAddNumbers(int a, int b) {
    if (!Py_IsInitialized()) {
        Py_Initialize();
    } // Initialize Python interpreter (ensure this is necessary)

    PyObject* pName = nullptr, * pModule = nullptr, * pFunc = nullptr, * pArgs = nullptr, * pValue = nullptr;

    try {
        // Import the Python module
        pName = PyUnicode_FromString("ai");
        if (!pName) throw std::runtime_error("Failed to create Python string for module name.");

        pModule = PyImport_Import(pName);
        Py_DECREF(pName); // Decrement pName after importing the module
        if (!pModule) throw std::runtime_error("Failed to import Python module 'ai'.");

        // Get the function "add_numbers" from the module
        pFunc = PyObject_GetAttrString(pModule, "add_numbers");
        if (!pFunc || !PyCallable_Check(pFunc)) throw std::runtime_error("Failed to find callable function 'add_numbers' in module.");

        // Pack the arguments into a Python tuple
        pArgs = PyTuple_Pack(2, PyLong_FromLong(a), PyLong_FromLong(b));
        if (!pArgs) throw std::runtime_error("Failed to create arguments tuple for function.");

        // Call the Python function with arguments
        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs); // Decrement pArgs after the function call
        if (!pValue) throw std::runtime_error("Python function call failed.");

        // Convert the Python result to a C++ int
        int result = PyLong_AsLong(pValue);
        if (PyErr_Occurred()) throw std::runtime_error("Error occurred while converting Python result to int.");

        Py_DECREF(pValue);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        //PyRun_SimpleString("quit()");
        //Py_FinalizeEx(); // Finalize Python interpreter
        return result; // Return the result
    }
    catch (const std::exception& e) {
        PyErr_Print(); // Print the Python error
        if (pValue) Py_DECREF(pValue);
        if (pFunc) Py_DECREF(pFunc);
        if (pModule) Py_DECREF(pModule);
        //Py_FinalizeEx(); // Ensure the interpreter is finalized in case of error
        throw; // Re-throw the exception
    }
}

std::string callGeneratePlantInfo(const std::string& type) {
    if (!Py_IsInitialized()) {
        Py_Initialize();
    }

    PyObject* pName = nullptr, * pModule = nullptr, * pFunc = nullptr, * pArgs = nullptr, * pValue = nullptr;
    std::string result;

    try {
        // Load the Python module
        pName = PyUnicode_FromString("ai");
        if (!pName) throw std::runtime_error("Failed to convert module name to Python string.");

        pModule = PyImport_Import(pName);
        if (!pModule) throw std::runtime_error("Failed to import Python module 'ai'.");

        // Load the Python function
        pFunc = PyObject_GetAttrString(pModule, "generateInfo"); //Func Name
        if (!pFunc || !PyCallable_Check(pFunc)) {
            throw std::runtime_error("Failed to load or call Python function 'generateInfo'.");
        }

        // Prepare arguments (type and message)
        pArgs = PyTuple_Pack(2, PyUnicode_FromString(ReturnMyApiKeyString1().c_str()), PyUnicode_FromString(type.c_str()));
        if (!pArgs) throw std::runtime_error("Failed to create arguments tuple.");

        // Call the Python function
        pValue = PyObject_CallObject(pFunc, pArgs);
        if (!pValue) {
            PyErr_Print();
            throw std::runtime_error("Python function call failed.");
        }

        // Convert Python string result to C++ string
        const char* cResult = PyUnicode_AsUTF8(pValue);
        if (!cResult) throw std::runtime_error("Failed to convert Python result to UTF-8 string.");
        result = std::string(cResult);

        // Print the result (optional)
        std::cout << "Python function output: " << result << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Clean up Python objects to prevent memory leaks
    Py_XDECREF(pName);
    Py_XDECREF(pModule);
    Py_XDECREF(pFunc);
    Py_XDECREF(pArgs);
    Py_XDECREF(pValue);

    // Return the result
    return result;
}

std::string callGenerateResponseToQuestion(const std::string& type, const std::string& message) {
    if (!Py_IsInitialized()) {
        Py_Initialize();
    }

    PyObject* pName = nullptr, * pModule = nullptr, * pFunc = nullptr, * pArgs = nullptr, * pValue = nullptr;
    std::string result;

    try {
        // Load the Python module
        pName = PyUnicode_FromString("ai");
        if (!pName) throw std::runtime_error("Failed to convert module name to Python string.");

        pModule = PyImport_Import(pName);
        if (!pModule) throw std::runtime_error("Failed to import Python module 'ai'.");

        // Load the Python function
        pFunc = PyObject_GetAttrString(pModule, "generateResponse"); //Func Name
        if (!pFunc || !PyCallable_Check(pFunc)) {
            throw std::runtime_error("Failed to load or call Python function 'generateResponse'.");
        }

        // Prepare arguments (key, type and message)

        pArgs = PyTuple_Pack(3, PyUnicode_FromString(ReturnMyApiKeyString1().c_str()), PyUnicode_FromString(type.c_str()), PyUnicode_FromString(message.c_str()));
        if (!pArgs) throw std::runtime_error("Failed to create arguments tuple.");

        // Call the Python function
        pValue = PyObject_CallObject(pFunc, pArgs);
        if (!pValue) {
            PyErr_Print();
            throw std::runtime_error("Python function call failed.");
        }

        // Convert Python string result to C++ string
        const char* cResult = PyUnicode_AsUTF8(pValue);
        if (!cResult) throw std::runtime_error("Failed to convert Python result to UTF-8 string.");
        result = std::string(cResult);

        // Print the result (optional)
        std::cout << "Python function output: " << result << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Clean up Python objects to prevent memory leaks
    Py_XDECREF(pName);
    Py_XDECREF(pModule);
    Py_XDECREF(pFunc);
    Py_XDECREF(pArgs);
    Py_XDECREF(pValue);

    // Return the result
    return result;
}


void ExecutePy_FinalizeEx() {
    Py_FinalizeEx();
}