clv = clang++

ALLDEP = tmp/RNNet.o tmp/DictCreate.o tmp/Generator.o tmp/debug.o

ALL:$(ALLDEP)
	$(clv) -o bin/leftdebug $(ALLDEP) -lpthread -std=c++11
	-rm $(ALLDEP)

tmp/RNNet.o:
	$(clv) -o tmp/RNNet.o -c src/RNNet.cpp -std=c++11
tmp/DictCreate.o:
	$(clv) -o tmp/DictCreate.o -c src/DictCreate.cpp -std=c++11
tmp/Generator.o:
	$(clv) -o tmp/Generator.o -c src/Generator.cpp -std=c++11
tmp/debug.o:
	$(clv) -o tmp/debug.o -c src/debug.cpp -std=c++11

.PHONY:clean
clean:
	-rm $(ALLDEP)
