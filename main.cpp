#include "Router.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <set>
#include <time.h> 
#include <stdio.h> 




double finalTime = 0;
vector<Router*> networkMesh;
int destination;



vector<pair <int, int> > shortestPath(int, int, vector<vector<pair<int, int> >>);
void printPath(vector<int> nodePath);

int main(void){

	int packetSize = 512;
	int bufferSize = 10; 
	
	double bandwidth = 1000;  //network bandwidth
	double packetLoss = .05;  //loss chance for a packet over the network
	double processingDelay = .05; 
	double transmissionDelay = 0.05; 
	double propigationDelay = 1; 
	double distanceDelay = 0;
	double totalDelay = 0; 
	int packetLosses = 0;
	int numPackets = 1;
	int source;
	
	vector<vector<pair<int, int>> > connectionDistances;
	string input;


	int numNetworks = 16;

	std::cout << "In order to simulate the routing algorithm,we have created a mesh network" << std::endl;
	std::cout << "The network is configured exactly like the example given in the project ideas PDF" << std::endl;
	std::cout << "The network has a total of 16 nodes, with different physical links." << std::endl;
	std::cout << "By defualt the routers all have the same information" << std::endl;

	std::cout << "Would you like to change defualt settings for the packet? y/n: ";
	cin >> input;
	//Input for packet settings
	if(input!="n")
	{
		std::cout << "Enter number of packet: ";
		cin >> numPackets;
		std::cout << "Enter packet size: ";
		cin >> packetSize;
		std::cout << "Enter packet loss chance: ";
		cin >> packetLoss;
	}

	std::cout << "Would you like to change defualt settings for the routers? y/n: ";
	cin >> input;

	//Input for router settings
	if(input!="n")
	{

		std::cout << "Enter bandwidth: ";
		cin >> bandwidth;
		std::cout << "Enter time to process a request: ";
		cin >> processingDelay;
		std::cout << "Enter buffer size for routers: ";
		cin >> bufferSize;
		input = "";
	}
	//Input for source and destination router
	std::cout << "Enter a source router: ";
	cin >> source;
	std::cout << "Enter a destination router: ";
	cin >> destination;
	//Creation of routers
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

	//Creating network mesh
	networkMesh[0]->addConnection(networkMesh[1], 1);
	networkMesh[1]->addConnection(networkMesh[0], 1);
	networkMesh[1]->addConnection(networkMesh[2], 2);
	networkMesh[1]->addConnection(networkMesh[4], 4);
	networkMesh[2]->addConnection(networkMesh[1], 2);
	networkMesh[2]->addConnection(networkMesh[3], 3);
	networkMesh[2]->addConnection(networkMesh[5], 3);
	networkMesh[3]->addConnection(networkMesh[2], 3);
	networkMesh[4]->addConnection(networkMesh[1], 4);
	networkMesh[4]->addConnection(networkMesh[5], 3);
	networkMesh[4]->addConnection(networkMesh[6], 5);
	networkMesh[5]->addConnection(networkMesh[2], 3);
	networkMesh[5]->addConnection(networkMesh[4], 3);
	networkMesh[5]->addConnection(networkMesh[7], 10);
	networkMesh[5]->addConnection(networkMesh[8], 11);
	networkMesh[6]->addConnection(networkMesh[4], 5);
	networkMesh[7]->addConnection(networkMesh[5], 10);
	networkMesh[7]->addConnection(networkMesh[9], 9);
	networkMesh[8]->addConnection(networkMesh[5], 11);
	networkMesh[8]->addConnection(networkMesh[9], 9);
	networkMesh[8]->addConnection(networkMesh[10], 15);
	networkMesh[9]->addConnection(networkMesh[7], 6);
	networkMesh[9]->addConnection(networkMesh[8], 7);
	networkMesh[10]->addConnection(networkMesh[8], 15);
	networkMesh[10]->addConnection(networkMesh[11], 6);
	networkMesh[11]->addConnection(networkMesh[10], 6);
	networkMesh[11]->addConnection(networkMesh[12], 12);
	networkMesh[11]->addConnection(networkMesh[13], 12);
	networkMesh[12]->addConnection(networkMesh[11], 12);
	networkMesh[12]->addConnection(networkMesh[13], 11);
	networkMesh[12]->addConnection(networkMesh[14], 3);
	networkMesh[13]->addConnection(networkMesh[11], 12);
	networkMesh[13]->addConnection(networkMesh[12], 11);
	networkMesh[13]->addConnection(networkMesh[14], 3);
	networkMesh[13]->addConnection(networkMesh[15], 3);
	networkMesh[14]->addConnection(networkMesh[12], 11);
	networkMesh[14]->addConnection(networkMesh[13], 3);
	networkMesh[15]->addConnection(networkMesh[13], 3);

	//Creating data to contain all connections between routers
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






	vector<pair <int, int> > pathInfo = shortestPath(source, destination, connectionDistances);
	int jumpCount = 0;
	int previousRouter = pathInfo[destination].second;
	vector <int> nodePath;
	nodePath.push_back(destination);
	nodePath.push_back(previousRouter);
	//Creating shortest path from data returned from shortestPath function
	while (previousRouter!=-1)
	{
		jumpCount++;
		
		previousRouter =pathInfo[previousRouter].second;
		nodePath.push_back(previousRouter);
	}
	//Calls on function to print path of nodes between source and destination router
	printPath(nodePath);

	Router* parent;
	Router* child;
	double timePassed;
	bool lost = false;
	int randmax = 100;
	int randChance;
	srand(time(NULL));
	int droppedRouter =0;
	//Calculating total time for packets to send
	for (int i=nodePath.size()-2; i>0; i--){
		
		randChance = (rand() % 101 );
		//Calculating chance for a packet to be lost
		if (randChance <packetLoss*100){
			if (numPackets=1){
				droppedRouter = i;
			} else {
				droppedRouter = rand() % (nodePath.size()-2);
			}
			std::cout << "!Packet lost occured on link from router " << nodePath[droppedRouter] << " to router "<< nodePath[droppedRouter-1] << "!" << std::endl;
			std::cout <<"\tResending another packet" << std::endl;
			lost = true;
		}

		parent = networkMesh[nodePath[i]];
		child = networkMesh[nodePath[i-1]];
		//Calculating time for packet to travel between two nodes
		timePassed = parent->travelTime(child,packetSize);
		if (lost){
			i++;
			packetLosses++;
			lost = false;
		} else if (numPackets>1) {
			//Allows for multiple packets to be sent
			numPackets--;
			i++;
		}
		//adding current travel time to final time
		finalTime += timePassed;

	}
	std::cout << "The total travel time took: " << finalTime << " Milliseconds" << std::endl;
	std::cout << "The packet was lost " << packetLosses << " times." << std::endl;

	return 0;

}	
//Data set for a node, used in shortest path function
struct Node{
	double dist;
	bool vis;
  	Node(double d, bool v):
    	dist(d), vis(v)
  	{}
};
//Function to determine shortest path between source and destination router
//Used modified djikstras algorithm to determine most optimal route
//Returns a vector pair which returns distance to get to new node and the node it left from
vector<pair <int, int> > shortestPath(int startID, int dest, vector< vector<pair<int, int> > >connections)
{
	set<pair<int, int> > finalRoute;
	int cursor = 0;
	vector<pair <int, int> >min_distance;
	for (int i =0; i<connections.size(); i++){
		min_distance.push_back(make_pair(INT_MAX, -1));
	}
    min_distance[ startID ].first = 0;
    finalRoute.insert( {0,startID} );
    
    //Comparing travel times between routes
    while (!finalRoute.empty()) {
        int where = finalRoute.begin()->second;
        if (where == dest)
        {
       		return min_distance; 	
        } 
        finalRoute.erase( finalRoute.begin() );
        for (auto ed : connections[where]) 
        {
	    //Triggers if it finds a more optimal path
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
//Prints out node path between source and destination router
void printPath(vector<int> nodePath)
{
	std::cout << "The packets starts at Router " << nodePath[nodePath.size()-2] << std::endl;

	for(int i=nodePath.size()-3; i>=0 ;i--)
	{
		std::cout << "The packets is then sent to Router " << nodePath[i] << std::endl;
		
	}
	std::cout << "The packet has now reached the destination" << std::endl;
	/*for(int j=0;j<nodePath.size();j++)
	{
		std::cout << nodePath[j] << std::endl;
	}*/
}
