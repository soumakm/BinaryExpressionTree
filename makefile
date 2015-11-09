proj4.x: proj4_driver.cpp
	g++ -Wall -pedantic -std=c++11 -g -o proj4.x proj4_driver.cpp

clean:
	rm -f *.o *.x core.*
