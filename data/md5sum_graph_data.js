var dot = "dinetwork {node[shape=circle]; edge [color=gray]; start -> main ; start [color=#a10540] ; main [color=#813f94] ; main -> sum ; main [color=#813f94] ; sum [color=#90300a] ; sum -> md5 ; sum [color=#90300a] ; md5 [color=#055478] ; md5 -> encode ; md5 [color=#055478] ; encode [color=#5c72d0] ; md5 -> decode ; md5 [color=#055478] ; decode [color=#c86860] ; md5 -> tab ; md5 [color=#055478] ; tab [color=#3922b0] ; md5 -> nil ; md5 [color=#055478] ; nil [color=#516430] ; md5 -> calloc ; md5 [color=#055478] ; calloc [color=#658b20] ; md5 -> free ; md5 [color=#055478] ; free [color=#48ce28] ; md5 -> memset ; md5 [color=#055478] ; memset [color=#c70608] ; sum -> enc64 ; sum [color=#90300a] ; enc64 [color=#d89420] ; enc64 -> init64 ; enc64 [color=#d89420] ; init64 [color=#a71180] ; init64 -> t64d ; init64 [color=#a71180] ; t64d [color=#8d9d00] ; init64 -> t64e ; init64 [color=#a71180] ; t64e [color=#942640] ; init64 -> memset ; init64 [color=#a71180] ; memset [color=#c70608] ; enc64 -> t64e ; enc64 [color=#d89420] ; t64e [color=#942640] ; sum -> hex ; sum [color=#90300a] ; hex [color=#65cc80] ; sum -> nil ; sum [color=#90300a] ; nil [color=#516430] ; sum -> calloc ; sum [color=#90300a] ; calloc [color=#658b20] ; sum -> free ; sum [color=#90300a] ; free [color=#48ce28] ; sum -> printf ; sum [color=#90300a] ; printf [color=#d38400] ; sum -> fread ; sum [color=#90300a] ; fread [color=#b30b20] ; main -> hex ; main [color=#813f94] ; hex [color=#65cc80] ; main -> debug ; main [color=#813f94] ; debug [color=#470910] ; main -> strcmp ; main [color=#813f94] ; strcmp [color=#a38900] ; main -> fopen ; main [color=#813f94] ; fopen [color=#42c380] ; main -> fclose ; main [color=#813f94] ; fclose [color=#b06550] ; main -> fprintf ; main [color=#813f94] ; fprintf [color=#469800] ; main -> stdin ; main [color=#813f94] ; stdin [color=#74cdc0] ; main -> stderr ; main [color=#813f94] ; stderr [color=#44c680] ; }";