#ifndef KEx_h
#define KEx_h

#include <Arduino.h>
#include <Entropy.h>
#include "Statistic.h"
#include "sha256.h"

#define bufferLen 200

// TODO define max neigbour bound

class KEx {

public:
  /**
  * saves RSSI measurement for neighbour node, to specified position in sequence
  */
  void storeRssi(uint8_t nodeID, uint8_t counter, float rssi);

  /**
  * get entropy estimate for link to node
  */
  float getMinEntropy(uint8_t nodeID);

  /**
  * processes RSSI measurements into bit string (saved as char array),
  * returns min entropy in this bit string
  */
  float processRSSI(uint8_t nodeID, char* outputBits);

private:
  uint8_t rssi[4][bufferLen] = {0};
  uint8_t neighbours[4] = {0};
  uint8_t neighCounter[4] = {0};
  float neighEntropy[4] = {0};

  void printHash(uint8_t* hash);


  //convert 8 bit string (1&0) to single char
  char stringToChar(String input);

  //compress whole string (1&0) to chars
  void processBits(String input, char* output);

};

#endif
