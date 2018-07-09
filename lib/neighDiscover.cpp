#include "neighDiscover.h"


using namespace neigh;


static const PROGMEM double neighDiscover::nodesDistTable[24][24] = {{0, 0, 0, 5.68339687159009, 0, 4.78117140458277, 0, 0, 0, 0, 0, 0, 5.01123737214672, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.373363094051889, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 3.57, 0.909340420304739, 2.20383756207212, 2.17494827524702, 6.41487334247528, 0, 5.78049305855478, 0, 5.98619244595427, 6.06577282792556, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {5.68339687159009, 0, 3.57, 0, 4.47188998075758, 1.37615406114286, 4.8888955808035, 7.46193674591255, 6.41611253018524, 7.25155155811499, 8.42326540006903, 4.69239810757783, 4.58022925190432, 0, 0, 0, 0, 0, 0, 9.28657633361187, 6.56479245673464, 0, 0, 0}, {0, 0, 0.909340420304739, 4.47188998075758, 0, 3.1, 1.85, 6.31354892275335, 7.87406502386156, 5.84, 0, 6.67658595391387, 6.78277966618406, 0, 0, 0, 0, 0, 0, 0, 7.50320598144553, 6.44810824971169, 0, 0}, {4.78117140458277, 0, 2.20383756207212, 1.37615406114286, 3.1, 0, 3.61005540123694, 6.74098657467881, 0, 0, 0, 0, 5.02355451846598, 0, 0, 0, 0, 0, 0, 0, 6.45972909648694, 6.84456718865408, 0, 0}, {0, 0, 2.17494827524702, 4.8888955808035, 1.85, 3.61005540123694, 0, 4.47743229987903, 6.49518283037514, 0, 0, 0, 8.17200097895246, 0, 0, 0, 0, 0, 0, 6.16, 6.00029999250038, 4.6134152208532, 0, 9.71957303589}, {0, 0, 6.41487334247528, 7.46193674591255, 6.31354892275335, 6.74098657467881, 4.47743229987903, 0, 4.1, 12.1374173529627, 0, 11.7885919430609, 11.7644974393299, 0, 0, 0, 0, 0, 0, 1.84808008484481, 3.25259896083117, 0.139283882771841, 0, 5.26365842356816}, {0, 0, 0, 6.41611253018524, 7.87406502386156, 0, 6.49518283037514, 4.1, 0, 0, 0, 0, 10.971025476226, 0, 0, 0, 0, 0, 0, 5.05523491046657, 0.859883713068227, 4.05208588260417, 0, 5.71192611997039}, {0, 0, 5.78049305855478, 7.25155155811499, 5.84, 0, 0, 12.1374173529627, 0, 0, 3.45079700938783, 0, 5.03314017289406, 7.16, 8.73301780600498, 0, 7.86426093158155, 10.3736444897635, 0, 13.85, 0, 12.2699837000707, 0, 0}, {0, 0.373363094051889, 0, 8.42326540006903, 0, 0, 0, 0, 0, 3.45079700938783, 0, 0, 4.37978309965231, 5.28643547203595, 5.36156693514125, 3.47942523989236, 0, 8.07530185194337, 7.92846138919778, 0, 0, 0, 0, 0}, {0, 0, 5.98619244595427, 4.69239810757783, 6.67658595391387, 0, 0, 11.7885919430609, 0, 0, 0, 0, 0.308706980808662, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {5.01123737214672, 0, 6.06577282792556, 4.58022925190432, 6.78277966618406, 5.02355451846598, 8.17200097895246, 11.7644974393299, 10.971025476226, 5.03314017289406, 4.37978309965231, 0.308706980808662, 0, 9.64707727760071, 0, 7.8321197641507, 8.66233802157362, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 7.16, 5.28643547203595, 0, 9.64707727760071, 0, 5, 2.2, 2.95286301747982, 3.26589956979697, 4.51841786469556, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 8.73301780600498, 5.36156693514125, 0, 0, 5, 0, 5.46260011349906, 2.05411781551108, 5.35407321578628, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.47942523989236, 0, 7.8321197641507, 2.2, 5.46260011349906, 0, 0, 0, 6.26834108835823, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 7.86426093158155, 0, 0, 8.66233802157362, 2.95286301747982, 2.05411781551108, 0, 0, 3.79817061228166, 3.07019543351885, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 10.3736444897635, 8.07530185194337, 0, 0, 3.26589956979697, 5.35407321578628, 0, 3.79817061228166, 0, 2.5, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.92846138919778, 0, 0, 4.51841786469556, 0, 6.26834108835823, 3.07019543351885, 2.5, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 9.28657633361187, 0, 0, 6.16, 1.84808008484481, 5.05523491046657, 13.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.2154477816716, 1.7464249196573, 1.78, 3.93686423438757}, {0, 0, 0, 6.56479245673464, 7.50320598144553, 6.45972909648694, 6.00029999250038, 3.25259896083117, 0.859883713068227, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.2154477816716, 0, 3.2, 5.16085264273259, 5.24832354185601}, {0, 0, 0, 0, 6.44810824971169, 6.84456718865408, 4.6134152208532, 0.139283882771841, 4.05208588260417, 12.2699837000707, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.7464249196573, 3.2, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.78, 5.16085264273259, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 9.71957303589, 5.26365842356816, 5.71192611997039, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.93686423438757, 5.24832354185601, 0, 0, 0}};
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
      // EXPERIMENTAL trustLvl
      distance = pgm_read_float(nodesDistTable[neighTable[i].id - 1] + j) * neighTable[i].trustLvl;
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

