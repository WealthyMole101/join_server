#!/bin/bash

echo TRUNCATE A | nc localhost 9000
echo TRUNCATE B | nc localhost 9000
echo INSERT A 0 lean | nc localhost 9000
echo INSERT A 1 sweater | nc localhost 9000
echo INSERT A 2 frank | nc localhost 9000
echo INSERT A 3 violation | nc localhost 9000
echo INSERT A 4 quality | nc localhost 9000
echo INSERT A 5 precision | nc localhost 9000
echo INSERT B 3 proposal | nc localhost 9000
echo INSERT B 4 example | nc localhost 9000
echo INSERT B 5 lake | nc localhost 9000
echo INSERT B 6 flour | nc localhost 9000
echo INSERT B 7 wonder | nc localhost 9000
echo INSERT B 8 selection | nc localhost 9000
echo INTERSECTION | nc localhost 9000
echo SYMMETRIC_DIFFERENCE | nc localhost 9000


