#pragma once

#include <so_5/all.hpp>

// Types of signals to be used.
struct ping final : so_5::signal_t {};
struct pong final : so_5::signal_t {};

// Pinger agent.
class pinger_t final : public so_5::agent_t {
	so_5::mbox_t m_target;
public :
	pinger_t( context_t ctx ) : so_5::agent_t{ std::move(ctx) } {
		so_subscribe_self().event( [this](mhood_t<pong>) {
			so_deregister_agent_coop_normally();
		} );
	}

	void set_target( const so_5::mbox_t & to ) { m_target = to; }

	void so_evt_start() override {
		so_5::send< ping >( m_target );
	}
};

// Ponger agent.
class ponger_t final : public so_5::agent_t {
	so_5::mbox_t m_target;
public :
	ponger_t( context_t ctx ) : so_5::agent_t{ std::move(ctx) } {
		so_subscribe_self().event( [this](mhood_t<ping>) {
			so_5::send< pong >( m_target );
		} );
	}

	void set_target( const so_5::mbox_t & to ) { m_target = to; }
};

