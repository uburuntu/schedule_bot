#!/bin/bash

time cppcheck --enable=warning,style,performance,portability,unusedFunction \
              --inconclusive                                                \
              --force --max-configs=200                                     \
              .                                                             \
              -I ./src/include -I ./config                                  \
              -i ./build
