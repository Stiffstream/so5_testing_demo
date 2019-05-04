/*
 * A simple implementation of demo of dining philosophers
 * problem. See description of this problem in Wikipedia:
 * http://en.wikipedia.org/wiki/Dining_philosophers_problem
 */

#pragma once

#include <so_5/all.hpp>

#include <random>

struct msg_take
{
	const so_5::mbox_t m_who;
};

struct msg_busy : public so_5::signal_t {};

struct msg_taken : public so_5::signal_t {};

struct msg_put : public so_5::signal_t {};

class fork_t final : public so_5::agent_t
{
public :
	fork_t( context_t ctx ) : so_5::agent_t( ctx )
   {
		this >>= st_free;

		st_free.event( [this]( const msg_take & evt )
				{
					this >>= st_taken;
					so_5::send< msg_taken >( evt.m_who );
				} );

		st_taken.event( []( const msg_take & evt )
				{
					so_5::send< msg_busy >( evt.m_who );
				} )
			.just_switch_to< msg_put >( st_free );
	}

private :
	state_t st_free{ this, "free" };
	state_t st_taken{ this, "taken" };
};

class philosopher_t final : public so_5::agent_t
{
public :
	struct msg_stop_thinking : public so_5::signal_t {};
	struct msg_stop_eating : public so_5::signal_t {};

	philosopher_t(
		context_t ctx,
		std::string name,
		so_5::mbox_t left_fork,
		so_5::mbox_t right_fork )
		:	so_5::agent_t( ctx )
		,	m_name( std::move( name ) )
		,	m_left_fork( std::move( left_fork ) )
		,	m_right_fork( std::move( right_fork ) )
	{}

	void so_define_agent() override
	{
		st_thinking.event( [=](mhood_t< msg_stop_thinking >) {
				show_msg( "become hungry, try to take left fork" );
				this >>= st_wait_left;
				so_5::send< msg_take >( m_left_fork, so_direct_mbox() );
			} );

		st_wait_left.event( [=](mhood_t< msg_taken >) {
				show_msg( "left fork taken, try to take right fork" );
				this >>= st_wait_right;
				so_5::send< msg_take >( m_right_fork, so_direct_mbox() );
			} )
			.event( [=](mhood_t< msg_busy >) {
				show_msg( "left fork is busy, return to thinking" );
				think();
			} );

		st_wait_right.event( [=](mhood_t< msg_taken >) {
				show_msg( "right fork taken, start eating" );
				this >>= st_eating;
				so_5::send_delayed< msg_stop_eating >( *this, pause() );
			} )
			.event( [=](mhood_t< msg_busy >) {
				show_msg( "right fork is busy, put left fork, return to thinking" );
				so_5::send< msg_put >( m_left_fork );
				think();
			} );

		st_eating.event( [=](mhood_t< msg_stop_eating >) {
				show_msg( "stop eating, put forks, return to thinking" );
				so_5::send< msg_put >( m_right_fork );
				so_5::send< msg_put >( m_left_fork );
				think();
			} );
	}

	void so_evt_start() override
	{
		think();
	}

private :
	const state_t st_thinking{ this, "thinking" };
	const state_t st_wait_left{ this, "wait_left" };
	const state_t st_wait_right{ this, "wait_right" };
	const state_t st_eating{ this, "eating" };

	const std::string m_name;

	const so_5::mbox_t m_left_fork;
	const so_5::mbox_t m_right_fork;

	void show_msg( const std::string & msg ) const
	{
		std::cout << "[" << m_name << "] " << msg << std::endl;
	}

	void think()
	{
		this >>= st_thinking;
		so_5::send_delayed< msg_stop_thinking >( *this, pause() );
	}

	// Helper function to generate a random integer in the specified range.
	static unsigned int random_value( unsigned int left, unsigned int right )
	{
		std::random_device rd;
		std::mt19937 gen{ rd() };
		return std::uniform_int_distribution< unsigned int >{left, right}(gen);
	}

	static std::chrono::milliseconds pause()
	{
		return std::chrono::milliseconds( 250 + random_value( 0, 250 ) );
	}
};

