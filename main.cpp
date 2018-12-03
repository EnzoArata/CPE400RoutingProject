#include "Router.h"
#include <iostream>
#include <fstream>

using namespace std;

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
	vector<vector<double> > connectionDistances;
	string input;

	int numNetworks = 16;
	vector<Router*> networkMesh;
	for (int i; i < numNetworks; i++){
		Router* tempRouter = new Router(i //routerID
						bufferSize //buffers
						transmissionDelay //transmission Delay
						propigationDelay //propigation Delay
						processingDelay //processing Delay
						bandwidth //bandwidth
						packetLoss //loss Chance
						)
		networkMesh.Push_Back(tempRouter);
	}
	
	networkMesh[0].addConnection(networkMesh[1], 1);
	networkMesh[1].addConnection(networkMesh[0], 1);
	networkMesh[1].addConnection(networkMesh[2], 2);
	networkMesh[1].addConnection(networkMesh[4], 4);
	networkMesh[2].addConnection(networkMesh[1], 1);
	networkMesh[2].addConnection(networkMesh[3], 3);
	networkMesh[2].addConnection(networkMesh[5], 3);
	networkMesh[3].addConnection(networkMesh[2], 2);
	networkMesh[4].addConnection(networkMesh[1], 1);
	networkMesh[4].addConnection(networkMesh[5], 3);
	networkMesh[4].addConnection(networkMesh[6], 5);
	networkMesh[5].addConnection(networkMesh[2], 4);
	networkMesh[5].addConnection(networkMesh[4], 10);
	networkMesh[5].addConnection(networkMesh[7], 10);
	networkMesh[5].addConnection(networkMesh[8], 11);
	networkMesh[6].addConnection(networkMesh[4], 9);
	networkMesh[7].addConnection(networkMesh[5], 8);
	networkMesh[7].addConnection(networkMesh[9], 9);
	networkMesh[8].addConnection(networkMesh[5], 7);
	networkMesh[8].addConnection(networkMesh[9], 9);
	networkMesh[8].addConnection(networkMesh[10], 15);
	networkMesh[9].addConnection(networkMesh[7], 6);
	networkMesh[9].addConnection(networkMesh[8], 7);
	networkMesh[10].addConnection(networkMesh[8], 5);
	networkMesh[10].addConnection(networkMesh[11], 6);
	networkMesh[11].addConnection(networkMesh[10], 5);
	networkMesh[11].addConnection(networkMesh[12], 12);
	networkMesh[11].addConnection(networkMesh[13], 12);
	networkMesh[12].addConnection(networkMesh[11], 4);
	networkMesh[12].addConnection(networkMesh[13], 11);
	networkMesh[12].addConnection(networkMesh[14], 11);
	networkMesh[13].addConnection(networkMesh[11], 3);
	networkMesh[13].addConnection(networkMesh[12], 3);
	networkMesh[13].addConnection(networkMesh[14], 3);
	networkMesh[13].addConnection(networkMesh[15], 3);
	networkMesh[14].addConnection(networkMesh[12], 6);
	networkMesh[14].addConnection(networkMesh[13], 9);
	networkMesh[14].addConnection(networkMesh[15], 15);
	networkMesh[15].addConnection(networkMesh[13], 8);


	for (int i = 0; i < 16; i++)
	{
		int totalConnections = networkMesh.connections.size();
		connectionDistances.push_back(std::vector<double>());
		for (int j = 0; j < totalConnections; j++)
		{
			distanceDelay = networkMesh[i].connections[j].second;//networkMesh[i].travelTime(networkMesh[i].connections[j].first);  //Calculates the distance between router i and its connections
			connectionDistances[i].push_back(distanceDelay);
		}
	}

	std::cout << "In order to simulate the routing algorithm,we have created a mesh network" << std::endl;
	std::cout << "The network is configured exactly like the example given in the project ideas PDF" << std::endl;
	std::cout << "The network has a total of 16 nodes, with different physical links." << std::endl;
	std::cout << "By defualt the routers all have the same information" << std::endl;
	std::cout << "Would you like to change defualt settings for the routers? y/n: ";

	cin >> input;

	if(!input=="n")
	{
		std::cout << "Enter packet size: ";
		std::cin >> packetSize;
		std::cout << "Enter bandwidth: ";
		std::cin >> bandwidth;
		std::cout << "Enter packet loss chance ";
		std::cin >> randomPacketLoss;
		std::cout << "Enter time to process a request";
		std::cin >> processingDelay;
		std::cout << "Enter buffer size for routers ";
		std::cin >> bufferSize;
		input = "";
	}

	return 0;

}	
