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
#include "SHA256.h"

class neighDiscover{
  public:
    /** 
     * @brief returns numNodes
     **/
    uint8_t const getnumNodes();

    /**
     * @brief returns numNeigh
     **/
    uint8_t getnumNeigh();

  private:
    /** @brief Total number of nodes in the network */
    uint8_t const numNodes = 24;

    /** @brief The maximum number of neighbours of particular node */
    uint8_t const maxNeigh = 5;

    /** @brief The length of amplification process in milliseconds */
    uint32_t const amplifLength = 300000;

    /** @brief The delay for amplification process after the node booted in milliseconds */
    uint32_t const amplifStart = 10000;

    /** @brief The node trasmission range used during the hybrid design protocol set up (referenced length) in meters */
    double const nodeTransmissionRange = 13;

    /** @brief The definition of network topology. The position [m][n] is the distance of nodes with IDs m - 1 and n - 1. The 0 indicates that nodes are not neighbours. */
    const PROGMEM double nodesDistTable[24][24] = {{0, 0, 0, 5.68339687159009, 0, 4.78117140458277, 0, 0, 0, 0, 0, 0, 5.01123737214672, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.373363094051889, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 3.57, 0.909340420304739, 2.20383756207212, 2.17494827524702, 6.41487334247528, 0, 5.78049305855478, 0, 5.98619244595427, 6.06577282792556, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {5.68339687159009, 0, 3.57, 0, 4.47188998075758, 1.37615406114286, 4.8888955808035, 7.46193674591255, 6.41611253018524, 7.25155155811499, 8.42326540006903, 4.69239810757783, 4.58022925190432, 0, 0, 0, 0, 0, 0, 9.28657633361187, 6.56479245673464, 0, 0, 0}, {0, 0, 0.909340420304739, 4.47188998075758, 0, 3.1, 1.85, 6.31354892275335, 7.87406502386156, 5.84, 0, 6.67658595391387, 6.78277966618406, 0, 0, 0, 0, 0, 0, 0, 7.50320598144553, 6.44810824971169, 0, 0}, {4.78117140458277, 0, 2.20383756207212, 1.37615406114286, 3.1, 0, 3.61005540123694, 6.74098657467881, 0, 0, 0, 0, 5.02355451846598, 0, 0, 0, 0, 0, 0, 0, 6.45972909648694, 6.84456718865408, 0, 0}, {0, 0, 2.17494827524702, 4.8888955808035, 1.85, 3.61005540123694, 0, 4.47743229987903, 6.49518283037514, 0, 0, 0, 8.17200097895246, 0, 0, 0, 0, 0, 0, 6.16, 6.00029999250038, 4.6134152208532, 0, 9.71957303589}, {0, 0, 6.41487334247528, 7.46193674591255, 6.31354892275335, 6.74098657467881, 4.47743229987903, 0, 4.1, 12.1374173529627, 0, 11.7885919430609, 11.7644974393299, 0, 0, 0, 0, 0, 0, 1.84808008484481, 3.25259896083117, 0.139283882771841, 0, 5.26365842356816}, {0, 0, 0, 6.41611253018524, 7.87406502386156, 0, 6.49518283037514, 4.1, 0, 0, 0, 0, 10.971025476226, 0, 0, 0, 0, 0, 0, 5.05523491046657, 0.859883713068227, 4.05208588260417, 0, 5.71192611997039}, {0, 0, 5.78049305855478, 7.25155155811499, 5.84, 0, 0, 12.1374173529627, 0, 0, 3.45079700938783, 0, 5.03314017289406, 7.16, 8.73301780600498, 0, 7.86426093158155, 10.3736444897635, 0, 13.85, 0, 12.2699837000707, 0, 0}, {0, 0.373363094051889, 0, 8.42326540006903, 0, 0, 0, 0, 0, 3.45079700938783, 0, 0, 4.37978309965231, 5.28643547203595, 5.36156693514125, 3.47942523989236, 0, 8.07530185194337, 7.92846138919778, 0, 0, 0, 0, 0}, {0, 0, 5.98619244595427, 4.69239810757783, 6.67658595391387, 0, 0, 11.7885919430609, 0, 0, 0, 0, 0.308706980808662, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {5.01123737214672, 0, 6.06577282792556, 4.58022925190432, 6.78277966618406, 5.02355451846598, 8.17200097895246, 11.7644974393299, 10.971025476226, 5.03314017289406, 4.37978309965231, 0.308706980808662, 0, 9.64707727760071, 0, 7.8321197641507, 8.66233802157362, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 7.16, 5.28643547203595, 0, 9.64707727760071, 0, 5, 2.2, 2.95286301747982, 3.26589956979697, 4.51841786469556, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 8.73301780600498, 5.36156693514125, 0, 0, 5, 0, 5.46260011349906, 2.05411781551108, 5.35407321578628, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.47942523989236, 0, 7.8321197641507, 2.2, 5.46260011349906, 0, 0, 0, 6.26834108835823, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 7.86426093158155, 0, 0, 8.66233802157362, 2.95286301747982, 2.05411781551108, 0, 0, 3.79817061228166, 3.07019543351885, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 10.3736444897635, 8.07530185194337, 0, 0, 3.26589956979697, 5.35407321578628, 0, 3.79817061228166, 0, 2.5, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.92846138919778, 0, 0, 4.51841786469556, 0, 6.26834108835823, 3.07019543351885, 2.5, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 9.28657633361187, 0, 0, 6.16, 1.84808008484481, 5.05523491046657, 13.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.2154477816716, 1.7464249196573, 1.78, 3.93686423438757}, {0, 0, 0, 6.56479245673464, 7.50320598144553, 6.45972909648694, 6.00029999250038, 3.25259896083117, 0.859883713068227, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.2154477816716, 0, 3.2, 5.16085264273259, 5.24832354185601}, {0, 0, 0, 0, 6.44810824971169, 6.84456718865408, 4.6134152208532, 0.139283882771841, 4.05208588260417, 12.2699837000707, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.7464249196573, 3.2, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.78, 5.16085264273259, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 9.71957303589, 5.26365842356816, 5.71192611997039, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.93686423438757, 5.24832354185601, 0, 0, 0}};

    /**
     * Definition of global parameters and structures
     **/

    /** @brief The definition of packet types (first byte of data part of packet) */
    enum pktType {
      PKT_NEIGH_DISC = 1,
      PKT_NONCE = 2,
      PKT_NONCE_CONF = 3,
    };

    /** @brief Structure for information about one neighbour */
    struct neighMember {
      uint8_t id = 0;                                             // Neighbour ID
      uint8_t interNode1 = 0;                                     // First intermediate node for amplification
      uint8_t interNode2 = 0;                                     // Second intermediate node for amplification
      uint8_t key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};        // Link key established with neighbouring node
      uint8_t myNonce[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    // The nonce generated for that neighbour,  will be used after nonce confirmation packet received
      uint8_t myNonceNew = 0;                                     // Indicator whether the myNonce was already used for key update (multiple confirmation packet received)
      uint8_t neighNonce[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // The nonce received for that particular neighbour (multiple nonce packets received)
      uint8_t neighNonceNew = 0;                                  // Indicator whether the neighNonce was already used for key update (multiple ack packets received)
    };

    /** @brief Structure for distance from a particular neighbour */
    struct distMember {
      uint8_t id = 0;     // Neighbour ID
      double dist = 0.0;  // Distance form that neighbour
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
    uint8_t* getKey(uint8_t id); 

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
    void rlSend (uint8_t hdr, const void* data, uint8_t size);

    /** 
     * @brief Reliable packet delivery - send packet and receive acknowledgement.
     *
     * The function ensures the reliable packet delivery. After the acknowledgement is received, 
     * the rlPending is set to 0 and packet is not re-sent again. If the acknowledgement was 
     * received for nonce confirmation, the link key is updated with respective neighbour. The 
     * function also transmitting a packet prepared for reliable delivery if the time between 
     * two attempts is reached.
     **/
    uint8_t rlReceive ();

    
    
    /**
     * @brief Identify the neighbours for a node.
     *  Simulates neighbour discovery for when network topology is not known in advance
     **/
    distMember identifyNeigh();
  
    /**
     * @brief Find an intermediate node for every neighbour the node has. 
     * @param neighDistsNP distMember structure containing neighbour information
     **/
    void findInterNode(distMember neighDistsNP);

    void calculateNumMessages();

    void setNeighKeys();


}
#endif
