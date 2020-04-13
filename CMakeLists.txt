cmake_minimum_required(VERSION 3.15)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab4 main.cpp Interpreter1.cpp Interpreter1.h Datalogprogram.h Datalogprogram.cpp Database.h Database.cpp Param.h Param.cpp
        Parser.cpp Parser.h Predicate.h Predicate.cpp Relation.cpp Relation.h Rule.h Rule.cpp Scanner1.h Scanner1.cpp Scheme.h Scheme.cpp
        Token1.h Token1.cpp Tuple.h Tuple.cpp Graph.cpp Graph.h Node.cpp Node.h)