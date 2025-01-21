#include <Python.h>
#include <iostream>
#include <string>


int callAddNumbers(int a, int b) {
    int result = -1; // Default result in case of error

    // Initialize the Python interpreter
    Py_Initialize();

    // Import the Python module
    PyObject* pModule = PyImport_ImportModule("ai");
    if (pModule != nullptr) {
        // Get the Python function add_numbers
        PyObject* pFunc = PyObject_GetAttrString(pModule, "add_numbers");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Create arguments for the function
            PyObject* pArgs = PyTuple_Pack(2, PyLong_FromLong(a), PyLong_FromLong(b));

            // Call the Python function
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue != nullptr) {
                // Convert the Python result to C++ int
                result = PyLong_AsLong(pValue);
                Py_DECREF(pValue);
            }
            else {
                PyErr_Print();
                std::cerr << "Error calling add_numbers()" << std::endl;
            }
            Py_DECREF(pArgs);
        }
        else {
            PyErr_Print();
            std::cerr << "add_numbers() function not found or not callable" << std::endl;
        }
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        std::cerr << "Failed to load Python module 'ai'" << std::endl;
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return result;
}

std::string callGeneratePlantInfo(const std::string& subject) {
    std::string result;

    // Initialize the Python interpreter
    Py_Initialize();

    // Add the directory of 'helper.py' to sys.path
    PyObject* sysPath = PySys_GetObject("path"); // Borrowed reference
    PyList_Append(sysPath, PyUnicode_FromString("."));

    // Import the Python module
    PyObject* pModule = PyImport_ImportModule("ai");
    if (pModule != nullptr) {
        // Get the Python function generate_response
        PyObject* pFunc = PyObject_GetAttrString(pModule, "generateInfo");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Create arguments for the function
            PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(subject.c_str()));

            // Call the Python function
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue != nullptr) {
                // Convert the Python result to a C++ string
                result = PyUnicode_AsUTF8(pValue);
                Py_DECREF(pValue);
            }
            else {
                PyErr_Print();
                std::cerr << "Error calling generateInfo()" << std::endl;
            }
            Py_DECREF(pArgs);
        }
        else {
            PyErr_Print();
            std::cerr << "generateInfo() function not found or not callable" << std::endl;
        }
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        std::cerr << "Failed to load Python module 'ai'" << std::endl;
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return result;
}

std::string callGenerateHello(const std::string& subject) {
    std::string result;

    // Initialize the Python interpreter
    Py_Initialize();

    // Add the directory of 'helper.py' to sys.path
    PyObject* sysPath = PySys_GetObject("path"); // Borrowed reference
    PyList_Append(sysPath, PyUnicode_FromString("."));

    // Import the Python module
    PyObject* pModule = PyImport_ImportModule("ai");
    if (pModule != nullptr) {
        // Get the Python function generate_response
        PyObject* pFunc = PyObject_GetAttrString(pModule, "hello");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Create arguments for the function
            PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(subject.c_str()));

            // Call the Python function
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue != nullptr) {
                // Convert the Python result to a C++ string
                result = PyUnicode_AsUTF8(pValue);
                Py_DECREF(pValue);
            }
            else {
                PyErr_Print();
                std::cerr << "Error calling generateInfo()" << std::endl;
            }
            Py_DECREF(pArgs);
        }
        else {
            PyErr_Print();
            std::cerr << "generateInfo() function not found or not callable" << std::endl;
        }
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        std::cerr << "Failed to load Python module 'ai'" << std::endl;
    }

    // Finalize the Python interpreter
    Py_Finalize();

    return result;
}