#include "agents.hpp"

int main() {
	so_5::launch( [](so_5::environment_t & env) {
		env.introduce_coop([&](so_5::coop_t & coop) {
			auto pinger = coop.make_agent< pinger_t >();
			auto ponger = coop.make_agent< ponger_t >();

			pinger->set_target( ponger->so_direct_mbox() );
			ponger->set_target( pinger->so_direct_mbox() );
		});
	} );
}

