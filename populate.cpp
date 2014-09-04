//////////////////////////////////////////////////
/// \file populate.cpp
/// \author Dillon Lohr
/// \date 3 September 2014
/// \brief CS-1428 Exam
///
/// Generates random information to fill a directed graph. Coincides
/// with graph.cpp.
//////////////////////////////////////////////////
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>

// Things that could be added:
// - Exception handling
//   + Regarding argc/argv
//   + Whether the file could be opened
int main( int argc, char* argv[] ) {
  // Seed the random number generator.
  using time = std::chrono::system_clock;
  unsigned int seed = time::now().time_since_epoch().count();
  std::default_random_engine engine;
  engine.seed( seed );

  std::ofstream fout;
  fout.open( "populated-graph.txt" );

  // Find the first argv that contains the user's input.
  unsigned int index = 0;
  for( unsigned int i = 0; i < static_cast< unsigned int >( argc );
       ++i ) {
    if( std::isdigit( argv[ i ][ 0 ] ) ) {
      if( i == 0 ) {
        index = 1;
      } else {
        index = i;
      }

      break;
    }
  }     // If index is 0 at this point, there are no arguments.

  // Set const values based on user input.
  const unsigned int NUM_ENTRIES = [ & ] {
    unsigned int entries = 100;
    
    if( index != 0 &&
        static_cast< unsigned int >( argc ) >= index + 1 ) {
      entries = std::atoi( argv[ index++ ] );
    } else {
      std::cout << "No input for NUM_ENTRIES     -> default: 100"
                << std::endl;
    }

    return entries;
  } ();

  const unsigned int MAX_CONNECTIONS = [ & ] {
    unsigned int connections = 10;
    
    if( index != 0 &&
        static_cast< unsigned int >( argc ) >= index + 1 ) {
      connections = std::atoi( argv[ index++ ] );
    } else {
      std::cout << "No input for MAX_CONNECTIONS -> default:  10"
                << std::endl;
    }

    return connections;
  } ();

  const unsigned int DATA_SIZE = [ & ] {
    unsigned int size = 10;
    
    if( index != 0 &&
        static_cast< unsigned int >( argc ) >= index + 1 ) {
      size = std::atoi( argv[ index++ ] );
    } else {
      std::cout << "No input for DATA_SIZE       -> default:  10"
                << std::endl;
    }

    return size;
  } ();

  // Begin writing to the file.
  fout << NUM_ENTRIES << std::endl;

  for( unsigned int i = 0; i < NUM_ENTRIES; ++i ) {
    fout << i << ":";
    
    // Generate random "data" string
    for( unsigned int j = 0; j < DATA_SIZE; ++j ) {
      std::uniform_int_distribution< char > randChar( 'A', 'Z' );
      fout << randChar( engine );
    }
    fout << ":";
    
    // Generate random connections.
    std::uniform_int_distribution< unsigned int > randInt( 0, 1 );
    std::uniform_int_distribution< unsigned int > randId( 0,
                                                          NUM_ENTRIES - 1 );
    unsigned int connections[ MAX_CONNECTIONS ];
    unsigned int count = 0;
    bool firstConnection = true;
    for( unsigned int k = 0; k < MAX_CONNECTIONS; ++k ) {
      if( randInt( engine ) == 1 ) {
        if( firstConnection ) {
          connections[ count ] = randId( engine );
          fout << connections[ count ];
          firstConnection = false;
          ++count;
        } else {
          // Make sure the generated connection is unique.
          bool matched;
          do {
            matched = false;
            connections[ count ] = randId( engine );
            for( unsigned int l = 0; l < count - 1; ++l ) {
              if( connections[ l ] == connections[ count ] ) {
                matched = true;
                break;
              }
            }
          } while( matched );
          fout << "," << connections[ count ];
          ++count;
        }
      }
    }

    fout << std::endl;
  }

  fout.close();

  return EXIT_SUCCESS;
}
