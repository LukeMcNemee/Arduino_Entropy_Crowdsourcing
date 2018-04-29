void KEx::storeRssi(uint8_t nodeID, uint8_t counter, float rssi){

}

/**
* get entropy estimate for link to node
*/
float KEx::getMinEntropy(uint8_t nodeID){
  return 0;
}

/**
* processes RSSI measurements into bit string (saved as char array),
* returns min entropy in this bit string
*/
float KEx::processRSSI(uint8_t nodeID, char* outputBits){
  return 0;
}


void KEx::printHash(uint8_t* hash){

}


//convert 8 bit string (1&0) to single char
char KEx::stringToChar(String input){
  return '0';
}

//compress whole string (1&0) to chars
void KEx::processBits(String input, char* output){

}
