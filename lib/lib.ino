#include "neighDiscover.h"

using namespace neigh;
neighDiscover   discovery;

void setup(){
  Serial.begin(57600);
  distMember* neighDistsNP = (distMember*) calloc(discovery.maxNeigh, sizeof(distMember));
  discovery.identifyNeigh(&neighDistsNP);
  discovery.findInterNode(neighDistsNP);
  discovery.calculateNumMessages();
  discovery.setNeighKeys();


}

void loop(){

  Serial.println("HAHAHA");
}
