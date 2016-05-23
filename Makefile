FLAGS = -std=c++11 -Wall -Wextra


make.x: MakeTree.o Reader.o DepGraph.o GraphNode.o TreeNode.o soln_main.o systemInterface.o
	g++ $(FLAGS) -ggdb MakeTree.o Reader.o DepGraph.o GraphNode.o TreeNode.o soln_main.o systemInterface.o -o make.x

MakeTree.o: MakeTree.cpp MakeTree.hpp TreeNode.hpp GraphNode.hpp TreeNode.hpp
	g++ $(FLAGS) -ggdb MakeTree.cpp -o MakeTree.o -c

Reader.o: Reader.cpp Reader.hpp Token.hpp
	g++ $(FLAGS) -ggdb Reader.cpp -o Reader.o -c

DepGraph.o: DepGraph.cpp DepGraph.hpp TreeNode.hpp systemInterface.hpp
	g++ $(FLAGS) -ggdb DepGraph.cpp -o DepGraph.o -c

GraphNode.o: GraphNode.cpp GraphNode.hpp Token.hpp Reader.hpp
	g++ $(FLAGS) -ggdb GraphNode.cpp -o GraphNode.o -c

TreeNode.o: TreeNode.cpp TreeNode.hpp GraphNode.hpp
	g++ $(FLAGS) -ggdb TreeNode.cpp -o TreeNode.o -c

soln_main.o: soln_main.cpp DepGraph.hpp
	g++ $(FLAGS) -ggdb soln_main.cpp -o soln_main.o -c

systemInterface.o: systemInterface.hpp systemInterface.cpp
	g++ $(FLAGS) -c systemInterface.cpp -o systemInterface.o

clean:
	rm -f *.o make.x *~
