/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/ads.h"

#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/internal/locale_helper.h"

namespace ads {

bool _is_debug = false;
bool _is_testing = false;
bool _is_production = false;

const char _bundle_schema_name[] = "bundle-schema.json";
const char _catalog_schema_name[] = "catalog-schema.json";
const char _catalog_name[] = "catalog.json";
const char _client_name[] = "client.json";

// static
Ads* Ads::CreateInstance(AdsClient* ads_client) {
  return new AdsImpl(ads_client);
}

bool Ads::IsSupportedRegion(const std::string& locale) {
  auto region = helper::Locale::GetCountryCode(locale);

  std::vector<std::string> regions = {
    "US",  // United States of America
    "CA",  // Canada
    "GB",  // United Kingdom (Great Britain and Northern Ireland)
    "DE",  // Germany
    "FR",  // France
    "AU",  // Australia
    "NZ",  // New Zealand
    "IE"   // Ireland
  };

  if (std::find(regions.begin(), regions.end(), region) == regions.end()) {
    return false;
  }

  return true;
}

std::string Ads::GetRegion(const std::string& locale) {
  return helper::Locale::GetCountryCode(locale);
}

}  // namespace ads
