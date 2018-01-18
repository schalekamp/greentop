/**
 * Copyright 2017 Colin Doig.  Distributed under the MIT license.
 */

#ifndef KEYLINEDESCRIPTION_H
#define KEYLINEDESCRIPTION_H

#include <json/json.h>
#include <vector>

#include "greentop/JsonMember.h"
#include "greentop/sport/KeyLineSelection.h"

namespace greentop {
/**
 * A list of KeyLineSelection objects describing the key line for the market
 */
class KeyLineDescription : public JsonMember {
    public:
        KeyLineDescription();

        KeyLineDescription(const std::vector<KeyLineSelection>& keyLine);

        virtual void fromJson(const Json::Value& json);

        virtual Json::Value toJson() const;

        virtual bool isValid() const;

        const std::vector<KeyLineSelection>& getKeyLine() const;
        void setKeyLine(const std::vector<KeyLineSelection>& keyLine);


    private:
        /**
         * A list of KeyLineSelection objects
         */
        std::vector<KeyLineSelection> keyLine;
};

}

#endif // KEYLINEDESCRIPTION_H
