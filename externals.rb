MxxRu::arch_externals :so5 do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/sobjectizer/downloads/so-5.6.0-b1.zip'

  e.sha512 '1682d77b9aaf7ed79722639cc9ccb803ce091506cf4cdb7338e54b0982b76afe09b35d99c562ee1c4e8e01a3bba586888d4c5931882be72ac4bc31b0c0edcca3'

  e.map_dir 'dev/so_5' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/2.3.1.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end

