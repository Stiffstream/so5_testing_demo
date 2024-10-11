MxxRu::arch_externals :so5 do |e|
  e.url 'https://github.com/Stiffstream/sobjectizer/archive/7eeb29c560342ecaa814026d42a149bca58692ea.tar.gz'

  e.map_dir 'dev/so_5' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/v2.4.11.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end

