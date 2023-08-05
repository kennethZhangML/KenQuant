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
#include <ql/interestrate.hpp>

#include <iostream>
#include <iomanip>

#include <boost/shared_ptr.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

using namespace QuantLib;

void prelims() {
    // Implement Interest Rates with Compounding 
    // Initialize annual interest rate for 5%, annual for 365-day year
    // Options for compounding: Annual, Semiannual, Quarterly
    InterestRate annualRate(0.05, Actual365Fixed(), Compounded, Quarterly); // Initialize annual Rate for 5%
    // rate is Compounded using Compounding Factor
    double rate = annualRate.compoundFactor(1);

    // Compounding Factor Outputted for One Year
    std::cout << "Compound factor for one year: " << rate << std::endl;

    // Implement Zero Coupon Bond 
    // Initialize Zero Coupon Bond Specifications (Maturity, face amount, yield rate, settlement days)
    // 1. Maturity
    // 2. Face amount (amount paid to the bond holder at maturity date) 
    // 3. Bond Yield Rate (similar to interest rate)
    // 4. Number of Settlement Days (period from trade date to the settlement date)
    Date maturity(31, Dec, 2023);
    Real faceAmount = 100.0;
    Rate yield = 0.05;
    Natural settlementDays = 2;

    // Handle class is a smart pointer that provides safe access to underlying object(s)
    // The quote in our case is our underlying object, which represents the bond's yield
    Handle<Quote> yieldQuote(boost::shared_ptr<Quote>(new SimpleQuote(yield)));

    // Similarly, a Handle to the yieldTermStructure is created using the FlatForward class
    // This initialization represents a yield term structure that remains constant with time 
    // Objects/Items required at initialization:
    // settlement days, yieldQuote, and day counter (i.e., Actual 365 Fixed)
    Handle<YieldTermStructure> discountingTermStructure(
        boost::shared_ptr<YieldTermStructure>(
            new FlatForward(settlementDays, TARGET(), yieldQuote, Actual365Fixed())
        )
    );

    // ZeroCouponBond represents a bond that:
    // does not make periodic interest payments but is sold at discount from its face value
    // Initialized with: settlementDays, calendar, face amount, maturity, business day convention, redemption, and issue Date
    ZeroCouponBond zeroCouponBond(settlementDays, TARGET(), faceAmount, maturity, Following, 100.0, Date(31, Dec, 2021));

    // Use a pricing engine, which prices a bond by discounting its future cashflows by yield term structure 
    zeroCouponBond.setPricingEngine(boost::shared_ptr<PricingEngine>(
        new DiscountingBondEngine(discountingTermStructure)
    ));

    std::cout << "Zero Coupon Bond NPV: " << zeroCouponBond.NPV() << std::endl;

    // Annuities 
    //InterestRate annualRate(0.05, Actual365Fixed(), Compounded, Annual);
    double totalPV = 0;

    // For a period of 5 years, we can initiailize a discount factor 
    // and multiplicably apply it to the total present value
    // in order to get the present annuity for 5 years 
    for (int i = 0; i <= 5; ++i) {
        double discountFactor = annualRate.discountFactor(i);
        totalPV += 1 * discountFactor;
    }
    std::cout << "Present Annuity for 5 Years: " << totalPV << std::endl;

    // Create day counter for actual 365 fixed calendar 
    DayCounter dayCounter = Actual365Fixed();
    Date from(1, Jan, 2023);
    Date to(31, Dec, 2023);

    // Counting number of days from specified date to e.g., maturity date
    Real days = dayCounter.dayCount(from, to);
    std::cout << "Day count from " << from << " to " << to << ": " << days << std::endl;
}