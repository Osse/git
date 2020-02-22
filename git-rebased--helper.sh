#!/usr/bin/zsh

[[ $XPLEASE ]] && set -x

current=${1#refs/heads/}
upstream=$(git rev-parse $current'@{u}')

reflog=$(git log -g --format=%gs --grep-reflog='rebase finished:' $current)


if [[ -n $reflog  ]]; then
	new_base=${reflog##* }
else
	exit 0;
fi

msg=$(git log -1 $upstream --format=%s)

c=$(git rev-list --count -F --grep="$msg" $new_base..$current)

if (( c )); then
    exit 1;
fi

count() {
	git rev-list --count $1..$2
}

n1=$(count $current $upstream)
n2=$(count $new_base $current)

(( n1 == n2 )) || exit 2

p() {
	git log -p $1..$2 | git patch-id | cut -f 1 -d ' '
}

# diff =(p $current $upstream) =(p $new_base $current) | diffstat -t | { read junk; IFS=, read ins del junk }

((ins == del)) || exit 2

(( (ins + 1.0)/n1 < 0.025 ))

exit $?
