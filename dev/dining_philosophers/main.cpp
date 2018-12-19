/*
 * A simple implementation of demo of dining philosophers
 * problem. See description of this problem in Wikipedia:
 * http://en.wikipedia.org/wiki/Dining_philosophers_problem
 */

#include "agents.hpp"

void init( so_5::environment_t & env )
{
	env.introduce_coop( []( so_5::coop_t & coop ) {
		const std::size_t count = 5;

		std::vector< so_5::agent_t * > forks( count, nullptr );
		for( std::size_t i = 0; i != count; ++i )
			forks[ i ] = coop.make_agent< fork_t >();

		for( std::size_t i = 0; i != count; ++i )
			coop.make_agent< philosopher_t >(
					std::to_string( i ),
					forks[ i ]->so_direct_mbox(),
					forks[ (i + 1) % count ]->so_direct_mbox() );
	});

	std::this_thread::sleep_for( std::chrono::seconds(20) );
	env.stop();
}

int main()
{
	try
	{
		so_5::launch( init );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

