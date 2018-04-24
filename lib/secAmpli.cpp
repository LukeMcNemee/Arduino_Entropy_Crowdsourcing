#include "secAmpli.h"


/** 
 * @brief Function returning the link key for the particular neighbour.
 *
 * @param id The ID of the neighbouring node. The returned link key is established with that node.
 **/
uint8_t* getKey(uint8_t id) {
  for (uint8_t i = 0; i < numNeigh; i++) {
    if (neighTable[i].id == id) return neighTable[i].key;
  }
}

/** 
 * @brief Function returning an index within the neighTable structure for the particular neighbour.
 *
 * @param id The ID of the neighbouring node. The returned index belongs to that node.
 **/
uint8_t getIndex(uint8_t id) {
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
void rlSend (uint8_t hdr, const void* data, uint8_t size) {
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
uint8_t rlReceive () {
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

