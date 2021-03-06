#!/usr/bin/ruby
require 'mxx_ru/cpp'

MxxRu::Cpp::composite_target( MxxRu::BUILD_ROOT ) {

	toolset.force_cpp17
	global_include_path "."

	if 'gcc' == toolset.name
		global_linker_option '-pthread'
	end

	if 'clang' == toolset.name
		if 'mswin' != toolset.tag( 'target_os' )
			global_linker_option '-pthread'
		end
	end

	# If there is local options file then use it.
	if FileTest.exist?( "local-build.rb" )
		required_prj "local-build.rb"
	else
		default_runtime_mode( MxxRu::Cpp::RUNTIME_RELEASE )
		MxxRu::enable_show_brief

		global_obj_placement MxxRu::Cpp::PrjAwareRuntimeSubdirObjPlacement.new(
			'target', MxxRu::Cpp::PrjAwareRuntimeSubdirObjPlacement::USE_COMPILER_ID )
	end

	required_prj 'tests/manager_logger/prj_s.ut.rb'
	required_prj 'tests/ping_pong/prj_s.ut.rb'
	required_prj 'tests/dining_philosophers/prj_s.ut.rb'

	required_prj 'ping_pong/prj_s.rb'
	required_prj 'dining_philosophers/prj_s.rb'
}

