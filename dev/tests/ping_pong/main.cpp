#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ping_pong/agents.hpp>

#include <so_5/experimental/testing.hpp>

namespace tests = so_5::experimental::testing;

TEST_CASE( "ping_pong" )
{
	tests::testing_env_t sobj;

	pinger_t * pinger{};
	ponger_t * ponger{};
	sobj.environment().introduce_coop([&](so_5::coop_t & coop) {
		pinger = coop.make_agent< pinger_t >();
		ponger = coop.make_agent< ponger_t >();

		pinger->set_target( ponger->so_direct_mbox() );
		ponger->set_target( pinger->so_direct_mbox() );
	});

	sobj.scenario().define_step("ping")
		.when(*ponger & tests::reacts_to<ping>());

	sobj.scenario().define_step("pong")
		.when(*pinger & tests::reacts_to<pong>());

	sobj.scenario().run_for(std::chrono::milliseconds(100));

	REQUIRE(tests::completed() == sobj.scenario().result());
}

