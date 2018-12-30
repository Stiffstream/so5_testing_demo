#pragma once

#include <so_5/all.hpp>

class logger_t final : public so_5::agent_t {
public :
	struct log_new_order {
		std::string m_manager;
		std::string m_id;
	};

	using so_5::agent_t::agent_t;

	void so_define_agent() override {
		so_subscribe_self().event( [](mhood_t<log_new_order> cmd) {
			std::cout << "new order: manager=" << cmd->m_manager
				<< ", id=" << cmd->m_id << std::endl;
		} );
	}
};

class manager_t final : public so_5::agent_t {
	const state_t st_free{ this, "free" };
	const state_t st_busy{ this, "busy" };

	const std::string m_name;
	const so_5::mbox_t m_logger;

public:
	struct new_order { 
		std::string m_id;
	};

	manager_t( context_t ctx, std::string name, so_5::mbox_t logger )
		:	so_5::agent_t{ std::move(ctx) }
		,	m_name{ std::move(name) }
		,	m_logger{ std::move(logger) }
	{}

	void so_define_agent() override {
		this >>= st_free;

		st_free.event( &manager_t::on_new_order );
	}

private:
	void on_new_order( mhood_t<new_order> cmd ) {
		this >>= st_busy;

		so_5::send< logger_t::log_new_order >( m_logger, m_name, cmd->m_id );
	}
};

