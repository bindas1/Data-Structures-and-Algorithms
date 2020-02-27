#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

#define INF 3000
#define FILE "matrix.txt"

// integer pair for pq
typedef std::pair<int, int> iPair; 

// handles adding to our priority queue and path
void check_distance(int u, int v, std::vector<int> & distance, std::vector<int> & prev, std::vector<iPair > & adj, std::priority_queue< iPair, std::vector<iPair> , std::greater<iPair> > & pq, std::vector<bool> & visited);

// shortest path algorithm
void dijkstra();

int main() {
  dijkstra();
  return 0;
}

void dijkstra()
{
  int value;
  // if 1 in result we visit the vertex
  std::vector<int> results(36, 0);
  // distance, location in tab
  std::priority_queue< iPair, std::vector<iPair> , std::greater<iPair> > pq;
  std::vector<iPair > adj;
  // updates if vertex has already been visited
  std::vector<bool> visited(36, false);
  // initially infinity, distance to the point from beggining
  std::vector<int> distance(36, INF);
  // remembers previous visited vertex 
  std::vector<int> prev(36, -1);

  std::ifstream inFile;
  inFile.open(FILE);

  for(int i = 0; i < 6; i++) {
      for(int j=0; j < 6; j++) {
        inFile >> value;
        adj.push_back(std::make_pair(i*6+j, value));
      }
  }
  pq.push(std::make_pair(0,0));
  distance[0] = 0;
  visited[0] = true;

  // for storing minimal value from pq
  int u = 0;

  while (!pq.empty() && u != 35) 
    { 
        // The first vertex in pair is the minimum distance 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        u = pq.top().second; 
        pq.pop();

        // if it's not 6 x 6 matrix just change 6 to c where c is c x c matrix
        // not first column 
        if(u % 6 != 0) 
        {
          int v = u - 1; 
          check_distance(u, v, distance, prev, adj, pq, visited);
        }

        // not last column
        if(u % 6 != 5)
        {
          int v = u + 1; 
          check_distance(u, v, distance, prev, adj, pq, visited);
        }

        // not first row
        if(u / 6 != 0)
        {
          int v = u - 6; 
          check_distance(u, v, distance, prev, adj, pq, visited);
        }

        // not last row
        if(u / 6 != 5)
        {
          int v = u + 6; 
          check_distance(u, v, distance, prev, adj, pq, visited);
        }
    } 
  
  // find all vertices from our path
  int k = 35;
  while(k != 0)
  {
    results[k] = 1;
    k = prev[k];
  }
  results[0] = 1;

  // print the matrix
  for(int i = 0; i < 6; i++) 
  {
      for(int j=0; j < 6; j++) 
      {
        std::cout << adj[i*6+j].second << " ";
      }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // print the path
  for(int i = 0; i < 6; i++) 
  {
      for(int j=0; j < 6; j++) 
      {
        if(results[i*6+j] != 0)
          std::cout << adj[i*6+j].second << " ";
        else
          std::cout << "  ";
      }
    std::cout << std::endl;
  }
}

void check_distance(int u, int v, std::vector<int> & distance, std::vector<int> & prev, std::vector<iPair > & adj, std::priority_queue< iPair, std::vector<iPair> , std::greater<iPair> > & pq, std::vector<bool> & visited)
{
  // check whether the vertex has already been visited
  if(!visited[v])
  {
    int weight = adj[v].second; 
    //  If there is shorted path to v through u. 
    if (distance[v] > distance[u] + weight) 
    { 
        // Updating distance of v 
        distance[v] = distance[u] + weight; 
        pq.push(std::make_pair(distance[v], v));
        prev[v] = u;
        visited[v] = true;
    } 
  }
}