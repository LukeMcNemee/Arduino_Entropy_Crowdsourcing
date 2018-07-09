/**
 * Library inspired from https://github.com/crocs-muni/sec_amplif
 * but put in form of a library for better reusability in other future projects
 * 
 **/
#ifndef neighDiscover_h
#define neighDiscover_h
#include "JeeLib.h"
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <SHA256.h>

namespace neigh
{
  /** @brief Structure for information about one neighbour */
  struct neighMember
  {
    uint8_t id = 0;                                                            // Neighbour ID
    uint8_t interNode1 = 0;                                                    // First intermediate node for amplification
    //EXPERIMENTAL trustLvl
    ufloat8_t trustLvl = 1;                                                    // Modifier used to ponderate distance relatively to trust level of link, i.e. recent execution of SA protocol
    uint8_t interNode2 = 0;                                                    // Second intermediate node for amplification
    uint8_t key[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};        // Link key established with neighbouring node
    uint8_t myNonce[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // The nonce generated for that neighbour,  will be used after nonce confirmation packet received
    uint8_t myNonceNew = 0;                                                    // Indicator whether the myNonce was already used for key update (multiple confirmation packet received)
    uint8_t neighNonce[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // The nonce received for that particular neighbour (multiple nonce packets received)
    uint8_t neighNonceNew = 0;                                                 // Indicator whether the neighNonce was already used for key update (multiple ack packets received)
  };

  /** @brief Structure for distance from a particular neighbour */
  struct distMember
  {
    uint8_t id = 0;    // Neighbour ID
    double dist = 0.0; // Distance form that neighbour
  };

  class neighDiscover
  {
    public:
      /** 
       * @brief returns numNodes
       **/
      static const uint8_t getnumNodes();
      /**
       * @brief returns numNeigh
       **/
      uint8_t getnumNeigh();

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
      void rlSend(uint8_t hdr, const void *data, uint8_t size);

      /** 
       * @brief Reliable packet delivery - send packet and receive acknowledgement.
       *
       * The function ensures the reliable packet delivery. After the acknowledgement is received, 
       * the rlPending is set to 0 and packet is not re-sent again. If the acknowledgement was 
       * received for nonce confirmation, the link key is updated with respective neighbour. The 
       * function also transmitting a packet prepared for reliable delivery if the time between 
       * two attempts is reached.
       **/
      uint8_t rlReceive();

      /**
       * @brief Identify the neighbours for a node.
       *  Simulates neighbour discovery for when network topology is not known in advance
       **/
      void identifyNeigh(distMember **neighDistsNC);

      /**
       * @brief Find an intermediate node for every neighbour the node has. 
       * @param neighDistsNP distMember structure containing neighbour information
       **/
      void findInterNode(distMember *neighDistsNP);

      void calculateNumMessages();

      void setNeighKeys();

      /** @brief The maximum number of neighbours of particular node */
      static const uint8_t maxNeigh = 5;

    private:
      /** @brief Total number of nodes in the network */
      static const uint8_t numNodes = 24;

      /** @brief The length of amplification process in milliseconds */
      static const uint32_t amplifLength = 300000;

      /** @brief The delay for amplification process after the node booted in milliseconds */
      static const uint32_t amplifStart = 10000;

      /** @brief The node trasmission range used during the hybrid design protocol set up (referenced length) in meters */
      static constexpr double nodeTransmissionRange = 13;

      /** @brief The definition of network topology. The position [m][n] is the distance of nodes with IDs m - 1 and n - 1. The 0 indicates that nodes are not neighbours. */
      static const PROGMEM double nodesDistTable[24][24];

      /**
       * Definition of global parameters and structures
       **/

      /** @brief The definition of packet types (first byte of data part of packet) */
      enum pktType
      {
        PKT_NEIGH_DISC = 1,
        PKT_NONCE = 2,
        PKT_NONCE_CONF = 3,
      };
      /** @brief Number of messages the node sends during the amplification execution. Calculated as 6 * number of neighbours. */
      uint8_t saMsgToBeSent = 0;

      /** @brief Number of messages already sent. Iterate from 0 up to saMsgToBeSent - 1. */
      uint8_t saMsgCounter = 0;

      /** @brief Pointer to a particular neighbour. The next amplification message will be generated for this neighbour. */
      uint8_t saNextMsgPtr = 0;

      /** @brief Every amplification message is send during an interval with length amplifLength / saMsgToBeSent (in milliseconds). */
      double saMsgInterval = 0;

      /** @brief The node ID is loaded form EEPROM memory. */
      uint8_t nodeId = eeprom_read_byte(RF12_EEPROM_ADDR) & B00011111;

      /** @brief The stack for building the data part when creating a network packet. */
      uint8_t stack[RF12_MAXDATA];

      /** @brief The number of neighbouring nodes. */
      uint8_t numNeigh = 0;

      /** @brief The table containing information about all the neighbours. */
      neighMember neighTable[maxNeigh];

      /** @brief Variable used for a random number generated throughout the application. */
      long randNumber;

      /** @brief Constructor for a SHA-256 hash object. */
      SHA256(SHA);

      /** 
       * @brief Function returning the link key for the particular neighbour.
       *
       * @param id The ID of the neighbouring node. The returned link key is established with that node.
       **/
      uint8_t *getKey(uint8_t id);

      /** 
       * @brief Function returning an index within the neighTable structure for the particular neighbour.
       *
       * @param id The ID of the neighbouring node. The returned index belongs to that node.
       **/
      uint8_t getIndex(uint8_t id);

      /** @brief The packet header stored during a reliable packet delivery. */
      uint8_t rlHdr;

      /** @brief The packet data part stored during a reliable packet delivery.  */
      uint8_t rlSendBuf[RF12_MAXDATA];

      /** @brief The length of data part stored during a reliable packet delivery. */
      uint8_t rlSendLen;

      /** @brief The number of remaining attempts for reliable packet delivery. */
      uint8_t rlPending;

      /** @brief The time for the next attempt of reliable packet delivery in case the acknowledgement was not delivered yet. */
      long rlNextSend;
  };
}
#endif
