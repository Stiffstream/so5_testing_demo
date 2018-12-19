MxxRu::svn_externals :so5 do |e|
  e.url 'https://svn.code.sf.net/p/sobjectizer/repo/branches/so_5/5.5.24--event-queue-hook'
  e.rev 3636
  e.option '--ignore-externals'

  e.map_dir 'dev/so_5' => 'dev'
end

MxxRu::svn_externals :timertt do |e|
  e.url 'https://svn.code.sf.net/p/sobjectizer/repo/tags/timertt/1.2.2'

  e.map_dir 'dev/timertt' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/2.2.0.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end
