#include <ql/qldefines.hpp>
#if !defined(BOOST_ALL_NO_LIB) && defined(BOOST_MSVC)
#  include <ql/auto_link.hpp>
#endif

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

using namespace QuantLib;

int main() {
    try {
        // Option parameters
        Option::Type optionType = Option::Type::Call;
        Real underlyingPrice = 100.0;
        Real strikePrice = 95.0;
        Rate riskFreeRate = 0.05;
        Volatility volatility = 0.2;
        Date maturityDate(15, August, 2023);

        // QuantLib objects
        DayCounter dayCounter = Actual365Fixed();
        Calendar calendar = TARGET();
        Settings::instance().evaluationDate() = Date(2, August, 2023);

        // Set up the underlying Quote
        std::shared_ptr<Quote> underlyingQuote = std::make_shared<SimpleQuote>(underlyingPrice);
        Handle<Quote> underlyingHandle(underlyingQuote);

        // Set up the yield term structure (flatRate)
        Rate flatRate = 0.05;
        Handle<YieldTermStructure> riskFreeRateCurve(std::make_shared<FlatForward>(0, NullCalendar(), Handle<Quote>(std::make_shared<SimpleQuote>(flatRate)), dayCounter));

        // Set up the Black volatility term structure (flatVol)
        Volatility flatVol = 0.2;
        Handle<BlackVolTermStructure> volatilityCurve(std::make_shared<BlackConstantVol>(0, NullCalendar(), Handle<Quote>(std::make_shared<SimpleQuote>(flatVol)), dayCounter));

        // Set up the option
        std::shared_ptr<Exercise> americanExercise = std::make_shared<AmericanExercise>(Settings::instance().evaluationDate(), maturityDate);
        std::shared_ptr<StrikedTypePayoff> payoff = std::make_shared<PlainVanillaPayoff>(optionType, strikePrice);
        std::shared_ptr<BlackScholesProcess> blackScholesProcess = std::make_shared<BlackScholesProcess>(
            underlyingHandle,
            riskFreeRateCurve,
            volatilityCurve
        );

        AmericanVanillaOption americanOption(payoff, americanExercise);
        americanOption.setPricingEngine(std::make_shared<BaroneAdesiWhaleyApproximationEngine>(blackScholesProcess));

        // Calculate option metrics
        Real optionPrice = americanOption.NPV();
        Real delta = americanOption.delta();
        Real gamma = americanOption.gamma();
        Real theta = americanOption.theta();
        Real vega = americanOption.vega();
        Real rho = americanOption.rho();

        // Output the results
        std::cout << "American Option Price: " << optionPrice << std::endl;
        std::cout << "Delta: " << delta << std::endl;
        std::cout << "Gamma: " << gamma << std::endl;
        std::cout << "Theta: " << theta << std::endl;
        std::cout << "Vega: " << vega << std::endl;
        std::cout << "Rho: " << rho << std::endl;

        return 0;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
