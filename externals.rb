MxxRu::arch_externals :so5 do |e|
  e.url 'https://github.com/Stiffstream/sobjectizer/releases/download/v.5.6.1/so-5.6.1.zip'

  e.sha512 '7c679472adec8023d693b014802c176390e294b1ea61a7ebece9d2007937dba04b6c422eded25c4d82f3011bef726d350a942ba78763e0b89ae857feb891b824'

  e.map_dir 'dev/so_5' => 'dev'
end

MxxRu::arch_externals :doctest do |e|
  e.url 'https://github.com/onqtam/doctest/archive/2.3.1.tar.gz'

  e.map_file 'doctest/doctest.h' => 'dev/doctest/*'
end

