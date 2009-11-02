#ifndef __KPORTMESSAGE__
#define __KPORTMESSAGE__

class KPort;

class KPortMessage
{
private:
	unsigned char* data;
	unsigned long dataLength;
	KPort** ports;
	unsigned long portCount;
public:
	KPortMessage ( const unsigned char* messageData, unsigned long messageDataLength, const KPort** messagePorts, unsigned long messagePortCount );
	~KPortMessage () { delete [] data; delete [] ports; }
	
	const unsigned char* GetData () const { return data; }
	unsigned long GetDataLength () const { return dataLength; }
	KPort* GetPort ( unsigned long idx ) const { return ports[idx]; }
	unsigned long GetPortCount () const { return portCount; }
};

#endif
