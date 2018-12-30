require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj_s.rb'

	target '_utest.manager_logger_s'

	cpp_source 'main.cpp'
}

