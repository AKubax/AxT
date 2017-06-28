#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <ctype.h>
#include <cstdio>
#include <string.h>

class Station{
public:
    std::vector<Station*> neighbours;

    Station();
    Station(std::vector<Station*> n);

    int id;
    static int counter;

    bool visited;

    void addN(Station* s){
        neighbours.push_back(s);
        s->neighbours.push_back(s);
    }
};

int Station::counter = 0;

std::vector<Station*> stations;

Station::Station(std::vector<Station*> n):
    neighbours (n),
    visited (false)
{
    id = counter++;
    stations.push_back(this);
}

Station::Station():
    visited (false)
{
    id = counter++;
    stations.push_back(this);
}


bool findWay(Station* from, Station* to){
    printf("\n\nfrom.id = %d. from.heighbours.size() = %d\n", from->id, from->neighbours.size());
    for(Station* s : from->neighbours){
        printf("Station s id = %d\n", s->id);

        if(s->id == to->id){
            printf("%d", s->id);
            return true;
        }
        if(s->visited) continue;

        s->visited = true;

        if(findWay(s, to)){
            printf(" <- %d", s->id);
            return true;
        }
    }

    return false;
}


int main(){
    for(int i = 0; i < 10; i++){
        Station();
    }

    stations[0]->addN(stations[1]);

    stations[1]->addN(stations[2]);
    stations[1]->addN(stations[7]);
    stations[1]->addN(stations[5]);

    stations[2]->addN(stations[3]);

    stations[3]->addN(stations[6]);

    stations[6]->addN(stations[4]);

    stations[4]->addN(stations[5]);
    stations[4]->addN(stations[8]);

    stations[5]->addN(stations[7]);

    stations[7]->addN(stations[8]);

    stations[8]->addN(stations[9]);

    findWay(stations[0], stations[9]);
}
