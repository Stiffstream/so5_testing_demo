MxxRu::arch_externals :so5 do |e|
  e.url 'https://sourceforge.net/projects/sobjectizer/files/sobjectizer/SObjectizer%20Core%20v.5.5/so-5.5.24.zip'

  e.sha512 'd33b5660fb6d7b1182d68069bb86782dd7632071723762875d88dd6d67353f6913b25e0574d87e06b86f472608631f59c3e26dc9c67cda9f8223454ae758b524'

  e.map_dir 'dev/so_5' => 'dev'
  e.map_dir 'dev/timertt' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/2.2.0.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end
