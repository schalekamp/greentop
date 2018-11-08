/**
 * Copyright 2017 Colin Doig.  Distributed under the MIT license.
 */

#ifndef MARKETGROUPID_H
#define MARKETGROUPID_H

#include <json/json.h>

#include "greentop/JsonMember.h"
#include "greentop/Optional.h"

namespace greentop {
/**
 * Container type for market group ID
 */
class MarketGroupId : public JsonMember {
    public:

        MarketGroupId(const Optional<int64_t>& eventId = Optional<int64_t>());

        virtual void fromJson(const Json::Value& json);

        virtual Json::Value toJson() const;

        virtual bool isValid() const;

        const Optional<int64_t>& getEventId() const;
        void setEventId(const Optional<int64_t>& eventId);


    private:
        /**
         * EventId (if type is EVENT)
         */
        Optional<int64_t> eventId;
};

}

#endif // MARKETGROUPID_H
