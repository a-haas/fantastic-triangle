CC = g++

drawtri : main.o mainframe.o dialogs.o versiondialog.o thicknessdialog.o colordialog.o triangledialog.o propertiesdialog.o openglcanvas.o triangle.o
	$(CC) -o drawtri main.o mainframe.o dialogs.o versiondialog.o thicknessdialog.o colordialog.o triangledialog.o propertiesdialog.o openglcanvas.o triangle.o `wx-config --libs --gl-libs` -lGL -lglut 

main.o : main.cpp 
	$(CC) `wx-config --cxxflags --gl-libs` -c main.cpp -o main.o

mainframe.o : mainframe.cpp
	$(CC) `wx-config --cxxflags --gl-libs` -c mainframe.cpp -o mainframe.o 

dialogs.o : dialogs.cpp
	$(CC) `wx-config --cxxflags` -c dialogs.cpp -o dialogs.o 

versiondialog.o : versiondialog.cpp
	$(CC) `wx-config --cxxflags` -c versiondialog.cpp -o versiondialog.o

thicknessdialog.o : thicknessdialog.cpp
	$(CC) `wx-config --cxxflags` -c thicknessdialog.cpp -o thicknessdialog.o

colordialog.o : colordialog.cpp
	$(CC) `wx-config --cxxflags` -c colordialog.cpp -o colordialog.o

triangledialog.o : triangledialog.cpp
	$(CC) `wx-config --cxxflags` -c triangledialog.cpp -o triangledialog.o

propertiesdialog.o : propertiesdialog.cpp
	$(CC) `wx-config --cxxflags` -c propertiesdialog.cpp -o propertiesdialog.o

openglcanvas.o : openglcanvas.cpp
	$(CC) `wx-config --cxxflags` -c openglcanvas.cpp -o openglcanvas.o -Wno-deprecated-declarations

triangle.o : triangle.cpp
	$(CC) `wx-config --cxxflags` -c triangle.cpp -o triangle.o

clean : 
	rm -f *.o drawtri 
