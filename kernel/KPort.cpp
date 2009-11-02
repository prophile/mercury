#include "KPort.h"

bool KPort::PushMessage ( KPortMessage* message )
{
	return KAtomic::CompareAndSwapPtr<KPortMessage>(&queuedMessage, message, NULL);
}

KPortMessage* KPort::PopMessage ()
{
	return KAtomic::ExchangePtr<KPortMessage>(&queuedMessage, NULL);
}
