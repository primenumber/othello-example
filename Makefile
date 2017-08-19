OBJS=main.o board.o eval.o search.o

othello: $(OBJS)
	g++ -o $@ -Og -g -Wall -Wextra $^

%.o: %.cpp
	g++ -c -o $@ -Og -g -Wall -Wextra $<
