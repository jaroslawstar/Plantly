Plantly

C++ aplication that allows users to easily take care of their plants, and more.

The app Plantly is developed by Jarosław Szekuła for the subject of Projekt C++ on Uniwersytet Wrocławski. This is NOT the final look or the final platform. This look was only created to present the idea and show what it is about.

The app is going to be developed for Windows and MacOS, using programming language C++, with small design changes (to make it usable on horizontal screens).

It is NO estimated date for final developed version for smartphones, yet.

Prototype: https://www.figma.com/proto/m4OTrDYCwLpU7Zen86sQkR/Untitled?node-id=1-325&node-type=symbol&t=y2W5PeZ82rFQpfOn-0&scaling=scale-down&content-scaling=responsive&page-id=0%3A1&starting-point-node-id=1%3A325


!!! This app requires Python v3.9.13 and python modules openai v1.59.9, pydantic v1.10.2 !!!


Installation:

Method #1 - Compilation:
	This repository is complete bulk with all you need.
 1. Clone the repo (Win)
 2. Add Python3.9.13 as a main python: Copy directory to User\AppData\Local\Programs\Python (add it to the Windows PATH). This directory alredy has all necessary py moduls.
 3. In Visual Studio (2019 at best) open solution file.
 4. If you possess your own OpenAI API key, in separate cpp file, write a simple function to return the string. Not forget to #include "ai.h". Otherwise, these functions won't be available.
 5. Compile solution.
 6. In order to have clean Windows app, while compiling put under comment the "int main()" line and uncomment the one above with windows requirements. Copy compiled "release" folder ($SolutionPath$/x64/Release) to another directory, into "release" folder copy and paste resources directory.

Method #2 - Download:
	1. Ask repo owner to drop you a link :)
