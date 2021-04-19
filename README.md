Author: Jacob Factora, Andres Maturin
Username: cssc3746, cssc3716
Class: CS530-01, Spring2021
Assignment: Project #2
Filename: README

File Manifest:
	led.cpp
	MAKEFILE
	README
	P2sampleAdder.txt
	P2sampleWriter.txt

Compile Instructions:
	Use "make" to compile the program
	
Operationg Instructions:
	Use led <filename> to run the program.
	Multiple files is supported = led <filename> <filename>
	
Design decisions:
	- The program reads the text fil
	- Then reads character by character except for commas.
	- Once the file is "clean" then we start building the ESTAB
	- Then once the ESTAB has been created we produce the Objectfile
	  
Extra Features:
	- Displays the ESTAB and Object file to the console
	
Deficiencies/Bugs:
	- lack in efficiency to conver the string to an int and then to a hexadecimal
	- couldn't figure out how to detect correct memory mapping
	
Lessons Learned:
	- Taking multiple CS classes with large project that are start and are due in the same week is a struggle
	- Time efficiency and management needs to improve
	- Work flow needs to stay consistent with the topic at hand
	- C++ is very interesting to work with