#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <manager_logger/agents.hpp>

#include <so_5/experimental/testing.hpp>

namespace tests = so_5::experimental::testing;

using namespace std::chrono_literals;

TEST_CASE( "manager_logger" )
{
	tests::testing_env_t sobj;

	logger_t * logger{};
	manager_t * manager{};
	sobj.environment().introduce_coop(
		so_5::disp::active_obj::make_dispatcher(sobj.environment()).binder(),
		[&](so_5::coop_t & coop) {
			logger = coop.make_agent< logger_t >();
			manager = coop.make_agent< manager_t >("Fred", logger->so_direct_mbox());
		});

	sobj.scenario().define_step("order_received")
		.impact<manager_t::new_order>(*manager, "000-0001/0")
		.when(*manager & tests::reacts_to<manager_t::new_order>()
				& tests::store_state_name("manager"));

	sobj.scenario().define_step("order_logged")
		.when(*logger & tests::reacts_to<logger_t::log_new_order>());

	sobj.scenario().run_for(100ms);

	REQUIRE(tests::completed() == sobj.scenario().result());

	REQUIRE("busy" == sobj.scenario().stored_state_name("order_received", "manager"));
}

