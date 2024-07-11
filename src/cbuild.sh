g++ -o main.o -c main.cpp -lsqlite3
g++ -o data_man.o -c data_man.cpp -lsqlite3
g++ -o main main.o data_man.o -lsqlite3
./main