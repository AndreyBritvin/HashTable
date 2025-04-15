
install perf:
`sudo apt install linux-perf`
install hotspot (to graph your profile data)
`sudo apt install hotspot`
then profile your program:
`perf record --call-graph dwarf -F 99 PROGR`
And to see graph call:
`hotspot ./perf.data`
