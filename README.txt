// Eli Simmonds
// Project 4

Everything appears to work in my project.

There is an output statement in DepGraph::isCyclic( GraphNode *p ) 
that prints which files are a part of the cycle. It is the extra credit assignment.
If there are no cycles it will specifically say there are no cycles.

Testing:
Test the file by typing make
run ./make testMake to test the timestamps and recompilation
run ./make testCycle to test for circualar dependencies

The output should just be the commands that are run to recompile files with old timestamps
It MUST be compiled with c++11 because of nullptr's. Otherwise it will not compile.
