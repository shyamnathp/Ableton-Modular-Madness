First of all, thank you so much. I really had fun doing this task.

Folder Descritpions:
UML Diagrams:
	Class Diagram, Acitivity and Sequence Diagrams, Unit Test Diagram. 
	The unit test diagram shows a representation of the cases in the unit tests.
		Cases Considered:
		1. Example in sheet (simple workflow)
		2. Multiple Starting Modules
		3. Multiple Output Modules
		4. Middle Modules Split (multiple parallel middle processing).

Ouputs: Screenshots of the outputs using the same cases as unit test i.e outputs from the actual systems.
 	Also find the output for successfull run of unit tests.

Applications: .exe files for both the actual project and unit test.


FOR RUNNING:

Run the actual project: \Ableton_Project\Applications\Ableton_Project.exe
Run the unit test: \Ableton_Project\Applications\Ableton_Test.exe

BUILD INSTRUCTION:
I assume visual studio is used in Ableton. Hence the following build instructions:

Ableton_Project:

1. Load the .vcxproj file using Visual Studio. (\Ableton_Project\Ableton_Project\Ableton_Project.vcxproj)
2. C/C++  -> Additonal Include Directories
   Add location of Ableton_Project : \Ableton_Project\Ableton_Project\
3. Run the project

Ableton_Test:

//This is the unit test project for Ableton_Project
1. Load the .vcxproj file unsing Visual Studio. (\Ableton_Project\Ableton_Test\Ableton_Test.vcxproj)
2. Using Nu package_manager install google mock (google test is already a part of VS2017)
   instruction here : https://www.nuget.org/packages/gmock/
3. Project Properties -> C/C++ -> Additional Include Directinos
   Add location of Ableton_Project : \Ableton_Project\Ableton_Project\
4. Project Properties -> Linker -> Addtion Dependencies
   Add Project Properties -> \Ableton_Project\Ableton_Test\Debug\Ableton_Project.lib
5. Test->Run->AllTests