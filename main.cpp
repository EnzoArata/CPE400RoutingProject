#include "Router.h"
#include <climits>


using namespace std;

vector<int> shortestPath(int, int, std::vector< std::vector<double> >, double&);

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

	int numNetworks = 16;
	vector<Router*> networkMesh;
	for (int i; i < numNetworks; i++){
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
	networkMesh[14]->addConnection(networkMesh[15], 15);
	networkMesh[15]->addConnection(networkMesh[13], 8);

	return 0;

}	

struct Node{
	double dist;
	bool vis;
  	Node(double d, bool v):
    	dist(d), vis(v)
  	{}
};

vector<int> shortestPath(int startID, int dest, std::vector< std::vector<double> > connections, double& time) 
{
	vector<Node*> Nodes;
	int numConnected = (int) connections.size();
	int path[16];
	int cur = -1;

	vector<int> finalRoute;

	for (int i = 0; i < numConnected; i++)   
	{
		Node* tempNode = new Node(INT_MAX,false);
	}
	Nodes[startID]->dist = 0;
	for (int i = 0; i < numConnected; i++)
	{
		cur = -1;
		for (int j = 0; j < numConnected; j++)
		{
			if (Nodes[j]->vis) 
			{
				continue;  
			}
			if (cur == -1 || Nodes[j]->dist < Nodes[cur]->dist)
			{
				cur = j; 
			}
		}
		Nodes[cur]->vis = true;
		for (int j = 0; j < numConnected; j++)
		{
			double tempPath = Nodes[cur]->dist + connections[cur][j];
			if (tempPath < Nodes[j]->dist)
			{
				Nodes[j]->dist = tempPath;
				path[j] = cur; 
			}
		}
	}
	int iterator = dest;
	while (iterator != startID)
	{
		finalRoute.push_back(iterator); 
		iterator = path[iterator];
	}
	time += Nodes[dest]->dist;  
	return finalRoute;
}
