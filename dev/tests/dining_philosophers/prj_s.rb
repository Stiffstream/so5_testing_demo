require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj_s.rb'

	target '_utest.dining_philosophers_s'

	cpp_source 'main.cpp'
}

