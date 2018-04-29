#include "neighDiscover.h"


using namespace neigh;

/** 
 * @brief Function returning the link key for the particular neighbour.
 *
 * @param id The ID of the neighbouring node. The returned link key is established with that node.
 **/
uint8_t* neighDiscover::getKey(uint8_t id) {
  for (uint8_t i = 0; i < numNeigh; i++) {
    if (neighTable[i].id == id) return neighTable[i].key;
  }
}

/** 
 * @brief Function returning an index within the neighTable structure for the particular neighbour.
 *
 * @param id The ID of the neighbouring node. The returned index belongs to that node.
 **/
uint8_t neighDiscover::getIndex(uint8_t id) {
  for (uint8_t i = 0; i < numNeigh; i++) {
    if (neighTable[i].id == id) return i;
  }
}


/** 
 * @brief Reliable packet delivery - store packet that should be send.
 *
 * The function ensures the reliable packet delivery. The full packet is stored in several 
 * variables. The number of attempts is identified by setting rlPending variable, currently
 * 4 attempts are performed. The actual sending is performed by function rlReceive.
 *
 * @param hdr The packet header.
 * @param data The data part of packet.
 * @param size The length of data part.
 **/
void neighDiscover::rlSend (uint8_t hdr, const void* data, uint8_t size) {
  rlHdr = hdr;
  memcpy(rlSendBuf, data, size);
  rlSendLen = size;
  rlPending = 4;
  rlNextSend = 0;
}

/** 
 * @brief Reliable packet delivery - send packet and receive acknowledgement.
 *
 * The function ensures the reliable packet delivery. After the acknowledgement is received, 
 * the rlPending is set to 0 and packet is not re-sent again. If the acknowledgement was 
 * received for nonce confirmation, the link key is updated with respective neighbour. The 
 * function also transmitting a packet prepared for reliable delivery if the time between 
 * two attempts is reached.
 **/
uint8_t neighDiscover::rlReceive () {
  if (rf12_recvDone() && rf12_crc == 0) {
    if ((rf12_hdr & B10000000) == RF12_HDR_CTL) {

      // The acknowledgement is received
      if (rlPending != 4) {
        rlPending = 0;
      }

      // Update the key, if the original message was a nonce confirmation packet
      if (rlSendBuf[0] == PKT_NONCE_CONF && neighTable[getIndex(rlSendBuf[1])].neighNonceNew == 1) {

        SHA.reset();
        SHA.update(getKey(rlSendBuf[1]), 16);
        SHA.update(neighTable[getIndex(rlSendBuf[1])].neighNonce, 16);
        SHA.finalize(getKey(rlSendBuf[1]), 16);

        neighTable[getIndex(rlSendBuf[1])].neighNonceNew = 0;
      }
    } else {

      // The packet is not acknowledgement, process it in a standard way
      return 1;
    }
  }

  if (rlPending > 0) {
    long now = millis();

    if (now >= rlNextSend && rf12_canSend()) {      
      rf12_sendStart((rlHdr | RF12_HDR_ACK | RF12_HDR_DST), rlSendBuf, rlSendLen);

      // Add the 100 millisecond delay before retransmission
      rlNextSend = now + 100;
      rlPending--;
    }
  }

  return 0;
}

/** 
 * @brief returns numNodes
 **/
uint8_t const neighDiscover::getnumNodes(){
  return numNodes;
}

/**
 * @brief returns numNeigh
 **/
uint8_t neighDiscover::getnumNeigh(){
  return numNeigh;
}

/**
 * @brief Identify the neighbours for a node.
 * Identify node neighbours and respective distances (this simulates the node discovery phase and RSSI measurements for case when the network topology is not known in advance)
 **/
void neighDiscover::identifyNeigh(distMember** neighDistsNC){
  double distance;

  for (uint8_t i = 0; i < numNodes; i++) { 
    distance = pgm_read_float(nodesDistTable[nodeId-1] + i);
    if (distance != 0) {
      neighTable[numNeigh].id = i+1;
      neighDistsNC[numNeigh]->id = i+1;
      neighDistsNC[numNeigh]->dist = distance;

      numNeigh++;
      if (numNeigh == maxNeigh) break;
    }
  }
}

/**
 * @brief Calculate intermediate node for every neighbour
 * @param neighDistsNC information about the neighbours
 **/
void neighDiscover::findInterNode(distMember* neighDistsNC){
  double distance;

  // Compute the relative distances based on hybrid designed protocol HD Final parameters and the transmission range
  double centralRelDist1 = 0.69 * nodeTransmissionRange;
  double neighRelDist1 = 0.98 * nodeTransmissionRange;
  double centralRelDist2 = 0.01 * nodeTransmissionRange;
  double neighRelDist2 = 0.39 * nodeTransmissionRange;
  // Calculate one intermediate node for every neighbour
  for (uint8_t i = 0; i < numNeigh; i++) { 

    // Get the neighbours and distances of particular neighbour NP (simulate the data received from the neighbour for case when the netwrok topology is not known in advance) 
    uint8_t numNeighNP = 0;
    distMember neighDistsNP[maxNeigh];

    for (uint8_t j = 0; j < numNodes; j++) { 
      distance = pgm_read_float(nodesDistTable[neighTable[i].id - 1] + j);
      if (distance != 0) {
        neighDistsNP[numNeighNP].id = j+1;
        neighDistsNP[numNeighNP].dist = distance;

        numNeighNP++;
        if (numNeighNP == maxNeigh) break;
      }
    }    
    // Use the direct link for case where is no better neighbour 
    uint8_t interNode1 = neighTable[i].id;

    double currentDistance1 = 0;
    double minimalDistance1 = 2 * pow(nodeTransmissionRange, 2);

    // Identify the common neighbours
    for (uint8_t k = 0; k < numNeigh; k++) {
      for (uint8_t l = 0; l < numNeighNP; l++) {

        if (neighDistsNC[k].id == neighDistsNP[l].id) {

          currentDistance1 = 0;

          currentDistance1 += pow(neighDistsNC[k].dist - centralRelDist1, 2);
          currentDistance1 += pow(neighDistsNP[l].dist - neighRelDist1, 2);

          if (currentDistance1 <= minimalDistance1) {
            minimalDistance1 = currentDistance1;
            interNode1 = neighDistsNC[k].id;
          }          
        }   
      }
    }
  // Store the final interNode 1 
  neighTable[i].interNode1 = interNode1;
  }
}

// Calculate the total number of amplification messages to be sent, message interval and the neighbour for the first amplification attempt
void neighDiscover::calculateNumMessages(){
  saMsgToBeSent = numNeigh * 6;
  saMsgInterval = (double)amplifLength / (double)saMsgToBeSent;
  for (uint8_t i = 0; i < numNeigh; i++) {
    if (neighTable[i].id > nodeId) {
      saNextMsgPtr = i;
      break;
    }
  }
  randNumber = random(saMsgInterval);
}

void neighDiscover::setNeighKeys(){
  // TO_BE_CHANGED Set the initial keys for my neighbours. 
  for (uint8_t i = 0; i < numNeigh; i++) {
    if (nodeId < neighTable[i].id) {
      neighTable[i].key[0] = nodeId;
      neighTable[i].key[4] = neighTable[i].id;
    } else {
      neighTable[i].key[0] = neighTable[i].id;
      neighTable[i].key[4] = nodeId;      
    }
  }
}

