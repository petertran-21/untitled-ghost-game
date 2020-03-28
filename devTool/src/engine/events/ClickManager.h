#ifndef CLICKMANAGER_H
#define CLICKMANAGER_H

#include "EventListener.h"
#include "Event.h"

using namespace std;


class ClickManager : public EventListener{

public:
  ClickManager();
  ~ClickManager();
	virtual void handleEvent(Event* e);

private:
};

#endif
