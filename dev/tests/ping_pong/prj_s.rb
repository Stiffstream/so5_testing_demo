require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj_s.rb'

	target '_utest.ping_pong_s'

	cpp_source 'main.cpp'
}

