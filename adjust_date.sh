#!/bin/bash
export PATH="$PWD:$PATH"

git filter-branch -f --env-filter '

if [ "$GIT_COMMIT" != "1123dc9362b4512437dce0d7864df6b697b15527" ]; then
    GIT_AUTHOR_DATE=`adjust_date.py --date $GIT_AUTHOR_DATE`
    export GIT_AUTHOR_DATE
fi
'

