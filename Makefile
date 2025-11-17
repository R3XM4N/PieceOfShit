all:
	g++ -o app main.cpp source/ncurses.cpp source/network.cpp source/ui.cpp source/datahandle.cpp -lncurses 
run: all
	./app