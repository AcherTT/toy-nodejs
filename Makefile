run: 
	g++ ./myNode.cc ./src/utils/*.cc -o Node -Iinclude/v8 -Iinclude/utils -ldl -lv8_monolith -lv8_libbase -lv8_libplatform -Llib -pthread -std=c++17 -DV8_COMPRESS_POINTERS
