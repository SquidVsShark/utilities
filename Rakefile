

task :ci do |t, args|

  sh("premake4 --help")
  Dir.chdir("../utilities-test/")
  sh("premake4 --file=premake.lua gmake")
  sh("make && ./Unit")

end
