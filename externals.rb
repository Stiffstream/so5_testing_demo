MxxRu::arch_externals :so5 do |e|
  e.url 'https://github.com/Stiffstream/sobjectizer/releases/download/v.5.7.2/so-5.7.2.zip'

  e.map_dir 'dev/so_5' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/2.4.1.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end

