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
		.impact([fork]{ so_5::send<msg_put>(*fork); })
		.when(*fork & tests::ignores<msg_put>());

	sobj.scenario().define_step("take_when_free")
		.impact([fork, philosopher]{
				so_5::send<msg_take>(*fork, philosopher->so_direct_mbox());
			})
		.when_all(
			*fork & tests::reacts_to<msg_take>() & tests::store_state_name("fork"),
			*philosopher & tests::reacts_to<msg_taken>());

	sobj.scenario().define_step("take_when_taken")
		.impact([fork, philosopher]{
				so_5::send<msg_take>(*fork, philosopher->so_direct_mbox());
			})
		.when_all(
			*fork & tests::reacts_to<msg_take>(),
			*philosopher & tests::reacts_to<msg_busy>());

	sobj.scenario().define_step("put_when_taken")
		.impact([fork]{ so_5::send<msg_put>(*fork); })
		.when(
			*fork & tests::reacts_to<msg_put>() & tests::store_state_name("fork"));

	sobj.scenario().run_for(std::chrono::milliseconds(100));

	REQUIRE(sobj.scenario().completed());

	REQUIRE("taken" == sobj.scenario().stored_state_name("take_when_free", "fork"));
	REQUIRE("free" == sobj.scenario().stored_state_name("put_when_taken", "fork"));

}

