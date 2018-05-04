#include<iostream>
#include<vector>

class ProtocolImpl{
public:
	virtual void protocol() = 0;
	virtual std::vector<uint8_t> make_header(int port) = 0;
};

class UDPProtocolImpl: public ProtocolImpl{
public:
	virtual void protocol(){
	  std::cout << "UDP Protocol" << std::endl;
	}
	virtual std::vector<uint8_t> make_header(int port){
	  std::vector<uint8_t> h{'T', 'C', 'P', '-'};
	  for(int i=0; i < 4; i++){
	    h.push_back(port >> i*8);
	  }
	  return  h;
	}
};

class TCPProtocolImpl: public ProtocolImpl{
public:
	virtual void protocol(){
	  std::cout << "TCP Protocol" << std::endl;
	}
	virtual std::vector<uint8_t> make_header(int port){
	  std::vector<uint8_t> h{'U', 'D', 'P', '-'};
	  for(int i=0; i < 4; i++){
	    h.push_back(port >> i*8);
	  }
	  return  h;
	}
};

class AbstractCommunicate{
private:
	ProtocolImpl *impl;
public:
	AbstractCommunicate(ProtocolImpl *im): impl(im) {}
	virtual void protocol(){
	  impl->protocol();
	}
	std::vector<uint8_t> make_header(int port){
	  return impl->make_header(port);
	}
};

class Communicate: public AbstractCommunicate{
public:
	Communicate(ProtocolImpl *impl): AbstractCommunicate(impl) {}
};

int main(){
  ProtocolImpl *udp_impl = new UDPProtocolImpl();
  AbstractCommunicate *udp_comm = new Communicate(udp_impl);
  udp_comm->protocol();
  udp_comm->make_header(3182);

  ProtocolImpl *tcp_impl = new TCPProtocolImpl();
  AbstractCommunicate *tcp_comm = new Communicate(tcp_impl);
  tcp_comm->protocol();
  tcp_comm->make_header(4432);
}
