/**
 * Copyright 2017 Colin Doig.  Distributed under the MIT license.
 */
#include <stdexcept>

#include "greentop/sport/enum/ExecutionReportErrorCode.h"
#include "greentop/Enum.h"

namespace greentop {

const std::string ExecutionReportErrorCode::ERROR_IN_MATCHER = "ERROR_IN_MATCHER";
const std::string ExecutionReportErrorCode::PROCESSED_WITH_ERRORS = "PROCESSED_WITH_ERRORS";
const std::string ExecutionReportErrorCode::BET_ACTION_ERROR = "BET_ACTION_ERROR";
const std::string ExecutionReportErrorCode::INVALID_ACCOUNT_STATE = "INVALID_ACCOUNT_STATE";
const std::string ExecutionReportErrorCode::INVALID_WALLET_STATUS = "INVALID_WALLET_STATUS";
const std::string ExecutionReportErrorCode::INSUFFICIENT_FUNDS = "INSUFFICIENT_FUNDS";
const std::string ExecutionReportErrorCode::LOSS_LIMIT_EXCEEDED = "LOSS_LIMIT_EXCEEDED";
const std::string ExecutionReportErrorCode::MARKET_SUSPENDED = "MARKET_SUSPENDED";
const std::string ExecutionReportErrorCode::MARKET_NOT_OPEN_FOR_BETTING = "MARKET_NOT_OPEN_FOR_BETTING";
const std::string ExecutionReportErrorCode::DUPLICATE_TRANSACTION = "DUPLICATE_TRANSACTION";
const std::string ExecutionReportErrorCode::INVALID_ORDER = "INVALID_ORDER";
const std::string ExecutionReportErrorCode::INVALID_MARKET_ID = "INVALID_MARKET_ID";
const std::string ExecutionReportErrorCode::PERMISSION_DENIED = "PERMISSION_DENIED";
const std::string ExecutionReportErrorCode::DUPLICATE_BETIDS = "DUPLICATE_BETIDS";
const std::string ExecutionReportErrorCode::NO_ACTION_REQUIRED = "NO_ACTION_REQUIRED";
const std::string ExecutionReportErrorCode::SERVICE_UNAVAILABLE = "SERVICE_UNAVAILABLE";
const std::string ExecutionReportErrorCode::REJECTED_BY_REGULATOR = "REJECTED_BY_REGULATOR";
const std::string ExecutionReportErrorCode::NO_CHASING = "NO_CHASING";
const std::string ExecutionReportErrorCode::REGULATOR_IS_NOT_AVAILABLE = "REGULATOR_IS_NOT_AVAILABLE";
const std::string ExecutionReportErrorCode::TOO_MANY_INSTRUCTIONS = "TOO_MANY_INSTRUCTIONS";
const std::string ExecutionReportErrorCode::INVALID_MARKET_VERSION = "INVALID_MARKET_VERSION";
const std::string ExecutionReportErrorCode::EVENT_EXPOSURE_LIMIT_EXCEEDED = "EVENT_EXPOSURE_LIMIT_EXCEEDED";
const std::string ExecutionReportErrorCode::EVENT_MATCHED_EXPOSURE_LIMIT_EXCEEDED = "EVENT_MATCHED_EXPOSURE_LIMIT_EXCEEDED";
const std::string ExecutionReportErrorCode::EVENT_BLOCKED = "EVENT_BLOCKED";

ExecutionReportErrorCode::ExecutionReportErrorCode() {
    valid = false;
}

ExecutionReportErrorCode::ExecutionReportErrorCode(const std::string& v) {
    if (v != ERROR_IN_MATCHER &&
        v != PROCESSED_WITH_ERRORS &&
        v != BET_ACTION_ERROR &&
        v != INVALID_ACCOUNT_STATE &&
        v != INVALID_WALLET_STATUS &&
        v != INSUFFICIENT_FUNDS &&
        v != LOSS_LIMIT_EXCEEDED &&
        v != MARKET_SUSPENDED &&
        v != MARKET_NOT_OPEN_FOR_BETTING &&
        v != DUPLICATE_TRANSACTION &&
        v != INVALID_ORDER &&
        v != INVALID_MARKET_ID &&
        v != PERMISSION_DENIED &&
        v != DUPLICATE_BETIDS &&
        v != NO_ACTION_REQUIRED &&
        v != SERVICE_UNAVAILABLE &&
        v != REJECTED_BY_REGULATOR &&
        v != NO_CHASING &&
        v != REGULATOR_IS_NOT_AVAILABLE &&
        v != TOO_MANY_INSTRUCTIONS &&
        v != INVALID_MARKET_VERSION &&
        v != EVENT_EXPOSURE_LIMIT_EXCEEDED &&
        v != EVENT_MATCHED_EXPOSURE_LIMIT_EXCEEDED &&
        v != EVENT_BLOCKED) {
        throw std::invalid_argument("Invalid ExecutionReportErrorCode: " + v);
    }
    value = v;
    valid = true;
}

bool ExecutionReportErrorCode::operator<(const ExecutionReportErrorCode& other) const {
    return value < other.value;
}

bool ExecutionReportErrorCode::operator==(const ExecutionReportErrorCode& other) const {
    return value == other.value;
}

bool ExecutionReportErrorCode::operator!=(const ExecutionReportErrorCode& other) const {
    return value != other.value;
}

}
