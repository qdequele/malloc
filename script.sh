#!/bin/sh

git filter-branch --env-filter '
OLD_EMAIL="qdequele@*.42.fr"
CORRECT_NAME="qdequele"
CORRECT_EMAIL="quentin@dequelen.me"
if [[ "$GIT_COMMITTER_EMAIL" = $OLD_EMAIL ]]
then
    export GIT_COMMITTER_NAME="$CORRECT_NAME"
    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [[ "$GIT_AUTHOR_EMAIL" = $OLD_EMAIL ]]
then
    export GIT_AUTHOR_NAME="$CORRECT_NAME"
    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' -f --tag-name-filter cat -- --branches --tags
