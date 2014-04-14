git add $*
current=$(pwd)
message=$(pwd | awk 'BEGIN {FS="/"}; {print $NF}')
cd $current;
git commit -m $message
git push
