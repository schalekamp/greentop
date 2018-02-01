/**
 * Copyright 2018 Colin Doig.  Distributed under the MIT license.
 */

#ifndef EXCHANGEAPI_H
#define EXCHANGEAPI_H

#include <curl/curl.h>
#include <set>
#include <string>
#include <vector>

#include "greentop/account/AccountDetailsResponse.h"
#include "greentop/account/AccountFundsResponse.h"
#include "greentop/account/AccountStatementReport.h"
#include "greentop/account/ActivateApplicationSubscriptionRequest.h"
#include "greentop/account/ActivateApplicationSubscriptionResponse.h"
#include "greentop/account/AuthorisationResponse.h"
#include "greentop/account/CancelApplicationSubscriptionRequest.h"
#include "greentop/account/CancelApplicationSubscriptionResponse.h"
#include "greentop/account/CreateDeveloperAppKeysRequest.h"
#include "greentop/account/DeveloperApp.h"
#include "greentop/account/GetAccountFundsRequest.h"
#include "greentop/account/GetAccountStatementRequest.h"
#include "greentop/account/GetAffiliateRelationRequest.h"
#include "greentop/account/GetAffiliateRelationResponse.h"
#include "greentop/account/GetApplicationSubscriptionHistoryRequest.h"
#include "greentop/account/GetApplicationSubscriptionHistoryResponse.h"
#include "greentop/account/GetApplicationSubscriptionTokenRequest.h"
#include "greentop/account/GetApplicationSubscriptionTokenResponse.h"
#include "greentop/account/GetAuthorisationCodeRequest.h"
#include "greentop/account/GetDeveloperAppKeysResponse.h"
#include "greentop/account/GetVendorClientIdResponse.h"
#include "greentop/account/GetVendorDetailsRequest.h"
#include "greentop/account/IsAccountSubscribedToWebAppRequest.h"
#include "greentop/account/IsAccountSubscribedToWebAppResponse.h"
#include "greentop/account/ListAccountSubscriptionTokensResponse.h"
#include "greentop/account/ListApplicationSubscriptionTokensRequest.h"
#include "greentop/account/ListApplicationSubscriptionTokensResponse.h"
#include "greentop/account/ListAuthorizedWebAppsResponse.h"
#include "greentop/account/ListCurrencyRatesRequest.h"
#include "greentop/account/ListCurrencyRatesResponse.h"
#include "greentop/account/RevokeAccessToWebAppRequest.h"
#include "greentop/account/RevokeAccessToWebAppResponse.h"
#include "greentop/account/TokenRequest.h"
#include "greentop/account/TransferFundsRequest.h"
#include "greentop/account/TransferResponse.h"
#include "greentop/account/UpdateApplicationSubscriptionRequest.h"
#include "greentop/account/UpdateApplicationSubscriptionResponse.h"
#include "greentop/account/VendorAccessTokenInfo.h"
#include "greentop/account/VendorDetails.h"

#include "greentop/heartbeat/HeartbeatRequest.h"
#include "greentop/heartbeat/HeartbeatReport.h"

#include "greentop/sport/CancelExecutionReport.h"
#include "greentop/sport/CancelOrdersRequest.h"
#include "greentop/sport/ClearedOrderSummaryReport.h"
#include "greentop/sport/CurrentOrderSummaryReport.h"
#include "greentop/sport/ListClearedOrdersRequest.h"
#include "greentop/sport/ListCompetitionsRequest.h"
#include "greentop/sport/ListCompetitionsResponse.h"
#include "greentop/sport/ListCountriesRequest.h"
#include "greentop/sport/ListCountriesResponse.h"
#include "greentop/sport/ListCurrentOrdersRequest.h"
#include "greentop/sport/ListEventsRequest.h"
#include "greentop/sport/ListEventsResponse.h"
#include "greentop/sport/ListEventTypesRequest.h"
#include "greentop/sport/ListEventTypesResponse.h"
#include "greentop/sport/ListMarketBookRequest.h"
#include "greentop/sport/ListMarketBookResponse.h"
#include "greentop/sport/ListMarketCatalogueRequest.h"
#include "greentop/sport/ListMarketCatalogueResponse.h"
#include "greentop/sport/ListMarketProfitAndLossRequest.h"
#include "greentop/sport/ListMarketProfitAndLossResponse.h"
#include "greentop/sport/ListMarketTypesRequest.h"
#include "greentop/sport/ListMarketTypesResponse.h"
#include "greentop/sport/ListRunnerBookRequest.h"
#include "greentop/sport/ListRunnerBookResponse.h"
#include "greentop/sport/ListTimeRangesRequest.h"
#include "greentop/sport/ListTimeRangesResponse.h"
#include "greentop/sport/ListVenuesRequest.h"
#include "greentop/sport/ListVenuesResponse.h"
#include "greentop/sport/PlaceExecutionReport.h"
#include "greentop/sport/PlaceOrdersRequest.h"
#include "greentop/sport/ReplaceExecutionReport.h"
#include "greentop/sport/ReplaceOrdersRequest.h"
#include "greentop/sport/UpdateExecutionReport.h"
#include "greentop/sport/UpdateOrdersRequest.h"

#include "greentop/JsonRequest.h"
#include "greentop/JsonResponse.h"
#include "greentop/curl/SList.h"
#include "greentop/Exchange.h"
#include "greentop/menu/Menu.h"

namespace greentop {

class ExchangeApi {

    public:
        /** The login end point for the global exchange. */
        static const std::string LOGIN_END_POINT_GLOBAL;
        /** The login end point for the Italian exchange. */
        static const std::string LOGIN_END_POINT_ITALY;
        /** The login end point for the Spanish exchange. */
        static const std::string LOGIN_END_POINT_SPAIN;
        /** The login end point for the Romanian exchange. */
        static const std::string LOGIN_END_POINT_ROMANIA;
        /** The certificate login end point. */
        static const std::string LOGIN_END_POINT_GLOBAL_CERT;
        /** There are three APIs - "account", "betting", and "heartbeat". */
        enum class Api {ACCOUNT, BETTING, HEARTBEAT};

        /**
         * Constructor.
         *
         * @param applicationKey The user's application key.  It is required by all operations except login,
         *        createDeveloperAppKeys and getDeveloperAppKeys.
         */
        ExchangeApi(const std::string& applicationKey = "");

        /**
         * Sets the login end point to use.
         *
         * @param loginEndPoint The login end point to use.
         */
        void setLoginEndPoint(const std::string& loginEndPoint);

        /**
         * Log in either with a certificate or without.
         *
         * @param username The betfair username.
         * @param password The betfair password.
         * @param certFilename The certificate filename.  If provided, keyFilename should be provided as well.
         * @param keyFilename The key filename.
         */
        bool login(const std::string& username, const std::string& password,
            const std::string& certFilename = "", const std::string& keyFilename = "");

        /**
         * Log out by throwing away the SSO token.
         */
        void logout();

        /**
         * Sets the application key.
         *
         * @param appKey The application key.
         */
        void setApplicationKey(const std::string& appKey);

        /**
         * Sets the SSO token.  Useful if log in has happened independently of greentop, eg using the interactive
         * login.
         *
         * @param ssoid The SSO token.
         */
        void setSsoid(const std::string& ssoid);

        /**
         * Retrieves the navigation menu from Betfair but does not parse it.  Call refreshMenu() to do both.  If
         * the cache filename is provided, the menu JSON is saved to this file.
         *
         * @param cacheFilename The cache filename.
         * @return True if the menu has been retrieved successfully else false.
         */
        bool retrieveMenu(const std::string& cacheFilename = "");

        /**
         * Parses the navigation menu JSON.  Call retrieveMenu() first or refreshMenu to do both.
         *
         * @return True if the menu has been successfully parsed else false.
         */
        bool parseMenu();

        /**
         * Refresh the menu.  If the cache filename is provided, the menu JSON is saved to this file.
         *
         * @param cacheFilename The cache filename.
         * @return True if the menu has been refreshed successfully else false.
         */
        bool refreshMenu(const std::string& cacheFilename = "");

        /**
         * Gets the menu.
         *
         * @return The menu.
         */
        menu::Menu& getMenu();

        /**
         * Returns a list of Event Types (i.e. Sports) associated with the markets selected by the
         * MarketFilter.
         */
        ListEventTypesResponse listEventTypes(const ListEventTypesRequest& request) const;

        /**
         * Returns a list of Competitions (i.e., World Cup 2013) associated with the markets
         * selected by the MarketFilter. Currently only Football markets have an associated
         * competition.
         */
        ListCompetitionsResponse listCompetitions(const ListCompetitionsRequest& request) const;

        /**
         * Returns a list of time ranges in the granularity specified in the request (i.e. 3PM to
         * 4PM, Aug 14th to Aug 15th) associated with the markets selected by the MarketFilter.
         */
        ListTimeRangesResponse listTimeRanges(const ListTimeRangesRequest& request) const;

        /**
         * Returns a list of Events (i.e, Reading vs. Man United) associated with the markets
         * selected by the MarketFilter.
         */
        ListEventsResponse listEvents(const ListEventsRequest& request) const;

        /**
         * Returns a list of market types (i.e. MATCH_ODDS, NEXT_GOAL) associated with the markets
         * selected by the MarketFilter. The market types are always the same, regardless of
         * locale.
         */
        ListMarketTypesResponse listMarketTypes(const ListMarketTypesRequest& request) const;

        /**
         * Returns a list of Countries associated with the markets selected by the MarketFilter.
         */
        ListCountriesResponse listCountries(const ListCountriesRequest& request) const;

        /**
         * Returns a list of Venues (i.e. Cheltenham, Ascot) associated with the markets selected
         * by the MarketFilter. Currently, only Horse Racing markets are associated with a Venue.
         */
        ListVenuesResponse listVenues(const ListVenuesRequest& request) const;

        /**
         * Returns a list of information about markets that does not change (or changes very
         * rarely). You use listMarketCatalogue to retrieve the name of the market, the names of
         * selections and other information about markets.
         */
        ListMarketCatalogueResponse listMarketCatalogue(const ListMarketCatalogueRequest& request) const;

        /**
         * Returns a list of dynamic data about markets. Dynamic data includes prices, the status
         * of the market, the status of selections, the traded volume, and the status of any orders
         * you have placed in the market.
         */
        ListMarketBookResponse listMarketBook(const ListMarketBookRequest& request) const;

        /**
         * Returns a list of dynamic data about a market and a specified runner. Dynamic data
         * includes prices, the status of the market, the status of selections, the traded volume,
         * and the status of any orders you have placed in the market.
         */
        ListRunnerBookResponse listRunnerBook(const ListRunnerBookRequest& request) const;

        /**
         * Returns a list of your current orders. Optionally you can filter and sort your current
         * orders using the various parameters, setting none of the parameters will return all of
         * your current orders, up to a maximum of 1000 bets, ordered BY_BET and sorted
         * EARLIEST_TO_LATEST. To retrieve more than 1000 orders, you need to make use of the
         * fromRecord and recordCount parameters.
         */
        CurrentOrderSummaryReport listCurrentOrders(const ListCurrentOrdersRequest& request) const;

        /**
         * Returns a List of bets based on the bet status, ordered by settled date.
         */
        ClearedOrderSummaryReport listClearedOrders(const ListClearedOrdersRequest& request) const;

        /**
         * Place new orders into market. LIMIT orders below the minimum bet size are allowed if
         * there is an unmatched bet at the same price in the market. This operation is atomic in
         * that all orders will be placed or none will be placed.
         */
        PlaceExecutionReport placeOrders(const PlaceOrdersRequest& request) const;

        /**
         * Cancel all bets OR cancel all bets on a market OR fully or partially cancel particular
         * orders on a market. Only LIMIT orders an be cancelled or partially cancelled once
         * placed.
         */
        CancelExecutionReport cancelOrders(const CancelOrdersRequest& request) const;

        /**
         * This operation is logically a bulk cancel followed by a bulk place. The cancel is
         * completed first then the new orders are placed. The new orders will be placed atomically
         * in that they will all be placed or none will be placed.
         * In the case where the new orders cannot be placed the cancellations will not be rolled
         * back.
         * See ReplaceInstruction.
         */
        ReplaceExecutionReport replaceOrders(const ReplaceOrdersRequest& request) const;

        /**
         * Update non-exposure changing fields.
         */
        UpdateExecutionReport updateOrders(const UpdateOrdersRequest& request) const;

        /**
         * Retrieve profit and loss for a given list of markets. The values are calculated using
         * matched bets and optionally settled bets. Only odds markets are implemented, markets of
         * other types are silently ignored.
         */
        ListMarketProfitAndLossResponse listMarketProfitAndLoss(const ListMarketProfitAndLossRequest& request) const;

        /**
         * Create 2 application keys for given user; one active and the other delayed.
         */
        DeveloperApp createDeveloperAppKeys(const CreateDeveloperAppKeysRequest& request) const;

        /**
         * Get all application keys owned by the given developer/vendor.
         */
        GetDeveloperAppKeysResponse getDeveloperAppKeys() const;

        /**
         * Get available to bet amount.
         */
        AccountFundsResponse getAccountFunds(const GetAccountFundsRequest& request) const;

        /**
         * Transfer funds between wallets.
         */
        TransferResponse transferFunds(const TransferFundsRequest& request) const;

        /**
         * Get Account details.
         */
        AccountDetailsResponse getAccountDetails() const;

        /**
         * Get vendor client id for customer account.
         */
        GetVendorClientIdResponse getVendorClientId() const;

        /**
         * Returns the newly generate subscription token.
         */
        GetApplicationSubscriptionTokenResponse getApplicationSubscriptionToken(const GetApplicationSubscriptionTokenRequest& request) const;

        /**
         * Activate the subscription token for the customer.
         */
        ActivateApplicationSubscriptionResponse activateApplicationSubscription(const ActivateApplicationSubscriptionRequest& request) const;

        /**
         * Cancel application subscription.
         */
        CancelApplicationSubscriptionResponse cancelApplicationSubscription(const CancelApplicationSubscriptionRequest& request) const;

        /**
         * Update an application subscription with a new expiry date.
         */
        UpdateApplicationSubscriptionResponse updateApplicationSubscription(const UpdateApplicationSubscriptionRequest& request) const;

        /**
         * List of subscription tokens for an application.
         */
        ListApplicationSubscriptionTokensResponse listApplicationSubscriptionTokens(const ListApplicationSubscriptionTokensRequest& request) const;

        /**
         * List of subscription tokens associated with the account.
         */
        ListAccountSubscriptionTokensResponse listAccountSubscriptionTokens() const;

        /**
         * Identify all subscriptions, regardless of status, for a single client for a single
         * application key. The operation may be called by either the application key owner or a client.
         */
        GetApplicationSubscriptionHistoryResponse getApplicationSubscriptionHistory(const GetApplicationSubscriptionHistoryRequest& request) const;

        /**
         * Get account statement.
         */
        AccountStatementReport getAccountStatement(const GetAccountStatementRequest& request) const;

        /**
         * Returns a list of currency rates based on given currency.
         */
        ListCurrencyRatesResponse listCurrencyRates(const ListCurrencyRatesRequest& listCurrencyRatesRequest) const;

        /**
         * Generate auth code for web vendor, used to get vendor session.
         */
        AuthorisationResponse getAuthorisationCode(const GetAuthorisationCodeRequest& request) const;

        /**
         * Generate web vendor session based on a standard session identifiable by auth code, vendor secret and app
         * key.
         */
        VendorAccessTokenInfo token(const TokenRequest& request) const;

        /**
         * Return details about a vendor from its identifier. Response includes Vendor Name and URL.
         */
        VendorDetails getVendorDetails(const GetVendorDetailsRequest& request) const;

        /**
         * Remove the link between an account and a vendor web app. This will remove the refreshToken for this
         * user-vendor pair subscription.
         */
        RevokeAccessToWebAppResponse revokeAccessToWebApp(const RevokeAccessToWebAppRequest& request) const;

        /**
         * Retrieve all vendors applications currently subscribed to by the user making the request.
         */
        ListAuthorizedWebAppsResponse listAuthorizedWebApps() const;

        /**
         * Return whether an account has authorised a web app.
         */
        IsAccountSubscribedToWebAppResponse isAccountSubscribedToWebApp(const IsAccountSubscribedToWebAppRequest& request) const;

        /**
         * Return relation between a list of users and an affiliate.
         */
        GetAffiliateRelationResponse getAffiliateRelation(const GetAffiliateRelationRequest& request) const;

        /**
         * This heartbeat operation is provided to help customers have their positions managed
         * automatically in the event of their API clients losing connectivity with the Betfair
         * API.
         *
         * If a heartbeat request is not received within a prescribed time period, then Betfair
         * will attempt to cancel all 'LIMIT' type bets for the given customer on the given
         * exchange.
         *
         * There is no guarantee that this service will result in all bets being cancelled as
         * there are a number of circumstances where bets are unable to be cancelled. Manual
         * intervention is strongly advised in the event of a loss of connectivity to ensure that
         * positions are correctly managed.
         *
         * If this service becomes unavailable for any reason, then your heartbeat will be
         * unregistered automatically to avoid bets being inadvertently cancelled upon resumption
         * of service. You should manage your position manually until the service is resumed.
         *
         * Heartbeat data may also be lost in the unlikely event of  nodes failing within the
         * cluster, which may result in your position not being managed until a subsequent
         * heartbeat request is received.
         */
        HeartbeatReport heartbeat(const HeartbeatRequest& request) const;

        ~ExchangeApi();

    private:
        static const std::string HOST_UK;

        std::string loginEndPoint;
        std::string loginEndPointCert;
        std::string ssoid;
        std::string applicationKey;
        menu::Menu menu;
        Json::Value pendingMenuJson;

        bool initRequest(const Api api, const std::string method, CURL* curl, SList& headers) const;

        bool performRequest(
            const Api api,
            const std::string& method, const JsonRequest& jsonRequest,
            JsonResponse& jsonResponse
        ) const;

        std::string buildUri(const Api api, const std::string method) const;
};

}

#endif // EXCHANGEAPI_H
