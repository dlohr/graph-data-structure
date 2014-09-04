//////////////////////////////////////////////////
/// \file   graph.cpp
/// \author Dillon Lohr
/// \date   3 September 2014
/// \brief  CS-1428 Exam
///
/// Finds strongly connected components of a directed graph.
//////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

class Node {
  public:
    Node( unsigned int id ) {
      this->id = id;
      data = "";
      isStacked = false;
      index = -1;
      lowlink = -1;
    }
    
    void addConnection( Node* node ) {
      connections.push_back( node );
    }

    void setData( std::string data ) {
      this->data = data;
    }

    bool isStacked;
    int index;
    int lowlink;

    std::list< Node* > connections;

    unsigned int id;
    std::string data;
};

class Graph {
  public:
    Graph( std::string filename, std::string outfile ) {
      std::ofstream fout( outfile, std::ios::ate );
      fout.close();
      this->outfile = outfile;

      std::ifstream fin( filename );
      // Get number of nodes
      unsigned int nodeCount;
      fin >> nodeCount;
      fin.ignore( 9999, '\n' );
      // Fill Node vector with enough dummy nodes
      for( unsigned int id = 0; id < nodeCount; ++id )
        nodes.push_back( Node( id ) );

      std::string chunk = "";
      unsigned int id = 0;
      while( true ) {
        // Get ID
        std::getline( fin, chunk, ':' );
        if( chunk.empty() ) {
          break;      // End of file
        }
        id = std::stoi( chunk );
        // Get data
        std::getline( fin, chunk, ':' );
        nodes.at( id ).setData( chunk );
        // Get connections
        std::getline( fin, chunk );
        if( chunk.empty() ) {
          continue;   // No connections
        }
        std::string delim = ",";
        size_t start = 0;
        size_t end = chunk.find( delim );
        while( end != std::string::npos ) {
          unsigned int connection =
              std::stoi( chunk.substr( start, end - start ) );
          nodes.at( id ).addConnection( &nodes.at( connection ) );
          start = end + delim.length();
          end = chunk.find( delim, start );
        }
        unsigned int connection =
              std::stoi( chunk.substr( start, end ) );
        nodes.at( id ).addConnection( &nodes.at( connection ) );
      }

      fin.close();
    }

    std::string outfile;
    std::vector< Node > nodes;
};

class StronglyConnectedComponent {
  public:
    StronglyConnectedComponent() { }

    void addConnection( Node* n ) {
      connections_.push_back( n );
    }

    void print() {
      std::cout << "[Strongly Connected Components]" << std::endl;
      for( Node* n : connections_ ) {
        std::cout << "    Node #" << n->id << "\n"
                  << "    Data: " << n->data << "\n"
                  << "    Connections:";
        for( Node* c : n->connections ) {
          std::cout << " " << c->id;
        }
        std::cout << std::endl;
      }
    }

    void print( std::string filename ) {
      std::ofstream fout( filename, std::ios::app );

      fout << "[Strongly Connected Components]" << std::endl;
      for( Node* n : connections_ ) {
        fout << "    Node #" << n->id << "\n"
             << "    Data: " << n->data << "\n"
             << "    Connections:";
        for( Node* c : n->connections ) {
          fout << " " << c->id;
        }
        fout << std::endl;
      }

      fout.close();
    }

  private:
    std::vector< Node* > connections_;
};



void strongConnect( Node* node, int index,
                    std::stack< Node* >& stack,
                    std::string& outfile ) {
  node->index = index;
  node->lowlink = index++;
  node->isStacked = true;
  stack.push( node );

  for( Node* n : node->connections ) {
    if( n->index == -1 ) {
      strongConnect( n, index, stack, outfile );
      node->lowlink = std::min( node->lowlink, n->lowlink );
    } else if( n->isStacked ) {
      node->lowlink = std::min( node->lowlink, n->index );
    }
  }

  if( node->lowlink == node->index ) {
    StronglyConnectedComponent scc;

    while( true ) {
      Node* n = stack.top();
      stack.pop();
      n->isStacked = false;
      scc.addConnection( n );

      if( n->id == node->id )
        break;
    }

    scc.print();
    scc.print( outfile );
  }
}



void tarjan( Graph& g ) {
  int index = 0;
  std::stack< Node* > stack;

  for( Node& node : g.nodes ) {
    if( node.index == -1 ) {
      strongConnect( &node, index, stack, g.outfile );
    }
  }
}



int main() {
  Graph g( "populated-graph.txt",
           "strongly-connected-components.txt" );

  tarjan( g );
  
  return 0;
}
