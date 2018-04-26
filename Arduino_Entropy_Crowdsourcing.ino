#include "lib/neighDiscover.h"


neighDiscover   discovery;

void setup(){
  neighDiscover::distMember neighDistsNP = discovery.identifyNeigh();
  discovery.findInterNode(neighDistsNP);

}

void loop(){

  Serial.println("HAHAHA");
}
