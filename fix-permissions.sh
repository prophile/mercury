#!/bin/bash
find . -type d | grep -v "\\.git" | xargs chmod 777
find . -type f | grep -v "\\.git" | xargs chmod 666
