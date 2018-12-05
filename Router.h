#include <vector>
#include <climits>

using namespace std;

class Router{

	private:
		int routerID;
		int buffer;
		double transmissionDelay;
		double propagationSpeed;
		double processingDelay;
		double bandwidth;
		double lossChance;
		bool isFull;
		bool abilityToRoute;
	public:
		Router();
		Router(int id, int buffSize, double transmissionDly, double propagationDly, double processingDly, double band, double loss);
		~Router();
		void addConnection(Router* newConnection, int length);
		int getID();
		double travelTime(Router* destination);

		vector<pair<Router*, int> > connections;
		
};
