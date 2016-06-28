/**
 * Copyright 2015 Colin Doig.  Distributed under the MIT license.
 */

#include "greentop/betting/Runner.h"

namespace greentop {
Runner::Runner()  : selectionId(0), handicap(-1), adjustmentFactor(-1){
}

Runner::Runner(const uint64_t selectionId,
    const double handicap,
    const RunnerStatus& status,
    const double adjustmentFactor,
    const Optional<double>& lastPriceTraded,
    const Optional<double>& totalMatched,
    const std::tm& removalDate,
    const StartingPrices& sp,
    const ExchangePrices& ex,
    const std::vector<Order>& orders,
    const std::vector<Match>& matches) :
    selectionId(selectionId),
    handicap(handicap),
    status(status),
    adjustmentFactor(adjustmentFactor),
    lastPriceTraded(lastPriceTraded),
    totalMatched(totalMatched),
    removalDate(removalDate),
    sp(sp),
    ex(ex),
    orders(orders),
    matches(matches) {
}

void Runner::fromJson(const Json::Value& json) {
    if (json.isMember("selectionId")) {
        selectionId = json["selectionId"].asUInt64();
    }
    if (json.isMember("handicap")) {
        handicap = json["handicap"].asDouble();
    }
    if (json.isMember("status")) {
        status = json["status"].asString();
    }
    if (json.isMember("adjustmentFactor")) {
        adjustmentFactor = json["adjustmentFactor"].asDouble();
    }
    if (json.isMember("lastPriceTraded")) {
        lastPriceTraded.fromJson(json["lastPriceTraded"]);
    }
    if (json.isMember("totalMatched")) {
        totalMatched.fromJson(json["totalMatched"]);
    }
    if (json.isMember("removalDate")) {
        strptime(json["removalDate"].asString().c_str(), "%Y-%m-%dT%H:%M:%S.000Z", &removalDate);
    }
    if (json.isMember("sp")) {
        sp.fromJson(json["sp"]);
    }
    if (json.isMember("ex")) {
        ex.fromJson(json["ex"]);
    }
    if (json.isMember("orders")) {
        for (unsigned i = 0; i < json["orders"].size(); ++i) {
                Order order;
                order.fromJson(json["orders"][i]);
                orders.push_back(order);
            };
    }
    if (json.isMember("matches")) {
        for (unsigned i = 0; i < json["matches"].size(); ++i) {
                Match matche;
                matche.fromJson(json["matches"][i]);
                matches.push_back(matche);
            };
    }
}

Json::Value Runner::toJson() const {
    Json::Value json(Json::objectValue);
    if (selectionId > 0) {
        json["selectionId"] = selectionId;
    }
    json["handicap"] = handicap;
    if (status.isValid()) {
        json["status"] = status.getValue();
    }
    json["adjustmentFactor"] = adjustmentFactor;
    if (lastPriceTraded.isValid()) {
        json["lastPriceTraded"] = lastPriceTraded.toJson();
    }
    if (totalMatched.isValid()) {
        json["totalMatched"] = totalMatched.toJson();
    }
    if (removalDate.tm_year > 0) {
        char buffer[25];
        strftime(buffer, 25,"%Y-%m-%dT%H:%M:%S.000Z", &removalDate);
        json["removalDate"] = std::string(buffer);
    }
    if (sp.isValid()) {
        json["sp"] = sp.toJson();
    }
    if (ex.isValid()) {
        json["ex"] = ex.toJson();
    }
    if (orders.size() > 0) {
        for (unsigned i = 0; i < orders.size(); ++i) {
            json["orders"].append(orders[i].toJson());
        };
    }
    if (matches.size() > 0) {
        for (unsigned i = 0; i < matches.size(); ++i) {
            json["matches"].append(matches[i].toJson());
        };
    }
    return json;
}

bool Runner::isValid() const {
    return selectionId > 0 && true && status.isValid() && true;
}

const uint64_t Runner::getSelectionId() const {
    return selectionId;
}
void Runner::setSelectionId(const uint64_t selectionId) {
    this->selectionId = selectionId;
}

const double Runner::getHandicap() const {
    return handicap;
}
void Runner::setHandicap(const double handicap) {
    this->handicap = handicap;
}

const RunnerStatus& Runner::getStatus() const {
    return status;
}
void Runner::setStatus(const RunnerStatus& status) {
    this->status = status;
}

const double Runner::getAdjustmentFactor() const {
    return adjustmentFactor;
}
void Runner::setAdjustmentFactor(const double adjustmentFactor) {
    this->adjustmentFactor = adjustmentFactor;
}

const Optional<double>& Runner::getLastPriceTraded() const {
    return lastPriceTraded;
}
void Runner::setLastPriceTraded(const Optional<double>& lastPriceTraded) {
    this->lastPriceTraded = lastPriceTraded;
}

const Optional<double>& Runner::getTotalMatched() const {
    return totalMatched;
}
void Runner::setTotalMatched(const Optional<double>& totalMatched) {
    this->totalMatched = totalMatched;
}

const std::tm& Runner::getRemovalDate() const {
    return removalDate;
}
void Runner::setRemovalDate(const std::tm& removalDate) {
    this->removalDate = removalDate;
}

const StartingPrices& Runner::getSp() const {
    return sp;
}
void Runner::setSp(const StartingPrices& sp) {
    this->sp = sp;
}

const ExchangePrices& Runner::getEx() const {
    return ex;
}
void Runner::setEx(const ExchangePrices& ex) {
    this->ex = ex;
}

const std::vector<Order>& Runner::getOrders() const {
    return orders;
}
void Runner::setOrders(const std::vector<Order>& orders) {
    this->orders = orders;
}

const std::vector<Match>& Runner::getMatches() const {
    return matches;
}
void Runner::setMatches(const std::vector<Match>& matches) {
    this->matches = matches;
}


}



