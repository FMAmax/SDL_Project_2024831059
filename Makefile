all:
	g++ task101.cpp -o task101.exe -I src/include -L src/lib -lSDL3 -mwindows -Wall -g
	g++ task102.cpp -o task102.exe -I src/include -L src/lib -lSDL3 -mwindows -Wall -g
	g++ task103.cpp -o task103.exe -I src/include -L src/lib -lSDL3 -mwindows -Wall -g

clean:
	rm -f task101.exe task102.exe task103.exe
