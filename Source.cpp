#include <ql/qldefines.hpp>
#if !defined(BOOST_ALL_NO_LIB) && defined(BOOST_MSVC)
#  include <ql/auto_link.hpp>
#endif

#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/math/integrals/tanhsinhintegral.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanvasicekengine.hpp>
#include <ql/pricingengines/vanilla/analytichestonengine.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/batesengine.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/integralengine.hpp>
#include <ql/pricingengines/vanilla/mcamericanengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/pricingengines/vanilla/qdfpamericanengine.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>

#include <iostream>
#include <iomanip>

#include <boost/shared_ptr.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

// Tutorial Header Files
#include "prelims.h"

using namespace QuantLib;

/*
 * ===========================================================================
 * File: Source.cpp
 * Company: Deloitte Canada
 * Author: Kenneth Zhang
 * Copyright (C) 2023 Deloitte Canada. All rights reserved.
 *
 * This file is part of a proprietary software system of Deloitte.
 * Unauthorized distribution, reproduction, or modification of this software,
 * or any portion of it, are not permitted. All information contained herein
 * is confidential and proprietary to Deloitte.
 *
 * Description: TBD
 *
 * Last Modified: August 3rd, 2023
 * ===========================================================================
 */


int main() {
	void prelims();


}