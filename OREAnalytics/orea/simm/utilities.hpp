/*
 Copyright (C) 2016 Quaternion Risk Management Ltd.
 All rights reserved.

 This file is part of ORE, a free-software/open-source library
 for transparent pricing and risk analysis - http://opensourcerisk.org

 ORE is free software: you can redistribute it and/or modify it
 under the terms of the Modified BSD License.  You should have received a
 copy of the license along with this program.
 The license is also available online at <http://opensourcerisk.org>

 This program is distributed on the basis that it will form a useful
 contribution to risk analytics and model standardisation, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
*/

/*! \file orea/simm/utilities.hpp
    \brief supporting utilities
*/

#pragma once

#include <ored/portfolio/trade.hpp>
#include <orea/simm/simmcalibration.hpp>
#include <orea/simm/simmbucketmapper.hpp>
#include <orea/simm/simmconfiguration.hpp>
#include <ql/math/matrix.hpp>
#include <string>
#include <vector>

namespace ore {
namespace analytics {

std::vector<std::string> loadFactorList(const std::string& inputFileName, const char delim = '\n');

std::vector<std::vector<double>> loadScenarios(const std::string& inputFileName, const char delim = '\n');

QuantLib::Matrix loadCovarianceMatrix(const std::string& inputFileName, const char delim = '\n');

//! Ordered SIMM versions
enum class SimmVersion { V1_0, V1_1, V1_2, V1_3, V1_3_38, V2_0, V2_1, V2_2, V2_3, V2_3_8, V2_5, V2_5A, V2_6, V2_6_5, V2_7_2412 };

SimmVersion parseSimmVersion(const std::string& version);

QuantLib::ext::shared_ptr<SimmConfiguration>
buildSimmConfiguration(const std::string& simmVersion, const QuantLib::ext::shared_ptr<SimmBucketMapper>& simmBucketMapper,
                       const QuantLib::ext::shared_ptr<SimmCalibrationData>& simmCalibrationData = nullptr,
                       const QuantExt::Size& mporDays = 10);

//! If the input *str* is a comma seperated list the method quotation marks " if the csvQuoteChar is '\0'
//! Example:
//!  commaSeparatedListToJsonArrayString("item1,item2", '') -> "item1, item2" 
//!  commaSeparatedListToJsonArrayString("item", '') -> "item" 
std::string escapeCommaSeparatedList(const std::string& str, const char& csvQuoteChar);

  //! true if ccy is not a simm standard ccy
bool isSimmNonStandardCurrency(const std::string& ccy);

//! true if ccy is a simm non-standard "unidade" ccy
bool isUnidadeCurrency(const std::string& ccy);

bool isIsin(const string& s);

//! return simm standard ccy corresponding to ccy (or ccy itself if this is a standard ccy)
std::string simmStandardCurrency(const std::string& ccy);

//! update given npv and ccy to standard ccy using market's fx rate
void convertToSimmStandardCurrency(double& npv, std::string& ccy, const QuantLib::ext::shared_ptr<ore::data::Market> market);

//! update given ccy to standard ccy
void convertToSimmStandardCurrency(std::string& ccy);

//! update given ccy pair to standard ccys, returns true if resulting pair contains different ccys
bool convertToSimmStandardCurrencyPair(std::string& ccy);

CrifRecord::ProductClass simmProductClassFromOreTrade(const QuantLib::ext::shared_ptr<ore::data::Trade>& trade);
CrifRecord::ProductClass scheduleProductClassFromOreTrade(const QuantLib::ext::shared_ptr<ore::data::Trade>& trade);
  
} // namespace analytics
} // namespace ore
