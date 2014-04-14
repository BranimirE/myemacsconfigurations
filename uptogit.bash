git add $*
message=$(pwd | awk 'BEGIN {FS="/"}; {print $NF}')
git commit -m $message
git push
