set title "Performance d'algorithmes de tri"
set xlabel "Taille de tableau"
set ylabel "Temps en ms"
set grid
set key outside
set xtics rotate by -90
set logscale y
plot "sort.txt" using 1:2 with lines title "A bulles", \
"sort.txt" using 1:3 with lines title "Insertion",\
"sort.txt" using 1:4 with lines title "Selection",\
"sort.txt" using 1:5 with lines title "Fusion",\
"sort.txt" using 1:6 with lines title "Rapide",\
"sort.txt" using 1:7 with lines title "Denombrement"



