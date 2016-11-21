#include <room.hpp>

class Map {
public:
/*Constructor which picks at random from a list of 
pre-created rooms*/
/*Function to draw current room in the game screen*/
	Map(int numberOfRooms);
private:

/*array pointers/references to rooms stored in some kind of list structure*/
	std::vector<Room>& map;
	int atRoom;
};
