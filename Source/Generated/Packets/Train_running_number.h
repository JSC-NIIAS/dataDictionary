
#ifndef TRAIN_RUNNING_NUMBER_H_INCLUDED
#define TRAIN_RUNNING_NUMBER_H_INCLUDED

#include "Bitstream.h"
#include "Train_running_number_Core.h"
#include "BasePacket.h"

struct Train_running_number : public BasePacket
{
    Train_running_number_Core core;

    Train_running_number() : BasePacket(5) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const Train_running_number*>(&p))
        {
            return header == q->header && core == q->core;
        }

        return false;
    }

    uint16_t length() const override
    {
        return  core.L_PACKET;
    }

    int encode(Bitstream& stream) const override
    {
        return ::encode(stream, core);
    }

};

typedef std::shared_ptr<Train_running_number> Train_running_numberPtr;

#endif // TRAIN_RUNNING_NUMBER_H_INCLUDED

