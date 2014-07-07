//
//  ContractNoteProcessor.h
//  mycoin-account
//
//  Created by lx on 13-12-25.
//  Copyright (c) 2013年 lx. All rights reserved.
//

#ifndef __mycoin_account__ContractNoteProcessor__
#define __mycoin_account__ContractNoteProcessor__

#include "MessageProcessor.h"

class ContractNoteProcessor:public EventProcessor{
protected:

public:
    ContractNoteProcessor(message_type msg_type, EventSwitcher* processorMap)
    :MessageProcessor(msg_type,processorMap){
        
    }
    
    virtual int execute(message_t *msg, EventSwitcher &switcher){
        return execute(*((ContractNote*)&msg), switcher);
    }

    int execute(ContractNote &note,EventSwitcher &switcher){
        switch (note.status) {
            case STATUS_NEW:
                account(note, switcher);
                return EVS_ACCEPTED;
            case STATUS_ACCOUNTED:
                notify
            default:
                return EVS_REJECTED;
        }
    }
                
    void account(ContractNote &note,EventSwitcher &switcher);
    void notify(ContractNote &note){
        event ;
        event.data = note;
        switcher.push(event);
    }
                
};

#endif /* defined(__mycoin_account__ContractNoteProcessor__) */
