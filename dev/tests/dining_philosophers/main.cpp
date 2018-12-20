#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <dining_philosophers/agents.hpp>

#include <so_5/experimental/testing.hpp>

namespace tests = so_5::experimental::testing::v1;

TEST_CASE( "fork" )
{
	class pseudo_philosopher_t final : public so_5::agent_t {
	public:
		pseudo_philosopher_t(context_t ctx) : so_5::agent_t{std::move(ctx)} {
			so_subscribe_self()
				.event([](mhood_t<msg_taken>) {})
				.event([](mhood_t<msg_busy>) {});
		}
	};

	tests::testing_env_t sobj;

	so_5::agent_t * fork{};
	so_5::agent_t * philosopher{};
	sobj.environment().introduce_coop([&](so_5::coop_t & coop) {
		fork = coop.make_agent<fork_t>();
		philosopher = coop.make_agent<pseudo_philosopher_t>();
	});

	sobj.scenario().define_step("put_when_free")
		.impact<msg_put>(*fork)
		.when(*fork & tests::ignores<msg_put>());

	sobj.scenario().define_step("take_when_free")
		.impact<msg_take>(*fork, philosopher->so_direct_mbox())
		.when_all(
			*fork & tests::reacts_to<msg_take>() & tests::store_state_name("fork"),
			*philosopher & tests::reacts_to<msg_taken>());

	sobj.scenario().define_step("take_when_taken")
		.impact<msg_take>(*fork, philosopher->so_direct_mbox())
		.when_all(
			*fork & tests::reacts_to<msg_take>(),
			*philosopher & tests::reacts_to<msg_busy>());

	sobj.scenario().define_step("put_when_taken")
		.impact<msg_put>(*fork)
		.when(
			*fork & tests::reacts_to<msg_put>() & tests::store_state_name("fork"));

	sobj.scenario().run_for(std::chrono::milliseconds(100));

	REQUIRE(tests::completed() == sobj.scenario().result());

	REQUIRE("taken" == sobj.scenario().stored_state_name("take_when_free", "fork"));
	REQUIRE("free" == sobj.scenario().stored_state_name("put_when_taken", "fork"));

}

TEST_CASE( "philosopher (takes both forks)" )
{
	tests::testing_env_t sobj{
		[](so_5::environment_params_t & params) {
			params.message_delivery_tracer(
					so_5::msg_tracing::std_cout_tracer());
		}
	};

	so_5::agent_t * philosopher{};
	so_5::agent_t * left_fork{};
	so_5::agent_t * right_fork{};

	sobj.environment().introduce_coop([&](so_5::coop_t & coop) {
		left_fork = coop.make_agent<fork_t>();
		right_fork = coop.make_agent<fork_t>();
		philosopher = coop.make_agent<philosopher_t>(
			"philosopher",
			left_fork->so_direct_mbox(),
			right_fork->so_direct_mbox());
	});

	auto & scenario = sobj.scenario();

	scenario.define_step("stop_thinking")
		.when( *philosopher
				& tests::reacts_to<philosopher_t::msg_stop_thinking>()
				& tests::store_state_name("philosopher") )
		.constraints( tests::not_before(std::chrono::milliseconds(250)) );

	scenario.define_step("take_left")
		.when( *left_fork & tests::reacts_to<msg_take>() );

	scenario.define_step("left_taken")
		.when( *philosopher
				& tests::reacts_to<msg_taken>()
				& tests::store_state_name("philosopher") );

	scenario.define_step("take_right")
		.when( *right_fork & tests::reacts_to<msg_take>() );

	scenario.define_step("right_taken")
		.when( *philosopher
				& tests::reacts_to<msg_taken>()
				& tests::store_state_name("philosopher") );

	scenario.define_step("stop_eating")
		.when( *philosopher
				& tests::reacts_to<philosopher_t::msg_stop_eating>()
				& tests::store_state_name("philosopher") )
		.constraints( tests::not_before(std::chrono::milliseconds(250)) );

	scenario.define_step("return_forks")
		.when_all( 
				*left_fork & tests::reacts_to<msg_put>(),
				*right_fork & tests::reacts_to<msg_put>() );

	scenario.run_for(std::chrono::seconds(1));

	REQUIRE(tests::completed() == scenario.result());

	REQUIRE("wait_left" == scenario.stored_state_name("stop_thinking", "philosopher"));
	REQUIRE("wait_right" == scenario.stored_state_name("left_taken", "philosopher"));
	REQUIRE("eating" == scenario.stored_state_name("right_taken", "philosopher"));
	REQUIRE("thinking" == scenario.stored_state_name("stop_eating", "philosopher"));
}

