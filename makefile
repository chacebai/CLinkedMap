
ALL:main

main:$(cpp)
	g++ $(cpp) $(files) -o $(exe) -g -fexec-charset=GBK -static -Wall -std=c++11 $(INCLUDE) $(LIB)

.PHONY: clean all
clean:
	# rm *.exe -rf

