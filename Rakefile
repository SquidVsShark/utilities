

task :ci do |t, args|

  Dir.chdir("../utilities-test/")
  sh("premake4 --file=premake.lua gmake")
  sh("make CXX=g++-5 && ./Unit")

end
