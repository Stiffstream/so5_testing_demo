#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <manager_logger/agents.hpp>

#include <so_5/experimental/testing.hpp>

namespace tests = so_5::experimental::testing;

using namespace std::chrono_literals;

TEST_CASE( "just-reacts_to" )
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

TEST_CASE( "reacts_to-plus-inspect_msg" )
{
	tests::testing_env_t sobj;

	const std::string manager_name{ "Chris" };
	const std::string order_id{ "2024-10-11-0001" };

	logger_t * logger{};
	manager_t * manager{};
	sobj.environment().introduce_coop(
		so_5::disp::active_obj::make_dispatcher(sobj.environment()).binder(),
		[&](so_5::coop_t & coop) {
			logger = coop.make_agent< logger_t >();
			manager = coop.make_agent< manager_t >(manager_name, logger->so_direct_mbox());
		});

	sobj.scenario().define_step("order_received")
		.impact<manager_t::new_order>(*manager, order_id)
		.when(*manager
				& tests::reacts_to<manager_t::new_order>()
				& tests::store_state_name("manager"));

	sobj.scenario().define_step("order_logged")
		.when(*logger
				& tests::reacts_to<logger_t::log_new_order>()
				& tests::inspect_msg("log_new_order",
					[&](const logger_t::log_new_order & msg) -> std::string {
						if(msg.m_manager != manager_name)
							return "manager_name mismatch, actual_value: " + msg.m_manager;
						if(msg.m_id != order_id)
							return "id mismatch, actual_value: " + msg.m_id;
						return "OK";
					})
		);

	sobj.scenario().run_for(100ms);

	REQUIRE(tests::completed() == sobj.scenario().result());

	REQUIRE("busy" == sobj.scenario().stored_state_name("order_received", "manager"));
	REQUIRE("OK" == sobj.scenario().stored_msg_inspection_result(
			"order_logged", "log_new_order"));
}

TEST_CASE( "receives-plus-inspect_msg" )
{
	tests::testing_env_t sobj;

	const std::string manager_name{ "Chris" };
	const std::string order_id{ "2024-10-11-0001" };

	const auto logger_mbox = sobj.environment().create_mbox();

	manager_t * manager{};
	sobj.environment().introduce_coop(
		so_5::disp::active_obj::make_dispatcher(sobj.environment()).binder(),
		[&](so_5::coop_t & coop) {
			// No acual logger agent in the cooperation!
			manager = coop.make_agent< manager_t >(manager_name, logger_mbox);
		});

	sobj.scenario().define_step("order_received")
		.impact<manager_t::new_order>(*manager, order_id)
		.when(*manager
				& tests::reacts_to<manager_t::new_order>()
				& tests::store_state_name("manager"));

	sobj.scenario().define_step("log_new_order_sent")
		.when(logger_mbox
				& tests::receives<logger_t::log_new_order>()
				& tests::inspect_msg("log_new_order",
					[&](const logger_t::log_new_order & msg) -> std::string {
						if(msg.m_manager != manager_name)
							return "manager_name mismatch, actual_value: " + msg.m_manager;
						if(msg.m_id != order_id)
							return "id mismatch, actual_value: " + msg.m_id;
						return "OK";
					})
		);

	sobj.scenario().run_for(100ms);

	REQUIRE(tests::completed() == sobj.scenario().result());

	REQUIRE("busy" == sobj.scenario().stored_state_name("order_received", "manager"));
	REQUIRE("OK" == sobj.scenario().stored_msg_inspection_result(
			"log_new_order_sent", "log_new_order"));
}

