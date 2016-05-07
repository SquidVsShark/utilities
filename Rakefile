

task :ci do |t, args|

  Dir.chdir("../utilities-test/")
  sh("premake4 --file=premake.lua gmake")
  sh("make CC=g++-5 && ./Unit")

end
