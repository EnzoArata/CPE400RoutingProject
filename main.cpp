#include "Router.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <set>



using namespace std;
int finalTime = 0;
vector<Router*> networkMesh;



vector<pair <int, int> > shortestPath(int, int, vector<vector<pair<int, int> >>);

int main(void){

	int packetSize = 512;
	int bufferSize = 10; 
	
	double bandwidth = 1500000;  //network bandwidth
	double packetLoss = .05;  //loss chance for a packet over the network
	double processingDelay = .05; 
	double transmissionDelay = 0;//.05; 
	double propigationDelay = 0;//.05; 
	double distanceDelay = 0;
	double totalDelay = 0; 
	int packetLosses = 0;
	int source;
	int destination;
	vector<vector<pair<int, int>> > connectionDistances;
	string input;


	int numNetworks = 16;

	for (int i=0; i < numNetworks; i++){
		Router* tempRouter = new Router(i, //routerID
						bufferSize, //buffers
						transmissionDelay, //transmission Delay
						propigationDelay, //propigation Delay
						processingDelay, //processing Delay
						bandwidth, //bandwidth
						packetLoss //loss Chance
						);
		networkMesh.push_back(tempRouter);
	}

	
	networkMesh[0]->addConnection(networkMesh[1], 1);
	networkMesh[1]->addConnection(networkMesh[0], 1);
	networkMesh[1]->addConnection(networkMesh[2], 2);
	networkMesh[1]->addConnection(networkMesh[4], 4);
	networkMesh[2]->addConnection(networkMesh[1], 1);
	networkMesh[2]->addConnection(networkMesh[3], 3);
	networkMesh[2]->addConnection(networkMesh[5], 3);
	networkMesh[3]->addConnection(networkMesh[2], 2);
	networkMesh[4]->addConnection(networkMesh[1], 1);
	networkMesh[4]->addConnection(networkMesh[5], 3);
	networkMesh[4]->addConnection(networkMesh[6], 5);
	networkMesh[5]->addConnection(networkMesh[2], 4);
	networkMesh[5]->addConnection(networkMesh[4], 10);
	networkMesh[5]->addConnection(networkMesh[7], 10);
	networkMesh[5]->addConnection(networkMesh[8], 11);
	networkMesh[6]->addConnection(networkMesh[4], 9);
	networkMesh[7]->addConnection(networkMesh[5], 8);
	networkMesh[7]->addConnection(networkMesh[9], 9);
	networkMesh[8]->addConnection(networkMesh[5], 7);
	networkMesh[8]->addConnection(networkMesh[9], 9);
	networkMesh[8]->addConnection(networkMesh[10], 15);
	networkMesh[9]->addConnection(networkMesh[7], 6);
	networkMesh[9]->addConnection(networkMesh[8], 7);
	networkMesh[10]->addConnection(networkMesh[8], 5);
	networkMesh[10]->addConnection(networkMesh[11], 6);
	networkMesh[11]->addConnection(networkMesh[10], 5);
	networkMesh[11]->addConnection(networkMesh[12], 12);
	networkMesh[11]->addConnection(networkMesh[13], 12);
	networkMesh[12]->addConnection(networkMesh[11], 4);
	networkMesh[12]->addConnection(networkMesh[13], 11);
	networkMesh[12]->addConnection(networkMesh[14], 11);
	networkMesh[13]->addConnection(networkMesh[11], 3);
	networkMesh[13]->addConnection(networkMesh[12], 3);
	networkMesh[13]->addConnection(networkMesh[14], 3);
	networkMesh[13]->addConnection(networkMesh[15], 3);
	networkMesh[14]->addConnection(networkMesh[12], 6);
	networkMesh[14]->addConnection(networkMesh[13], 9);
	networkMesh[15]->addConnection(networkMesh[13], 8);


	for (int i = 0; i < 16; i++)
	{
		int totalConnections = networkMesh[i]->connections.size();
		connectionDistances.push_back(std::vector<pair<int, int> >());
		for (int j = 0; j < totalConnections; j++)
		{
			distanceDelay = networkMesh[i]->connections[j].second;//networkMesh[i].travelTime(networkMesh[i].connections[j].first);  //Calculates the distance between router i and its connections
			connectionDistances[i].push_back(make_pair(networkMesh[i]->connections[j].first->getID(), distanceDelay));
		}
	}

	cout << "In order to simulate the routing algorithm,we have created a mesh network" << endl;
	cout << "The network is configured exactly like the example given in the project ideas PDF" << endl;
	cout << "The network has a total of 16 nodes, with different physical links." << endl;
	cout << "By defualt the routers all have the same information" << endl;
	//std::cout << "Would you like to change defualt settings for the routers? y/n: ";
	cout << "Enter a source router: " << endl;
	cin >> source;
	cout << "Enter a destination router: " << endl;
	cin >> destination;
	vector<pair <int, int> > pathInfo = shortestPath(source, destination, connectionDistances);
	int jumpCount = 0;
	int previousRouter = pathInfo[destination].second;
	while (previousRouter!=-1)
	{
		jumpCount++;
		cout << previousRouter << " ";
		previousRouter =pathInfo[previousRouter].second;
	}
	
	cout << endl ;

	if(input!="n")
	{
		
		/*std::cout << "Enter packet size: ";
		std::cin >> packetSize;
		std::cout << "Enter bandwidth: ";
		std::cin >> bandwidth;
		std::cout << "Enter packet loss chance ";
		std::cin >> randomPacketLoss;
		std::cout << "Enter time to process a request";
		std::cin >> processingDelay;
		std::cout << "Enter buffer size for routers ";
		std::cin >> bufferSize;
		input = "";*/
	}

	return 0;

}	

struct Node{
	double dist;
	bool vis;
  	Node(double d, bool v):
    	dist(d), vis(v)
  	{}
};

vector<pair <int, int> > shortestPath(int startID, int dest, vector< vector<pair<int, int> > >connections)
{
	set<pair<int, int> > finalRoute;
	int cursor = 0;
	//int dijkstra(const vector< vector<edge> > &graph, int source, int dest) {
	vector<pair <int, int> >min_distance;
	for (int i =0; i<connections.size(); i++){
		min_distance.push_back(make_pair(INT_MAX, -1));
	}
    min_distance[ startID ].first = 0;
    finalRoute.insert( {0,startID} );
     
    while (!finalRoute.empty()) {
        int where = finalRoute.begin()->second;
        if (where == dest)
        {
        	for(int i=0;i<min_distance.size();i++)
        	{
        		 cout << "distance to " << i << ": "<<min_distance[i].first << " previous node " << min_distance[i].second << endl;
        	}
        	
       		return min_distance; 	
        } 
        finalRoute.erase( finalRoute.begin() );
        for (auto ed : connections[where]) 
        {
        	
            if (min_distance[ed.first].first > min_distance[where].first + ed.second) {
            	
                finalRoute.erase( { min_distance[ed.first].first, ed.first } );
                min_distance[ed.first].first = min_distance[where].first + ed.second;
                min_distance[ed.first].second = where;
                
                finalRoute.insert( { min_distance[ed.first].first, ed.first } );
            }
        }

    }
 
    

	return min_distance;
}
