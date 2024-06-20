/TEST/
/TIMEOUT/ {printf "\n%s\n", $0}
/TOTAL/ {printf "\n%s\n", $0}
/Run cpplint/ {printf "\n%s\n", $0}
/errors found/ {printf "\t%s\n", $0}
/Run clang-tidy-12/ {printf "\n%s\n", $0}
/warnings generated/ {printf "\t%s\n", $0}
