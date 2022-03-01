doxygen = find_program('doxygen', required : true)
if not doxygen.found()
	error('Program "doxygen" not found or not executable. Try building with -Denable_build_doc=false')
endif
dot = find_program('dot', required : true)
if not dot.found()
	error('Program "dot" not found or not executable. Try building with -Denable_build_doc=false')
endif

docdir = join_paths(meson.current_source_dir(), 'doc')

src_path = join_paths(meson.source_root(), 'src')

doc_config = configuration_data()
#doc_config.set('PROJECT_DESCRIPTION', meson.project_description())
doc_config.set('PROJECT_NAME', meson.project_name())
doc_config.set('PROJECT_NUMBER', meson.project_version())
doc_config.set('DOXYGEN_INPUT', src_path)
doc_config.set('DOXYGEN_OUTPUT', meson.current_build_dir())

doxyfile = configure_file(input : 'Doxyfile.in',
			output : 'Doxyfile',
			configuration : doc_config,
			install : false)

custom_target('doxygen',
		built_by_default : true,
		input : doxyfile,
		command : [ doxygen, doxyfile ],
		output : [ 'html' ])
