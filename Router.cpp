#include "Router.h"

Router::Router(){
	routerID = -1;
	buffer = 0;
	transmissionDelay = 0;
	propagationSpeed = 0;
	processingDelay = 0;
	bandwidth = 0;
	lossChance = 0;
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
	pair<Router, int> tempConnection;
	tempConnection.first = newConnection;
	tempConnection.second = length;
	connections.push_back(tempConnection);
}

double Router::travelTime(Router destination, int physicalLink)
{
	double propagationDelay = (physicalLink) / propagationSpeed;
	return (propagationDelay + transmissionDelay);
}



