#include "Router.h"
#include <iostream>

//default Constructor for uninitialized routers
Router::Router(){
	routerID = -1;
	buffer = 0;
	transmissionDelay = 0;
	propagationSpeed = 200000000000;
	processingDelay = INT_MAX;
	bandwidth = 1500000;
	lossChance = 1;
	isFull = false;
	abilityToRoute = false;

}

//paramterized constructor for set up routers
Router::Router(int id, int buffSize, double transmissionDly, double propagationDly, double processingDly, double band, double loss){

	routerID = id;
	buffer = buffSize;
	transmissionDelay = transmissionDly;
	propagationSpeed = propagationDly;
	processingDelay = processingDly;
	bandwidth = band;
	lossChance = loss;
}
//Function to add router connections, including physical links
void Router::addConnection(Router* newConnection, int length){
	/*pair<Router*, int> tempConnection;
	tempConnection.first = newConnection;
	tempConnection.second = length;
	connections.push_back(tempConnection);*/
	
	connections.push_back(std::make_pair(newConnection, length));
}
//Returns id of router
int Router::getID()
{
	return routerID;
}
//Calculates travel time along a path between routers
double Router::travelTime(Router* destination, int packetSize)
{
	

	for (int i=0; i<connections.size();i++){
		if (connections[i].first == destination){
				double propagationDelay = packetSize / bandwidth + (connections[i].second) / propagationSpeed;
				
				return (propagationDelay + transmissionDelay);
		}
	}
	std::cout << "unable to find path to specified router" << std::endl;
	return 0;
}



