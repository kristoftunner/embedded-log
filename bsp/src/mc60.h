


/*functions*/
int MC60_sendAT(struct MC60_ATCmd);
void MC60_TcpIpInit();
int MC60_TcipIpConnect(char* ip, uint16_t port);
int MC60_TcpIpSend(char* data, uint16_t length);
char* data MC60_TcpIpRecv(uint16_t length);
