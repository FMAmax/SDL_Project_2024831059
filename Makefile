all:
	g++ task101.cpp -o task101.exe -I src/include -L src/lib -lSDL3 -mwindows -Wall -g
	g++ task102.cpp -o task102.exe -I src/include -L src/lib -lSDL3 -mwindows -Wall -g
# 	g++ -I src/include -L src/lib -o main main.cpp -lSDL3
# 	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL3main -lSDL3
# 	g++ main.cpp -o my_sdl_app -I f:/2024831059/src/include -L f:/2024831059/src/lib -lSDL3 -mwindows
