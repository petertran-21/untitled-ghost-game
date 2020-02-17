#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "EventListener.h"
#include "Event.h"

using namespace std;


class QuestManager : public EventListener{

public:
  QuestManager();
  ~QuestManager();
	virtual void handleEvent(Event* e);

private:
};

#endif
