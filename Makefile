build: src/%.cpp
	cmake --build build
run:
	cmake --build build && ./build/ogre_game
src/%.cpp:
	
