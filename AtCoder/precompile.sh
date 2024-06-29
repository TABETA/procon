baseDir="/usr/include/x86_64-linux-gnu/c++/11/bits"
pchDir="stdc++.h.gch"
sudo g++ -g3 -O0 -std=c++2b -D_DEBUG $baseDir/stdc++.h -o $baseDir/$pchDir/stdc++_debug.gch
sudo g++ -O3 -std=c++2b $baseDir/stdc++.h -o $baseDir/$pchDir/stdc++_release.gch
