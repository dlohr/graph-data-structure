all: populate graph

.PHONY: populate

populate: populate.cpp
	g++ -std=c++11 populate.cpp -o populate

.PHONY: graph

graph: graph.cpp
	g++ -std=c++11 graph.cpp -o graph

.PHONY: clean

clean:
	rm -rf populate graph

.PHONY: clean-all

clean-all: clean
	rm -rf populated-graph.txt strongly-connected-components.txt
