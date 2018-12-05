#include "Router.h"
#include <iostream>

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


Router::Router(int id, int buffSize, double transmissionDly, double propagationDly, double processingDly, double band, double loss){

	routerID = id;
	buffer = buffSize;
	transmissionDelay = transmissionDly;
	propagationSpeed = propagationDly;
	processingDelay = processingDly;
	bandwidth = band;
	lossChance = loss;
}

void Router::addConnection(Router* newConnection, int length){
	/*pair<Router*, int> tempConnection;
	tempConnection.first = newConnection;
	tempConnection.second = length;
	connections.push_back(tempConnection);*/
	
	connections.push_back(std::make_pair(newConnection, length));
}
int Router::getID()
{
	return routerID;
}

double Router::travelTime(Router* destination)
{
	for (int i=0; i<connections.size();i++){
		if (connections[i].first == destination){
				double propagationDelay = (connections[i].second) / propagationSpeed;
				return (propagationDelay + transmissionDelay);
		}
	}
	std::cout << "unable to find path to specified router" << std::endl;
	return 0;
}



