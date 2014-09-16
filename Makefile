all:
	clang++ warcer.cpp -o warcer -std=gnu++11 -Wall -Wpedantic -lboost_system -lboost_filesystem -lboost_regex
debug:
	clang++ warcer.cpp -o warcer -std=gnu++11 -Wall -Wpedantic -lboost_system -lboost_filesystem -lboost_regex -g
gnu:
	g++ warcer.cpp -o warcer -std=gnu++11 -Wall -Wpedantic -lboost_system -lboost_filesystem -lboost_regex
clean:
	rm -rf *o warcer amp-off.com istwulffnochimamt.de gnu.org www.dadadata.de
