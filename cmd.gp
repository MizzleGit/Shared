set title "Sorting Algorithms Performance"\
set xlabel "Input Size (A_size)"\
set ylabel "Time (ms)"\
set grid\
set key outside

set logscale y
plot "sort.txt" using 1:2 with lines title "Bubble", "sort.txt" using 1:3 with lines title "Insertion", "sort.txt" using 1:4 with lines title "Selection","sort.txt" using 1:5 with lines title "Merge", "sort.txt" using 1:6 with lines title "Quick", "sort.txt" using 1:7 with lines title "Counting"
