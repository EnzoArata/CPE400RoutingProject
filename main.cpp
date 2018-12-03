#include <vector.h>
#include "Router.h"

using namespace std;

void main(void){

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

	numNetworks = 15;
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
	}


}	