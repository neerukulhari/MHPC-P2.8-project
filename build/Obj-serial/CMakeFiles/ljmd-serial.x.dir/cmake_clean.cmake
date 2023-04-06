file(REMOVE_RECURSE
  "../ljmd-serial.x"
  "../ljmd-serial.x.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/ljmd-serial.x.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
