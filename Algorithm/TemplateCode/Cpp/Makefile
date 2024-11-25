%.out: %.cpp
	g++ $*.cpp -o $@ -std=c++17 -Wall -g

run-%: %.out
	./$*.out

clean:
	rm -f *.out

.PHONY: clean run-%

# CC = g++
# CC_FLAG = -fno-omit-frame-pointer -g3 -O0 -pipe -Wall -Wextra -Wshadow -Wno-unused-variable -finput-charset=UTF-8 -fexec-charset=UTF-8
# CC_STD = c++17
# CC_ASAN = -fsanitize=address,undefined
# CC_MACRO = -DUNICODE -D_UNICODE -DLOCAL_JUDGE

# %.out: %.cpp
# 	$(CC) $*.cpp -o $@ -std=$(CC_STD) $(CC_FLAG) $(CC_ASAN) $(CC_MACRO)

# test-%.out: %.out %.in.txt %.out.txt
# 	@./$*.out < $*.in.txt > $*.out.txt
# 	@cat $*.out.txt

# clean:
# 	rm *.out

# .PHONY: clean
